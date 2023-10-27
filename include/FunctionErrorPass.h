#pragma once

#include "ASTNodes.h"
#include "ASTPass.h"
#include "Scope.h"
#include "Symbol.h"
#include "Token.h"

namespace gazprea {

class FunctionErrorPass : public ASTPass {
  bool in_function_ = false;
  bool in_procedure_ = false;
  bool in_binary_expression_;

  Scope *global_scope_;

public:
  FunctionErrorPass() {}

  Symbol visitBinaryExpr(BinaryExpr *node) override;

  Symbol visitBlock(Block *node) override;
  Symbol visitConditionStatement(ConditionStatement *node) override;

  Symbol visitReturnNode(ReturnNode *node) override;
  Symbol visitFileNode(FileNode *node) override;

  Symbol visitBuiltInCall(BuiltInCall *node) override;
  Symbol visitFunctionCallNode(FunctionCallNode *node) override;
  Symbol visitFunctionDeclNode(FunctionDeclNode *node) override;

  Symbol visitProcedureDecl(ProcedureDecl *node) override;
  Symbol visitStream(Stream *node) override;
};
} // namespace gazprea
