#pragma once
#include "LogicalPlanNodes.h"
#include "PhysicalPlan.h"
#include "LogicalPlanVisitor.h"
#include <memory>
#include <stack>

class PhysicalPlanner : public LogicalPlanVisitor {
public:
    std::unique_ptr<PhysicalPlanNode> build(LogicalPlanNode* logicalPlan);

    // Visitor methods
    void visitNodeScan(NodeScanNode* node) override;
    void visitEdgeScan(EdgeScanNode* node) override;
    void visitFilter(FilterNode* node) override;
    void visitProject(ProjectNode* n) override; // Wait, interface uses 'n' or types? Types matter.
    void visitJoin(JoinNode* node) override;
    void visitAggregate(AggregateNode* node) override;
    void visitSort(SortNode* node) override;
    void visitLimit(LimitNode* node) override;
    void visitOffset(OffsetNode* node) override;
    void visitUnion(UnionNode* node) override;
    void visitDeleteOp(DeleteOpNode* node) override;
    void visitInsertOp(InsertOpNode* node) override;
    void visitUpdateOp(UpdateOpNode* node) override;

    // Expressions
    void visitBinaryExpression(BinaryExpressionNode* node) override;
    void visitPropertyAccess(PropertyAccessNode* node) override;
    void visitVariableReference(VariableReferenceNode* node) override;
    void visitLiteral(LiteralNode* node) override;

private:
   std::unique_ptr<PhysicalPlanNode> currentPhysicalNode;
   std::string currentExpressionString; // Temporary Hack to build expression strings
};
