#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>

namespace gazprea {

class TypeCast : public AST {
public:
  std::unique_ptr<AST> value_;       // Value to typecast
  std::unique_ptr<AST> target_type_; // Type to cast to

  TypeCast();
  TypeCast(std::unique_ptr<AST> value, std::unique_ptr<AST> target_type);

  void setValue(std::unique_ptr<AST> value);
  void setTargetType(std::unique_ptr<AST> target_type);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea