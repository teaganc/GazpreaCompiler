#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>

namespace gazprea {

class BinaryExpr : public AST {
public:
  std::unique_ptr<AST> left_sub_expr_;
  std::unique_ptr<AST> right_sub_expr_;

  BinaryExpr();
  BinaryExpr(Token token, std::unique_ptr<AST> left_sub_expr,
             std::unique_ptr<AST> right_sub_expr);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea
