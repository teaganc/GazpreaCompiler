#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>
#include <string>
#include <vector>

namespace gazprea {

class IntNode : public AST {
public:
  int value_;

  IntNode(int value);

  virtual Symbol visit(ASTPass *pass) override;
};

class BooleanNode : public AST {
public:
  bool value_;

  BooleanNode(bool value);

  virtual Symbol visit(ASTPass *pass) override;
};

class CharacterNode : public AST {
public:
  char value_;

  CharacterNode(char value);

  virtual Symbol visit(ASTPass *pass) override;
};

class RealNode : public AST {
public:
  float value_;

  RealNode(float value);

  virtual Symbol visit(ASTPass *pass) override;
};

class TupleNode : public AST {
public:
  std::vector<std::unique_ptr<AST>> values_;
  Symbol type_;

  TupleNode();

  void addValue(std::unique_ptr<AST> new_value);

  virtual Symbol visit(ASTPass *pass) override;
};

class VectorNode : public AST {
public:
  std::vector<std::unique_ptr<AST>> values_;
  Symbol type_;

  VectorNode();

  void addValue(std::unique_ptr<AST> new_value);

  virtual Symbol visit(ASTPass *pass) override;
};

class IntervalNode : public AST {
public:
  std::unique_ptr<AST> lowerbound_;
  std::unique_ptr<AST> upperbound_;

  IntervalNode();

  virtual Symbol visit(ASTPass *pass) override;
};

class StringNode : public AST {
public:
  std::string value_;

  StringNode(std::string value);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea
