#pragma once

#include "AST.h"
#include "ProcedureParam.h"
#include "Token.h"

#include <memory>
#include <string>
#include <vector>

namespace gazprea {

class ProcedureDecl : public AST {
public:
  std::string id_;            // Identifier expression for the procedure name
  std::unique_ptr<AST> body_; // The block node
  std::unique_ptr<AST> return_type_;                    // The return type
  std::vector<std::unique_ptr<ProcedureParam>> params_; // Procedure parameters

  ProcedureDecl();
  ProcedureDecl(std::string id, std::unique_ptr<AST> body);
  ProcedureDecl(std::string id, std::unique_ptr<AST> body,
                std::unique_ptr<AST> return_type);

  void setId(std::string id);
  void setBody(std::unique_ptr<AST> body);
  void setReturnType(std::unique_ptr<AST> return_type);
  void addParam(std::unique_ptr<ProcedureParam> param);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea