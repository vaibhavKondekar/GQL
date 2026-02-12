# Logical Plan - Complete Explanation (Simple Words)

## 🎯 What is Logical Plan?

**Logical Plan = High-level operations (WHAT to do, not HOW)**

Think of it like this:
- **AST** = "What did the user write?" (syntax structure)
- **Logical Plan** = "What operations do we need?" (high-level operations)
- **Physical Plan** = "How exactly will we do it?" (implementation details)

### Example:

**Query:**
```gql
MATCH (p:Person) WHERE p.age > 30 RETURN p.name
```

**AST says:**
- There's a MATCH statement
- There's a node pattern (p:Person)
- There's a WHERE clause
- There's a RETURN statement

**Logical Plan says:**
```
Project([name])          ← Select the "name" field
  Filter(age > 30)       ← Keep only rows where age > 30
    NodeScan(Person)     ← Scan all Person nodes
```

This is a **tree structure** - data flows from bottom to top:
1. Start: Scan all Person nodes
2. Filter: Keep only those with age > 30
3. Project: Return only the "name" field

---

## 📁 Files Created and What They Do

### 1. `LogicalPlanNodes.h` - Define All Operations

**Purpose:** Defines all possible operations in a logical plan

**What's inside:**
- **Base class** `LogicalPlanNode` - parent of all operations
- **Specific operations:**
  - `NodeScanNode` - Scan nodes by label (e.g., scan all Person nodes)
  - `EdgeScanNode` - Scan edges by label (e.g., scan all ACTED_IN edges)
  - `FilterNode` - Filter rows based on condition (e.g., WHERE clause)
  - `ProjectNode` - Select specific fields (e.g., RETURN clause)
  - `JoinNode` - Join two data sources
  - `AggregateNode` - Group by and aggregate (COUNT, SUM, etc.)
  - `SortNode` - Sort results
  - `LimitNode` / `OffsetNode` - Pagination
  - `UnionNode` - Union of queries
  - `DeleteOpNode` / `InsertOpNode` - Data modification

**Simple explanation:**
This file is like a **menu** - it lists all the operations we can use, but doesn't do anything yet.

---

### 2. `LogicalPlanNodes.cpp` - Implement Visitor Pattern

**Purpose:** Implements the visitor pattern for logical plan nodes

**What's inside:**
- `accept()` methods for each node type
- These methods call the visitor's corresponding method

**Simple explanation:**
This is like a **receptionist** - when someone visits a node, it directs them to the right place.

**Example:**
```cpp
void NodeScanNode::accept(LogicalPlanVisitor* visitor) {
    visitor->visitNodeScan(this);  // "Hey visitor, come visit this NodeScan!"
}
```

---

### 3. `LogicalPlanBuilder.h` - Interface for AST → Logical Plan Conversion

**Purpose:** Declares the class that converts AST to Logical Plan

**What's inside:**
- `LogicalPlanBuilder` class (extends `ASTVisitor`)
- Methods to visit AST nodes and build logical plan:
  - `visitMatchStatement()` - Convert MATCH to logical plan
  - `visitNodePattern()` - Convert node pattern to NodeScan
  - `visitEdgePattern()` - Convert edge pattern to EdgeScan
  - `visitWhereClause()` - Convert WHERE to Filter
  - `visitReturnStatement()` - Convert RETURN to Project
  - `build()` - Main entry point

**Simple explanation:**
This is like a **translator** - it knows how to translate AST language to Logical Plan language.

---

### 4. `LogicalPlanBuilder.cpp` - Implementation of AST → Logical Plan Conversion

**Purpose:** Actually converts AST nodes to Logical Plan nodes

**How it works:**

#### Step 1: `build()` - Entry Point
```cpp
std::unique_ptr<LogicalPlanNode> build(QueryNode* astRoot) {
    // Start with empty plan
    currentPlan = nullptr;
    
    // Visit AST root - this triggers all other visits
    astRoot->accept(this);
    
    // Return the built logical plan
    return std::move(currentPlan);
}
```

#### Step 2: `visitQuery()` - Find MATCH Statement
```cpp
void visitQuery(QueryNode* n) {
    // Look for MATCH statement in children
    for (auto& child : n->children) {
        if (child->type == ASTNode::MATCH_STATEMENT) {
            child->accept(this);  // Visit the MATCH statement
            break;
        }
    }
}
```

#### Step 3: `visitMatchStatement()` - Build Logical Plan Tree

This is the **main conversion logic**:

```cpp
void visitMatchStatement(MatchStatementNode* n) {
    std::unique_ptr<LogicalPlanNode> plan;
    
    // STEP 1: Build NodeScan from node patterns
    for (auto& pattern : n->patterns) {
        if (pattern->type == ASTNode::NODE_PATTERN) {
            pattern->accept(this);  // This calls visitNodePattern()
            // visitNodePattern() sets currentPlan to NodeScan
            plan = std::move(currentPlan);
            break;  // Only handle first node for now
        }
    }
    
    // STEP 2: Add Filter if WHERE exists
    if (n->whereClause) {
        auto filter = std::make_unique<FilterNode>();
        // Put the scan as child of filter
        filter->children.push_back(std::move(plan));
        plan = std::move(filter);  // Filter is now on top
    }
    
    // STEP 3: Add Project if RETURN exists
    if (n->returnStatement) {
        auto project = std::make_unique<ProjectNode>();
        // Extract field names from RETURN
        // ... (extract fields)
        // Put filter as child of project
        project->children.push_back(std::move(plan));
        plan = std::move(project);  // Project is now on top
    }
    
    currentPlan = std::move(plan);  // Save the final plan
}
```

**Visual Flow:**
```
AST: MatchStatement
  ↓
visitMatchStatement() called
  ↓
1. Visit NodePattern → NodeScan created
  ↓
2. If WHERE exists → Filter created, NodeScan becomes its child
  ↓
3. If RETURN exists → Project created, Filter becomes its child
  ↓
Result: Project → Filter → NodeScan (tree structure)
```

#### Step 4: `visitNodePattern()` - Create NodeScan
```cpp
void visitNodePattern(NodePatternNode* n) {
    auto nodeScan = std::make_unique<NodeScanNode>();
    nodeScan->variable = n->variable;  // e.g., "p"
    nodeScan->label = n->labels[0];  // e.g., "Person"
    currentPlan = std::move(nodeScan);  // Save it
}
```

**Simple explanation:**
- Takes node pattern `(p:Person)` from AST
- Creates `NodeScan(Person, var=p)` in logical plan

#### Step 5: `visitWhereClause()` - Currently Empty
```cpp
void visitWhereClause(WhereClauseNode* n) {
    // For now, just placeholder
    // Full implementation would build expression tree
}
```

#### Step 6: `visitReturnStatement()` - Currently Empty
```cpp
void visitReturnStatement(ReturnStatementNode* n) {
    // Already handled in visitMatchStatement()
}
```

**Simple explanation:**
This file is the **actual translator** - it reads AST and writes Logical Plan.

---

### 5. `LogicalPlanPrinter.h` - Interface for Printing

**Purpose:** Declares the class that prints logical plan

**What's inside:**
- `LogicalPlanPrinter` class (extends `LogicalPlanVisitor`)
- Methods to visit and print each node type
- `print()` - Main entry point

**Simple explanation:**
This is like a **display screen** - it shows the logical plan in a readable format.

---

### 6. `LogicalPlanPrinter.cpp` - Implementation of Printing

**Purpose:** Actually prints the logical plan tree

**How it works:**

#### Example: Printing NodeScan
```cpp
void visitNodeScan(NodeScanNode* n) {
    printIndent();  // Add spaces for indentation
    std::cout << "NodeScan(" << n->label;
    if (!n->variable.empty()) {
        std::cout << ", var=" << n->variable;
    }
    std::cout << ")\n";
    
    // Visit children (recursive)
    indent++;
    for (auto& child : n->children) {
        child->accept(this);  // Print children too
    }
    indent--;
}
```

**Output example:**
```
Project([name])
  Filter(condition)
    NodeScan(Person, var=p)
```

**Simple explanation:**
This file is the **printer** - it walks through the logical plan tree and prints it nicely.

---

## 🔄 Complete Flow: How Everything Works Together

### Step-by-Step Process:

1. **User writes query:**
   ```gql
   MATCH (p:Person) WHERE p.age > 30 RETURN p.name
   ```

2. **Parser creates Parse Tree** (ANTLR)
   - Grammar structure

3. **ASTBuilder creates AST** (already done)
   ```
   Query
     MatchStatement
       NodePattern: p:Person
       WhereClause
       ReturnStatement
   ```

4. **LogicalPlanBuilder converts AST → Logical Plan:**
   - `build()` called with AST root
   - `visitQuery()` finds MATCH statement
   - `visitMatchStatement()` builds plan:
     - Calls `visitNodePattern()` → creates NodeScan
     - If WHERE exists → creates Filter, puts NodeScan as child
     - If RETURN exists → creates Project, puts Filter as child
   - Returns logical plan tree

5. **LogicalPlanPrinter prints the plan:**
   - Visits each node
   - Prints with indentation
   - Shows tree structure

### Visual Flow:

```
Query Text
  ↓
Parse Tree (ANTLR)
  ↓
AST (ASTBuilder)
  ↓
Logical Plan (LogicalPlanBuilder) ← WE BUILT THIS
  ↓
Printed Output (LogicalPlanPrinter)
```

---

## 📊 What's Working vs What's Missing

### ✅ What's Working (Implemented):

1. **Single Node Pattern** → NodeScan
   - `(p:Person)` → `NodeScan(Person, var=p)`

2. **WHERE Clause** → Filter
   - `WHERE condition` → `Filter(condition)`

3. **RETURN Statement** → Project
   - `RETURN p.name` → `Project([name])`

4. **Tree Structure** → Correctly builds bottom-up
   - Project on top
   - Filter in middle
   - NodeScan at bottom

### ❌ What's Missing (Not Implemented):

1. **Multiple Patterns** → No Join operations
   - `(p:Person)-[:ACTED_IN]->(m:Movie)` → Only first node processed

2. **Edge Patterns** → EdgeScan created but not used
   - Edge patterns exist in code but not connected to joins

3. **Expression Trees** → Conditions stored as text
   - `p.age > 30` → Stored as string, not proper tree

4. **DELETE/INSERT** → Not converted to logical plan
   - DELETE statements not converted to DeleteOp

5. **Aggregates** → COUNT, SUM, etc. not handled
   - `RETURN COUNT(p)` → Not converted to Aggregate

6. **Sorting/Pagination** → ORDER BY, LIMIT, OFFSET not handled

---

## 🎓 Simple Analogy for Your Professor

**Think of it like a restaurant:**

1. **AST (Abstract Syntax Tree)** = Customer's order written down
   - "I want pizza, but only vegetarian, and bring me the menu"

2. **Logical Plan** = Kitchen's work plan
   - Step 1: Get all pizzas (Scan)
   - Step 2: Filter vegetarian ones (Filter)
   - Step 3: Show only menu items (Project)

3. **Physical Plan** = Actual cooking steps
   - Use oven at 400°F
   - Check ingredients in fridge
   - Use specific cooking time

**Our Logical Plan Builder:**
- Reads the customer's order (AST)
- Creates a kitchen work plan (Logical Plan)
- Doesn't care HOW to cook (that's Physical Plan)

---

## 📝 Summary for Presentation

**What we built:**
- A system that converts AST (syntax) to Logical Plan (operations)
- Currently handles: Single node patterns, WHERE clauses, RETURN statements
- Creates a tree structure showing operations from bottom to top

**How it works:**
1. ASTBuilder creates AST from parse tree
2. LogicalPlanBuilder visits AST nodes
3. For each AST node, creates corresponding logical plan node
4. Connects them in a tree (children = data sources)
5. LogicalPlanPrinter displays the tree

**What's next:**
- Handle multiple patterns (joins)
- Build proper expression trees
- Add more operations (aggregates, sorting, etc.)

---

## 🔍 Key Concepts to Remember

1. **Logical Plan = WHAT operations** (not HOW)
2. **Tree structure** = Data flows from bottom to top
3. **Visitor pattern** = Way to traverse and convert nodes
4. **Bottom-up construction** = Start with scans, build up to projections

---

## 📖 Example Query That Works

**Query:**
```gql
MATCH (p:Person) WHERE p.age > 30 RETURN p.name
```

**Logical Plan Generated:**
```
Project([name])
  Filter(condition)
    NodeScan(Person, var=p)
```

**Why this works:**
- ✅ Single node pattern (only one node)
- ✅ WHERE clause exists
- ✅ RETURN statement exists
- ✅ All three operations are implemented

**Why your test.gql doesn't work fully:**
- ❌ Multiple nodes (p and f) - only first processed
- ❌ Edge pattern - not converted to join
- ❌ DELETE - not converted to DeleteOp

---

This explanation should help you understand and explain to your professor! 🎓

