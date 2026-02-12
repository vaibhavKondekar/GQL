
// Generated from GQL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "GQLVisitor.h"


/**
 * This class provides an empty implementation of GQLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  GQLBaseVisitor : public GQLVisitor {
public:

  virtual antlrcpp::Any visitGqlProgram(GQLParser::GqlProgramContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitProgramActivity(GQLParser::ProgramActivityContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSessionActivity(GQLParser::SessionActivityContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTransactionActivity(GQLParser::TransactionActivityContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSessionSetCommand(GQLParser::SessionSetCommandContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSessionSetSchemaClause(GQLParser::SessionSetSchemaClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSessionSetGraphClause(GQLParser::SessionSetGraphClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSessionSetTimeZoneClause(GQLParser::SessionSetTimeZoneClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSessionSetParameterClause(GQLParser::SessionSetParameterClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSessionResetCommand(GQLParser::SessionResetCommandContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitStartTransactionCommand(GQLParser::StartTransactionCommandContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTransactionAccessMode(GQLParser::TransactionAccessModeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNestedProcedureSpecification(GQLParser::NestedProcedureSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitProcedureBody(GQLParser::ProcedureBodyContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitStatementBlock(GQLParser::StatementBlockContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitStatement(GQLParser::StatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNextStatement(GQLParser::NextStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingVariableDefinition(GQLParser::BindingVariableDefinitionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphExpression(GQLParser::GraphExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingTableExpression(GQLParser::BindingTableExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLinearCatalogModifyingStatement(GQLParser::LinearCatalogModifyingStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPrimitiveCatalogModifyingStatement(GQLParser::PrimitiveCatalogModifyingStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitOpenGraphType(GQLParser::OpenGraphTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitOfGraphType(GQLParser::OfGraphTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphTypeSource(GQLParser::GraphTypeSourceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphSource(GQLParser::GraphSourceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLinearDataModifyingStatement(GQLParser::LinearDataModifyingStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitFocusedLinearDataModifyingStatement(GQLParser::FocusedLinearDataModifyingStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAmbientLinearDataModifyingStatement(GQLParser::AmbientLinearDataModifyingStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimpleDataAccessingStatement(GQLParser::SimpleDataAccessingStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPrimitiveDataModifyingStatement(GQLParser::PrimitiveDataModifyingStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSetItem(GQLParser::SetItemContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRemoveItem(GQLParser::RemoveItemContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCompositeQueryStatement(GQLParser::CompositeQueryStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCompositeQueryExpression(GQLParser::CompositeQueryExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitQueryConjunction(GQLParser::QueryConjunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLinearQueryStatement(GQLParser::LinearQueryStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitFocusedLinearQueryStatement(GQLParser::FocusedLinearQueryStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAmbientLinearQueryStatement(GQLParser::AmbientLinearQueryStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNestedQuerySpecification(GQLParser::NestedQuerySpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimpleQueryStatement(GQLParser::SimpleQueryStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPrimitiveQueryStatement(GQLParser::PrimitiveQueryStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitMatchStatement(GQLParser::MatchStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLetVariableDefinition(GQLParser::LetVariableDefinitionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitOrderByAndPageStatement(GQLParser::OrderByAndPageStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPrimitiveResultStatement(GQLParser::PrimitiveResultStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitReturnItem(GQLParser::ReturnItemContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSelectStatement(GQLParser::SelectStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSelectItem(GQLParser::SelectItemContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitHavingClause(GQLParser::HavingClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSelectStatementBody(GQLParser::SelectStatementBodyContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSelectGraphMatch(GQLParser::SelectGraphMatchContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSelectQuerySpecification(GQLParser::SelectQuerySpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCallProcedureStatement(GQLParser::CallProcedureStatementContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitProcedureCall(GQLParser::ProcedureCallContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAtSchemaClause(GQLParser::AtSchemaClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitUseGraphClause(GQLParser::UseGraphClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphPatternBindingTable(GQLParser::GraphPatternBindingTableContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphPattern(GQLParser::GraphPatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitMatchMode(GQLParser::MatchModeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathPattern(GQLParser::PathPatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitKeepClause(GQLParser::KeepClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitInsertGraphPattern(GQLParser::InsertGraphPatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitInsertPathPattern(GQLParser::InsertPathPatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitInsertNodePattern(GQLParser::InsertNodePatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitInsertEdgePattern(GQLParser::InsertEdgePatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitInsertElementPatternFiller(GQLParser::InsertElementPatternFillerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelAndPropertySetSpecification(GQLParser::LabelAndPropertySetSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathPatternPrefix(GQLParser::PathPatternPrefixContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathModePrefix(GQLParser::PathModePrefixContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathSearchPrefix(GQLParser::PathSearchPrefixContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitShortestPathSearch(GQLParser::ShortestPathSearchContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPpePathTerm(GQLParser::PpePathTermContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPpeMultisetAlternation(GQLParser::PpeMultisetAlternationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPpePatternUnion(GQLParser::PpePatternUnionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathTerm(GQLParser::PathTermContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPfPathPrimary(GQLParser::PfPathPrimaryContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPfQuantifiedPathPrimary(GQLParser::PfQuantifiedPathPrimaryContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPfQuestionedPathPrimary(GQLParser::PfQuestionedPathPrimaryContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPpElementPattern(GQLParser::PpElementPatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPpParenthesizedPathPatternExpression(GQLParser::PpParenthesizedPathPatternExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPpSimplifiedPathPatternExpression(GQLParser::PpSimplifiedPathPatternExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementPattern(GQLParser::ElementPatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementPatternFiller(GQLParser::ElementPatternFillerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementVariableDeclaration(GQLParser::ElementVariableDeclarationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitIsLabelExpression(GQLParser::IsLabelExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitIsOrColon(GQLParser::IsOrColonContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementPatternPredicate(GQLParser::ElementPatternPredicateContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementPropertySpecification(GQLParser::ElementPropertySpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPropertyKeyValuePairList(GQLParser::PropertyKeyValuePairListContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPropertyKeyValuePair(GQLParser::PropertyKeyValuePairContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitFullEdgePattern(GQLParser::FullEdgePatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAbbreviatedEdgePattern(GQLParser::AbbreviatedEdgePatternContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitParenthesizedPathPatternExpression(GQLParser::ParenthesizedPathPatternExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelExpressionNegation(GQLParser::LabelExpressionNegationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelExpressionDisjunction(GQLParser::LabelExpressionDisjunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelExpressionParenthesized(GQLParser::LabelExpressionParenthesizedContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelExpressionWildcard(GQLParser::LabelExpressionWildcardContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelExpressionConjunction(GQLParser::LabelExpressionConjunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelExpressionName(GQLParser::LabelExpressionNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphPatternQuantifier(GQLParser::GraphPatternQuantifierContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedPathPatternExpression(GQLParser::SimplifiedPathPatternExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedContents(GQLParser::SimplifiedContentsContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedFactorLowLabel(GQLParser::SimplifiedFactorLowLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedConcatenationLabel(GQLParser::SimplifiedConcatenationLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedConjunctionLabel(GQLParser::SimplifiedConjunctionLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedFactorHighLabel(GQLParser::SimplifiedFactorHighLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedFactorHigh(GQLParser::SimplifiedFactorHighContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedTertiary(GQLParser::SimplifiedTertiaryContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedSecondary(GQLParser::SimplifiedSecondaryContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimplifiedPrimary(GQLParser::SimplifiedPrimaryContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitWhereClause(GQLParser::WhereClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitYieldClause(GQLParser::YieldClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitYieldItem(GQLParser::YieldItemContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGroupByClause(GQLParser::GroupByClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitOrderByClause(GQLParser::OrderByClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSortSpecification(GQLParser::SortSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLimitClause(GQLParser::LimitClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitOffsetClause(GQLParser::OffsetClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSchemaReference(GQLParser::SchemaReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAbsoluteCatalogSchemaReference(GQLParser::AbsoluteCatalogSchemaReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCatalogSchemaParentAndName(GQLParser::CatalogSchemaParentAndNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRelativeCatalogSchemaReference(GQLParser::RelativeCatalogSchemaReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAbsoluteDirectoryPath(GQLParser::AbsoluteDirectoryPathContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRelativeDirectoryPath(GQLParser::RelativeDirectoryPathContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimpleDirectoryPath(GQLParser::SimpleDirectoryPathContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphReference(GQLParser::GraphReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCatalogGraphParentAndName(GQLParser::CatalogGraphParentAndNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphTypeReference(GQLParser::GraphTypeReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCatalogGraphTypeParentAndName(GQLParser::CatalogGraphTypeParentAndNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingTableReference(GQLParser::BindingTableReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitProcedureReference(GQLParser::ProcedureReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCatalogObjectParentReference(GQLParser::CatalogObjectParentReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNestedGraphTypeSpecification(GQLParser::NestedGraphTypeSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementTypeSpecification(GQLParser::ElementTypeSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNodeTypeSpecification(GQLParser::NodeTypeSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNodeTypePhraseFiller(GQLParser::NodeTypePhraseFillerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNodeTypeFiller(GQLParser::NodeTypeFillerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNodeTypeImpliedContent(GQLParser::NodeTypeImpliedContentContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeTypeSpecification(GQLParser::EdgeTypeSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeTypePhraseFiller(GQLParser::EdgeTypePhraseFillerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeTypeFiller(GQLParser::EdgeTypeFillerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeTypeImpliedContent(GQLParser::EdgeTypeImpliedContentContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeTypePatternDirected(GQLParser::EdgeTypePatternDirectedContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeTypePatternUndirected(GQLParser::EdgeTypePatternUndirectedContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitArcTypePointingRight(GQLParser::ArcTypePointingRightContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitArcTypePointingLeft(GQLParser::ArcTypePointingLeftContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitArcTypeUndirected(GQLParser::ArcTypeUndirectedContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSourceNodeTypeReference(GQLParser::SourceNodeTypeReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDestinationNodeTypeReference(GQLParser::DestinationNodeTypeReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeKind(GQLParser::EdgeKindContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEndpointPairPhrase(GQLParser::EndpointPairPhraseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEndpointPair(GQLParser::EndpointPairContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelSetPhrase(GQLParser::LabelSetPhraseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelSetSpecification(GQLParser::LabelSetSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPropertyTypesSpecification(GQLParser::PropertyTypesSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPropertyValueType(GQLParser::PropertyValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingTableType(GQLParser::BindingTableTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDynamicPropertyValueTypeLabel(GQLParser::DynamicPropertyValueTypeLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitClosedDynamicUnionTypeAtl1(GQLParser::ClosedDynamicUnionTypeAtl1Context *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitClosedDynamicUnionTypeAtl2(GQLParser::ClosedDynamicUnionTypeAtl2Context *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathValueTypeLabel(GQLParser::PathValueTypeLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListValueTypeAlt3(GQLParser::ListValueTypeAlt3Context *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListValueTypeAlt2(GQLParser::ListValueTypeAlt2Context *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListValueTypeAlt1(GQLParser::ListValueTypeAlt1Context *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPredefinedTypeLabel(GQLParser::PredefinedTypeLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRecordTypeLabel(GQLParser::RecordTypeLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitOpenDynamicUnionTypeLabel(GQLParser::OpenDynamicUnionTypeLabelContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTyped(GQLParser::TypedContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPredefinedType(GQLParser::PredefinedTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBooleanType(GQLParser::BooleanTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCharacterStringType(GQLParser::CharacterStringTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitByteStringType(GQLParser::ByteStringTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitMinLength(GQLParser::MinLengthContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitMaxLength(GQLParser::MaxLengthContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitFixedLength(GQLParser::FixedLengthContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNumericType(GQLParser::NumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitExactNumericType(GQLParser::ExactNumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBinaryExactNumericType(GQLParser::BinaryExactNumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSignedBinaryExactNumericType(GQLParser::SignedBinaryExactNumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitUnsignedBinaryExactNumericType(GQLParser::UnsignedBinaryExactNumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitVerboseBinaryExactNumericType(GQLParser::VerboseBinaryExactNumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDecimalExactNumericType(GQLParser::DecimalExactNumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPrecision(GQLParser::PrecisionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitScale(GQLParser::ScaleContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitApproximateNumericType(GQLParser::ApproximateNumericTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTemporalType(GQLParser::TemporalTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTemporalInstantType(GQLParser::TemporalInstantTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDatetimeType(GQLParser::DatetimeTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLocaldatetimeType(GQLParser::LocaldatetimeTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDateType(GQLParser::DateTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTimeType(GQLParser::TimeTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLocaltimeType(GQLParser::LocaltimeTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTemporalDurationType(GQLParser::TemporalDurationTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitReferenceValueType(GQLParser::ReferenceValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitImmaterialValueType(GQLParser::ImmaterialValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphReferenceValueType(GQLParser::GraphReferenceValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingTableReferenceValueType(GQLParser::BindingTableReferenceValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNodeReferenceValueType(GQLParser::NodeReferenceValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeReferenceValueType(GQLParser::EdgeReferenceValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathValueType(GQLParser::PathValueTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListValueTypeName(GQLParser::ListValueTypeNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRecordType(GQLParser::RecordTypeContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitFieldTypesSpecification(GQLParser::FieldTypesSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNotNull(GQLParser::NotNullContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSearchCondition(GQLParser::SearchConditionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPredicate(GQLParser::PredicateContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCompOp(GQLParser::CompOpContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitConjunctiveExprAlt(GQLParser::ConjunctiveExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPropertyGraphExprAlt(GQLParser::PropertyGraphExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitMultDivExprAlt(GQLParser::MultDivExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingTableExprAlt(GQLParser::BindingTableExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSignedExprAlt(GQLParser::SignedExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitIsNotExprAlt(GQLParser::IsNotExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNormalizedPredicateExprAlt(GQLParser::NormalizedPredicateExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNotExprAlt(GQLParser::NotExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitValueFunctionExprAlt(GQLParser::ValueFunctionExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitConcatenationExprAlt(GQLParser::ConcatenationExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDisjunctiveExprAlt(GQLParser::DisjunctiveExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitComparisonExprAlt(GQLParser::ComparisonExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPrimaryExprAlt(GQLParser::PrimaryExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAddSubtractExprAlt(GQLParser::AddSubtractExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPredicateExprAlt(GQLParser::PredicateExprAltContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitValueFunction(GQLParser::ValueFunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBooleanValueExpression(GQLParser::BooleanValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCharacterOrByteStringFunction(GQLParser::CharacterOrByteStringFunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAggregatingValueExpression(GQLParser::AggregatingValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitValueExpressionPrimary(GQLParser::ValueExpressionPrimaryContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitParenthesizedValueExpression(GQLParser::ParenthesizedValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNonParenthesizedValueExpressionPrimarySpecialCase(GQLParser::NonParenthesizedValueExpressionPrimarySpecialCaseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitUnsignedValueSpecification(GQLParser::UnsignedValueSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNonNegativeIntegerSpecification(GQLParser::NonNegativeIntegerSpecificationContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCaseExpression(GQLParser::CaseExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSimpleWhenClause(GQLParser::SimpleWhenClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSearchedWhenClause(GQLParser::SearchedWhenClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElseClause(GQLParser::ElseClauseContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCaseOperand(GQLParser::CaseOperandContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitWhenOperand(GQLParser::WhenOperandContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitResult(GQLParser::ResultContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitAggregateFunction(GQLParser::AggregateFunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSetQuantifier(GQLParser::SetQuantifierContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingVariableReference(GQLParser::BindingVariableReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementVariableReference(GQLParser::ElementVariableReferenceContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathValueExpression(GQLParser::PathValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathValueConstructor(GQLParser::PathValueConstructorContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListValueExpression(GQLParser::ListValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListValueFunction(GQLParser::ListValueFunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListValueConstructor(GQLParser::ListValueConstructorContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRecordConstructor(GQLParser::RecordConstructorContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTruthValue(GQLParser::TruthValueContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNumericValueExpression(GQLParser::NumericValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNumericValueFunction(GQLParser::NumericValueFunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCharacterStringValueExpression(GQLParser::CharacterStringValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitByteStringValueExpression(GQLParser::ByteStringValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTrimOperands(GQLParser::TrimOperandsContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitStringLength(GQLParser::StringLengthContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDatetimeValueExpression(GQLParser::DatetimeValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDatetimeValueFunction(GQLParser::DatetimeValueFunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDurationValueExpression(GQLParser::DurationValueExpressionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDatetimeSubtraction(GQLParser::DatetimeSubtractionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDurationValueFunction(GQLParser::DurationValueFunctionContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitObjectName(GQLParser::ObjectNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitObjectNameOrBindingVariable(GQLParser::ObjectNameOrBindingVariableContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDirectoryName(GQLParser::DirectoryNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSchemaName(GQLParser::SchemaNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphName(GQLParser::GraphNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDelimitedGraphName(GQLParser::DelimitedGraphNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGraphTypeName(GQLParser::GraphTypeNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNodeTypeName(GQLParser::NodeTypeNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeTypeName(GQLParser::EdgeTypeNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingTableName(GQLParser::BindingTableNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDelimitedBindingTableName(GQLParser::DelimitedBindingTableNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitProcedureName(GQLParser::ProcedureNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitLabelName(GQLParser::LabelNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPropertyName(GQLParser::PropertyNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitFieldName(GQLParser::FieldNameContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitElementVariable(GQLParser::ElementVariableContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitPathVariable(GQLParser::PathVariableContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitSubpathVariable(GQLParser::SubpathVariableContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitBindingVariable(GQLParser::BindingVariableContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitUnsignedLiteral(GQLParser::UnsignedLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitGeneralLiteral(GQLParser::GeneralLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTemporalLiteral(GQLParser::TemporalLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitListLiteral(GQLParser::ListLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRecordLiteral(GQLParser::RecordLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitIdentifier(GQLParser::IdentifierContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitRegularIdentifier(GQLParser::RegularIdentifierContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTimeZoneString(GQLParser::TimeZoneStringContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitCharacterStringLiteral(GQLParser::CharacterStringLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitUnsignedNumericLiteral(GQLParser::UnsignedNumericLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitExactNumericLiteral(GQLParser::ExactNumericLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitApproximateNumericLiteral(GQLParser::ApproximateNumericLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitUnsignedInteger(GQLParser::UnsignedIntegerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitUnsignedDecimalInteger(GQLParser::UnsignedDecimalIntegerContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNullLiteral(GQLParser::NullLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDateString(GQLParser::DateStringContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitTimeString(GQLParser::TimeStringContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDatetimeString(GQLParser::DatetimeStringContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDurationLiteral(GQLParser::DurationLiteralContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitDurationString(GQLParser::DurationStringContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNodeSynonym(GQLParser::NodeSynonymContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgesSynonym(GQLParser::EdgesSynonymContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitEdgeSynonym(GQLParser::EdgeSynonymContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }

  virtual antlrcpp::Any visitNonReservedWords(GQLParser::NonReservedWordsContext *ctx) override {
    return antlrcpp::Any(visitChildren(ctx));
  }


};

