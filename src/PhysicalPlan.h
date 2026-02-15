#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <map>

// Logical Plan Nodes for reference (if needed directly in physical plan, though ideally decoupled)
// For now we'll just use strings/simple structures or forward declare if we need to keep a reference.
// But for a pure physical plan, we usually copy strict necessary info.

enum class PhysicalOperatorType {
    SCAN_NODE,
    SCAN_EDGE,
    FILTER,
    PROJECT,
    NESTED_LOOP_JOIN,
    HASH_JOIN,
    SORT,
    LIMIT,
    OFFSET,
    AGGREGATE,
    UNION,
    DELETE,
    INSERT,
    UPDATE,
    VALUES // For literals/constants (e.g. "RETURN 1")
};

class PhysicalPlanNode {
public:
    PhysicalOperatorType type;
    std::vector<std::unique_ptr<PhysicalPlanNode>> children;

    PhysicalPlanNode(PhysicalOperatorType t) : type(t) {}
    virtual ~PhysicalPlanNode() = default;

    // Helper for printing the tree
    virtual std::string toString() const = 0;

    void print(int indent = 0) const {
        std::string indentation(indent * 2, ' ');
        std::cout << indentation << toString() << std::endl;
        for (const auto& child : children) {
            child->print(indent + 1);
        }
    }
};

// --- Scans ---

class PhysicalNodeScan : public PhysicalPlanNode {
public:
    std::string label;
    std::string variable;

    PhysicalNodeScan(std::string l, std::string v) 
        : PhysicalPlanNode(PhysicalOperatorType::SCAN_NODE), label(l), variable(v) {}

    std::string toString() const override {
        return "NodeScan(label: " + label + ", variable: " + variable + ")";
    }
};

class PhysicalEdgeScan : public PhysicalPlanNode {
public:
    std::string label;
    std::string variable;
    std::string direction; // "OUT", "IN", "BOTH" - simplified

    PhysicalEdgeScan(std::string l, std::string v, std::string dir) 
        : PhysicalPlanNode(PhysicalOperatorType::SCAN_EDGE), label(l), variable(v), direction(dir) {}

    std::string toString() const override {
        return "EdgeScan(label: " + label + ", variable: " + variable + ", direction: " + direction + ")";
    }
};

// --- Core Operators ---

class PhysicalFilter : public PhysicalPlanNode {
public:
    std::string conditionDescription; // Simplified for now, just the string representation of condition

    PhysicalFilter(std::string condDesc) 
        : PhysicalPlanNode(PhysicalOperatorType::FILTER), conditionDescription(condDesc) {}

    std::string toString() const override {
        return "Filter(condition: " + conditionDescription + ")";
    }
};

class PhysicalProject : public PhysicalPlanNode {
public:
    std::vector<std::string> fields;

    PhysicalProject(std::vector<std::string> f) 
        : PhysicalPlanNode(PhysicalOperatorType::PROJECT), fields(f) {}

    std::string toString() const override {
        std::string s = "Project([";
        for (size_t i = 0; i < fields.size(); ++i) {
            s += fields[i];
            if (i < fields.size() - 1) s += ", ";
        }
        s += "])";
        return s;
    }
};

// --- Joins ---

class PhysicalNestedLoopJoin : public PhysicalPlanNode {
public:
    std::string joinType; // INNER, LEFT, etc.
    std::string condition; 

    PhysicalNestedLoopJoin(std::string type, std::string cond) 
        : PhysicalPlanNode(PhysicalOperatorType::NESTED_LOOP_JOIN), joinType(type), condition(cond) {}

    std::string toString() const override {
        return "NestedLoopJoin(type: " + joinType + ", condition: " + condition + ")";
    }
};

// --- Other ---

class PhysicalSort : public PhysicalPlanNode {
public:
    struct SortItem {
        std::string field;
        bool ascending;
    };
    std::vector<SortItem> items;

    PhysicalSort(std::vector<SortItem> i) 
        : PhysicalPlanNode(PhysicalOperatorType::SORT), items(i) {}

    std::string toString() const override {
        std::string s = "Sort([";
        for (size_t i = 0; i < items.size(); ++i) {
            s += items[i].field + (items[i].ascending ? " ASC" : " DESC");
            if (i < items.size() - 1) s += ", ";
        }
        s += "])";
        return s;
    }
};

class PhysicalLimit : public PhysicalPlanNode {
public:
    int limit;
    PhysicalLimit(int l) : PhysicalPlanNode(PhysicalOperatorType::LIMIT), limit(l) {}
    std::string toString() const override { return "Limit(" + std::to_string(limit) + ")"; }
};

class PhysicalOffset : public PhysicalPlanNode {
public:
    int offset;
    PhysicalOffset(int o) : PhysicalPlanNode(PhysicalOperatorType::OFFSET), offset(o) {}
    std::string toString() const override { return "Offset(" + std::to_string(offset) + ")"; }
};

class PhysicalAggregate : public PhysicalPlanNode {
public:
    std::vector<std::string> groupings;
    std::vector<std::string> measures; // e.g. "COUNT(p)", "SUM(age)"

    PhysicalAggregate(std::vector<std::string> g, std::vector<std::string> m)
        : PhysicalPlanNode(PhysicalOperatorType::AGGREGATE), groupings(g), measures(m) {}

    std::string toString() const override {
        std::string s = "Aggregate(GroupBy: [";
        for (size_t i = 0; i < groupings.size(); ++i) {
            s += groupings[i];
            if (i < groupings.size() - 1) s += ", ";
        }
        s += "], Measures: [";
         for (size_t i = 0; i < measures.size(); ++i) {
            s += measures[i];
            if (i < measures.size() - 1) s += ", ";
        }
        s += "])";
        return s;
    }
};

class PhysicalValues : public PhysicalPlanNode {
public:
    std::vector<std::string> values;

    PhysicalValues(std::vector<std::string> v)
        : PhysicalPlanNode(PhysicalOperatorType::VALUES), values(v) {}
    
    std::string toString() const override {
        return "Values(...)";
    }
};

// --- Modification ---
class PhysicalInsert : public PhysicalPlanNode {
public:
    std::string details;
    PhysicalInsert(std::string d) : PhysicalPlanNode(PhysicalOperatorType::INSERT), details(d) {}
    std::string toString() const override { return "Insert(" + details + ")"; }
};

class PhysicalDelete : public PhysicalPlanNode {
public:
    std::vector<std::string> variables;
    bool detach;
    PhysicalDelete(std::vector<std::string> vars, bool d) 
        : PhysicalPlanNode(PhysicalOperatorType::DELETE), variables(vars), detach(d) {}
    std::string toString() const override { 
        std::string s = "Delete(vars: [";
        for(auto& v : variables) s += v + " ";
        s += "], detach: " + std::to_string(detach) + ")";
        return s;
    }
};

class PhysicalUpdate : public PhysicalPlanNode {
public: 
    std::string updateOps;
    PhysicalUpdate(std::string ops) 
        : PhysicalPlanNode(PhysicalOperatorType::UPDATE), updateOps(ops) {}
    std::string toString() const override { return "Update(" + updateOps + ")"; }
};

class PhysicalUnion : public PhysicalPlanNode {
public:
    bool distinct;
    PhysicalUnion(bool d) : PhysicalPlanNode(PhysicalOperatorType::UNION), distinct(d) {}
    std::string toString() const override { return distinct ? "UnionDistinct" : "UnionAll"; }
};

