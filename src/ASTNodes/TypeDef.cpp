#include "TypeDef.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

TypeDef::TypeDef() : AST() { token_ = Token::TYPEDEF; }

TypeDef::TypeDef(std::string id, std::unique_ptr<AST> base_type) : AST() {
  token_ = Token::TYPEDEF;
  id_ = id;
  base_type_ = std::move(base_type);
}

void TypeDef::setId(std::string id) { id_ = id; }

void TypeDef::setBaseType(std::unique_ptr<AST> base_type) {
  base_type_ = std::move(base_type);
}

Symbol TypeDef::visit(ASTPass *pass) { return pass->visitTypeDef(this); }

} // namespace gazprea