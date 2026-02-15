#include "PhysicalPlanner.h"
#include <iostream>

std::unique_ptr<PhysicalPlanNode> PhysicalPlanner::build(LogicalPlanNode* logicalPlan) {
    if (!logicalPlan) return nullptr;
    logicalPlan->accept(this);
    return std::move(currentPhysicalNode);
}

void PhysicalPlanner::visitNodeScan(NodeScanNode* node) {
    currentPhysicalNode = std::make_unique<PhysicalNodeScan>(node->label, node->variable);
}

void PhysicalPlanner::visitEdgeScan(EdgeScanNode* node) {
    currentPhysicalNode = std::make_unique<PhysicalEdgeScan>(node->label, node->variable, node->direction);
}

void PhysicalPlanner::visitFilter(FilterNode* node) {
    // 1. Visit child (source of data)
    std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }

    // 2. Process condition
    currentExpressionString = "";
    if (node->condition) {
        node->condition->accept(this);
    }
    std::string condition = currentExpressionString;

    // 3. Create Physical Filter
    auto filter = std::make_unique<PhysicalFilter>(condition);
    if (childPlan) {
        filter->children.push_back(std::move(childPlan)); // Single child
    }
    currentPhysicalNode = std::move(filter);
}

void PhysicalPlanner::visitProject(ProjectNode* node) {
    // 1. Visit child
    std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }

    // 2. Create Project
    std::vector<std::string> projectFields;
    // Iterate over expressions to potentially get field names
    for (size_t i = 0; i < node->expressions.size(); ++i) {
        currentExpressionString = "";
        node->expressions[i]->accept(this);
        
        std::string fieldName = "";
        if (i < node->fields.size()) {
            fieldName = node->fields[i]; // Use alias if available
        }
        
        if (fieldName.empty()) {
            fieldName = currentExpressionString; // Fallback
        }
        projectFields.push_back(fieldName);
    }
    
    // Fallback if no expressions found but fields exist
    if (projectFields.empty() && !node->fields.empty()) {
        projectFields = node->fields;
    }

    auto project = std::make_unique<PhysicalProject>(projectFields);
    if (childPlan) {
        project->children.push_back(std::move(childPlan)); // Single child
    }
    currentPhysicalNode = std::move(project);
}

void PhysicalPlanner::visitJoin(JoinNode* node) {
    // Join has 2 children: Left and Right sources
    
    std::unique_ptr<PhysicalPlanNode> leftPlan = nullptr;
    std::unique_ptr<PhysicalPlanNode> rightPlan = nullptr;

    if (node->children.size() > 0) {
        node->children[0]->accept(this);
        leftPlan = std::move(currentPhysicalNode);
    }
    if (node->children.size() > 1) {
        node->children[1]->accept(this);
        rightPlan = std::move(currentPhysicalNode);
    }

    // Process condition
    currentExpressionString = "";
    if (node->condition) {
        node->condition->accept(this);
    }
    std::string condition = currentExpressionString;

    // Default to NestedLoopJoin for now
    auto join = std::make_unique<PhysicalNestedLoopJoin>(node->joinType, condition);
    if (leftPlan) join->children.push_back(std::move(leftPlan));
    if (rightPlan) join->children.push_back(std::move(rightPlan));

    currentPhysicalNode = std::move(join);
}

void PhysicalPlanner::visitAggregate(AggregateNode* node) {
    std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }

    // Build groupings string
    std::vector<std::string> groups;
    for (size_t i=0; i < node->groupingExpressions.size(); ++i) {
        currentExpressionString = "";
        node->groupingExpressions[i]->accept(this);
        groups.push_back(currentExpressionString); 
    }

    // Build measures
    std::vector<std::string> measures;
    for (const auto& item : node->aggregateItems) {
        currentExpressionString = "";
        if (item.expression) item.expression->accept(this);
        std::string measure = item.functionName + "(" + (item.distinct ? "DISTINCT " : "") + currentExpressionString + ")";
        if (!item.alias.empty()) measure += " AS " + item.alias;
        measures.push_back(measure);
    }

    auto agg = std::make_unique<PhysicalAggregate>(groups, measures);
    if (childPlan) agg->children.push_back(std::move(childPlan));
    currentPhysicalNode = std::move(agg);
}

void PhysicalPlanner::visitSort(SortNode* node) {
    std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }

    std::vector<PhysicalSort::SortItem> items;
    for (const auto& f : node->sortFields) {
        items.push_back({f.field, (f.direction == "ASC")});
    }

    auto sort = std::make_unique<PhysicalSort>(items);
    if (childPlan) sort->children.push_back(std::move(childPlan));
    currentPhysicalNode = std::move(sort);
}

void PhysicalPlanner::visitLimit(LimitNode* node) {
    std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }

    auto limit = std::make_unique<PhysicalLimit>(node->limit);
    if (childPlan) limit->children.push_back(std::move(childPlan));
    currentPhysicalNode = std::move(limit);
}

void PhysicalPlanner::visitOffset(OffsetNode* node) {
    std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }
    
    auto offset = std::make_unique<PhysicalOffset>(node->offset);
    if (childPlan) offset->children.push_back(std::move(childPlan));
    currentPhysicalNode = std::move(offset);
}

void PhysicalPlanner::visitUnion(UnionNode* node) {
    std::unique_ptr<PhysicalPlanNode> leftPlan = nullptr;
    std::unique_ptr<PhysicalPlanNode> rightPlan = nullptr;

    if (node->children.size() > 0) {
        node->children[0]->accept(this);
        leftPlan = std::move(currentPhysicalNode);
    }
    if (node->children.size() > 1) {
        node->children[1]->accept(this);
        rightPlan = std::move(currentPhysicalNode);
    }

    auto unionOp = std::make_unique<PhysicalUnion>(node->distinct);
    if (leftPlan) unionOp->children.push_back(std::move(leftPlan));
    if (rightPlan) unionOp->children.push_back(std::move(rightPlan));
    currentPhysicalNode = std::move(unionOp);
}

void PhysicalPlanner::visitDeleteOp(DeleteOpNode* node) {
     std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }

    auto deleteOp = std::make_unique<PhysicalDelete>(node->variables, node->detach);
    if (childPlan) deleteOp->children.push_back(std::move(childPlan));
    currentPhysicalNode = std::move(deleteOp);
}

void PhysicalPlanner::visitInsertOp(InsertOpNode* node) {
    auto insertOp = std::make_unique<PhysicalInsert>("(Insert Content Placeholder)");
    currentPhysicalNode = std::move(insertOp);
}

void PhysicalPlanner::visitUpdateOp(UpdateOpNode* node) {
     std::unique_ptr<PhysicalPlanNode> childPlan = nullptr;
    if (!node->children.empty()) {
        node->children[0]->accept(this);
        childPlan = std::move(currentPhysicalNode);
    }
    
    std::string desc;
    for (const auto& item : node->items) {
        desc += item.variable + "." + item.key + " ";
    }
    
    auto update = std::make_unique<PhysicalUpdate>(desc);
    if (childPlan) update->children.push_back(std::move(childPlan));
    currentPhysicalNode = std::move(update);
}

// --- Expressions ---
void PhysicalPlanner::visitBinaryExpression(BinaryExpressionNode* node) {
    if (node->left) node->left->accept(this);
    std::string left = currentExpressionString;
    
    if (node->right) node->right->accept(this);
    std::string right = currentExpressionString;
    
    currentExpressionString = "(" + left + " " + node->op + " " + right + ")"; 
}

void PhysicalPlanner::visitPropertyAccess(PropertyAccessNode* node) {
    currentExpressionString = node->variable + "." + node->property;
}

void PhysicalPlanner::visitVariableReference(VariableReferenceNode* node) {
    currentExpressionString = node->variable;
}

void PhysicalPlanner::visitLiteral(LiteralNode* node) {
    if (node->literalType == "STRING") currentExpressionString = "\"" + node->value + "\"";
    else currentExpressionString = node->value;
}
