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
    printIndent(); std::cout << "MatchStatement";
    if (n->optional) std::cout << " (OPTIONAL)";
    std::cout << "\n";
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
    if (!n->quantifier.empty()) {
        std::cout << n->quantifier;
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
    if (!n->literalType.empty()) {
        std::cout << " <" << n->literalType << ">";
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
    if (!n->arguments.empty()) {
        indent++;
        printIndent(); std::cout << "Arguments:\n";
        indent++;
        for (auto& arg : n->arguments) {
            arg->accept(this);
        }
        indent--;
        indent--;
    }
    if (n->object) {
        indent++;
        printIndent(); std::cout << "Object:\n";
        indent++;
        n->object->accept(this);
        indent--;
        indent--;
    }
    if (!n->propertyName.empty()) {
        printIndent(); std::cout << "Property: " << n->propertyName << "\n";
    }
}

void ASTPrinter::visitLetStatement(LetStatementNode* n) {
    printIndent(); std::cout << "LetStatement\n";
    indent++;
    for (const auto& def : n->definitions) {
        printIndent(); std::cout << "Variable: " << def.variable;
        if (def.hasType) {
            std::cout << " Type: " << def.type;
        }
        if (def.hasValue && def.valueExpression) {
            std::cout << " Value: ";
            def.valueExpression->accept(this);
        }
        std::cout << "\n";
    }
    indent--;
}

void ASTPrinter::visitForStatement(ForStatementNode* n) {
    printIndent(); std::cout << "ForStatement: " << n->variable;
    if (n->withOrdinality) std::cout << " (WITH ORDINALITY)";
    if (n->withOffset) std::cout << " (WITH OFFSET)";
    if (!n->ordinalityVar.empty()) std::cout << " var: " << n->ordinalityVar;
    std::cout << "\n";
    indent++;
    if (n->collectionExpression) {
        n->collectionExpression->accept(this);
    }
    indent--;
}

void ASTPrinter::visitFilterStatement(FilterStatementNode* n) {
    printIndent(); std::cout << "FilterStatement\n";
    indent++;
    if (n->condition) {
        n->condition->accept(this);
    }
    indent--;
}

void ASTPrinter::visitOrderByStatement(OrderByStatementNode* n) {
    printIndent(); std::cout << "OrderByStatement\n";
    indent++;
    for (const auto& spec : n->sortSpecs) {
        printIndent(); std::cout << "SortKey";
        if (!spec.direction.empty()) {
            std::cout << " (" << spec.direction << ")";
        }
        std::cout << "\n";
        if (spec.sortKey) {
            indent++;
            spec.sortKey->accept(this);
            indent--;
        }
    }
    if (n->offset) {
        printIndent(); std::cout << "Offset\n";
        indent++;
        n->offset->accept(this);
        indent--;
    }
    if (n->limit) {
        printIndent(); std::cout << "Limit\n";
        indent++;
        n->limit->accept(this);
        indent--;
    }
    indent--;
}

void ASTPrinter::visitInsertStatement(InsertStatementNode* n) {
    printIndent(); std::cout << "InsertStatement\n";
    indent++;
    for (auto& pattern : n->insertPatterns) {
        pattern->accept(this);
    }
    indent--;
}

void ASTPrinter::visitSetStatement(SetStatementNode* n) {
    printIndent(); std::cout << "SetStatement\n";
    indent++;
    for (const auto& item : n->items) {
        printIndent(); std::cout << "SetItem: " << item.variable << " Type: " << item.type;
        if (item.type == "PROPERTY") {
            std::cout << " Property: " << item.propertyName;
        } else if (item.type == "LABEL") {
            std::cout << " Label: " << item.labelName;
        }
        std::cout << "\n";
        if (item.valueExpression) {
            indent++;
            item.valueExpression->accept(this);
            indent--;
        }
    }
    indent--;
}

void ASTPrinter::visitRemoveStatement(RemoveStatementNode* n) {
    printIndent(); std::cout << "RemoveStatement\n";
    indent++;
    for (const auto& item : n->items) {
        printIndent(); std::cout << "RemoveItem: " << item.variable << " Type: " << item.type;
        if (item.type == "PROPERTY") {
            std::cout << " Property: " << item.propertyName;
        } else if (item.type == "LABEL") {
            std::cout << " Label: " << item.labelName;
        }
        std::cout << "\n";
    }
    indent--;
}

void ASTPrinter::visitDeleteStatement(DeleteStatementNode* n) {
    printIndent(); std::cout << "DeleteStatement";
    if (n->detach) std::cout << " (DETACH)";
    if (n->nodetach) std::cout << " (NODETACH)";
    std::cout << "\n";
    indent++;
    for (auto& expr : n->expressions) {
        expr->accept(this);
    }
    indent--;
}

void ASTPrinter::visitCompositeQuery(CompositeQueryNode* n) {
    printIndent(); std::cout << "CompositeQuery: " << n->operator_;
    if (n->distinct) std::cout << " DISTINCT";
    if (n->all) std::cout << " ALL";
    std::cout << "\n";
    indent++;
    if (n->left) {
        printIndent(); std::cout << "Left:\n";
        indent++;
        n->left->accept(this);
        indent--;
    }
    if (n->right) {
        printIndent(); std::cout << "Right:\n";
        indent++;
        n->right->accept(this);
        indent--;
    }
    indent--;
}

void ASTPrinter::visitSelectStatement(SelectStatementNode* n) {
    printIndent(); std::cout << "SelectStatement";
    if (n->distinct) std::cout << " (DISTINCT)";
    if (n->selectAll) std::cout << " (*)";
    std::cout << "\n";
    indent++;
    if (!n->selectItems.empty()) {
        printIndent(); std::cout << "SelectItems:\n";
        indent++;
        for (auto& item : n->selectItems) {
            item->accept(this);
        }
        indent--;
    }
    if (!n->fromMatches.empty()) {
        printIndent(); std::cout << "FromMatches:\n";
        indent++;
        for (auto& match : n->fromMatches) {
            match->accept(this);
        }
        indent--;
    }
    if (n->whereClause) {
        n->whereClause->accept(this);
    }
    if (n->groupByClause) {
        n->groupByClause->accept(this);
    }
    if (n->havingClause) {
        n->havingClause->accept(this);
    }
    if (n->orderByClause) {
        n->orderByClause->accept(this);
    }
    if (n->offset) {
        printIndent(); std::cout << "Offset\n";
        indent++;
        n->offset->accept(this);
        indent--;
    }
    if (n->limit) {
        printIndent(); std::cout << "Limit\n";
        indent++;
        n->limit->accept(this);
        indent--;
    }
    indent--;
}

void ASTPrinter::visitGroupByClause(GroupByClauseNode* n) {
    printIndent(); std::cout << "GroupByClause\n";
    indent++;
    for (auto& expr : n->groupingExpressions) {
        expr->accept(this);
    }
    indent--;
}

void ASTPrinter::visitHavingClause(HavingClauseNode* n) {
    printIndent(); std::cout << "HavingClause\n";
    indent++;
    if (n->condition) {
        n->condition->accept(this);
    }
    indent--;
}

void ASTPrinter::visitUseGraph(UseGraphNode* n) {
    printIndent(); std::cout << "UseGraph\n";
    indent++;
    if (n->graphExpression) {
        n->graphExpression->accept(this);
    }
    indent--;
}

