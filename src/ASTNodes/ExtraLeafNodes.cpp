#include "ExtraLeafNodes.h"
#include "ASTPass.h"

namespace gazprea {

IdentityNode::IdentityNode() { token_ = Token::IDENTITY; };

Symbol IdentityNode::visit(ASTPass *pass) {
  return pass->visitIdentityNode(this);
}

NullNode::NullNode() { token_ = Token::NULL_TOKEN; };

Symbol NullNode::visit(ASTPass *pass) { return pass->visitNullNode(this); }

BreakNode::BreakNode() { token_ = Token::BREAK; };

Symbol BreakNode::visit(ASTPass *pass) { return pass->visitBreakNode(this); }

ContinueNode::ContinueNode() { token_ = Token::CONTINUE; };

Symbol ContinueNode::visit(ASTPass *pass) {
  return pass->visitContinueNode(this);
}

ReturnNode::ReturnNode() { token_ = Token::RETURN; };

ReturnNode::ReturnNode(std::unique_ptr<AST> return_value) {
  token_ = Token::RETURN;
  return_value_ = std::move(return_value);
};

Symbol ReturnNode::visit(ASTPass *pass) { return pass->visitReturnNode(this); }

} // namespace gazprea
