#include "LogicalPlanBuilder.h"
#include "ASTNodes.h"
#include "LogicalPlanNodes.h"
#include "LogicalPlanPrinter.h"
#include <iostream>

// ========== LogicalPlanBuilder Implementation ==========

std::unique_ptr<LogicalPlanNode> LogicalPlanBuilder::build(QueryNode* astRoot) {
    currentPlan = nullptr;
    
    // Visit AST root - this will build the logical plan
    astRoot->accept(this);
    
    return std::move(currentPlan);
}

void LogicalPlanBuilder::visitQuery(QueryNode* n) {
    // Process all children (statements) sequentially
    // This allows MATCH followed by SET/DELETE/etc.
    for (auto& child : n->children) {
        child->accept(this);
    }
}

void LogicalPlanBuilder::visitInsertStatement(InsertStatementNode* n) {
    auto insertOp = std::make_unique<InsertOpNode>();
    
    // Save current plan (e.g. from MATCH) as it is the data stream for INSERT
    if (currentPlan) {
        insertOp->children.push_back(std::move(currentPlan));
    }
    
    // Build patterns to insert
    for (auto& pattern : n->insertPatterns) {
        pattern->accept(this); // This creates a Scan node in currentPlan
        if (currentPlan) {
            insertOp->patterns.push_back(std::move(currentPlan));
        }
    }
    
    currentPlan = std::move(insertOp);
}

void LogicalPlanBuilder::visitSetStatement(SetStatementNode* n) {
    auto updateOp = std::make_unique<UpdateOpNode>();
    
    for (auto& item : n->items) {
        UpdateOpNode::UpdateItem updateItem;
        updateItem.variable = item.variable;
        updateItem.key = (item.type == "LABEL") ? item.labelName : item.propertyName;
        
        if (item.type == "PROPERTY") updateItem.type = UpdateOpNode::SET_PROPERTY;
        else if (item.type == "LABEL") updateItem.type = UpdateOpNode::SET_LABEL;
        else if (item.type == "MAP")   updateItem.type = UpdateOpNode::SET_MAP;
        
        if (item.valueExpression) {
            updateItem.value = buildExpression(item.valueExpression.get());
        }
        
        updateOp->items.push_back(std::move(updateItem));
    }
    
    if (currentPlan) {
        updateOp->children.push_back(std::move(currentPlan));
    }
    currentPlan = std::move(updateOp);
}

void LogicalPlanBuilder::visitRemoveStatement(RemoveStatementNode* n) {
    auto updateOp = std::make_unique<UpdateOpNode>();
    
    for (auto& item : n->items) {
        UpdateOpNode::UpdateItem updateItem;
        updateItem.variable = item.variable;
        updateItem.key = (item.type == "LABEL") ? item.labelName : item.propertyName;
        
        if (item.type == "PROPERTY") updateItem.type = UpdateOpNode::REMOVE_PROPERTY;
        else if (item.type == "LABEL") updateItem.type = UpdateOpNode::REMOVE_LABEL;
        
        updateOp->items.push_back(std::move(updateItem));
    }
    
    if (currentPlan) {
        updateOp->children.push_back(std::move(currentPlan));
    }
    currentPlan = std::move(updateOp);
}

void LogicalPlanBuilder::visitDeleteStatement(DeleteStatementNode* n) {
    auto deleteOp = std::make_unique<DeleteOpNode>();
    deleteOp->detach = n->detach;
    
    for (auto& expr : n->expressions) {
        if (expr->type == ASTNode::EXPRESSION) {
            ExpressionNode* exprNode = static_cast<ExpressionNode*>(expr.get());
            deleteOp->variables.push_back(exprNode->value);
        }
    }
    
    if (currentPlan) {
        deleteOp->children.push_back(std::move(currentPlan));
    }
    currentPlan = std::move(deleteOp);
}

void LogicalPlanBuilder::visitMatchStatement(MatchStatementNode* n) {
    /**
     * Convert MATCH statement to Logical Plan:
     * 
     * MATCH (p:Person) WHERE p.age > 30 RETURN p.name
     * 
     * Logical Plan structure (bottom-up):
     *   1. NodeScan(Person) - scan nodes
     *   2. Filter(age > 30) - filter rows
     *   3. Project(name) - select fields
     */
    
    std::unique_ptr<LogicalPlanNode> plan;
    
    // Step 1: Build scan operations from patterns
    // We need to process ALL patterns and join them
    for (auto& pattern : n->patterns) {
        // Visit the pattern to create its scan node
        // This will set 'currentPlan' to the new scan node
        pattern->accept(this);
        auto newScan = std::move(currentPlan);
        
        if (!plan) {
            // First pattern - just set it as the base
            plan = std::move(newScan);
        } else {
            // Subsequent patterns - join with existing plan
            auto join = std::make_unique<JoinNode>();
            join->joinType = "INNER"; // Default to inner join
            // In a real implementation, we would set join condition here
            
            join->children.push_back(std::move(plan));
            join->children.push_back(std::move(newScan));
            
            plan = std::move(join);
        }
    }
    
    // Step 2: Add Filter if WHERE clause exists
    if (n->whereClause) {
        WhereClauseNode* whereNode = static_cast<WhereClauseNode*>(n->whereClause.get());
        if (whereNode->condition) {
            auto filter = std::make_unique<FilterNode>();
            filter->condition = buildExpression(whereNode->condition.get());
            
            // Attach filter on top of scan/join tree
            if (plan) {
                filter->children.push_back(std::move(plan));
            }
            plan = std::move(filter);
        }
    }
    
    // Step 3: Add Aggregate/Project if RETURN exists
    if (n->returnStatement) {
        ReturnStatementNode* ret = static_cast<ReturnStatementNode*>(n->returnStatement.get());
        
        if (containsAggregations(ret->expressions)) {
            // Aggregation case: divide into grouping and aggregates
            auto aggregate = std::make_unique<AggregateNode>();
            
            for (auto& expr : ret->expressions) {
                if (expr->type == ASTNode::EXPRESSION) {
                    ExpressionNode* exprNode = static_cast<ExpressionNode*>(expr.get());
                    if (isAggregateExpression(exprNode)) {
                        AggregateNode::AggregateItem aggItem;
                        aggItem.functionName = exprNode->value;
                        aggItem.distinct = (exprNode->operator_ == "DISTINCT");
                        if (!exprNode->arguments.empty()) {
                            aggItem.expression = buildExpression(exprNode->arguments[0].get());
                        }
                        aggregate->aggregateItems.push_back(std::move(aggItem));
                    } else {
                        // Grouping item
                        aggregate->groupingExpressions.push_back(buildExpression(exprNode));
                        aggregate->groupingAliases.push_back(exprNode->value);
                    }
                }
            }
            
            if (plan) {
                aggregate->children.push_back(std::move(plan));
            }
            plan = std::move(aggregate);
        } else {
            // No aggregations, traditional Project logic
            auto project = std::make_unique<ProjectNode>();
            
            for (auto& expr : ret->expressions) {
                if (expr->type == ASTNode::EXPRESSION) {
                    ExpressionNode* exprNode = static_cast<ExpressionNode*>(expr.get());
                    
                    std::string field = exprNode->value;
                    size_t dotPos = field.find('.');
                    if (dotPos != std::string::npos) {
                        field = field.substr(dotPos + 1);
                    }
                    project->fields.push_back(field);
                    
                    // Also build the expression node
                    project->expressions.push_back(buildExpression(exprNode));
                }
            }
            
            if (plan) {
                project->children.push_back(std::move(plan));
            }
            plan = std::move(project);
        }
    }
    
    // Set as current plan
    currentPlan = std::move(plan);
}

void LogicalPlanBuilder::visitNodePattern(NodePatternNode* n) {
    /**
     * Convert NodePattern → NodeScan
     * Example: (p:Person) → NodeScan(Person)
     */
    auto nodeScan = std::make_unique<NodeScanNode>();
    
    nodeScan->variable = n->variable;
    
    // Extract label (first label for now)
    if (!n->labels.empty()) {
        nodeScan->label = n->labels[0];
    }
    
    // Copy properties (for filtering)
    nodeScan->properties = n->properties;
    
    currentPlan = std::move(nodeScan);
}

void LogicalPlanBuilder::visitEdgePattern(EdgePatternNode* n) {
    /**
     * Convert EdgePattern → EdgeScan
     * Example: -[r:ACTED_IN]-> → EdgeScan(ACTED_IN)
     */
    auto edgeScan = std::make_unique<EdgeScanNode>();
    
    edgeScan->variable = n->variable;
    edgeScan->direction = n->direction;
    
    // Extract label (first label for now)
    if (!n->labels.empty()) {
        edgeScan->label = n->labels[0];
    }
    
    // Copy properties
    edgeScan->properties = n->properties;
    
    currentPlan = std::move(edgeScan);
}

// visitWhereClause is now handled directly in visitMatchStatement via buildExpression
void LogicalPlanBuilder::visitWhereClause(WhereClauseNode* n) {
    // No-op
}

void LogicalPlanBuilder::visitReturnStatement(ReturnStatementNode* n) {
    // No-op: handled in visitMatchStatement
}

void LogicalPlanBuilder::visitExpression(ExpressionNode* n) {
    // No-op: handled via buildExpression helper
}

// Helper to convert AST Expression to Logical Expression
std::unique_ptr<LogicalPlanNode> LogicalPlanBuilder::buildExpression(ASTNode* node) {
    if (!node) return nullptr;
    
    if (node->type != ASTNode::EXPRESSION) {
        return nullptr;
    }
    
    ExpressionNode* expr = static_cast<ExpressionNode*>(node);
    
    if (expr->type == "BINARY_OP") {
        auto binOp = std::make_unique<BinaryExpressionNode>();
        binOp->op = expr->operator_;
        binOp->left = buildExpression(expr->left.get());
        binOp->right = buildExpression(expr->right.get());
        return binOp;
    } 
    else if (expr->type == "PROPERTY_ACCESS") {
        // object.propertyName
        // object should be a VARIABLE expression
        std::string varName;
        if (expr->object && expr->object->type == ASTNode::EXPRESSION) {
            ExpressionNode* obj = static_cast<ExpressionNode*>(expr->object.get());
            varName = obj->value;
        }
        return std::make_unique<PropertyAccessNode>(varName, expr->propertyName);
    }
    else if (expr->type == "VARIABLE") {
        return std::make_unique<VariableReferenceNode>(expr->value);
    }
    else if (expr->type == "LITERAL" || expr->type == "VALUE") {
        return std::make_unique<LiteralNode>(expr->value, expr->literalType);
    }
    else if (expr->type == "FUNCTION_CALL") {
        // We'll treat function calls as specific logical nodes or expressions
        // For now, let's just create a BinaryExpressionNode-like structure 
        // or just return a placeholder.
        // Actually, AggregateNode handles the function name.
        // If it's used inside buildExpression (e.g. nested), we need a node.
        // Let's reuse LiteralNode to store function name for now, 
        // or better, add a FUNCTION_CALL node if needed.
        // For simple aggregations, the AggregateNode will handle it.
        return std::make_unique<VariableReferenceNode>(expr->value + "(...)");
    }
    
    return nullptr;
}

bool LogicalPlanBuilder::isAggregateExpression(ASTNode* node) {
    if (!node || node->type != ASTNode::EXPRESSION) return false;
    ExpressionNode* expr = static_cast<ExpressionNode*>(node);
    if (expr->type == "FUNCTION_CALL") {
        std::string funcName = expr->value;
        for (auto & c: funcName) c = toupper(c);
        return (funcName == "COUNT" || funcName == "SUM" || funcName == "AVG" || 
                funcName == "MIN" || funcName == "MAX" || funcName == "COLLECT_LIST");
    }
    return false;
}

bool LogicalPlanBuilder::containsAggregations(const std::vector<std::unique_ptr<ASTNode>>& expressions) {
    for (auto& expr : expressions) {
        if (isAggregateExpression(expr.get())) return true;
    }
    return false;
}

std::vector<std::string> LogicalPlanBuilder::extractReturnFields(ReturnStatementNode* ret) {
    std::vector<std::string> fields;
    
    for (auto& expr : ret->expressions) {
        if (expr->type == ASTNode::EXPRESSION) {
            ExpressionNode* exprNode = static_cast<ExpressionNode*>(expr.get());
            fields.push_back(exprNode->value);
        }
    }
    
    return fields;
}

