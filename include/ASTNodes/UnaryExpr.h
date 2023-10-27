#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>

namespace gazprea {

class UnaryExpr : public AST {
public:
  std::unique_ptr<AST> expr_;

  UnaryExpr();
  UnaryExpr(Token token, std::unique_ptr<AST> expr);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea