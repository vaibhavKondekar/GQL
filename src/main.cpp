#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "GQLLexer.h"
#include "GQLParser.h"
#include "ASTBuilder.h"
#include "ASTPrinter.h"
#include "LogicalPlanBuilder.h"
#include "LogicalPlanPrinter.h"
#include "PhysicalPlanner.h"
#include "Value.h"
#include "Graph.h"
#include "PhysicalOperator.h"
#include "ExecutionBuilder.h"

using namespace antlr4;
using namespace std;

// Helper to escape strings for JSON
string jsonEscape(const string& s) {
    string res;
    for (char c : s) {
        if (c == '"') res += "\\\"";
        else if (c == '\\') res += "\\\\";
        else if (c == '\b') res += "\\b";
        else if (c == '\f') res += "\\f";
        else if (c == '\n') res += "\\n";
        else if (c == '\r') res += "\\r";
        else if (c == '\t') res += "\\t";
        else if (c >= 0 && c <= 0x1f) {
            // control characters (ignore or hex likely not needed for this simple case)
        } else {
            res += c;
        }
    }
    return res;
}

// Helper to escape strings for display
string escapeText(const string& s) {
    string res;
    for (char c : s) {
        if (c == '\n') res += "\\n";
        else if (c == '\r') res += "\\r";
        else if (c == '\t') res += "\\t";
        else res += c;
    }
    return res;
}

// Helper to print the parse tree in ASCII style
void printTree(antlr4::tree::ParseTree* t, antlr4::Parser* recognizer, string prefix = "", bool isLast = true) {
    // 1. Determine the name of the current node
    string nodeName;
    bool isRule = (dynamic_cast<antlr4::RuleContext*>(t) != nullptr);
    
    if (isRule) {
        antlr4::RuleContext* ctx = dynamic_cast<antlr4::RuleContext*>(t);
        size_t ruleIndex = ctx->getRuleIndex();
        const vector<string>& ruleNames = recognizer->getRuleNames();
        nodeName = (ruleIndex < ruleNames.size()) ? ruleNames[ruleIndex] : "UnknownRule";
    } else {
        string text = t->getText();
        if (text == "<EOF>") text = "EOF";
        nodeName = "'" + escapeText(text) + "'";
    }

    // 2. Print current node
    cout << prefix;
    cout << (isLast ? "└── " : "├── ");
    cout << nodeName << endl;

    // 3. Prepare prefix for children
    string childPrefix = prefix + (isLast ? "    " : "│   ");

    for (size_t i = 0; i < t->children.size(); i++) {
        printTree(t->children[i], recognizer, childPrefix, i == t->children.size() - 1);
    }
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input-file>" << endl;
        return 1;
    }

    ifstream stream(argv[1]);
    if (!stream.is_open()) {
        cerr << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    ANTLRInputStream input(stream);
    GQLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    GQLParser parser(&tokens);

    // ✅ Correct type here
    GQLParser::GqlProgramContext* tree = parser.gqlProgram();

    // ✅ Build AST correctly
    ASTBuilder builder;
    auto ast = builder.build(tree);

    cout << "\n==================== PARSE TREE ====================\n";
    if (tree) {
        printTree(tree, &parser);
    }
    cout << endl; // Extra newline at end 

    cout << "\n==================== AST ====================\n";
    if (ast) {
        ASTPrinter printer;
        ast->accept(&printer);  // ✅ Correct visitor pattern
    } else {
        cout << "(No AST generated)\n";
    }

    // ✅ Build Logical Plan from AST
    cout << "\n==================== LOGICAL PLAN ====================\n";
    if (ast) {
        LogicalPlanBuilder planBuilder;
        auto logicalPlan = planBuilder.build(ast.get());
        
        if (logicalPlan) {
            LogicalPlanPrinter planPrinter;
            planPrinter.print(logicalPlan.get());

            // ✅ Build Physical Plan from Logical Plan
            cout << "\n==================== PHYSICAL PLAN ====================\n";
            PhysicalPlanner phyPlanner;
            auto phyPlan = phyPlanner.build(logicalPlan.get());
            if (phyPlan) {
                phyPlan->print();

                // ✅ EXECUTION ENGINE
                cout << "\n==================== EXECUTION RESULTS ====================\n";
                
                // 1. Init Graph with Sample Data
                Graph graph;
                
                // Alice (25)
                graph.createNode({"Person"}, {
                    {"name", Value("Alice")},
                    {"age", Value(25)},
                    {"city", Value("New York")}
                });
                
                // Bob (35)
                graph.createNode({"Person"}, {
                    {"name", Value("Bob")},
                    {"age", Value(35)},
                    {"city", Value("San Francisco")}
                });
                
                // Charlie (40)
                graph.createNode({"Person"}, {
                    {"name", Value("Charlie")},
                    {"age", Value(40)},
                    {"city", Value("London")}
                });

                // David (30)
                graph.createNode({"Person"}, {
                    {"name", Value("David")},
                    {"age", Value(30)},
                    {"city", Value("Berlin")}
                });

                // Eve (22)
                graph.createNode({"Person"}, {
                    {"name", Value("Eve")},
                    {"age", Value(22)},
                    {"city", Value("Paris")}
                });

                // Frank (50)
                graph.createNode({"Person"}, {
                    {"name", Value("Frank")},
                    {"age", Value(50)},
                    {"city", Value("Tokyo")}
                });

                // Grace (28)
                graph.createNode({"Person"}, {
                    {"name", Value("Grace")},
                    {"age", Value(28)},
                    {"city", Value("Sydney")}
                });

                // Dave (Software, 35) - Test different label/properties
                graph.createNode({"Software"}, {
                    {"name", Value("GQE Engine")},
                    {"version", Value(1.0)},
                    {"developer", Value("Vaibhav")}
                });

                // Adding a Company node
                graph.createNode({"Company"}, {
                    {"name", Value("GraphCorp")},
                    {"location", Value("Remote")}
                });

                // 2. Build Execution Tree
                // ExecutionBuilder execBuilder(graph);
                ExecutionBuilder execBuilder(graph);
                unique_ptr<PhysicalOperator> rootOp = execBuilder.build(phyPlan.get());

                // 3. Run Pipeline
                if (rootOp) {
                    rootOp->open();
                    
                    Row row;
                    int rowCount = 0;
                    while (rootOp->next(row)) {
                        rowCount++;
                        cout << "Row " << rowCount << ": { ";
                        for (const auto& pair : row.values) {
                            cout << pair.first << ": " << pair.second.toString() << ", ";
                        }
                        cout << "}" << endl;
                    }
                    
                    rootOp->close();
                } else {
                    cout << "Failed to build execution tree." << endl;
                }

            } else {
                cout << "(No physical plan generated)\n";
            }

        } else {
            cout << "(No logical plan generated)\n";
        }
    }

    return 0;
}

