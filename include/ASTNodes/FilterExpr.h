#pragma once

#include "AST.h"
#include "DomainExpr.h"
#include "Token.h"

#include <memory>
#include <vector>

namespace gazprea {

class FilterExpr : public AST {
public:
  std::unique_ptr<DomainExpr> domain_; // domain expression
  std::vector<std::unique_ptr<AST>>
      sub_exprs_; // the sub-expressions to filter by

  FilterExpr();
  FilterExpr(std::unique_ptr<DomainExpr> domain);

  void setDomain(std::unique_ptr<DomainExpr> domain);
  void addSubExpr(std::unique_ptr<AST> sub_expr);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea
