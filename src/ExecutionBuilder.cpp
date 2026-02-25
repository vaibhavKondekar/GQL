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
            auto scanNode = dynamic_cast<PhysicalIndexScan*>(plan);
            if (scanNode) {
                return make_unique<MemoryIndexScan>(graph, scanNode->label, scanNode->variable);
            }
            break;
        }
        case PhysicalOperatorType::MEM_SCAN_EDGE: {
            auto scanNode = dynamic_cast<PhysicalEdgeScan*>(plan);
            if (scanNode) {
                return make_unique<MemoryEdgeScan>(graph, scanNode->label, scanNode->variable);
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
        case PhysicalOperatorType::MEM_NESTED_LOOP_JOIN: {
            auto joinNode = dynamic_cast<PhysicalNestedLoopJoin*>(plan);
            if (joinNode && plan->children.size() >= 2) {
                auto left = build(plan->children[0].get());
                auto right = build(plan->children[1].get());
                if (left && right) {
                    return make_unique<MemoryNestedLoopJoin>(move(left), move(right), joinNode->condition);
                }
            }
            break;
        }
        default:
            cerr << "Unsupported physical operator type in execution builder: " << (int)plan->type << endl;
            return nullptr;
    }
    return nullptr;
}
