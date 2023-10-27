#pragma once

#include "AST.h"
#include "ASTNodes/IdNode.h"
#include "Token.h"

#include <memory>
#include <string>

namespace gazprea {

class AssignStatement : public AST {
public:
  std::string
      id_; // TODO: remove this once all other classes upgrade to use lvalues
  std::vector<std::unique_ptr<IdNode>> lValues_;
  std::unique_ptr<AST> expr_;

  AssignStatement();
  AssignStatement(std::string id, std::unique_ptr<AST> expr);

  void setExpr(std::unique_ptr<AST> expr);
  void addLValue(std::unique_ptr<IdNode> lValue);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea