#include "BinaryExpr.h"
#include "ASTPass.h"

namespace gazprea {

BinaryExpr::BinaryExpr(){};

BinaryExpr::BinaryExpr(Token token, std::unique_ptr<AST> left_sub_expr,
                       std::unique_ptr<AST> right_sub_expr) {
  token_ = token;
  left_sub_expr_ = std::move(left_sub_expr);
  right_sub_expr_ = std::move(right_sub_expr);
};

Symbol BinaryExpr::visit(ASTPass *pass) { return pass->visitBinaryExpr(this); }

} // namespace gazprea
