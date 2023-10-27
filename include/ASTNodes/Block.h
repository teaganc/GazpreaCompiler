#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>
#include <vector>

namespace gazprea {

class Block : public AST {
public:
  std::vector<std::unique_ptr<AST>> statements_; // statements in the block

  Block();

  void addStatement(std::unique_ptr<AST> statement);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea