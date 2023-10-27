#include "ProcedureParam.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

ProcedureParam::ProcedureParam() : AST() { token_ = Token::PROC_PARAM; }

ProcedureParam::ProcedureParam(std::string id, std::unique_ptr<AST> type)
    : AST() {
  token_ = Token::PROC_PARAM;
  id_ = id;
  type_ = std::move(type);
}

ProcedureParam::ProcedureParam(std::string id, std::unique_ptr<AST> type,
                               Qualifier qualifier)
    : AST() {
  token_ = Token::PROC_PARAM;
  id_ = id;
  type_ = std::move(type);
  qualifier_ = qualifier;
}

void ProcedureParam::setId(std::string id) { id_ = id; }

void ProcedureParam::setType(std::unique_ptr<AST> type) {
  type_ = std::move(type);
}

void ProcedureParam::setQualifier(Qualifier qualifier) {
  qualifier_ = qualifier;
}

Symbol ProcedureParam::visit(ASTPass *pass) {
  return pass->visitProcedureParam(this);
}

} // namespace gazprea