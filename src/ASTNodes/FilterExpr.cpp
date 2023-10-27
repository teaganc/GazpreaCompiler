#include "FilterExpr.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

FilterExpr::FilterExpr() : AST() { token_ = Token::FILTER_EXPR; }

FilterExpr::FilterExpr(std::unique_ptr<DomainExpr> domain) : AST() {
  token_ = Token::FILTER_EXPR;
  domain_ = std::move(domain);
}

void FilterExpr::setDomain(std::unique_ptr<DomainExpr> domain) {
  domain_ = std::move(domain);
}

void FilterExpr::addSubExpr(std::unique_ptr<AST> sub_expr) {
  sub_exprs_.push_back(std::move(sub_expr));
}

Symbol FilterExpr::visit(ASTPass *pass) { return pass->visitFilterExpr(this); }

} // namespace gazprea