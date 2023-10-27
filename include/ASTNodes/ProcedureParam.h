#pragma once

#include "AST.h"
#include "Qualifier.h"
#include "Token.h"

#include <memory>
#include <string>

namespace gazprea {

class ProcedureParam : public AST {
public:
  std::string id_; // Identifier expression for the procedure parameter
  std::unique_ptr<AST> type_;              // Type of the parameter
  Qualifier qualifier_ = Qualifier::CONST; // Qualifier of the parameter

  ProcedureParam();
  ProcedureParam(std::string id, std::unique_ptr<AST> type);
  ProcedureParam(std::string id, std::unique_ptr<AST> type,
                 Qualifier qualifier);

  void setId(std::string id);
  void setType(std::unique_ptr<AST> type);
  void setQualifier(Qualifier qualifier);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea
