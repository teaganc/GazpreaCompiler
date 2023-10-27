#include "DomainExpr.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

DomainExpr::DomainExpr() : AST() { token_ = Token::DOMAIN_EXPR; }

DomainExpr::DomainExpr(std::string id, std::unique_ptr<AST> mainExpr) : AST() {
  token_ = Token::DOMAIN_EXPR;
  id_ = id;
  main_expr_ = std::move(mainExpr);
}

void DomainExpr::setId(std::string id) { id_ = id; }

void DomainExpr::setMainExpr(std::unique_ptr<AST> mainExpr) {
  main_expr_ = std::move(mainExpr);
}

Symbol DomainExpr::visit(ASTPass *pass) { return pass->visitDomainExpr(this); }

} // namespace gazprea