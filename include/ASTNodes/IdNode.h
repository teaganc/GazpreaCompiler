#pragma once

#include "AST.h"
#include "Token.h"

#include <string>

namespace gazprea {

class IdNode : public AST {
public:
  std::string id_name_;         // Identifier
  std::unique_ptr<AST> index0_; // id[x], id[x,_]
  std::unique_ptr<AST> index1_; // id[_, x]
  size_t int_index_;            // id.x, x is int
  std::string id_index_;        // id.x, x is identifer

  IdNode();

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea