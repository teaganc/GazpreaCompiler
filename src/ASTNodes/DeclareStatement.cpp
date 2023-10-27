#include "DeclareStatement.h"
#include "ASTPass.h"

namespace gazprea {

DeclareStatement::DeclareStatement() { token_ = Token::VAR_DECL; };

DeclareStatement::DeclareStatement(std::string id, std::unique_ptr<AST> type,
                                   std::unique_ptr<AST> main_expr,
                                   Qualifier qualifier) {
  token_ = Token::VAR_DECL;
  id_ = id;
  main_expr_ = std::move(main_expr);
  qualifier_ = qualifier;
};

Symbol DeclareStatement::visit(ASTPass *pass) {
  return pass->visitDeclareStatement(this);
}

} // namespace gazprea