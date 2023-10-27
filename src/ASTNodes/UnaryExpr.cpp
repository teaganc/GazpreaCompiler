#include "UnaryExpr.h"
#include "ASTPass.h"

namespace gazprea {

UnaryExpr::UnaryExpr() {}

UnaryExpr::UnaryExpr(Token token, std::unique_ptr<AST> expr) {
  token_ = token;
  expr_ = std::move(expr);
}

Symbol UnaryExpr::visit(ASTPass *pass) { return pass->visitUnaryExpr(this); }

} // namespace gazprea
