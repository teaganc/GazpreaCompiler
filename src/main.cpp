#include <fstream>
#include <iostream>

#include "ANTLRFileStream.h"
#include "CommonTokenStream.h"
#include "GazpreaLexer.h"
#include "GazpreaParser.h"
#include "tree/ParseTree.h"
#include "tree/ParseTreeWalker.h"

#include "ASTBuilder.h"
#include "ASTNodes.h"
#include "CodeGenPass.h"
#include "DefRef.h"
#include "Exceptions.h"
#include "FunctionErrorPass.h"

class SyntaxErrorListener : public antlr4::BaseErrorListener {
  void syntaxError(antlr4::Recognizer *recognizer,
                   antlr4::Token *offendingSymbol, size_t line,
                   size_t charPositionInLine, const std::string &msg,
                   std::exception_ptr e) override {
    std::vector<std::string> rule_stack =
        ((antlr4::Parser *)recognizer)->getRuleInvocationStack();
    throw gazprea::SyntaxError(msg, line, charPositionInLine);
  }
};

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "Missing required argument.\n"
              << "Required arguments: <input file path> <output file path>\n";
    return 1;
  }

  // Open the file then parse and lex it.
  antlr4::ANTLRFileStream afs;
  afs.loadFromFile(argv[1]);
  gazprea::GazpreaLexer lexer(&afs);
  antlr4::CommonTokenStream tokens(&lexer);
  gazprea::GazpreaParser parser(&tokens);

  // Override errors
  parser.removeErrorListeners(); // Remove the default console error listener
  parser.addErrorListener(new SyntaxErrorListener()); // Add our error listener

  // Get the root of the parse tree. Use your base rule name.
  antlr4::tree::ParseTree *tree = parser.file();

  // Build AST

  // std::cerr << "Starting ASTBuilder\n";

  gazprea::ASTBuilder builder;
  gazprea::FileNode *ast =
      std::any_cast<gazprea::FileNode *>(builder.visit(tree));

  // std::cerr << "Starting defref\n";

  gazprea::DefRef defref;
  defref.run(ast);

  gazprea::FunctionErrorPass funcerrorpass;
  funcerrorpass.run(ast);

  // std::cerr << "Starting codegen\n";

  std::ofstream file(argv[2]);
  gazprea::CodeGenPass codegen(file);
  codegen.run(ast);

  // HOW TO USE A LISTENER
  // Make the listener
  // MyListener listener;
  // Walk the tree
  // antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

  // HOW TO USE A VISITOR
  // Make the visitor
  // MyVisitor visitor;
  // Visit the tree
  // visitor.visit(tree);

  // HOW TO WRITE OUT.
  // std::ofstream out(argv[2]);
  // out << "This is out...\n";

  return 0;
}
