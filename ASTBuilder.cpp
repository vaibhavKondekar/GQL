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
    
    // Visit the graph pattern binding table
    if (ctx->graphPatternBindingTable()) {
        visit(ctx->graphPatternBindingTable());
    }
    
    root->children.push_back(std::move(matchNode));
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitGraphPattern(GQLParser::GraphPatternContext* ctx) {
    // Visit path patterns
    for (auto* pathPattern : ctx->pathPattern()) {
        visit(pathPattern);
    }
    
    // Visit WHERE clause if present - GraphPattern has searchCondition, not whereClause
    if (ctx->searchCondition()) {
        visit(ctx->searchCondition());
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

antlrcpp::Any ASTBuilder::visitElementPattern(GQLParser::ElementPatternContext* ctx) {
    // Handle node patterns: (variable:label {properties})
    if (ctx->elementPatternFiller()) {
        auto nodePattern = std::make_unique<NodePatternNode>();
        
        // Extract variable name
        if (ctx->elementPatternFiller()->elementVariableDeclaration()) {
            nodePattern->variable = ctx->elementPatternFiller()->elementVariableDeclaration()->getText();
        }
        
        // Extract labels
        if (ctx->elementPatternFiller()->isLabelExpression()) {
            // For now, just store the text - in a real implementation, we'd parse the label expression
            std::string labelText = ctx->elementPatternFiller()->isLabelExpression()->getText();
            if (!labelText.empty()) {
                nodePattern->labels.push_back(labelText);
            }
        }
        
        // Extract properties
        if (ctx->elementPatternFiller()->elementPatternPredicate()) {
            // For now, just store the text - in a real implementation, we'd parse the properties
            std::string propText = ctx->elementPatternFiller()->elementPatternPredicate()->getText();
            if (!propText.empty() && propText[0] == '{') {
                // Simple property parsing - this is a simplified version
                nodePattern->properties["raw"] = propText;
            }
        }
        
        root->children.push_back(std::move(nodePattern));
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
        
        // Visit return items
        for (auto* returnItem : ctx->returnItem()) {
            visit(returnItem);
        }
        
        root->children.push_back(std::move(returnNode));
    }
    
    return nullptr;
}

antlrcpp::Any ASTBuilder::visitReturnItem(GQLParser::ReturnItemContext* ctx) {
    if (ctx->aggregatingValueExpression()) {
        auto exprNode = std::make_unique<ExpressionNode>();
        exprNode->type = "VARIABLE";
        exprNode->value = ctx->aggregatingValueExpression()->getText();
        
        root->children.push_back(std::move(exprNode));
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
    
    root->children.push_back(std::move(whereNode));
    return nullptr;
}



