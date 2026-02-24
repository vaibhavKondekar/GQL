#include "ExecutionBuilder.h"
#include <iostream>

unique_ptr<PhysicalOperator> ExecutionBuilder::build(PhysicalPlanNode* plan) {
    if (!plan) return nullptr;
    
    // Recursive build
    unique_ptr<PhysicalOperator> childOp = nullptr;
    if (!plan->children.empty()) {
        childOp = build(plan->children[0].get());
    }
    
    switch (plan->type) {
        case PhysicalOperatorType::MEM_SCAN_INDEX: {
            // Need to cast to specific node type to access fields
            // Assuming PhysicalIndexScan is defined in PhysicalPlan.h
            // But PhysicalPlanNode only has virtual toString. 
            // We need to cast.
            auto scanNode = dynamic_cast<PhysicalIndexScan*>(plan);
            if (scanNode) {
                return make_unique<MemoryIndexScan>(graph, scanNode->label, scanNode->variable);
            }
            break;
        }
        case PhysicalOperatorType::MEM_FILTER: {
            auto filterNode = dynamic_cast<PhysicalFilter*>(plan);
            if (filterNode && childOp) {
                return make_unique<MemoryFilter>(move(childOp), filterNode->conditionDescription);
            }
            break;
        }
        case PhysicalOperatorType::MEM_PROJECT: {
            auto projectNode = dynamic_cast<PhysicalProject*>(plan);
            if (projectNode && childOp) {
                return make_unique<MemoryProject>(move(childOp), projectNode->fields);
            }
            break;
        }
        default:
            cerr << "Unsupported physical operator type in execution builder: " << (int)plan->type << endl;
            return nullptr;
    }
    return nullptr;
}
