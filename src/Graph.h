#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Value.h"

using namespace std;

struct Node {
    int id;
    vector<string> labels;
    unordered_map<string, Value> properties;

    bool hasLabel(const string& label) const {
        for (const auto& l : labels) {
            if (l == label) return true;
        }
        return false;
    }
};

struct Edge {
    int id;
    int sourceId;
    int targetId;
    string label;
    unordered_map<string, Value> properties;
};

class Graph {
public:
    unordered_map<int, shared_ptr<Node>> nodes;
    unordered_map<int, shared_ptr<Edge>> edges;
    int nextNodeId = 1;
    int nextEdgeId = 1;

    // Indexes: Label -> [NodeId]
    unordered_map<string, vector<int>> labelIndex;

    void addNode(shared_ptr<Node> node) {
        nodes[node->id] = node;
        for (const auto& label : node->labels) {
            labelIndex[label].push_back(node->id);
        }
    }

    shared_ptr<Node> createNode(vector<string> labels, unordered_map<string, Value> props) {
        auto node = make_shared<Node>();
        node->id = nextNodeId++;
        node->labels = labels;
        node->properties = props;
        addNode(node);
        return node;
    }

    // scans
    vector<shared_ptr<Node>> getNodesByLabel(const string& label) {
        vector<shared_ptr<Node>> result;
        if (labelIndex.find(label) != labelIndex.end()) {
            for (int id : labelIndex[label]) {
                result.push_back(nodes[id]);
            }
        }
        return result;
    }
    
    vector<shared_ptr<Node>> getAllNodes() {
        vector<shared_ptr<Node>> result;
        for (auto& pair : nodes) {
            result.push_back(pair.second);
        }
        return result;
    }
};
