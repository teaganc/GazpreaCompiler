#pragma once

#include "AST.h"
#include "Qualifier.h"
#include "Token.h"

#include <memory>
#include <string>

namespace gazprea {

class DeclareStatement : public AST {
public:
  std::string id_;
  std::unique_ptr<AST> type_;
  std::unique_ptr<AST> main_expr_;
  Qualifier qualifier_ =
      Qualifier::VAR; // the qualifier of the parameter (VAR or CONST)

  DeclareStatement();
  DeclareStatement(std::string id, std::unique_ptr<AST> type,
                   std::unique_ptr<AST> main_expr, Qualifier qualifier);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea
