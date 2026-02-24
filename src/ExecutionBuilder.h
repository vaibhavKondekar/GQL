#pragma once
#include "PhysicalPlan.h"
#include "PhysicalOperator.h"
#include "Graph.h"

// Builds the execution tree from the physical plan
class ExecutionBuilder {
    Graph& graph;
public:
    ExecutionBuilder(Graph& g) : graph(g) {}
    
    unique_ptr<PhysicalOperator> build(PhysicalPlanNode* plan);
};
