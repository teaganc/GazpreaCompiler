#include "TypeNode.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

TypeNode::TypeNode() : AST() { token_ = Token::TYPE; }

TypeNode::TypeNode(std::string id) : AST() {
  token_ = Token::TYPE;
  id_ = id;
}

TypeNode::TypeNode(std::string id, size_t first_dim) : AST() {
  token_ = Token::TYPE;
  id_ = id;
  size0_ = first_dim;
}

TypeNode::TypeNode(std::string id, size_t first_dim, size_t second_dim)
    : AST() {
  token_ = Token::TYPE;
  id_ = id;
  size0_ = first_dim;
  size1_ = second_dim;
}

void TypeNode::setId(std::string id) { id_ = id; }

void TypeNode::setSize(size_t first_dim) { size0_ = first_dim; }

void TypeNode::setSize(size_t first_dim, size_t second_dim) {
  size0_ = first_dim;
  size1_ = second_dim;
}

Symbol TypeNode::visit(ASTPass *pass) { return pass->visitTypeNode(this); }

} // namespace gazprea