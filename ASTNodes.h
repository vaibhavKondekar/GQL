#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>

class ASTVisitor;

class ASTNode {
public:
    enum Type {
        QUERY,
        SESSION_SET,
        SESSION_RESET,
        SESSION_CLOSE,
        TRANSACTION,
        // Phase 2 additions:
        PROCEDURE_CALL,
        CATALOG_STATEMENT,
        // MATCH statement additions:
        MATCH_STATEMENT,
        NODE_PATTERN,
        EDGE_PATTERN,
        RETURN_STATEMENT,
        WHERE_CLAUSE,
        EXPRESSION
    };
    Type type;
    ASTNode(Type t) : type(t) {}
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor* v) = 0;
};

// Root Query node
class QueryNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> children;
    QueryNode() : ASTNode(QUERY) {}
    void accept(ASTVisitor* v) override;
};

// Session Set
class SessionSetNode : public ASTNode {
public:
    std::string text;
    SessionSetNode(const std::string& t) : ASTNode(SESSION_SET), text(t) {}
    void accept(ASTVisitor* v) override;
};

// Session Reset
class SessionResetNode : public ASTNode {
public:
    std::string text;
    SessionResetNode(const std::string& t) : ASTNode(SESSION_RESET), text(t) {}
    void accept(ASTVisitor* v) override;
};

// Session Close
class SessionCloseNode : public ASTNode {
public:
    SessionCloseNode() : ASTNode(SESSION_CLOSE) {}
    void accept(ASTVisitor* v) override;
};

// Transaction
class TransactionNode : public ASTNode {
public:
    std::string action; // START / COMMIT / ROLLBACK
    TransactionNode(const std::string& act) : ASTNode(TRANSACTION), action(act) {}
    void accept(ASTVisitor* v) override;
};

// ---------- Procedure Call ----------
class ProcedureCallNode : public ASTNode {
public:
    std::string name; // either "procName(...)" or "<inline>"
    std::vector<std::unique_ptr<ASTNode>> arguments;
    bool optional = false; // from OPTIONAL CALL

    ProcedureCallNode() : ASTNode(PROCEDURE_CALL) {}
    void accept(ASTVisitor* v) override;
};

// ---------- Catalog Statement ----------
class CatalogStatementNode : public ASTNode {
public:
    std::string action;     // CREATE / DROP
    std::string objectType; // SCHEMA / GRAPH / GRAPH_TYPE
    std::string name;       // object name (we'll just store text for now)

    CatalogStatementNode() : ASTNode(CATALOG_STATEMENT) {}
    void accept(ASTVisitor* v) override;
};

// ---------- MATCH Statement ----------
class MatchStatementNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> patterns;  // NodePattern and EdgePattern nodes
    std::unique_ptr<ASTNode> whereClause;           // Optional WHERE clause
    std::unique_ptr<ASTNode> returnStatement;       // RETURN statement
    
    MatchStatementNode() : ASTNode(MATCH_STATEMENT) {}
    void accept(ASTVisitor* v) override;
};

// ---------- Node Pattern ----------
class NodePatternNode : public ASTNode {
public:
    std::string variable;    // Variable name (e.g., "p", "m")
    std::vector<std::string> labels;  // Labels (e.g., "Person", "Movie")
    std::map<std::string, std::string> properties;  // Properties {key: value}
    
    NodePatternNode() : ASTNode(NODE_PATTERN) {}
    void accept(ASTVisitor* v) override;
};

// ---------- Edge Pattern ----------
class EdgePatternNode : public ASTNode {
public:
    std::string variable;    // Variable name (e.g., "r")
    std::vector<std::string> labels;  // Relationship labels (e.g., "ACTED_IN")
    std::map<std::string, std::string> properties;  // Properties {key: value}
    std::string direction;  // "->", "<-", "<->", etc.
    
    EdgePatternNode() : ASTNode(EDGE_PATTERN) {}
    void accept(ASTVisitor* v) override;
};

// ---------- Return Statement ----------
class ReturnStatementNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> expressions;  // Return expressions
    bool distinct = false;  // DISTINCT modifier
    
    ReturnStatementNode() : ASTNode(RETURN_STATEMENT) {}
    void accept(ASTVisitor* v) override;
};

// ---------- Where Clause ----------
class WhereClauseNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> condition;  // Boolean expression
    
    WhereClauseNode() : ASTNode(WHERE_CLAUSE) {}
    void accept(ASTVisitor* v) override;
};

// ---------- Expression ----------
class ExpressionNode : public ASTNode {
public:
    std::string type;        // "VARIABLE", "PROPERTY", "LITERAL", "BINARY_OP", etc.
    std::string value;       // The actual value/text
    std::string operator_;   // For binary operations: "=", ">", "<", etc.
    std::unique_ptr<ASTNode> left;   // Left operand
    std::unique_ptr<ASTNode> right;  // Right operand
    
    ExpressionNode() : ASTNode(EXPRESSION) {}
    void accept(ASTVisitor* v) override;
};
