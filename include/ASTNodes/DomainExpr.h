#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>
#include <string>

namespace gazprea {

class DomainExpr : public AST {
public:
  std::string id_;                 // identifier
  std::unique_ptr<AST> main_expr_; // main sub-expression

  Symbol base_type_;

  DomainExpr();
  DomainExpr(std::string id, std::unique_ptr<AST> mainExpr);

  void setId(std::string id);
  void setMainExpr(std::unique_ptr<AST> mainExpr);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea