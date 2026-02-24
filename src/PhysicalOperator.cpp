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
    // 1. Check if it's a binary comparison (very simple: just > for now)
    size_t gtPos = expr.find('>');
    size_t eqPos = expr.find('='); // Add equality for better testing
    
    // Handle ">"
    if (gtPos != string::npos) {
        string leftStr = expr.substr(0, gtPos);
        string rightStr = expr.substr(gtPos + 1);
        
        // Trim whitespace
        leftStr.erase(0, leftStr.find_first_not_of(" \t\n\r()"));
        leftStr.erase(leftStr.find_last_not_of(" \t\n\r()") + 1);
        rightStr.erase(0, rightStr.find_first_not_of(" \t\n\r()"));
        rightStr.erase(rightStr.find_last_not_of(" \t\n\r()") + 1);

        Value leftVal = evaluate(row, leftStr);
        Value rightVal = evaluate(row, rightStr);
        
        return Value(leftVal > rightVal);
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
    
    // 1. Variable itself (maybe just ID for now)
    row.values[variable] = Value(node->id); 
    
    // 2. Properties
    for (auto& prop : node->properties) {
        row.values[variable + "." + prop.first] = prop.second;
    }
    
    return true;
}

void MemoryIndexScan::close() {
    nodes.clear();
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
    // 1. Get next row from child
    if (!child->next(row)) return false;
    
    // 2. Create new projected row
    // Actually, "next(Row&)" pattern usually means "fill this row".
    // But here we are modifying it or filtering it.
    // Ideally we should return a NEW row containing only projected fields.
    // But since `row` is passed by ref, we can just modify it in place or create a new one to return.
    // However, the caller passed `row` expecting it to be filled.
    // We should compute the projection based on the `row` we got from child.
    
    Row projectedRow;
    for (const string& field : fields) {
        // Evaluate field expression
        // Simple case: field is just "p.name"
        Value val = evaluate(row, field);
        projectedRow.values[field] = val;
    }
    
    // Replace original row with projected row
    row = projectedRow;
    return true;
}

void MemoryProject::close() {
    child->close();
}
