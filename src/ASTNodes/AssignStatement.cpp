#include "AssignStatement.h"
#include "ASTPass.h"

namespace gazprea {

AssignStatement::AssignStatement() { token_ = Token::ASSIGN; }

AssignStatement::AssignStatement(std::string id, std::unique_ptr<AST> expr) {
  token_ = Token::ASSIGN;
  id_ = id;
  expr_ = std::move(expr);
}

void AssignStatement::setExpr(std::unique_ptr<AST> new_expr) {
  expr_ = std::move(new_expr);
}

Symbol AssignStatement::visit(ASTPass *pass) {
  return pass->visitAssignStatement(this);
}

void AssignStatement::addLValue(std::unique_ptr<IdNode> lValue) {
  lValues_.push_back(std::move(lValue));
}

} // namespace gazprea
