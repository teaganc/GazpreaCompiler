#pragma once

#include "AST.h"
#include "Token.h"
#include <memory>

namespace gazprea {

class ConditionStatement : public AST {
public:
  std::unique_ptr<AST> condition_expr_;
  std::unique_ptr<AST> true_block_;
  std::unique_ptr<AST> false_block_;

  ConditionStatement();
  // if statement only
  ConditionStatement(std::unique_ptr<AST> expr,
                     std::unique_ptr<AST> true_block);
  // Condition statement with "else if" or "else" clauses
  ConditionStatement(std::unique_ptr<AST> expr, std::unique_ptr<AST> true_block,
                     std::unique_ptr<AST> false_block);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea
