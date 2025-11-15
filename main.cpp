#include <iostream>
#include <fstream>
#include <chrono>
#include "antlr4-runtime.h"
#include "GQLLexer.h"
#include "GQLParser.h"
#include "ASTBuilder.h"
#include "ASTPrinter.h"

using namespace antlr4;
using namespace std;
using namespace std::chrono;

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

    auto start = high_resolution_clock::now();

    ANTLRInputStream input(stream);
    GQLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    GQLParser parser(&tokens);

    // ✅ Correct type here
    GQLParser::GqlProgramContext* tree = parser.gqlProgram();

    auto parseEnd = high_resolution_clock::now();

    // ✅ Build AST correctly
    ASTBuilder builder;
    auto ast = builder.build(tree);
    auto astEnd = high_resolution_clock::now();

    cout << "\n==================== PARSE TREE ====================\n";
    cout << tree->toStringTree(&parser) << endl;

    cout << "\n==================== AST ====================\n";
    if (ast) {
        ASTPrinter printer;
        ast->accept(&printer);  // ✅ Correct visitor pattern
    } else {
        cout << "(No AST generated)\n";
    }

    auto end = high_resolution_clock::now();

    cout << "\n==================== TIMING ====================\n";
    cout << "Lexing + Parsing Time: " 
         << duration_cast<milliseconds>(parseEnd - start).count() << " ms\n";
    cout << "AST Construction Time: " 
         << duration_cast<milliseconds>(astEnd - parseEnd).count() << " ms\n";
    cout << "Total Execution Time:  " 
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}

