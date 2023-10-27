#pragma once

#include "AST.h"
#include "ASTNodes/IdNode.h"
#include "Token.h"

#include <memory>

namespace gazprea {

class Stream : public AST {
public:
  std::unique_ptr<AST> stream_expr_; // The expression to stream out
  std::string id_; // TODO: Remove this once all other classes use lvalues
  std::unique_ptr<IdNode> stream_lvalue_; // The l-value to stream into

  Stream(Token token);
  Stream(Token token, std::unique_ptr<AST> stream_expr);

  void setStreamExpr(std::unique_ptr<AST> stream_expr);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea