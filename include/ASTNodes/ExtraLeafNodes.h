#pragma once

#include "AST.h"
#include "Token.h"
#include <memory>

namespace gazprea {

class IdentityNode : public AST {
public:
  IdentityNode();
  virtual Symbol visit(ASTPass *pass) override;
};

class NullNode : public AST {
public:
  NullNode();
  virtual Symbol visit(ASTPass *pass) override;
};

class BreakNode : public AST {
public:
  BreakNode();
  virtual Symbol visit(ASTPass *pass) override;
};

class ContinueNode : public AST {
public:
  ContinueNode();
  virtual Symbol visit(ASTPass *pass) override;
};

class ReturnNode : public AST {
public:
  std::unique_ptr<AST> return_value_;

  ReturnNode();
  ReturnNode(std::unique_ptr<AST> return_value);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea