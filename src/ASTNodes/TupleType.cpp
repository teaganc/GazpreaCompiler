#include "TupleType.h"
#include "ASTPass.h"

namespace gazprea {

TupleType::TupleType() { token_ = Token::TUPLE_TYPE; }

void TupleType::addType(std::unique_ptr<TupleMember> t) {
  types_.push_back(std::move(t));
}

Symbol TupleType::visit(ASTPass *pass) { return pass->visitTuple_type(this); }

TupleMember::TupleMember(std::unique_ptr<TypeNode> type) {
  type_ = std::move(type);
}

TupleMember::TupleMember(std::string id, std::unique_ptr<TypeNode> type) {
  id_ = id;
  type_ = std::move(type);
}

Symbol TupleMember::visit(ASTPass *pass) {
  return pass->visitTuple_member(this);
}

} // namespace gazprea