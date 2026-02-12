#pragma once
#include "LogicalPlanNodes.h"
#include <iostream>

/**
 * LogicalPlanVisitor: Visitor interface for logical plan nodes
 */
class LogicalPlanVisitor {
public:
    virtual ~LogicalPlanVisitor() = default;
    virtual void visitNodeScan(NodeScanNode* n) = 0;
    virtual void visitEdgeScan(EdgeScanNode* n) = 0;
    virtual void visitFilter(FilterNode* n) = 0;
    virtual void visitProject(ProjectNode* n) = 0;
    virtual void visitJoin(JoinNode* n) = 0;
    virtual void visitAggregate(AggregateNode* n) = 0;
    virtual void visitSort(SortNode* n) = 0;
    virtual void visitLimit(LimitNode* n) = 0;
    virtual void visitOffset(OffsetNode* n) = 0;
    virtual void visitUnion(UnionNode* n) = 0;
    virtual void visitDeleteOp(DeleteOpNode* n) = 0;
    virtual void visitInsertOp(InsertOpNode* n) = 0;
    virtual void visitUpdateOp(UpdateOpNode* n) = 0;
    virtual void visitBinaryExpression(BinaryExpressionNode* n) = 0;
    virtual void visitPropertyAccess(PropertyAccessNode* n) = 0;
    virtual void visitVariableReference(VariableReferenceNode* n) = 0;
    virtual void visitLiteral(LiteralNode* n) = 0;
};

/**
 * LogicalPlanPrinter: Pretty-prints logical plan tree
 */
class LogicalPlanPrinter : public LogicalPlanVisitor {
private:
    int indent = 0;
    void printIndent();
    
public:
    void visitNodeScan(NodeScanNode* n) override;
    void visitEdgeScan(EdgeScanNode* n) override;
    void visitFilter(FilterNode* n) override;
    void visitProject(ProjectNode* n) override;
    void visitJoin(JoinNode* n) override;
    void visitAggregate(AggregateNode* n) override;
    void visitSort(SortNode* n) override;
    void visitLimit(LimitNode* n) override;
    void visitOffset(OffsetNode* n) override;
    void visitUnion(UnionNode* n) override;
    void visitDeleteOp(DeleteOpNode* n) override;
    void visitInsertOp(InsertOpNode* n) override;
    void visitUpdateOp(UpdateOpNode* n) override;
    void visitBinaryExpression(BinaryExpressionNode* n) override;
    void visitPropertyAccess(PropertyAccessNode* n) override;
    void visitVariableReference(VariableReferenceNode* n) override;
    void visitLiteral(LiteralNode* n) override;
    
    // Entry point
    void print(LogicalPlanNode* plan);
};

