#pragma once

#include "AST.h"
#include "Token.h"
#include <memory>
#include <vector>

namespace gazprea {

class FileNode : public AST {
public:
  std::vector<std::unique_ptr<AST>> children_;

  FileNode();

  void addChild(std::unique_ptr<AST> child);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea