#pragma once

#include "Symbol.h"
#include "Token.h"

namespace gazprea {

class ASTPass;

class AST {
public:
  // Base token
  Token token_;

  size_t node_id_;
  size_t node_line_;

  // Returns node type
  Token getNodeType() const;

  virtual Symbol visit(ASTPass *pass) = 0;
};

} // namespace gazprea