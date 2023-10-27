#pragma once

#include <memory>
#include <string>
#include <vector>

#include "AST.h"

namespace gazprea {

class ProcedureCall : public AST {
public:
  std::string id_;
  std::vector<std::unique_ptr<AST>> args_;

  ProcedureCall();
  ProcedureCall(std::string id);
  ProcedureCall(std::string id, std::vector<std::unique_ptr<AST>> args);

  void addArg(std::unique_ptr<AST> arg);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea