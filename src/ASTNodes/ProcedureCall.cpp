#include "ProcedureCall.h"
#include "ASTPass.h"

namespace gazprea {

ProcedureCall::ProcedureCall() { token_ = Token::PROC_CALL; }

ProcedureCall::ProcedureCall(std::string id) {
  token_ = Token::PROC_CALL;
  id_ = id;
}

ProcedureCall::ProcedureCall(std::string id,
                             std::vector<std::unique_ptr<AST>> args) {
  token_ = Token::PROC_CALL;
  id_ = id;
  args_ = std::move(args);
}

void ProcedureCall::addArg(std::unique_ptr<AST> arg) {
  args_.push_back(std::move(arg));
}

Symbol ProcedureCall::visit(ASTPass *pass) {
  return pass->visitProcedureCall(this);
}

} // namespace gazprea