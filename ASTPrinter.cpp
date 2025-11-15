#include "ASTPrinter.h"
#include "ASTNodes.h"

void ASTPrinter::printIndent() { for(int i=0;i<indent;i++) std::cout<<"  "; }

void ASTPrinter::visitQuery(QueryNode* n) {
    printIndent(); std::cout << "Query\n";
    indent++;
    for (auto& c : n->children) c->accept(this);
    indent--;
}
void ASTPrinter::visitSessionSet(SessionSetNode* n) {
    printIndent(); std::cout << "SessionSet: " << n->text << "\n";
}
void ASTPrinter::visitSessionReset(SessionResetNode* n) {
    printIndent(); std::cout << "SessionReset: " << n->text << "\n";
}
void ASTPrinter::visitSessionClose(SessionCloseNode* n) {
    printIndent(); std::cout << "SessionClose\n";
}
void ASTPrinter::visitTransaction(TransactionNode* n) {
    printIndent(); std::cout << "Transaction: " << n->action << "\n";
}
void ASTPrinter::visitProcedureCall(ProcedureCallNode* n) {
    printIndent(); std::cout << "ProcedureCall: " << n->name << "\n";
}
void ASTPrinter::visitCatalogStatement(CatalogStatementNode* n) {
    printIndent(); std::cout << "CatalogStatement: " << n->action << " " << n->objectType << " " << n->name << "\n";
}
void ASTPrinter::visitMatchStatement(MatchStatementNode* n) {
    printIndent(); std::cout << "MatchStatement\n";
    indent++;
    for (auto& pattern : n->patterns) {
        pattern->accept(this);
    }
    if (n->whereClause) {
        n->whereClause->accept(this);
    }
    if (n->returnStatement) {
        n->returnStatement->accept(this);
    }
    indent--;
}
void ASTPrinter::visitNodePattern(NodePatternNode* n) {
    printIndent(); std::cout << "NodePattern: " << n->variable;
    if (!n->labels.empty()) {
        std::cout << ":" << n->labels[0];
        for (size_t i = 1; i < n->labels.size(); i++) {
            std::cout << ":" << n->labels[i];
        }
    }
    if (!n->properties.empty()) {
        std::cout << " {";
        bool first = true;
        for (const auto& prop : n->properties) {
            if (!first) std::cout << ", ";
            std::cout << prop.first << ": " << prop.second;
            first = false;
        }
        std::cout << "}";
    }
    std::cout << "\n";
}
void ASTPrinter::visitEdgePattern(EdgePatternNode* n) {
    printIndent(); std::cout << "EdgePattern: " << n->variable;
    if (!n->labels.empty()) {
        std::cout << ":" << n->labels[0];
        for (size_t i = 1; i < n->labels.size(); i++) {
            std::cout << ":" << n->labels[i];
        }
    }
    if (!n->properties.empty()) {
        std::cout << " {";
        bool first = true;
        for (const auto& prop : n->properties) {
            if (!first) std::cout << ", ";
            std::cout << prop.first << ": " << prop.second;
            first = false;
        }
        std::cout << "}";
    }
    std::cout << " " << n->direction << "\n";
}
void ASTPrinter::visitReturnStatement(ReturnStatementNode* n) {
    printIndent(); std::cout << "ReturnStatement";
    if (n->distinct) std::cout << " (DISTINCT)";
    std::cout << "\n";
    indent++;
    for (auto& expr : n->expressions) {
        expr->accept(this);
    }
    indent--;
}
void ASTPrinter::visitWhereClause(WhereClauseNode* n) {
    printIndent(); std::cout << "WhereClause\n";
    indent++;
    if (n->condition) {
        n->condition->accept(this);
    }
    indent--;
}
void ASTPrinter::visitExpression(ExpressionNode* n) {
    printIndent(); std::cout << "Expression: " << n->type;
    if (!n->value.empty()) {
        std::cout << " (" << n->value << ")";
    }
    if (!n->operator_.empty()) {
        std::cout << " [" << n->operator_ << "]";
    }
    std::cout << "\n";
    if (n->left) {
        indent++;
        n->left->accept(this);
        indent--;
    }
    if (n->right) {
        indent++;
        n->right->accept(this);
        indent--;
    }
}

