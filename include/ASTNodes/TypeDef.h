#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>
#include <string>

namespace gazprea {

class TypeDef : public AST {
public:
  std::string id_;                 // Identifier for the type name
  std::unique_ptr<AST> base_type_; // The base type

  TypeDef();
  TypeDef(std::string id, std::unique_ptr<AST> base_type);

  void setId(std::string id);
  void setBaseType(std::unique_ptr<AST> base_type);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea