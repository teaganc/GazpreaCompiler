#pragma once

#include <memory>
#include <vector>

#include "AST.h"

namespace gazprea {

class BuiltInCall : public AST {
public:
  std::string id_;
  std::unique_ptr<AST> arg_;
  Type return_type_;

  BuiltInCall();

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea