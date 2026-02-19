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
            } else {
                cout << "(No physical plan generated)\n";
            }

        } else {
            cout << "(No logical plan generated)\n";
        }
    }

    return 0;
}

