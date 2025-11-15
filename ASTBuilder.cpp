#include "ASTBuilder.h"
#include "GQLParser.h"

std::unique_ptr<QueryNode> ASTBuilder::build(GQLParser::GqlProgramContext* ctx) {
    root = std::make_unique<QueryNode>();
    visit(ctx);
    return std::move(root);
}

antlrcpp::Any ASTBuilder::visitGqlProgram(GQLParser::GqlProgramContext* ctx) {
    if (ctx->programActivity()) visit(ctx->programActivity());
    if (ctx->SESSION() && ctx->CLOSE()) {
        root->children.push_back(std::make_unique<SessionCloseNode>());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitProgramActivity(GQLParser::ProgramActivityContext* ctx) {
    if (ctx->sessionActivity()) visit(ctx->sessionActivity());
    if (ctx->transactionActivity()) visit(ctx->transactionActivity());
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitSessionActivity(GQLParser::SessionActivityContext* ctx) {
    for (auto* s : ctx->sessionSetCommand()) visit(s);
    for (auto* r : ctx->sessionResetCommand()) visit(r);
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitSessionSetCommand(GQLParser::SessionSetCommandContext* ctx) {
    root->children.push_back(std::make_unique<SessionSetNode>(ctx->getText()));
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitSessionResetCommand(GQLParser::SessionResetCommandContext* ctx) {
    root->children.push_back(std::make_unique<SessionResetNode>(ctx->getText()));
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitTransactionActivity(GQLParser::TransactionActivityContext* ctx) {
    if (ctx->startTransactionCommand()) visit(ctx->startTransactionCommand());
    if (ctx->procedureBody()) {
        // Visit procedure body which contains statements
        visit(ctx->procedureBody());
    }
    if (ctx->COMMIT()) root->children.push_back(std::make_unique<TransactionNode>("COMMIT"));
    if (ctx->ROLLBACK()) root->children.push_back(std::make_unique<TransactionNode>("ROLLBACK"));
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitProcedureBody(GQLParser::ProcedureBodyContext* ctx) {
    if (ctx->statementBlock()) {
        visit(ctx->statementBlock());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitStatementBlock(GQLParser::StatementBlockContext* ctx) {
    if (ctx->statement()) {
        visit(ctx->statement());
    }
    for (auto* nextStmt : ctx->nextStatement()) {
        visit(nextStmt);
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitStatement(GQLParser::StatementContext* ctx) {
    if (ctx->linearCatalogModifyingStatement()) {
        visit(ctx->linearCatalogModifyingStatement());
    }
    if (ctx->linearDataModifyingStatement()) {
        visit(ctx->linearDataModifyingStatement());
    }
    if (ctx->compositeQueryStatement()) {
        visit(ctx->compositeQueryStatement());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPrimitiveQueryStatement(GQLParser::PrimitiveQueryStatementContext* ctx) {
    if (ctx->matchStatement()) {
        visit(ctx->matchStatement());
    }
    // Handle LET statement
    if (ctx->LET()) {
        auto letNode = std::make_unique<LetStatementNode>();
        for (auto* letVarDef : ctx->letVariableDefinition()) {
            visit(letVarDef);
        }
        root->children.push_back(std::move(letNode));
    }
    // Handle FOR statement
    if (ctx->FOR()) {
        auto forNode = std::make_unique<ForStatementNode>();
        if (!ctx->bindingVariable().empty()) {
            forNode->variable = ctx->bindingVariable(0)->getText();
        }
        if (ctx->valueExpression()) {
            auto exprNode = std::make_unique<ExpressionNode>();
            exprNode->type = "COLLECTION";
            exprNode->value = ctx->valueExpression()->getText();
            forNode->collectionExpression = std::move(exprNode);
        }
        if (ctx->WITH()) {
            if (ctx->ORDINALITY()) {
                forNode->withOrdinality = true;
            } else if (ctx->OFFSET()) {
                forNode->withOffset = true;
            }
            // Extract ordinality/offset variable
            if (ctx->bindingVariable().size() > 1) {
                forNode->ordinalityVar = ctx->bindingVariable(1)->getText();
            }
        }
        root->children.push_back(std::move(forNode));
    }
    // Handle FILTER statement
    if (ctx->FILTER()) {
        auto filterNode = std::make_unique<FilterStatementNode>();
        if (ctx->whereClause()) {
            visit(ctx->whereClause());
            // The whereClause visitor adds to currentMatchNode if available, otherwise root
            // We need to attach it to filterNode instead
        } else if (ctx->searchCondition()) {
            auto exprNode = std::make_unique<ExpressionNode>();
            exprNode->type = "CONDITION";
            exprNode->value = ctx->searchCondition()->getText();
            filterNode->condition = std::move(exprNode);
        }
        root->children.push_back(std::move(filterNode));
    }
    // Handle ORDER BY statement
    if (ctx->orderByAndPageStatement()) {
        visit(ctx->orderByAndPageStatement());
    }
    // Note: PrimitiveQueryStatement doesn't have primitiveResultStatement directly
    // It's handled at a higher level in the statement hierarchy
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitStartTransactionCommand(GQLParser::StartTransactionCommandContext* ctx) {
    root->children.push_back(std::make_unique<TransactionNode>("START"));
    return nullptr;
}

// MATCH statement visitors
antlrcpp::Any ASTBuilder::visitMatchStatement(GQLParser::MatchStatementContext* ctx) {
    auto matchNode = std::make_unique<MatchStatementNode>();
    currentMatchNode = matchNode.get();  // Set current match node
    
    // Visit the graph pattern binding table
    if (ctx->graphPatternBindingTable()) {
        visit(ctx->graphPatternBindingTable());
    }
    
    currentMatchNode = nullptr;  // Clear current match node
    root->children.push_back(std::move(matchNode));
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitGraphPatternBindingTable(GQLParser::GraphPatternBindingTableContext* ctx) {
    // Visit graph pattern
    if (ctx->graphPattern()) {
        visit(ctx->graphPattern());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitGraphPattern(GQLParser::GraphPatternContext* ctx) {
    // Visit path patterns
    for (auto* pathPattern : ctx->pathPattern()) {
        visit(pathPattern);
    }
    
    // Visit WHERE clause if present - GraphPattern has searchCondition, not whereClause
    if (ctx->searchCondition() && currentMatchNode) {
        auto whereNode = std::make_unique<WhereClauseNode>();
        auto exprNode = std::make_unique<ExpressionNode>();
        exprNode->type = "CONDITION";
        exprNode->value = ctx->searchCondition()->getText();
        whereNode->condition = std::move(exprNode);
        currentMatchNode->whereClause = std::move(whereNode);
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPathPattern(GQLParser::PathPatternContext* ctx) {
    // Visit path pattern expression
    if (ctx->pathPatternExpression()) {
        visit(ctx->pathPatternExpression());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPpePathTerm(GQLParser::PpePathTermContext* ctx) {
    // Single path term
    if (ctx->pathTerm()) {
        visit(ctx->pathTerm());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPpePatternUnion(GQLParser::PpePatternUnionContext* ctx) {
    // Visit path terms
    for (auto* pathTerm : ctx->pathTerm()) {
        visit(pathTerm);
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPpeMultisetAlternation(GQLParser::PpeMultisetAlternationContext* ctx) {
    // Visit path terms
    for (auto* pathTerm : ctx->pathTerm()) {
        visit(pathTerm);
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPathTerm(GQLParser::PathTermContext* ctx) {
    // Visit path factors
    for (auto* pathFactor : ctx->pathFactor()) {
        visit(pathFactor);
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPfPathPrimary(GQLParser::PfPathPrimaryContext* ctx) {
    // Simple path primary
    if (ctx->pathPrimary()) {
        visit(ctx->pathPrimary());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPfQuantifiedPathPrimary(GQLParser::PfQuantifiedPathPrimaryContext* ctx) {
    // Quantified path primary (with *, +, {n}, etc.)
    if (ctx->pathPrimary()) {
        visit(ctx->pathPrimary());
    }
    // TODO: Handle quantifier
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPfQuestionedPathPrimary(GQLParser::PfQuestionedPathPrimaryContext* ctx) {
    // Optional path primary (with ?)
    if (ctx->pathPrimary()) {
        visit(ctx->pathPrimary());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPpElementPattern(GQLParser::PpElementPatternContext* ctx) {
    // Element pattern in path primary
    if (ctx->elementPattern()) {
        visit(ctx->elementPattern());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPpParenthesizedPathPatternExpression(GQLParser::PpParenthesizedPathPatternExpressionContext* ctx) {
    // Parenthesized path pattern expression
    if (ctx->parenthesizedPathPatternExpression()) {
        visit(ctx->parenthesizedPathPatternExpression());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPpSimplifiedPathPatternExpression(GQLParser::PpSimplifiedPathPatternExpressionContext* ctx) {
    // Simplified path pattern expression
    if (ctx->simplifiedPathPatternExpression()) {
        visit(ctx->simplifiedPathPatternExpression());
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitElementPattern(GQLParser::ElementPatternContext* ctx) {
    // Handle node patterns: (variable:label {properties})
    if (ctx->elementPatternFiller()) {
        auto nodePattern = std::make_unique<NodePatternNode>();
        
        // Extract variable name
        if (ctx->elementPatternFiller()->elementVariableDeclaration()) {
            auto varDecl = ctx->elementPatternFiller()->elementVariableDeclaration();
            if (varDecl->elementVariable()) {
                if (varDecl->elementVariable()->bindingVariable()) {
                    nodePattern->variable = varDecl->elementVariable()->bindingVariable()->getText();
                }
            }
        }
        
        // Extract labels - parse the label expression to get just the label name
        if (ctx->elementPatternFiller()->isLabelExpression()) {
            auto labelExpr = ctx->elementPatternFiller()->isLabelExpression()->labelExpression();
            if (labelExpr) {
                // Try to cast to LabelExpressionName to extract label directly
                auto labelNameCtx = dynamic_cast<GQLParser::LabelExpressionNameContext*>(labelExpr);
                if (labelNameCtx && labelNameCtx->labelName() && labelNameCtx->labelName()->identifier()) {
                    std::string labelName = labelNameCtx->labelName()->identifier()->getText();
                    nodePattern->labels.push_back(labelName);
                } else {
                    // Fallback: extract from text and remove colon prefix
                    std::string labelText = ctx->elementPatternFiller()->isLabelExpression()->getText();
                    // Remove leading colon if present
                    if (!labelText.empty() && labelText[0] == ':') {
                        labelText = labelText.substr(1);
                    }
                    if (!labelText.empty()) {
                        nodePattern->labels.push_back(labelText);
                    }
                }
            }
        }
        
        // Extract properties
        if (ctx->elementPatternFiller()->elementPatternPredicate()) {
            auto pred = ctx->elementPatternFiller()->elementPatternPredicate();
            if (pred->elementPropertySpecification()) {
                auto propSpec = pred->elementPropertySpecification();
                std::string propText = propSpec->getText();
                if (!propText.empty() && propText[0] == '{') {
                    nodePattern->properties["raw"] = propText;
                }
            }
        }
        
        // Add to current match node if available, otherwise to root
        if (currentMatchNode) {
            currentMatchNode->patterns.push_back(std::move(nodePattern));
        } else {
            root->children.push_back(std::move(nodePattern));
        }
    } else if (ctx->fullEdgePattern()) {
        // Handle full edge patterns
        visit(ctx->fullEdgePattern());
    } else if (ctx->abbreviatedEdgePattern()) {
        // Handle abbreviated edge patterns
        visit(ctx->abbreviatedEdgePattern());
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitFullEdgePattern(GQLParser::FullEdgePatternContext* ctx) {
    auto edgePattern = std::make_unique<EdgePatternNode>();
    
    // Determine direction based on which alternative matched
    if (ctx->LEFT_ARROW_BRACKET() && ctx->RIGHT_BRACKET_MINUS()) {
        edgePattern->direction = "<--";
    } else if (ctx->TILDE_LEFT_BRACKET() && ctx->RIGHT_BRACKET_TILDE()) {
        edgePattern->direction = "<->";
    } else if (ctx->MINUS_LEFT_BRACKET() && ctx->BRACKET_RIGHT_ARROW()) {
        edgePattern->direction = "-->";
    } else if (ctx->LEFT_ARROW_BRACKET() && ctx->BRACKET_RIGHT_ARROW()) {
        edgePattern->direction = "<->";
    } else if (ctx->MINUS_LEFT_BRACKET() && ctx->RIGHT_BRACKET_MINUS()) {
        edgePattern->direction = "<--";
    } else {
        edgePattern->direction = "-->";  // Default
    }
    
    // Extract edge filler information
    if (ctx->elementPatternFiller()) {
        auto filler = ctx->elementPatternFiller();
        
        // Extract variable name
        if (filler->elementVariableDeclaration()) {
            auto varDecl = filler->elementVariableDeclaration();
            if (varDecl->elementVariable() && varDecl->elementVariable()->bindingVariable()) {
                edgePattern->variable = varDecl->elementVariable()->bindingVariable()->getText();
            }
        }
        
        // Extract labels
        if (filler->isLabelExpression()) {
            auto labelExpr = filler->isLabelExpression()->labelExpression();
            if (labelExpr) {
                // Try to cast to LabelExpressionName to extract label directly
                auto labelNameCtx = dynamic_cast<GQLParser::LabelExpressionNameContext*>(labelExpr);
                if (labelNameCtx && labelNameCtx->labelName() && labelNameCtx->labelName()->identifier()) {
                    std::string labelName = labelNameCtx->labelName()->identifier()->getText();
                    edgePattern->labels.push_back(labelName);
                } else {
                    // Fallback: extract from text and remove colon prefix
                    std::string labelText = filler->isLabelExpression()->getText();
                    if (!labelText.empty() && labelText[0] == ':') {
                        labelText = labelText.substr(1);
                    }
                    if (!labelText.empty()) {
                        edgePattern->labels.push_back(labelText);
                    }
                }
            }
        }
        
        // Extract properties
        if (filler->elementPatternPredicate()) {
            auto pred = filler->elementPatternPredicate();
            if (pred->elementPropertySpecification()) {
                std::string propText = pred->elementPropertySpecification()->getText();
                if (!propText.empty() && propText[0] == '{') {
                    edgePattern->properties["raw"] = propText;
                }
            }
        }
    }
    
    // Add to current match node if available, otherwise to root
    if (currentMatchNode) {
        currentMatchNode->patterns.push_back(std::move(edgePattern));
    } else {
        root->children.push_back(std::move(edgePattern));
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitAbbreviatedEdgePattern(GQLParser::AbbreviatedEdgePatternContext* ctx) {
    auto edgePattern = std::make_unique<EdgePatternNode>();
    
    // Determine direction from token
    if (ctx->LEFT_ARROW()) {
        edgePattern->direction = "<-";
    } else if (ctx->RIGHT_ARROW()) {
        edgePattern->direction = "->";
    } else if (ctx->TILDE()) {
        edgePattern->direction = "-";
    } else if (ctx->LEFT_ARROW_TILDE()) {
        edgePattern->direction = "<-";
    } else if (ctx->TILDE_RIGHT_ARROW()) {
        edgePattern->direction = "->";
    } else if (ctx->LEFT_MINUS_RIGHT()) {
        edgePattern->direction = "-";
    } else if (ctx->MINUS_SIGN()) {
        edgePattern->direction = "-";
    } else {
        edgePattern->direction = "-";
    }
    
    // Abbreviated edges don't have variables or labels
    edgePattern->variable = "";
    
    // Add to current match node if available, otherwise to root
    if (currentMatchNode) {
        currentMatchNode->patterns.push_back(std::move(edgePattern));
    } else {
        root->children.push_back(std::move(edgePattern));
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitPrimitiveResultStatement(GQLParser::PrimitiveResultStatementContext* ctx) {
    if (ctx->RETURN()) {
        auto returnNode = std::make_unique<ReturnStatementNode>();
        
        // Check for DISTINCT
        if (ctx->setQuantifier() && ctx->setQuantifier()->DISTINCT()) {
            returnNode->distinct = true;
        }
        
        // Visit return items - store reference to returnNode temporarily
        ReturnStatementNode* returnNodePtr = returnNode.get();
        
        // Visit return items
        for (auto* returnItem : ctx->returnItem()) {
            visit(returnItem);
        }
        
        // Attach to current match node if available, otherwise to root
        if (currentMatchNode) {
            currentMatchNode->returnStatement = std::move(returnNode);
        } else {
            root->children.push_back(std::move(returnNode));
        }
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitReturnItem(GQLParser::ReturnItemContext* ctx) {
    if (ctx->aggregatingValueExpression()) {
        auto exprNode = std::make_unique<ExpressionNode>();
        exprNode->type = "VARIABLE";
        exprNode->value = ctx->aggregatingValueExpression()->getText();
        
        // Find the return statement to attach to (could be in currentMatchNode or last in root)
        if (currentMatchNode && currentMatchNode->returnStatement) {
            ReturnStatementNode* returnNode = static_cast<ReturnStatementNode*>(currentMatchNode->returnStatement.get());
            returnNode->expressions.push_back(std::move(exprNode));
        } else {
            // Look for last return statement in root children
            bool added = false;
            for (auto it = root->children.rbegin(); it != root->children.rend(); ++it) {
                if ((*it)->type == ASTNode::RETURN_STATEMENT) {
                    ReturnStatementNode* returnNode = static_cast<ReturnStatementNode*>(it->get());
                    returnNode->expressions.push_back(std::move(exprNode));
                    added = true;
                    break;
                }
            }
            if (!added) {
                root->children.push_back(std::move(exprNode));
            }
        }
    }
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitWhereClause(GQLParser::WhereClauseContext* ctx) {
    auto whereNode = std::make_unique<WhereClauseNode>();
    
    if (ctx->searchCondition()) {
        auto exprNode = std::make_unique<ExpressionNode>();
        exprNode->type = "CONDITION";
        exprNode->value = ctx->searchCondition()->getText();
        whereNode->condition = std::move(exprNode);
    }
    
    // Add to current match node if available, otherwise to root
    if (currentMatchNode) {
        currentMatchNode->whereClause = std::move(whereNode);
    } else {
        root->children.push_back(std::move(whereNode));
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitLabelExpressionName(GQLParser::LabelExpressionNameContext* ctx) {
    // Label expression is just a label name
    // Extract the label name and store it for the current pattern being built
    // This is called when visiting a label expression that's a simple name
    if (ctx->labelName() && ctx->labelName()->identifier()) {
        std::string labelName = ctx->labelName()->identifier()->getText();
        // Store label name - we'll need to attach it to the current pattern
        // For now, return it as the result so calling code can use it
        return labelName;
    }
    return std::string("");
}

// Phase 2: Primitive query statement visitors
antlrcpp::Any ASTBuilder::visitLetVariableDefinition(GQLParser::LetVariableDefinitionContext* ctx) {
    LetStatementNode::LetVariableDefinition def;
    
    // Handle VALUE bindingVariable (typed? valueType)? (EQUALS_OPERATOR valueExpression)
    if (ctx->VALUE()) {
        if (ctx->bindingVariable()) {
            def.variable = ctx->bindingVariable()->getText();
        }
        // TODO: Handle typed and valueType
        if (ctx->EQUALS_OPERATOR() && ctx->valueExpression()) {
            auto exprNode = std::make_unique<ExpressionNode>();
            exprNode->type = "VALUE";
            exprNode->value = ctx->valueExpression()->getText();
            def.valueExpression = std::move(exprNode);
            def.hasValue = true;
        }
    } else if (ctx->bindingVariable()) {
        // Handle bindingVariable EQUALS_OPERATOR valueExpression
        def.variable = ctx->bindingVariable()->getText();
        if (ctx->EQUALS_OPERATOR() && ctx->valueExpression()) {
            auto exprNode = std::make_unique<ExpressionNode>();
            exprNode->type = "VALUE";
            exprNode->value = ctx->valueExpression()->getText();
            def.valueExpression = std::move(exprNode);
            def.hasValue = true;
        }
    }
    
    // Find the last LET statement node in root children and add to it
    for (auto it = root->children.rbegin(); it != root->children.rend(); ++it) {
        if ((*it)->type == ASTNode::LET_STATEMENT) {
            LetStatementNode* letNode = static_cast<LetStatementNode*>(it->get());
            letNode->definitions.push_back(std::move(def));
            break;
        }
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitOrderByAndPageStatement(GQLParser::OrderByAndPageStatementContext* ctx) {
    auto orderByNode = std::make_unique<OrderByStatementNode>();
    
    // Handle orderByClause offsetClause? limitClause?
    if (ctx->orderByClause()) {
        visit(ctx->orderByClause());
        // The orderByClause visitor should populate orderByNode
    }
    // Handle offsetClause limitClause?
    if (ctx->offsetClause()) {
        visit(ctx->offsetClause());
    }
    // Handle limitClause
    if (ctx->limitClause()) {
        visit(ctx->limitClause());
    }
    
    // Look for existing OrderByStatementNode or create new one
    // For now, just add to root
    root->children.push_back(std::move(orderByNode));
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitOrderByClause(GQLParser::OrderByClauseContext* ctx) {
    OrderByStatementNode* orderByNode = nullptr;
    
    // Find last OrderByStatementNode in root children
    for (auto it = root->children.rbegin(); it != root->children.rend(); ++it) {
        if ((*it)->type == ASTNode::ORDER_BY_STATEMENT) {
            orderByNode = static_cast<OrderByStatementNode*>(it->get());
            break;
        }
    }
    
    if (!orderByNode) {
        // Create new one if not found
        auto newNode = std::make_unique<OrderByStatementNode>();
        orderByNode = newNode.get();
        root->children.push_back(std::move(newNode));
    }
    
    // Visit sort specifications
    for (auto* sortSpec : ctx->sortSpecification()) {
        visit(sortSpec);
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitSortSpecification(GQLParser::SortSpecificationContext* ctx) {
    OrderByStatementNode::SortSpecification spec;
    
    // Extract sort key expression (aggregatingValueExpression)
    if (ctx->aggregatingValueExpression()) {
        auto exprNode = std::make_unique<ExpressionNode>();
        exprNode->type = "SORT_KEY";
        exprNode->value = ctx->aggregatingValueExpression()->getText();
        spec.sortKey = std::move(exprNode);
    }
    
    // Extract direction (ASC/DESC/ASCENDING/DESCENDING)
    if (ctx->ASC() || ctx->ASCENDING()) {
        spec.direction = "ASC";
    } else if (ctx->DESC() || ctx->DESCENDING()) {
        spec.direction = "DESC";
    }
    
    // Find last OrderByStatementNode in root children
    for (auto it = root->children.rbegin(); it != root->children.rend(); ++it) {
        if ((*it)->type == ASTNode::ORDER_BY_STATEMENT) {
            OrderByStatementNode* orderByNode = static_cast<OrderByStatementNode*>(it->get());
            orderByNode->sortSpecs.push_back(std::move(spec));
            break;
        }
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitOffsetClause(GQLParser::OffsetClauseContext* ctx) {
    OrderByStatementNode* orderByNode = nullptr;
    
    // Find last OrderByStatementNode in root children
    for (auto it = root->children.rbegin(); it != root->children.rend(); ++it) {
        if ((*it)->type == ASTNode::ORDER_BY_STATEMENT) {
            orderByNode = static_cast<OrderByStatementNode*>(it->get());
            break;
        }
    }
    
    if (!orderByNode) {
        // Create new one if not found
        auto newNode = std::make_unique<OrderByStatementNode>();
        orderByNode = newNode.get();
        root->children.push_back(std::move(newNode));
    }
    
    // Extract offset expression (nonNegativeIntegerSpecification)
    if (ctx->nonNegativeIntegerSpecification()) {
        auto exprNode = std::make_unique<ExpressionNode>();
        exprNode->type = "OFFSET";
        exprNode->value = ctx->nonNegativeIntegerSpecification()->getText();
        orderByNode->offset = std::move(exprNode);
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitLimitClause(GQLParser::LimitClauseContext* ctx) {
    OrderByStatementNode* orderByNode = nullptr;
    
    // Find last OrderByStatementNode in root children
    for (auto it = root->children.rbegin(); it != root->children.rend(); ++it) {
        if ((*it)->type == ASTNode::ORDER_BY_STATEMENT) {
            orderByNode = static_cast<OrderByStatementNode*>(it->get());
            break;
        }
    }
    
    if (!orderByNode) {
        // Create new one if not found
        auto newNode = std::make_unique<OrderByStatementNode>();
        orderByNode = newNode.get();
        root->children.push_back(std::move(newNode));
    }
    
    // Extract limit expression (nonNegativeIntegerSpecification)
    if (ctx->nonNegativeIntegerSpecification()) {
        auto exprNode = std::make_unique<ExpressionNode>();
        exprNode->type = "LIMIT";
        exprNode->value = ctx->nonNegativeIntegerSpecification()->getText();
        orderByNode->limit = std::move(exprNode);
    }
    
    return nullptr;
}



