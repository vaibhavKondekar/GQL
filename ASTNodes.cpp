#include "ASTNodes.h"
#include "ASTVisitor.h"

void QueryNode::accept(ASTVisitor* v) { v->visitQuery(this); }
void SessionSetNode::accept(ASTVisitor* v) { v->visitSessionSet(this); }
void SessionResetNode::accept(ASTVisitor* v) { v->visitSessionReset(this); }
void SessionCloseNode::accept(ASTVisitor* v) { v->visitSessionClose(this); }
void TransactionNode::accept(ASTVisitor* v) { v->visitTransaction(this); }
void ProcedureCallNode::accept(ASTVisitor* v) { v->visitProcedureCall(this); }
void CatalogStatementNode::accept(ASTVisitor* v) { v->visitCatalogStatement(this); }
void MatchStatementNode::accept(ASTVisitor* v) { v->visitMatchStatement(this); }
void NodePatternNode::accept(ASTVisitor* v) { v->visitNodePattern(this); }
void EdgePatternNode::accept(ASTVisitor* v) { v->visitEdgePattern(this); }
void ReturnStatementNode::accept(ASTVisitor* v) { v->visitReturnStatement(this); }
void WhereClauseNode::accept(ASTVisitor* v) { v->visitWhereClause(this); }
void ExpressionNode::accept(ASTVisitor* v) { v->visitExpression(this); }


