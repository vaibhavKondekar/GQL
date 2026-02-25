#include "PhysicalOperator.h"
#include <sstream>
#include <algorithm>

// --- Helper Functions ---

// Simple parser for "variable.property"
pair<string, string> parseVarProp(const string& s) {
    size_t dotPos = s.find('.');
    if (dotPos == string::npos) return {s, ""}; // Just variable
    return {s.substr(0, dotPos), s.substr(dotPos + 1)};
}

// Evaluate expression on a Row
// Supports: "p.age", "30", "p.age > 30"
Value evaluate(const Row& row, const string& expr) {
    // 1. Check if it's a binary comparison
    size_t gtPos = expr.find('>');
    size_t eqPos = expr.find('=');
    
    // Handle ">"
    if (gtPos != string::npos) {
        string leftStr = expr.substr(0, gtPos);
        string rightStr = expr.substr(gtPos + 1);
        
        // Trim whitespace and parentheses
        auto trim = [](string s) {
            s.erase(0, s.find_first_not_of(" \t\n\r()"));
            s.erase(s.find_last_not_of(" \t\n\r()") + 1);
            return s;
        };
        leftStr = trim(leftStr);
        rightStr = trim(rightStr);

        Value leftVal = evaluate(row, leftStr);
        Value rightVal = evaluate(row, rightStr);
        
        return Value(leftVal > rightVal);
    }

    // Handle "="
    if (eqPos != string::npos) {
        string leftStr = expr.substr(0, eqPos);
        string rightStr = expr.substr(eqPos + 1);
        
        auto trim = [](string s) {
            s.erase(0, s.find_first_not_of(" \t\n\r()"));
            s.erase(s.find_last_not_of(" \t\n\r()") + 1);
            return s;
        };
        leftStr = trim(leftStr);
        rightStr = trim(rightStr);

        Value leftVal = evaluate(row, leftStr);
        Value rightVal = evaluate(row, rightStr);

        // Simple equality check
        if (holds_alternative<int>(leftVal.data) && holds_alternative<int>(rightVal.data)) {
            return Value(get<int>(leftVal.data) == get<int>(rightVal.data));
        }
        if (holds_alternative<string>(leftVal.data) && holds_alternative<string>(rightVal.data)) {
            return Value(get<string>(leftVal.data) == get<string>(rightVal.data));
        }
        return Value(false);
    }

    // 2. Handle literals
    if (isdigit(expr[0])) {
        return Value(stoi(expr));
    }
    if (expr[0] == '"') {
       return Value(expr.substr(1, expr.size() - 2));
    }
    
    // 3. Handle Variable/Property access
    auto [varName, propName] = parseVarProp(expr);
    
    // Check if variable exists in row
    if (row.values.find(varName) != row.values.end()) {
        const Value& val = row.values.at(varName);
        
        // If it's a Node (stored as generic Value?), we need to access property
        // But Value currently uses variant<...>. 
        // We need to store Node* in Value to access properties dynamically.
        // OR, for this tasks simplicity, we can just say "p.age" is looked up directly in row?
        // But IndexScan puts a "Node" object effectively.
        // Let's cheat slightly: Row stores "p" -> NodeImpl* (as void* or something?)
        // OR we just store all properties of the node into the row flattened: "p.age", "p.name".
        // Flattening is easiest for now without complex Type system.
        
        // BUT, Project might ask for "p".
        // Let's support both:
        // IndexScan loads: "p" -> NodeID(int), "p.age"->30, "p.name"->"Alice" into the row.
        
        string fullKey = varName;
        if (!propName.empty()) {
             fullKey = varName + "." + propName;
        }
        
        if (row.values.count(fullKey)) {
            return row.values.at(fullKey);
        }
    }
    
    // Fallback/Error
    return Value();
}


// --- MemoryIndexScan ---

void MemoryIndexScan::open() {
    nodes = graph.getNodesByLabel(label);
    currentIndex = 0;
    // cout << "IndexScan opened. Found " << nodes.size() << " nodes for label " << label << endl;
}

bool MemoryIndexScan::next(Row& row) {
    if (currentIndex >= nodes.size()) return false;
    
    // Load current node into row
    auto node = nodes[currentIndex];
    currentIndex++;
    
    // Populate row with node properties flattened
    // AND the node reference itself (simulated by ID + all props)
    
    // 1. Variable itself and .id
    row.values[variable] = Value(node->id); 
    row.values[variable + ".id"] = Value(node->id); 
    
    // 2. Properties
    for (auto& prop : node->properties) {
        row.values[variable + "." + prop.first] = prop.second;
    }
    
    return true;
}

void MemoryIndexScan::close() {
    nodes.clear();
}


// --- MemoryEdgeScan ---

void MemoryEdgeScan::open() {
    edges = graph.getEdgesByLabel(label);
    currentIndex = 0;
}

bool MemoryEdgeScan::next(Row& row) {
    if (currentIndex >= edges.size()) return false;
    
    auto edge = edges[currentIndex];
    currentIndex++;
    
    // Populate row with edge properties
    row.values[variable] = Value(edge->id);
    row.values[variable + ".id"] = Value(edge->id);
    row.values[variable + "._source"] = Value(edge->sourceId);
    row.values[variable + "._target"] = Value(edge->targetId);
    
    // Support non-underscored for join conditions if needed
    row.values[variable + ".source"] = Value(edge->sourceId);
    row.values[variable + ".target"] = Value(edge->targetId);
    
    for (auto& prop : edge->properties) {
        row.values[variable + "." + prop.first] = prop.second;
    }
    
    return true;
}

void MemoryEdgeScan::close() {
    edges.clear();
}


// --- MemoryFilter ---

void MemoryFilter::open() {
    child->open();
}

bool MemoryFilter::next(Row& row) {
    while (child->next(row)) {
        // Evaluate condition
        Value result = evaluate(row, condition);
        if (holds_alternative<bool>(result.data) && get<bool>(result.data)) {
            return true;
        }
    }
    return false;
}

void MemoryFilter::close() {
    child->close();
}


// --- MemoryProject ---

void MemoryProject::open() {
    child->open();
}

bool MemoryProject::next(Row& row) {
    if (!child->next(row)) return false;
    
    Row projectedRow;
    for (const string& field : fields) {
        Value val = evaluate(row, field);
        projectedRow.values[field] = val;
    }
    
    row = projectedRow;
    return true;
}

void MemoryProject::close() {
    child->close();
}

// --- MemoryNestedLoopJoin ---

void MemoryNestedLoopJoin::open() {
    left->open();
    leftFinished = false;
    rightOpen = false;
}

bool MemoryNestedLoopJoin::next(Row& row) {
    while (true) {
        if (!rightOpen) {
            if (!left->next(currentLeftRow)) {
                return false;
            }
            right->open();
            rightOpen = true;
        }

        Row rightRow;
        if (right->next(rightRow)) {
            Row combinedRow = currentLeftRow;
            for (auto& pair : rightRow.values) {
                combinedRow.values[pair.first] = pair.second;
            }

            if (condition.empty()) {
                 row = combinedRow;
                 return true;
            }

            Value res = evaluate(combinedRow, condition);
            if (holds_alternative<bool>(res.data) && get<bool>(res.data)) {
                row = combinedRow;
                return true;
            }
        } else {
            right->close();
            rightOpen = false;
        }
    }
}

void MemoryNestedLoopJoin::close() {
    left->close();
    if (rightOpen) {
        right->close();
        rightOpen = false;
    }
}
