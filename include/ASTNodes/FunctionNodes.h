#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>
#include <string>
#include <vector>

namespace gazprea {
class FunctionCallNode : public AST {
public:
  std::string id_;
  std::vector<std::unique_ptr<AST>> args_;

  FunctionCallNode();
  FunctionCallNode(std::string id);
  FunctionCallNode(std::string id, std::vector<std::unique_ptr<AST>> args);

  void addArg(std::unique_ptr<AST> arg);

  virtual Symbol visit(ASTPass *pass) override;
};

class FunctionParamNode : public AST {
public:
  std::string id_;
  std::unique_ptr<AST> type_;

  FunctionParamNode();
  FunctionParamNode(std::string id, std::unique_ptr<AST> type);

  void setId(std::string id);
  void setType(std::unique_ptr<AST> type);

  virtual Symbol visit(ASTPass *pass) override;
};

class FunctionDeclNode : public AST {
public:
  std::string id_;
  std::vector<std::unique_ptr<FunctionParamNode>> params_;
  std::unique_ptr<AST> body_;
  std::unique_ptr<AST> return_type_;

  FunctionDeclNode();
  FunctionDeclNode(std::string id, std::unique_ptr<AST> body,
                   std::unique_ptr<AST> return_type);
  FunctionDeclNode(std::string id,
                   std::vector<std::unique_ptr<FunctionParamNode>> params,
                   std::unique_ptr<AST> body, std::unique_ptr<AST> return_type);

  void setId(std::string id);
  void addParam(std::unique_ptr<FunctionParamNode> param);
  void setBody(std::unique_ptr<AST> body);
  void setReturnType(std::unique_ptr<AST> return_type);

  virtual Symbol visit(ASTPass *pass) override;
};
} // namespace gazprea