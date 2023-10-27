#include "TypeCast.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

TypeCast::TypeCast() : AST() { token_ = Token::TYPECAST; }

TypeCast::TypeCast(std::unique_ptr<AST> value, std::unique_ptr<AST> target_type)
    : AST() {
  token_ = Token::TYPECAST;
  value_ = std::move(value);
  target_type_ = std::move(target_type);
}

void TypeCast::setTargetType(std::unique_ptr<AST> target_type) {
  target_type_ = std::move(target_type);
}

void TypeCast::setValue(std::unique_ptr<AST> value) {
  value_ = std::move(value);
}

Symbol TypeCast::visit(ASTPass *pass) { return pass->visitTypeCast(this); }

} // namespace gazprea