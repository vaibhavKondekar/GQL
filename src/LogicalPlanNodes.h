#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>

// Forward declaration
class LogicalPlanVisitor;

/**
 * Logical Plan = High-level operations (WHAT to do, not HOW)
 * 
 * Example:
 *   MATCH (p:Person) WHERE p.age > 30 RETURN p.name
 *   
 *   Logical Plan:
 *     Project(name)
 *       Filter(age > 30)
 *         NodeScan(Person)
 */

// Base class for all logical plan nodes
class LogicalPlanNode {
public:
    enum Type {
        NODE_SCAN,        // Scan nodes by label (e.g., NodeScan(Person))
        EDGE_SCAN,        // Scan edges by label
        FILTER,           // Filter rows based on condition
        PROJECT,          // Project/select specific fields
        JOIN,             // Join two data sources
        NESTED_LOOP_JOIN, // Join using nested loops
        HASH_JOIN,        // Join using hash table
        SORT,             // Sort results
        LIMIT,            // Limit number of results
        OFFSET,           // Skip results
        AGGREGATE,        // Group by and aggregate (COUNT, SUM, etc.)
        UNION,            // Union of two queries
        DISTINCT,         // Remove duplicates
        DELETE_OP,        // Delete operation
        INSERT_OP,        // Insert operation
        UPDATE_OP,        // Update operation
        BINARY_EXPRESSION,// Binary expression (AND, OR, >, =, etc.)
        PROPERTY_ACCESS,  // Property access (p.age)
        VARIABLE_REF,     // Variable reference (p)
        LITERAL           // Literal value (25, "London")
    };
    
    Type type;
    std::vector<std::unique_ptr<LogicalPlanNode>> children; // Child operations
    
    LogicalPlanNode(Type t) : type(t) {}
    virtual ~LogicalPlanNode() = default;
    virtual void accept(LogicalPlanVisitor* visitor) = 0;
};

// ========== SCAN OPERATIONS ==========

/**
 * NodeScan: Scan all nodes matching a label
 * Example: MATCH (p:Person) → NodeScan(Person)
 */
class NodeScanNode : public LogicalPlanNode {
public:
    std::string label;           // Label to scan (e.g., "Person")
    std::string variable;        // Variable name (e.g., "p")
    std::map<std::string, std::string> properties; // Property filters
    
    NodeScanNode() : LogicalPlanNode(NODE_SCAN) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

/**
 * EdgeScan: Scan edges matching a label
 * Example: MATCH ()-[r:ACTED_IN]->() → EdgeScan(ACTED_IN)
 */
class EdgeScanNode : public LogicalPlanNode {
public:
    std::string label;           // Edge label (e.g., "ACTED_IN")
    std::string variable;        // Variable name (e.g., "r")
    std::string direction;       // "->", "<-", "<->"
    std::map<std::string, std::string> properties; // Property filters
    
    EdgeScanNode() : LogicalPlanNode(EDGE_SCAN) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== FILTER OPERATION ==========

/**
 * Filter: Filter rows based on condition
 * Example: WHERE p.age > 30 → Filter(age > 30)
 */
class FilterNode : public LogicalPlanNode {
public:
    std::unique_ptr<LogicalPlanNode> condition; // Condition expression tree
    
    FilterNode() : LogicalPlanNode(FILTER) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== PROJECT OPERATION ==========

/**
 * Project: Select specific fields/expressions
 * Example: RETURN p.name, p.age → Project([name, age])
 */
class ProjectNode : public LogicalPlanNode {
public:
    std::vector<std::string> fields;  // Field names to project
    std::vector<std::unique_ptr<LogicalPlanNode>> expressions; // Expressions to project
    
    ProjectNode() : LogicalPlanNode(PROJECT) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== JOIN OPERATIONS ==========

/**
 * Join: Join two data sources
 * Example: MATCH (p:Person)-[r:ACTED_IN]->(m:Movie)
 *          → Join(NodeScan(Person), EdgeScan(ACTED_IN), NodeScan(Movie))
 */
class JoinNode : public LogicalPlanNode {
public:
    std::string joinType;  // "INNER", "LEFT", "RIGHT", "FULL"
    std::unique_ptr<LogicalPlanNode> condition; // Join condition
    
    JoinNode() : LogicalPlanNode(JOIN) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== AGGREGATE OPERATION ==========

/**
 * Aggregate: Group by and aggregate functions
 * Example: RETURN COUNT(p) → Aggregate([COUNT(p)])
 */
class AggregateNode : public LogicalPlanNode {
public:
    // Grouping expressions
    std::vector<std::unique_ptr<LogicalPlanNode>> groupingExpressions;
    std::vector<std::string> groupingAliases;
    
    // Aggregate items
    struct AggregateItem {
        std::string functionName;
        std::unique_ptr<LogicalPlanNode> expression;
        std::string alias;
        bool distinct = false;
    };
    std::vector<AggregateItem> aggregateItems;
    
    AggregateNode() : LogicalPlanNode(AGGREGATE) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== SORT OPERATION ==========

/**
 * Sort: Sort results
 * Example: ORDER BY p.age DESC → Sort([(age, DESC)])
 */
class SortNode : public LogicalPlanNode {
public:
    struct SortField {
        std::string field;
        std::string direction; // "ASC" or "DESC"
    };
    std::vector<SortField> sortFields;
    
    SortNode() : LogicalPlanNode(SORT) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== LIMIT/OFFSET OPERATIONS ==========

/**
 * Limit: Limit number of results
 * Example: LIMIT 10 → Limit(10)
 */
class LimitNode : public LogicalPlanNode {
public:
    int limit;
    
    LimitNode(int l) : LogicalPlanNode(LIMIT), limit(l) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

/**
 * Offset: Skip results
 * Example: SKIP 5 → Offset(5)
 */
class OffsetNode : public LogicalPlanNode {
public:
    int offset;
    
    OffsetNode(int o) : LogicalPlanNode(OFFSET), offset(o) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== SET OPERATIONS ==========

/**
 * Union: Union of two queries
 * Example: Query1 UNION Query2 → Union(Query1, Query2)
 */
class UnionNode : public LogicalPlanNode {
public:
    bool distinct; // UNION DISTINCT vs UNION ALL
    
    UnionNode() : LogicalPlanNode(UNION), distinct(false) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

// ========== MODIFY OPERATIONS ==========

/**
 * Delete: Delete nodes/edges
 * Example: DELETE p → DeleteOp([p])
 */
class DeleteOpNode : public LogicalPlanNode {
public:
    std::vector<std::string> variables; // Variables to delete
    bool detach; // DETACH DELETE
    
    DeleteOpNode() : LogicalPlanNode(DELETE_OP), detach(false) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

/**
 * Insert: Insert nodes/edges
 * Example: INSERT (p:Person {name: "Alice"}) → InsertOp([NodePattern])
 */
class InsertOpNode : public LogicalPlanNode {
public:
    std::vector<std::unique_ptr<LogicalPlanNode>> patterns; // Patterns to insert
    
    InsertOpNode() : LogicalPlanNode(INSERT_OP) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

/**
 * Update: Update node/edge properties or labels (SET/REMOVE)
 */
class UpdateOpNode : public LogicalPlanNode {
public:
    enum UpdateType { SET_PROPERTY, SET_LABEL, REMOVE_PROPERTY, REMOVE_LABEL, SET_MAP };
    
    struct UpdateItem {
        UpdateType type;
        std::string variable;
        std::string key;      // property name or label name
        std::unique_ptr<LogicalPlanNode> value; // for SET_PROPERTY/SET_MAP
    };
    
    std::vector<UpdateItem> items;
    
    UpdateOpNode() : LogicalPlanNode(UPDATE_OP) {}
    void accept(LogicalPlanVisitor* visitor) override;
};
// ========== EXPRESSION OPERATIONS ==========

/**
 * Base class for logical expressions (used in Filter, Project, etc.)
 */
class LogicalExpressionNode : public LogicalPlanNode {
public:
    LogicalExpressionNode(Type t) : LogicalPlanNode(t) {}
};

/**
 * Binary Expression: left OP right
 * Example: age > 30
 */
class BinaryExpressionNode : public LogicalExpressionNode {
public:
    std::string op; // ">", "=", "AND", "OR", etc.
    std::unique_ptr<LogicalPlanNode> left;
    std::unique_ptr<LogicalPlanNode> right;
    
    BinaryExpressionNode() : LogicalExpressionNode(BINARY_EXPRESSION) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

/**
 * Property Access: variable.property
 * Example: p.age
 */
class PropertyAccessNode : public LogicalExpressionNode {
public:
    std::string variable; // "p"
    std::string property; // "age"
    
    PropertyAccessNode(std::string var, std::string prop) 
        : LogicalExpressionNode(PROPERTY_ACCESS), variable(var), property(prop) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

/**
 * Variable Reference: variable
 * Example: p
 */
class VariableReferenceNode : public LogicalExpressionNode {
public:
    std::string variable; // "p"
    
    VariableReferenceNode(std::string var) 
        : LogicalExpressionNode(VARIABLE_REF), variable(var) {}
    void accept(LogicalPlanVisitor* visitor) override;
};

/**
 * Literal Value: 25, "London", true
 */
class LiteralNode : public LogicalExpressionNode {
public:
    std::string value; // "25", "London"
    std::string literalType; // "NUMBER", "STRING", "BOOLEAN"
    
    LiteralNode(std::string val, std::string type) 
        : LogicalExpressionNode(LITERAL), value(val), literalType(type) {}
    void accept(LogicalPlanVisitor* visitor) override;
};
