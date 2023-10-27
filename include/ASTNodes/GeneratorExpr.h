#pragma once

#include "AST.h"
#include "DomainExpr.h"
#include "Token.h"

#include <memory>
#include <vector>

namespace gazprea {

class GeneratorExpr : public AST {
public:
  std::vector<std::unique_ptr<DomainExpr>> domains_;
  std::unique_ptr<AST> main_expr_;

  GeneratorExpr();

  GeneratorExpr(std::vector<std::unique_ptr<DomainExpr>> domains,

                std::unique_ptr<AST> main_expr);

  void addDomain(std::unique_ptr<DomainExpr> domain);
  void setMainExpr(std::unique_ptr<AST> expr);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea