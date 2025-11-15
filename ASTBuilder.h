#pragma once
#include "GQLBaseVisitor.h"
#include "ASTNodes.h"

class ASTBuilder : public GQLBaseVisitor {
    std::unique_ptr<QueryNode> root;
public:
    std::unique_ptr<QueryNode> build(GQLParser::GqlProgramContext* ctx);

    antlrcpp::Any visitGqlProgram(GQLParser::GqlProgramContext* ctx) override;
    antlrcpp::Any visitProgramActivity(GQLParser::ProgramActivityContext* ctx) override;
    antlrcpp::Any visitSessionActivity(GQLParser::SessionActivityContext* ctx) override;
    antlrcpp::Any visitSessionSetCommand(GQLParser::SessionSetCommandContext* ctx) override;
    antlrcpp::Any visitSessionResetCommand(GQLParser::SessionResetCommandContext* ctx) override;
    antlrcpp::Any visitTransactionActivity(GQLParser::TransactionActivityContext* ctx) override;
    antlrcpp::Any visitStartTransactionCommand(GQLParser::StartTransactionCommandContext* ctx) override;
    
    // MATCH statement visitors
    antlrcpp::Any visitMatchStatement(GQLParser::MatchStatementContext* ctx) override;
    antlrcpp::Any visitGraphPattern(GQLParser::GraphPatternContext* ctx) override;
    antlrcpp::Any visitPathPattern(GQLParser::PathPatternContext* ctx) override;
    antlrcpp::Any visitElementPattern(GQLParser::ElementPatternContext* ctx) override;
    antlrcpp::Any visitPrimitiveResultStatement(GQLParser::PrimitiveResultStatementContext* ctx) override;
    antlrcpp::Any visitReturnItem(GQLParser::ReturnItemContext* ctx) override;
    antlrcpp::Any visitWhereClause(GQLParser::WhereClauseContext* ctx) override;
    
    // Additional visitors for procedure body and statements
    antlrcpp::Any visitProcedureBody(GQLParser::ProcedureBodyContext* ctx) override;
    antlrcpp::Any visitStatementBlock(GQLParser::StatementBlockContext* ctx) override;
    antlrcpp::Any visitStatement(GQLParser::StatementContext* ctx) override;
    antlrcpp::Any visitPrimitiveQueryStatement(GQLParser::PrimitiveQueryStatementContext* ctx) override;
  
    
};
