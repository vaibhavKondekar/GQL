
// Generated from GQL.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "GQLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by GQLParser.
 */
class  GQLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by GQLParser.
   */
    virtual antlrcpp::Any visitGqlProgram(GQLParser::GqlProgramContext *context) = 0;

    virtual antlrcpp::Any visitProgramActivity(GQLParser::ProgramActivityContext *context) = 0;

    virtual antlrcpp::Any visitSessionActivity(GQLParser::SessionActivityContext *context) = 0;

    virtual antlrcpp::Any visitTransactionActivity(GQLParser::TransactionActivityContext *context) = 0;

    virtual antlrcpp::Any visitSessionSetCommand(GQLParser::SessionSetCommandContext *context) = 0;

    virtual antlrcpp::Any visitSessionSetSchemaClause(GQLParser::SessionSetSchemaClauseContext *context) = 0;

    virtual antlrcpp::Any visitSessionSetGraphClause(GQLParser::SessionSetGraphClauseContext *context) = 0;

    virtual antlrcpp::Any visitSessionSetTimeZoneClause(GQLParser::SessionSetTimeZoneClauseContext *context) = 0;

    virtual antlrcpp::Any visitSessionSetParameterClause(GQLParser::SessionSetParameterClauseContext *context) = 0;

    virtual antlrcpp::Any visitSessionResetCommand(GQLParser::SessionResetCommandContext *context) = 0;

    virtual antlrcpp::Any visitStartTransactionCommand(GQLParser::StartTransactionCommandContext *context) = 0;

    virtual antlrcpp::Any visitTransactionAccessMode(GQLParser::TransactionAccessModeContext *context) = 0;

    virtual antlrcpp::Any visitNestedProcedureSpecification(GQLParser::NestedProcedureSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitProcedureBody(GQLParser::ProcedureBodyContext *context) = 0;

    virtual antlrcpp::Any visitStatementBlock(GQLParser::StatementBlockContext *context) = 0;

    virtual antlrcpp::Any visitStatement(GQLParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitNextStatement(GQLParser::NextStatementContext *context) = 0;

    virtual antlrcpp::Any visitBindingVariableDefinition(GQLParser::BindingVariableDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitGraphExpression(GQLParser::GraphExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBindingTableExpression(GQLParser::BindingTableExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLinearCatalogModifyingStatement(GQLParser::LinearCatalogModifyingStatementContext *context) = 0;

    virtual antlrcpp::Any visitPrimitiveCatalogModifyingStatement(GQLParser::PrimitiveCatalogModifyingStatementContext *context) = 0;

    virtual antlrcpp::Any visitOpenGraphType(GQLParser::OpenGraphTypeContext *context) = 0;

    virtual antlrcpp::Any visitOfGraphType(GQLParser::OfGraphTypeContext *context) = 0;

    virtual antlrcpp::Any visitGraphTypeSource(GQLParser::GraphTypeSourceContext *context) = 0;

    virtual antlrcpp::Any visitGraphSource(GQLParser::GraphSourceContext *context) = 0;

    virtual antlrcpp::Any visitLinearDataModifyingStatement(GQLParser::LinearDataModifyingStatementContext *context) = 0;

    virtual antlrcpp::Any visitFocusedLinearDataModifyingStatement(GQLParser::FocusedLinearDataModifyingStatementContext *context) = 0;

    virtual antlrcpp::Any visitAmbientLinearDataModifyingStatement(GQLParser::AmbientLinearDataModifyingStatementContext *context) = 0;

    virtual antlrcpp::Any visitSimpleDataAccessingStatement(GQLParser::SimpleDataAccessingStatementContext *context) = 0;

    virtual antlrcpp::Any visitPrimitiveDataModifyingStatement(GQLParser::PrimitiveDataModifyingStatementContext *context) = 0;

    virtual antlrcpp::Any visitSetItem(GQLParser::SetItemContext *context) = 0;

    virtual antlrcpp::Any visitRemoveItem(GQLParser::RemoveItemContext *context) = 0;

    virtual antlrcpp::Any visitCompositeQueryStatement(GQLParser::CompositeQueryStatementContext *context) = 0;

    virtual antlrcpp::Any visitCompositeQueryExpression(GQLParser::CompositeQueryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitQueryConjunction(GQLParser::QueryConjunctionContext *context) = 0;

    virtual antlrcpp::Any visitLinearQueryStatement(GQLParser::LinearQueryStatementContext *context) = 0;

    virtual antlrcpp::Any visitFocusedLinearQueryStatement(GQLParser::FocusedLinearQueryStatementContext *context) = 0;

    virtual antlrcpp::Any visitAmbientLinearQueryStatement(GQLParser::AmbientLinearQueryStatementContext *context) = 0;

    virtual antlrcpp::Any visitNestedQuerySpecification(GQLParser::NestedQuerySpecificationContext *context) = 0;

    virtual antlrcpp::Any visitSimpleQueryStatement(GQLParser::SimpleQueryStatementContext *context) = 0;

    virtual antlrcpp::Any visitPrimitiveQueryStatement(GQLParser::PrimitiveQueryStatementContext *context) = 0;

    virtual antlrcpp::Any visitMatchStatement(GQLParser::MatchStatementContext *context) = 0;

    virtual antlrcpp::Any visitLetVariableDefinition(GQLParser::LetVariableDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitOrderByAndPageStatement(GQLParser::OrderByAndPageStatementContext *context) = 0;

    virtual antlrcpp::Any visitPrimitiveResultStatement(GQLParser::PrimitiveResultStatementContext *context) = 0;

    virtual antlrcpp::Any visitReturnItem(GQLParser::ReturnItemContext *context) = 0;

    virtual antlrcpp::Any visitSelectStatement(GQLParser::SelectStatementContext *context) = 0;

    virtual antlrcpp::Any visitSelectItem(GQLParser::SelectItemContext *context) = 0;

    virtual antlrcpp::Any visitHavingClause(GQLParser::HavingClauseContext *context) = 0;

    virtual antlrcpp::Any visitSelectStatementBody(GQLParser::SelectStatementBodyContext *context) = 0;

    virtual antlrcpp::Any visitSelectGraphMatch(GQLParser::SelectGraphMatchContext *context) = 0;

    virtual antlrcpp::Any visitSelectQuerySpecification(GQLParser::SelectQuerySpecificationContext *context) = 0;

    virtual antlrcpp::Any visitCallProcedureStatement(GQLParser::CallProcedureStatementContext *context) = 0;

    virtual antlrcpp::Any visitProcedureCall(GQLParser::ProcedureCallContext *context) = 0;

    virtual antlrcpp::Any visitAtSchemaClause(GQLParser::AtSchemaClauseContext *context) = 0;

    virtual antlrcpp::Any visitUseGraphClause(GQLParser::UseGraphClauseContext *context) = 0;

    virtual antlrcpp::Any visitGraphPatternBindingTable(GQLParser::GraphPatternBindingTableContext *context) = 0;

    virtual antlrcpp::Any visitGraphPattern(GQLParser::GraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitMatchMode(GQLParser::MatchModeContext *context) = 0;

    virtual antlrcpp::Any visitPathPattern(GQLParser::PathPatternContext *context) = 0;

    virtual antlrcpp::Any visitKeepClause(GQLParser::KeepClauseContext *context) = 0;

    virtual antlrcpp::Any visitInsertGraphPattern(GQLParser::InsertGraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitInsertPathPattern(GQLParser::InsertPathPatternContext *context) = 0;

    virtual antlrcpp::Any visitInsertNodePattern(GQLParser::InsertNodePatternContext *context) = 0;

    virtual antlrcpp::Any visitInsertEdgePattern(GQLParser::InsertEdgePatternContext *context) = 0;

    virtual antlrcpp::Any visitInsertElementPatternFiller(GQLParser::InsertElementPatternFillerContext *context) = 0;

    virtual antlrcpp::Any visitLabelAndPropertySetSpecification(GQLParser::LabelAndPropertySetSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitPathPatternPrefix(GQLParser::PathPatternPrefixContext *context) = 0;

    virtual antlrcpp::Any visitPathModePrefix(GQLParser::PathModePrefixContext *context) = 0;

    virtual antlrcpp::Any visitPathSearchPrefix(GQLParser::PathSearchPrefixContext *context) = 0;

    virtual antlrcpp::Any visitShortestPathSearch(GQLParser::ShortestPathSearchContext *context) = 0;

    virtual antlrcpp::Any visitPpePathTerm(GQLParser::PpePathTermContext *context) = 0;

    virtual antlrcpp::Any visitPpeMultisetAlternation(GQLParser::PpeMultisetAlternationContext *context) = 0;

    virtual antlrcpp::Any visitPpePatternUnion(GQLParser::PpePatternUnionContext *context) = 0;

    virtual antlrcpp::Any visitPathTerm(GQLParser::PathTermContext *context) = 0;

    virtual antlrcpp::Any visitPfPathPrimary(GQLParser::PfPathPrimaryContext *context) = 0;

    virtual antlrcpp::Any visitPfQuantifiedPathPrimary(GQLParser::PfQuantifiedPathPrimaryContext *context) = 0;

    virtual antlrcpp::Any visitPfQuestionedPathPrimary(GQLParser::PfQuestionedPathPrimaryContext *context) = 0;

    virtual antlrcpp::Any visitPpElementPattern(GQLParser::PpElementPatternContext *context) = 0;

    virtual antlrcpp::Any visitPpParenthesizedPathPatternExpression(GQLParser::PpParenthesizedPathPatternExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPpSimplifiedPathPatternExpression(GQLParser::PpSimplifiedPathPatternExpressionContext *context) = 0;

    virtual antlrcpp::Any visitElementPattern(GQLParser::ElementPatternContext *context) = 0;

    virtual antlrcpp::Any visitElementPatternFiller(GQLParser::ElementPatternFillerContext *context) = 0;

    virtual antlrcpp::Any visitElementVariableDeclaration(GQLParser::ElementVariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitIsLabelExpression(GQLParser::IsLabelExpressionContext *context) = 0;

    virtual antlrcpp::Any visitIsOrColon(GQLParser::IsOrColonContext *context) = 0;

    virtual antlrcpp::Any visitElementPatternPredicate(GQLParser::ElementPatternPredicateContext *context) = 0;

    virtual antlrcpp::Any visitElementPropertySpecification(GQLParser::ElementPropertySpecificationContext *context) = 0;

    virtual antlrcpp::Any visitPropertyKeyValuePairList(GQLParser::PropertyKeyValuePairListContext *context) = 0;

    virtual antlrcpp::Any visitPropertyKeyValuePair(GQLParser::PropertyKeyValuePairContext *context) = 0;

    virtual antlrcpp::Any visitFullEdgePattern(GQLParser::FullEdgePatternContext *context) = 0;

    virtual antlrcpp::Any visitAbbreviatedEdgePattern(GQLParser::AbbreviatedEdgePatternContext *context) = 0;

    virtual antlrcpp::Any visitParenthesizedPathPatternExpression(GQLParser::ParenthesizedPathPatternExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLabelExpressionNegation(GQLParser::LabelExpressionNegationContext *context) = 0;

    virtual antlrcpp::Any visitLabelExpressionDisjunction(GQLParser::LabelExpressionDisjunctionContext *context) = 0;

    virtual antlrcpp::Any visitLabelExpressionParenthesized(GQLParser::LabelExpressionParenthesizedContext *context) = 0;

    virtual antlrcpp::Any visitLabelExpressionWildcard(GQLParser::LabelExpressionWildcardContext *context) = 0;

    virtual antlrcpp::Any visitLabelExpressionConjunction(GQLParser::LabelExpressionConjunctionContext *context) = 0;

    virtual antlrcpp::Any visitLabelExpressionName(GQLParser::LabelExpressionNameContext *context) = 0;

    virtual antlrcpp::Any visitGraphPatternQuantifier(GQLParser::GraphPatternQuantifierContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedPathPatternExpression(GQLParser::SimplifiedPathPatternExpressionContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedContents(GQLParser::SimplifiedContentsContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedFactorLowLabel(GQLParser::SimplifiedFactorLowLabelContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedConcatenationLabel(GQLParser::SimplifiedConcatenationLabelContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedConjunctionLabel(GQLParser::SimplifiedConjunctionLabelContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedFactorHighLabel(GQLParser::SimplifiedFactorHighLabelContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedFactorHigh(GQLParser::SimplifiedFactorHighContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedTertiary(GQLParser::SimplifiedTertiaryContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedSecondary(GQLParser::SimplifiedSecondaryContext *context) = 0;

    virtual antlrcpp::Any visitSimplifiedPrimary(GQLParser::SimplifiedPrimaryContext *context) = 0;

    virtual antlrcpp::Any visitWhereClause(GQLParser::WhereClauseContext *context) = 0;

    virtual antlrcpp::Any visitYieldClause(GQLParser::YieldClauseContext *context) = 0;

    virtual antlrcpp::Any visitYieldItem(GQLParser::YieldItemContext *context) = 0;

    virtual antlrcpp::Any visitGroupByClause(GQLParser::GroupByClauseContext *context) = 0;

    virtual antlrcpp::Any visitOrderByClause(GQLParser::OrderByClauseContext *context) = 0;

    virtual antlrcpp::Any visitSortSpecification(GQLParser::SortSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitLimitClause(GQLParser::LimitClauseContext *context) = 0;

    virtual antlrcpp::Any visitOffsetClause(GQLParser::OffsetClauseContext *context) = 0;

    virtual antlrcpp::Any visitSchemaReference(GQLParser::SchemaReferenceContext *context) = 0;

    virtual antlrcpp::Any visitAbsoluteCatalogSchemaReference(GQLParser::AbsoluteCatalogSchemaReferenceContext *context) = 0;

    virtual antlrcpp::Any visitCatalogSchemaParentAndName(GQLParser::CatalogSchemaParentAndNameContext *context) = 0;

    virtual antlrcpp::Any visitRelativeCatalogSchemaReference(GQLParser::RelativeCatalogSchemaReferenceContext *context) = 0;

    virtual antlrcpp::Any visitAbsoluteDirectoryPath(GQLParser::AbsoluteDirectoryPathContext *context) = 0;

    virtual antlrcpp::Any visitRelativeDirectoryPath(GQLParser::RelativeDirectoryPathContext *context) = 0;

    virtual antlrcpp::Any visitSimpleDirectoryPath(GQLParser::SimpleDirectoryPathContext *context) = 0;

    virtual antlrcpp::Any visitGraphReference(GQLParser::GraphReferenceContext *context) = 0;

    virtual antlrcpp::Any visitCatalogGraphParentAndName(GQLParser::CatalogGraphParentAndNameContext *context) = 0;

    virtual antlrcpp::Any visitGraphTypeReference(GQLParser::GraphTypeReferenceContext *context) = 0;

    virtual antlrcpp::Any visitCatalogGraphTypeParentAndName(GQLParser::CatalogGraphTypeParentAndNameContext *context) = 0;

    virtual antlrcpp::Any visitBindingTableReference(GQLParser::BindingTableReferenceContext *context) = 0;

    virtual antlrcpp::Any visitProcedureReference(GQLParser::ProcedureReferenceContext *context) = 0;

    virtual antlrcpp::Any visitCatalogObjectParentReference(GQLParser::CatalogObjectParentReferenceContext *context) = 0;

    virtual antlrcpp::Any visitNestedGraphTypeSpecification(GQLParser::NestedGraphTypeSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitElementTypeSpecification(GQLParser::ElementTypeSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitNodeTypeSpecification(GQLParser::NodeTypeSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitNodeTypePhraseFiller(GQLParser::NodeTypePhraseFillerContext *context) = 0;

    virtual antlrcpp::Any visitNodeTypeFiller(GQLParser::NodeTypeFillerContext *context) = 0;

    virtual antlrcpp::Any visitNodeTypeImpliedContent(GQLParser::NodeTypeImpliedContentContext *context) = 0;

    virtual antlrcpp::Any visitEdgeTypeSpecification(GQLParser::EdgeTypeSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitEdgeTypePhraseFiller(GQLParser::EdgeTypePhraseFillerContext *context) = 0;

    virtual antlrcpp::Any visitEdgeTypeFiller(GQLParser::EdgeTypeFillerContext *context) = 0;

    virtual antlrcpp::Any visitEdgeTypeImpliedContent(GQLParser::EdgeTypeImpliedContentContext *context) = 0;

    virtual antlrcpp::Any visitEdgeTypePatternDirected(GQLParser::EdgeTypePatternDirectedContext *context) = 0;

    virtual antlrcpp::Any visitEdgeTypePatternUndirected(GQLParser::EdgeTypePatternUndirectedContext *context) = 0;

    virtual antlrcpp::Any visitArcTypePointingRight(GQLParser::ArcTypePointingRightContext *context) = 0;

    virtual antlrcpp::Any visitArcTypePointingLeft(GQLParser::ArcTypePointingLeftContext *context) = 0;

    virtual antlrcpp::Any visitArcTypeUndirected(GQLParser::ArcTypeUndirectedContext *context) = 0;

    virtual antlrcpp::Any visitSourceNodeTypeReference(GQLParser::SourceNodeTypeReferenceContext *context) = 0;

    virtual antlrcpp::Any visitDestinationNodeTypeReference(GQLParser::DestinationNodeTypeReferenceContext *context) = 0;

    virtual antlrcpp::Any visitEdgeKind(GQLParser::EdgeKindContext *context) = 0;

    virtual antlrcpp::Any visitEndpointPairPhrase(GQLParser::EndpointPairPhraseContext *context) = 0;

    virtual antlrcpp::Any visitEndpointPair(GQLParser::EndpointPairContext *context) = 0;

    virtual antlrcpp::Any visitLabelSetPhrase(GQLParser::LabelSetPhraseContext *context) = 0;

    virtual antlrcpp::Any visitLabelSetSpecification(GQLParser::LabelSetSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitPropertyTypesSpecification(GQLParser::PropertyTypesSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitPropertyValueType(GQLParser::PropertyValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitBindingTableType(GQLParser::BindingTableTypeContext *context) = 0;

    virtual antlrcpp::Any visitDynamicPropertyValueTypeLabel(GQLParser::DynamicPropertyValueTypeLabelContext *context) = 0;

    virtual antlrcpp::Any visitClosedDynamicUnionTypeAtl1(GQLParser::ClosedDynamicUnionTypeAtl1Context *context) = 0;

    virtual antlrcpp::Any visitClosedDynamicUnionTypeAtl2(GQLParser::ClosedDynamicUnionTypeAtl2Context *context) = 0;

    virtual antlrcpp::Any visitPathValueTypeLabel(GQLParser::PathValueTypeLabelContext *context) = 0;

    virtual antlrcpp::Any visitListValueTypeAlt3(GQLParser::ListValueTypeAlt3Context *context) = 0;

    virtual antlrcpp::Any visitListValueTypeAlt2(GQLParser::ListValueTypeAlt2Context *context) = 0;

    virtual antlrcpp::Any visitListValueTypeAlt1(GQLParser::ListValueTypeAlt1Context *context) = 0;

    virtual antlrcpp::Any visitPredefinedTypeLabel(GQLParser::PredefinedTypeLabelContext *context) = 0;

    virtual antlrcpp::Any visitRecordTypeLabel(GQLParser::RecordTypeLabelContext *context) = 0;

    virtual antlrcpp::Any visitOpenDynamicUnionTypeLabel(GQLParser::OpenDynamicUnionTypeLabelContext *context) = 0;

    virtual antlrcpp::Any visitTyped(GQLParser::TypedContext *context) = 0;

    virtual antlrcpp::Any visitPredefinedType(GQLParser::PredefinedTypeContext *context) = 0;

    virtual antlrcpp::Any visitBooleanType(GQLParser::BooleanTypeContext *context) = 0;

    virtual antlrcpp::Any visitCharacterStringType(GQLParser::CharacterStringTypeContext *context) = 0;

    virtual antlrcpp::Any visitByteStringType(GQLParser::ByteStringTypeContext *context) = 0;

    virtual antlrcpp::Any visitMinLength(GQLParser::MinLengthContext *context) = 0;

    virtual antlrcpp::Any visitMaxLength(GQLParser::MaxLengthContext *context) = 0;

    virtual antlrcpp::Any visitFixedLength(GQLParser::FixedLengthContext *context) = 0;

    virtual antlrcpp::Any visitNumericType(GQLParser::NumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitExactNumericType(GQLParser::ExactNumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitBinaryExactNumericType(GQLParser::BinaryExactNumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitSignedBinaryExactNumericType(GQLParser::SignedBinaryExactNumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedBinaryExactNumericType(GQLParser::UnsignedBinaryExactNumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitVerboseBinaryExactNumericType(GQLParser::VerboseBinaryExactNumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitDecimalExactNumericType(GQLParser::DecimalExactNumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitPrecision(GQLParser::PrecisionContext *context) = 0;

    virtual antlrcpp::Any visitScale(GQLParser::ScaleContext *context) = 0;

    virtual antlrcpp::Any visitApproximateNumericType(GQLParser::ApproximateNumericTypeContext *context) = 0;

    virtual antlrcpp::Any visitTemporalType(GQLParser::TemporalTypeContext *context) = 0;

    virtual antlrcpp::Any visitTemporalInstantType(GQLParser::TemporalInstantTypeContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeType(GQLParser::DatetimeTypeContext *context) = 0;

    virtual antlrcpp::Any visitLocaldatetimeType(GQLParser::LocaldatetimeTypeContext *context) = 0;

    virtual antlrcpp::Any visitDateType(GQLParser::DateTypeContext *context) = 0;

    virtual antlrcpp::Any visitTimeType(GQLParser::TimeTypeContext *context) = 0;

    virtual antlrcpp::Any visitLocaltimeType(GQLParser::LocaltimeTypeContext *context) = 0;

    virtual antlrcpp::Any visitTemporalDurationType(GQLParser::TemporalDurationTypeContext *context) = 0;

    virtual antlrcpp::Any visitReferenceValueType(GQLParser::ReferenceValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitImmaterialValueType(GQLParser::ImmaterialValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitGraphReferenceValueType(GQLParser::GraphReferenceValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitBindingTableReferenceValueType(GQLParser::BindingTableReferenceValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitNodeReferenceValueType(GQLParser::NodeReferenceValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitEdgeReferenceValueType(GQLParser::EdgeReferenceValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitPathValueType(GQLParser::PathValueTypeContext *context) = 0;

    virtual antlrcpp::Any visitListValueTypeName(GQLParser::ListValueTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitRecordType(GQLParser::RecordTypeContext *context) = 0;

    virtual antlrcpp::Any visitFieldTypesSpecification(GQLParser::FieldTypesSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitNotNull(GQLParser::NotNullContext *context) = 0;

    virtual antlrcpp::Any visitSearchCondition(GQLParser::SearchConditionContext *context) = 0;

    virtual antlrcpp::Any visitPredicate(GQLParser::PredicateContext *context) = 0;

    virtual antlrcpp::Any visitCompOp(GQLParser::CompOpContext *context) = 0;

    virtual antlrcpp::Any visitConjunctiveExprAlt(GQLParser::ConjunctiveExprAltContext *context) = 0;

    virtual antlrcpp::Any visitPropertyGraphExprAlt(GQLParser::PropertyGraphExprAltContext *context) = 0;

    virtual antlrcpp::Any visitMultDivExprAlt(GQLParser::MultDivExprAltContext *context) = 0;

    virtual antlrcpp::Any visitBindingTableExprAlt(GQLParser::BindingTableExprAltContext *context) = 0;

    virtual antlrcpp::Any visitSignedExprAlt(GQLParser::SignedExprAltContext *context) = 0;

    virtual antlrcpp::Any visitIsNotExprAlt(GQLParser::IsNotExprAltContext *context) = 0;

    virtual antlrcpp::Any visitNormalizedPredicateExprAlt(GQLParser::NormalizedPredicateExprAltContext *context) = 0;

    virtual antlrcpp::Any visitNotExprAlt(GQLParser::NotExprAltContext *context) = 0;

    virtual antlrcpp::Any visitValueFunctionExprAlt(GQLParser::ValueFunctionExprAltContext *context) = 0;

    virtual antlrcpp::Any visitConcatenationExprAlt(GQLParser::ConcatenationExprAltContext *context) = 0;

    virtual antlrcpp::Any visitDisjunctiveExprAlt(GQLParser::DisjunctiveExprAltContext *context) = 0;

    virtual antlrcpp::Any visitComparisonExprAlt(GQLParser::ComparisonExprAltContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExprAlt(GQLParser::PrimaryExprAltContext *context) = 0;

    virtual antlrcpp::Any visitAddSubtractExprAlt(GQLParser::AddSubtractExprAltContext *context) = 0;

    virtual antlrcpp::Any visitPredicateExprAlt(GQLParser::PredicateExprAltContext *context) = 0;

    virtual antlrcpp::Any visitValueFunction(GQLParser::ValueFunctionContext *context) = 0;

    virtual antlrcpp::Any visitBooleanValueExpression(GQLParser::BooleanValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitCharacterOrByteStringFunction(GQLParser::CharacterOrByteStringFunctionContext *context) = 0;

    virtual antlrcpp::Any visitAggregatingValueExpression(GQLParser::AggregatingValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitValueExpressionPrimary(GQLParser::ValueExpressionPrimaryContext *context) = 0;

    virtual antlrcpp::Any visitParenthesizedValueExpression(GQLParser::ParenthesizedValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitNonParenthesizedValueExpressionPrimarySpecialCase(GQLParser::NonParenthesizedValueExpressionPrimarySpecialCaseContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedValueSpecification(GQLParser::UnsignedValueSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitNonNegativeIntegerSpecification(GQLParser::NonNegativeIntegerSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitCaseExpression(GQLParser::CaseExpressionContext *context) = 0;

    virtual antlrcpp::Any visitSimpleWhenClause(GQLParser::SimpleWhenClauseContext *context) = 0;

    virtual antlrcpp::Any visitSearchedWhenClause(GQLParser::SearchedWhenClauseContext *context) = 0;

    virtual antlrcpp::Any visitElseClause(GQLParser::ElseClauseContext *context) = 0;

    virtual antlrcpp::Any visitCaseOperand(GQLParser::CaseOperandContext *context) = 0;

    virtual antlrcpp::Any visitWhenOperand(GQLParser::WhenOperandContext *context) = 0;

    virtual antlrcpp::Any visitResult(GQLParser::ResultContext *context) = 0;

    virtual antlrcpp::Any visitAggregateFunction(GQLParser::AggregateFunctionContext *context) = 0;

    virtual antlrcpp::Any visitSetQuantifier(GQLParser::SetQuantifierContext *context) = 0;

    virtual antlrcpp::Any visitBindingVariableReference(GQLParser::BindingVariableReferenceContext *context) = 0;

    virtual antlrcpp::Any visitElementVariableReference(GQLParser::ElementVariableReferenceContext *context) = 0;

    virtual antlrcpp::Any visitPathValueExpression(GQLParser::PathValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPathValueConstructor(GQLParser::PathValueConstructorContext *context) = 0;

    virtual antlrcpp::Any visitListValueExpression(GQLParser::ListValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitListValueFunction(GQLParser::ListValueFunctionContext *context) = 0;

    virtual antlrcpp::Any visitListValueConstructor(GQLParser::ListValueConstructorContext *context) = 0;

    virtual antlrcpp::Any visitRecordConstructor(GQLParser::RecordConstructorContext *context) = 0;

    virtual antlrcpp::Any visitTruthValue(GQLParser::TruthValueContext *context) = 0;

    virtual antlrcpp::Any visitNumericValueExpression(GQLParser::NumericValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitNumericValueFunction(GQLParser::NumericValueFunctionContext *context) = 0;

    virtual antlrcpp::Any visitCharacterStringValueExpression(GQLParser::CharacterStringValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitByteStringValueExpression(GQLParser::ByteStringValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitTrimOperands(GQLParser::TrimOperandsContext *context) = 0;

    virtual antlrcpp::Any visitStringLength(GQLParser::StringLengthContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeValueExpression(GQLParser::DatetimeValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeValueFunction(GQLParser::DatetimeValueFunctionContext *context) = 0;

    virtual antlrcpp::Any visitDurationValueExpression(GQLParser::DurationValueExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeSubtraction(GQLParser::DatetimeSubtractionContext *context) = 0;

    virtual antlrcpp::Any visitDurationValueFunction(GQLParser::DurationValueFunctionContext *context) = 0;

    virtual antlrcpp::Any visitObjectName(GQLParser::ObjectNameContext *context) = 0;

    virtual antlrcpp::Any visitObjectNameOrBindingVariable(GQLParser::ObjectNameOrBindingVariableContext *context) = 0;

    virtual antlrcpp::Any visitDirectoryName(GQLParser::DirectoryNameContext *context) = 0;

    virtual antlrcpp::Any visitSchemaName(GQLParser::SchemaNameContext *context) = 0;

    virtual antlrcpp::Any visitGraphName(GQLParser::GraphNameContext *context) = 0;

    virtual antlrcpp::Any visitDelimitedGraphName(GQLParser::DelimitedGraphNameContext *context) = 0;

    virtual antlrcpp::Any visitGraphTypeName(GQLParser::GraphTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitNodeTypeName(GQLParser::NodeTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitEdgeTypeName(GQLParser::EdgeTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitBindingTableName(GQLParser::BindingTableNameContext *context) = 0;

    virtual antlrcpp::Any visitDelimitedBindingTableName(GQLParser::DelimitedBindingTableNameContext *context) = 0;

    virtual antlrcpp::Any visitProcedureName(GQLParser::ProcedureNameContext *context) = 0;

    virtual antlrcpp::Any visitLabelName(GQLParser::LabelNameContext *context) = 0;

    virtual antlrcpp::Any visitPropertyName(GQLParser::PropertyNameContext *context) = 0;

    virtual antlrcpp::Any visitFieldName(GQLParser::FieldNameContext *context) = 0;

    virtual antlrcpp::Any visitElementVariable(GQLParser::ElementVariableContext *context) = 0;

    virtual antlrcpp::Any visitPathVariable(GQLParser::PathVariableContext *context) = 0;

    virtual antlrcpp::Any visitSubpathVariable(GQLParser::SubpathVariableContext *context) = 0;

    virtual antlrcpp::Any visitBindingVariable(GQLParser::BindingVariableContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedLiteral(GQLParser::UnsignedLiteralContext *context) = 0;

    virtual antlrcpp::Any visitGeneralLiteral(GQLParser::GeneralLiteralContext *context) = 0;

    virtual antlrcpp::Any visitTemporalLiteral(GQLParser::TemporalLiteralContext *context) = 0;

    virtual antlrcpp::Any visitListLiteral(GQLParser::ListLiteralContext *context) = 0;

    virtual antlrcpp::Any visitRecordLiteral(GQLParser::RecordLiteralContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(GQLParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitRegularIdentifier(GQLParser::RegularIdentifierContext *context) = 0;

    virtual antlrcpp::Any visitTimeZoneString(GQLParser::TimeZoneStringContext *context) = 0;

    virtual antlrcpp::Any visitCharacterStringLiteral(GQLParser::CharacterStringLiteralContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedNumericLiteral(GQLParser::UnsignedNumericLiteralContext *context) = 0;

    virtual antlrcpp::Any visitExactNumericLiteral(GQLParser::ExactNumericLiteralContext *context) = 0;

    virtual antlrcpp::Any visitApproximateNumericLiteral(GQLParser::ApproximateNumericLiteralContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedInteger(GQLParser::UnsignedIntegerContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedDecimalInteger(GQLParser::UnsignedDecimalIntegerContext *context) = 0;

    virtual antlrcpp::Any visitNullLiteral(GQLParser::NullLiteralContext *context) = 0;

    virtual antlrcpp::Any visitDateString(GQLParser::DateStringContext *context) = 0;

    virtual antlrcpp::Any visitTimeString(GQLParser::TimeStringContext *context) = 0;

    virtual antlrcpp::Any visitDatetimeString(GQLParser::DatetimeStringContext *context) = 0;

    virtual antlrcpp::Any visitDurationLiteral(GQLParser::DurationLiteralContext *context) = 0;

    virtual antlrcpp::Any visitDurationString(GQLParser::DurationStringContext *context) = 0;

    virtual antlrcpp::Any visitNodeSynonym(GQLParser::NodeSynonymContext *context) = 0;

    virtual antlrcpp::Any visitEdgesSynonym(GQLParser::EdgesSynonymContext *context) = 0;

    virtual antlrcpp::Any visitEdgeSynonym(GQLParser::EdgeSynonymContext *context) = 0;

    virtual antlrcpp::Any visitNonReservedWords(GQLParser::NonReservedWordsContext *context) = 0;


};

