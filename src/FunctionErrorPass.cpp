#include "FunctionErrorPass.h"
#include "Exceptions.h"

namespace gazprea {
Symbol FunctionErrorPass::visitBinaryExpr(BinaryExpr *node) {
  in_binary_expression_ = true;
  ASTPass::visitBinaryExpr(node);
  in_binary_expression_ = false;
  return {};
}

Symbol FunctionErrorPass::visitBlock(Block *node) {
  std::vector<Symbol> returns;
  for (auto &i : node->statements_) {
    returns.push_back(i->visit(this));
  }

  if (std::any_of(returns.begin(), returns.end(),
                  [](Symbol s) { return (bool)s; })) {
    return {Type::IDENTITY};
  }
  return {};
}

Symbol FunctionErrorPass::visitConditionStatement(ConditionStatement *node) {
  node->condition_expr_->visit(this);
  auto true_ret = node->true_block_->visit(this);
  if (!node->false_block_) {
    return {};
  }
  auto false_ret = node->false_block_->visit(this);

  if (true_ret || false_ret) {
    return {Type::IDENTITY};
  }
  return {};
}

Symbol FunctionErrorPass::visitReturnNode(ReturnNode *node) {
  ASTPass::visitReturnNode(node);
  return {Type::IDENTITY};
}

Symbol FunctionErrorPass::visitFileNode(FileNode *node) {
  global_scope_ = Scope::scopes_.at(node->node_id_);
  return ASTPass::visitFileNode(node);
}

Symbol FunctionErrorPass::visitBuiltInCall(BuiltInCall *node) {
  if (node->token_ == Token::STREAM_STATE) {
    if (!in_procedure_ || in_binary_expression_) {
      throw InvalidProcedureCall(node->node_line_);
    }
  } else {
    if (!in_function_ && !in_procedure_) {
      throw InvalidFunctionCall(node->node_line_);
    }
  }
  return {};
}

Symbol FunctionErrorPass::visitFunctionCallNode(FunctionCallNode *node) {
  auto function = global_scope_->resolve(node->id_);
  if (function.type_ == Type::FUNCTION) {
    if (!in_function_ && !in_procedure_) {
      throw InvalidFunctionCall(node->node_line_);
    }
  } else if (function.type_ == Type::PROCEDURE) {
    if (!in_procedure_ || in_binary_expression_) {
      throw InvalidProcedureCall(node->node_line_);
    }
  }
  return {};
}

Symbol FunctionErrorPass::visitFunctionDeclNode(FunctionDeclNode *node) {
  if (node->body_ == nullptr || node->body_->token_ != Token::BLOCK) {
    return {};
  }
  in_function_ = true;
  auto return_symbol = node->body_->visit(this);
  if (!return_symbol) {
    throw MissingReturn(node->node_line_);
  }
  in_function_ = false;
  return {};
}

Symbol FunctionErrorPass::visitProcedureDecl(ProcedureDecl *node) {
  if (node->body_ == nullptr || node->body_->token_ != Token::BLOCK) {
    return {};
  }
  in_procedure_ = true;
  auto function = global_scope_->resolve(node->id_);
  auto return_symbol = node->body_->visit(this);
  if (!return_symbol && function.return_type_ != Type::NONE) {

    throw MissingReturn(node->node_line_);
  }
  in_procedure_ = false;
  return {};
}

Symbol FunctionErrorPass::visitStream(Stream *node) {
  if (in_function_) {
    throw IoInFunction(node->node_line_);
  }
  return ASTPass::visitStream(node);
}
} // namespace gazprea
