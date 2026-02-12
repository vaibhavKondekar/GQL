# Logical Plan Generation Guide

## Overview

**Logical Plan** = High-level operations (WHAT to do, not HOW)

This guide shows how to convert AST → Logical Plan.

## Architecture

```
Query → AST → Logical Plan → Physical Plan → Execution
```

### Example Conversion

**Query:**
```gql
MATCH (p:Person) WHERE p.age > 30 RETURN p.name
```

**AST (Abstract Syntax Tree):**
```
Query
  MatchStatement
    NodePattern: p:Person
    WhereClause
      Expression: p.age > 30
    ReturnStatement
      Expression: p.name
```

**Logical Plan:**
```
Project([name])
  Filter(age > 30)
    NodeScan(Person, var=p)
```

## Files Created

### 1. `LogicalPlanNodes.h`
Defines all logical plan operator types:
- **NodeScan**: Scan nodes by label
- **EdgeScan**: Scan edges by label  
- **Filter**: Filter rows based on condition
- **Project**: Select specific fields
- **Join**: Join two data sources
- **Aggregate**: Group by and aggregate
- **Sort**: Sort results
- **Limit/Offset**: Pagination
- **Union**: Union of queries
- **DeleteOp/InsertOp**: Data modification

### 2. `LogicalPlanBuilder.h/cpp`
Converts AST → Logical Plan by:
- Visiting AST nodes (MatchStatement, NodePattern, etc.)
- Building corresponding logical plan nodes
- Connecting them in a tree structure

### 3. `LogicalPlanPrinter.h/cpp`
Pretty-prints the logical plan tree for visualization.

## How It Works

### Step 1: Build AST (already done)
```cpp
ASTBuilder builder;
auto ast = builder.build(parseTree);
```

### Step 2: Build Logical Plan from AST
```cpp
LogicalPlanBuilder planBuilder;
auto logicalPlan = planBuilder.build(ast.get());
```

### Step 3: Print Logical Plan
```cpp
LogicalPlanPrinter printer;
printer.print(logicalPlan.get());
```

## Conversion Rules

### MATCH Statement → Logical Plan

**Pattern:**
```gql
MATCH (p:Person) WHERE condition RETURN fields
```

**Logical Plan:**
```
Project(fields)
  Filter(condition)
    NodeScan(Person, var=p)
```

### Implementation in `LogicalPlanBuilder::visitMatchStatement()`

1. **Extract Node Patterns** → Create `NodeScanNode`
2. **Extract WHERE Clause** → Create `FilterNode` on top
3. **Extract RETURN** → Create `ProjectNode` on top

## Usage in main.cpp

```cpp
// After building AST
LogicalPlanBuilder planBuilder;
auto logicalPlan = planBuilder.build(ast.get());

if (logicalPlan) {
    LogicalPlanPrinter printer;
    printer.print(logicalPlan.get());
}
```

## Next Steps

1. **Enhance Expression Parsing**: Build proper expression trees for WHERE conditions
2. **Handle Joins**: Convert edge patterns to Join operations
3. **Add More Operators**: Aggregate, Sort, Limit, etc.
4. **Optimization**: Reorder operations for better performance
5. **Physical Plan**: Convert logical plan to physical execution plan

## Key Concepts

- **Logical Plan = WHAT operations** (not HOW)
- **Bottom-up construction**: Start with scans, build up to projections
- **Tree structure**: Each operator has children (data flows up)
- **Rule-based**: Independent of hardware/implementation details

