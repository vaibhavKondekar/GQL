#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "Value.h"
#include "Graph.h"

using namespace std;

// Base Physical Operator
class PhysicalOperator {
public:
    virtual void open() = 0;
    virtual bool next(Row& row) = 0;
    virtual void close() = 0;
    virtual ~PhysicalOperator() = default;
};

// Memory Index Scan
class MemoryIndexScan : public PhysicalOperator {
private:
    Graph& graph;
    string label;
    string variable;
    vector<shared_ptr<Node>> nodes;
    size_t currentIndex = 0;

public:
    MemoryIndexScan(Graph& g, string l, string v) 
        : graph(g), label(l), variable(v) {}

    void open() override;
    bool next(Row& row) override;
    void close() override;
};

// Memory Edge Scan
class MemoryEdgeScan : public PhysicalOperator {
private:
    Graph& graph;
    string label;
    string variable;
    vector<shared_ptr<Edge>> edges;
    size_t currentIndex = 0;

public:
    MemoryEdgeScan(Graph& g, string l, string v) 
        : graph(g), label(l), variable(v) {}

    void open() override;
    bool next(Row& row) override;
    void close() override;
};

// Memory Filter
class MemoryFilter : public PhysicalOperator {
private:
    unique_ptr<PhysicalOperator> child;
    string condition; // "p.age > 30"

public:
    MemoryFilter(unique_ptr<PhysicalOperator> c, string cond) 
        : child(move(c)), condition(cond) {}

    void open() override;
    bool next(Row& row) override;
    void close() override;
};

// Memory Project
class MemoryProject : public PhysicalOperator {
private:
    unique_ptr<PhysicalOperator> child;
    vector<string> fields; // "p.name", "p.age"

public:
    MemoryProject(unique_ptr<PhysicalOperator> c, vector<string> f) 
        : child(move(c)), fields(f) {}

    void open() override;
    bool next(Row& row) override;
    void close() override;
};

// Memory Nested Loop Join
class MemoryNestedLoopJoin : public PhysicalOperator {
private:
    unique_ptr<PhysicalOperator> left;
    unique_ptr<PhysicalOperator> right;
    string condition;
    Row currentLeftRow;
    bool leftFinished = false;
    bool rightOpen = false;

public:
    MemoryNestedLoopJoin(unique_ptr<PhysicalOperator> l, unique_ptr<PhysicalOperator> r, string cond) 
        : left(move(l)), right(move(r)), condition(cond) {}

    void open() override;
    bool next(Row& row) override;
    void close() override;
};
