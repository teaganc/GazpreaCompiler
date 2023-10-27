#include "FunctionNodes.h"
#include "ASTPass.h"

namespace gazprea {

FunctionCallNode::FunctionCallNode() { token_ = Token::FUNC_CALL; }

FunctionCallNode::FunctionCallNode(std::string id) {
  token_ = Token::FUNC_CALL;
  id_ = id;
}

FunctionCallNode::FunctionCallNode(std::string id,
                                   std::vector<std::unique_ptr<AST>> args) {
  token_ = Token::FUNC_CALL;
  id_ = id;
  args_ = std::move(args);
}

void FunctionCallNode::addArg(std::unique_ptr<AST> arg) {
  args_.push_back(std::move(arg));
}

Symbol FunctionCallNode::visit(ASTPass *pass) {
  return pass->visitFunctionCallNode(this);
}

FunctionDeclNode::FunctionDeclNode() { token_ = Token::FUNC_DECL; }

FunctionDeclNode::FunctionDeclNode(std::string id, std::unique_ptr<AST> body,
                                   std::unique_ptr<AST> return_type) {
  token_ = Token::FUNC_DECL;
  id_ = id;
  body_ = std::move(body);
  return_type_ = std::move(return_type);
}

FunctionDeclNode::FunctionDeclNode(
    std::string id, std::vector<std::unique_ptr<FunctionParamNode>> params,
    std::unique_ptr<AST> body, std::unique_ptr<AST> return_type) {
  token_ = Token::FUNC_DECL;
  id_ = id;
  body_ = std::move(body);
  params_ = std::move(params);
  return_type_ = std::move(return_type);
}

void FunctionDeclNode::setId(std::string id) { id_ = id; }

void FunctionDeclNode::addParam(std::unique_ptr<FunctionParamNode> param) {
  params_.push_back(std::move(param));
}

void FunctionDeclNode::setBody(std::unique_ptr<AST> body) {
  body_ = std::move(body);
}

void FunctionDeclNode::setReturnType(std::unique_ptr<AST> return_type) {
  return_type_ = std::move(return_type);
}

Symbol FunctionDeclNode::visit(ASTPass *pass) {
  return pass->visitFunctionDeclNode(this);
}

FunctionParamNode::FunctionParamNode() { token_ = Token::FUNC_PARAM; }

FunctionParamNode::FunctionParamNode(std::string id,
                                     std::unique_ptr<AST> type) {
  token_ = Token::FUNC_PARAM;
  id_ = id;
  type_ = std::move(type);
}

void FunctionParamNode::setId(std::string id) { id_ = id; }

void FunctionParamNode::setType(std::unique_ptr<AST> type) {
  type_ = std::move(type);
}

Symbol FunctionParamNode::visit(ASTPass *pass) {
  return pass->visitFunctionParamNode(this);
}

} // namespace gazprea
