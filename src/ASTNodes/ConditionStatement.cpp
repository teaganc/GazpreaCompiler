#include "ConditionStatement.h"
#include "ASTPass.h"

namespace gazprea {

ConditionStatement::ConditionStatement() { token_ = Token::IF; };

// if statement only
ConditionStatement::ConditionStatement(std::unique_ptr<AST> expr,
                                       std::unique_ptr<AST> true_block) {
  token_ = Token::IF;
  condition_expr_ = std::move(expr);
  true_block_ = std::move(true_block);
};

// Condition statement with "else if" or "else" clauses
ConditionStatement::ConditionStatement(std::unique_ptr<AST> expr,
                                       std::unique_ptr<AST> true_block,
                                       std::unique_ptr<AST> false_block) {
  token_ = Token::IF_ELSE;
  condition_expr_ = std::move(expr);
  true_block_ = std::move(true_block);
  false_block_ = std::move(false_block);
};

Symbol ConditionStatement::visit(ASTPass *pass) {
  return pass->visitConditionStatement(this);
}

} // namespace gazprea
