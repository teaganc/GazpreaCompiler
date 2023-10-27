#include "GeneratorExpr.h"
#include "ASTPass.h"

namespace gazprea {

GeneratorExpr::GeneratorExpr() { token_ = Token::GENERATOR; }

GeneratorExpr::GeneratorExpr(std::vector<std::unique_ptr<DomainExpr>> domains,
                             std::unique_ptr<AST> main_expr) {
  token_ = Token::GENERATOR;
  domains_ = std::move(domains);
  main_expr_ = std::move(main_expr);
}

void GeneratorExpr::addDomain(std::unique_ptr<DomainExpr> domain) {
  domains_.push_back(std::move(domain));
}

void GeneratorExpr::setMainExpr(std::unique_ptr<AST> expr) {
  main_expr_ = std::move(expr);
}

Symbol GeneratorExpr::visit(ASTPass *pass) {
  return pass->visitGeneratorExpr(this);
}

} // namespace gazprea
