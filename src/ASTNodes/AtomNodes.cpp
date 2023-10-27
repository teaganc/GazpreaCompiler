#include "AtomNodes.h"
#include "ASTPass.h"
namespace gazprea {

IntNode::IntNode(int value) {
  token_ = Token::INT_ATOM;
  value_ = value;
}

Symbol IntNode::visit(ASTPass *pass) { return pass->visitIntNode(this); }

BooleanNode::BooleanNode(bool value) {
  token_ = Token::BOOLEAN_ATOM;
  value_ = value;
}

Symbol BooleanNode::visit(ASTPass *pass) {
  return pass->visitBooleanNode(this);
}

CharacterNode::CharacterNode(char value) {
  token_ = Token::CHAR_ATOM;
  value_ = value;
}

Symbol CharacterNode::visit(ASTPass *pass) {
  return pass->visitCharacterNode(this);
}

RealNode::RealNode(float value) {
  token_ = Token::REAL_ATOM;
  value_ = value;
}

Symbol RealNode::visit(ASTPass *pass) { return pass->visitRealNode(this); }

TupleNode::TupleNode() { token_ = Token::TUPLE_ATOM; }

void TupleNode::addValue(std::unique_ptr<AST> new_value) {
  values_.push_back(std::move(new_value));
}

Symbol TupleNode::visit(ASTPass *pass) { return pass->visitTupleNode(this); }

VectorNode::VectorNode() { token_ = Token::VECT_ATOM; }

void VectorNode::addValue(std::unique_ptr<AST> new_value) {
  values_.push_back(std::move(new_value));
}

Symbol VectorNode::visit(ASTPass *pass) { return pass->visitVectorNode(this); }

IntervalNode::IntervalNode() { token_ = Token::INTERVAL_ATOM; }

Symbol IntervalNode::visit(ASTPass *pass) {
  return pass->visitIntervalNode(this);
}

StringNode::StringNode(std::string value) {
  token_ = Token::STR_ATOM;
  value_ = value;
}

Symbol StringNode::visit(ASTPass *pass) { return pass->visitStringNode(this); }

} // namespace gazprea
