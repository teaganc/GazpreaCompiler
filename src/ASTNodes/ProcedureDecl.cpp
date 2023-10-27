#include "ProcedureDecl.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

ProcedureDecl::ProcedureDecl() : AST() { token_ = Token::PROC_DECL; }

ProcedureDecl::ProcedureDecl(std::string id, std::unique_ptr<AST> body)
    : AST() {
  token_ = Token::PROC_DECL;
  id_ = id;
  body_ = std::move(body);
}

ProcedureDecl::ProcedureDecl(std::string id, std::unique_ptr<AST> body,
                             std::unique_ptr<AST> return_type)
    : AST() {
  token_ = Token::PROC_DECL;
  id_ = id;
  body_ = std::move(body);
  return_type_ = std::move(return_type);
}

void ProcedureDecl::setId(std::string id) { id_ = id; }

void ProcedureDecl::setBody(std::unique_ptr<AST> body) {
  body_ = std::move(body);
}

void ProcedureDecl::setReturnType(std::unique_ptr<AST> return_type) {
  return_type_ = std::move(return_type);
}

void ProcedureDecl::addParam(std::unique_ptr<ProcedureParam> param) {
  params_.push_back(std::move(param));
}

Symbol ProcedureDecl::visit(ASTPass *pass) {
  return pass->visitProcedureDecl(this);
}

} // namespace gazprea