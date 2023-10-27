#include "Loop.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

Loop::Loop() : AST() {}

Loop::Loop(Token token) : AST() { token_ = token; }

Loop::Loop(Token token, std::unique_ptr<AST> block) : AST() {
  token_ = token;
  block_ = std::move(block);
}

Loop::Loop(std::unique_ptr<AST> predicate_expr, std::unique_ptr<AST> block)
    : AST() {
  token_ = Token::PRED_LOOP;
  predicate_expr_ = std::move(predicate_expr);
  block_ = std::move(block);
}

void Loop::addDomain(std::unique_ptr<DomainExpr> domain) {
  domains_.push_back(std::move(domain));
}

void Loop::setBlock(std::unique_ptr<AST> block) { block_ = std::move(block); }

void Loop::setPredicateExpr(std::unique_ptr<AST> predicate_expr) {
  predicate_expr_ = std::move(predicate_expr);
}

Symbol Loop::visit(ASTPass *pass) { return pass->visitLoop(this); }

} // namespace gazprea
