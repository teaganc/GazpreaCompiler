#include "ASTPass.h"
#include "Exceptions.h"

namespace gazprea {

void ASTPass::run(AST *node) {
  begin();
  node->visit(this);
  end();
};

Symbol ASTPass::visitAssignStatement(AssignStatement *node) {
  for (auto &i : node->lValues_) {
    i->visit(this);
  }
  node->expr_->visit(this);
  return {};
}

Symbol ASTPass::visitIntNode(IntNode *node) { return {}; }

Symbol ASTPass::visitBooleanNode(BooleanNode *node) { return {}; }

Symbol ASTPass::visitCharacterNode(CharacterNode *node) { return {}; }

Symbol ASTPass::visitRealNode(RealNode *node) { return {}; }

Symbol ASTPass::visitTupleNode(TupleNode *node) {
  for (auto &child : node->values_) {
    child->visit(this);
  }
  return {};
}

Symbol ASTPass::visitVectorNode(VectorNode *node) {
  for (auto &child : node->values_) {
    child->visit(this);
  }
  return {};
}

Symbol ASTPass::visitIntervalNode(IntervalNode *node) {
  node->lowerbound_->visit(this);
  node->upperbound_->visit(this);
  return {};
}

Symbol ASTPass::visitStringNode(StringNode *node) { return {}; }

Symbol ASTPass::visitBinaryExpr(BinaryExpr *node) {
  node->left_sub_expr_->visit(this);
  node->right_sub_expr_->visit(this);
  return {};
}

Symbol ASTPass::visitBlock(Block *node) {
  for (auto &i : node->statements_) {
    i->visit(this);
  }
  return {};
}

Symbol ASTPass::visitBuiltInCall(BuiltInCall *node) {
  if (node->arg_)
    node->arg_->visit(this);
  return {};
}

Symbol ASTPass::visitConditionStatement(ConditionStatement *node) {
  node->condition_expr_->visit(this);
  node->true_block_->visit(this);
  if (node->false_block_)
    node->false_block_->visit(this);
  return {};
}

Symbol ASTPass::visitDeclareStatement(DeclareStatement *node) {
  if (node->main_expr_)
    node->main_expr_->visit(this);
  if (node->type_)
    node->type_->visit(this);
  return {};
}

Symbol ASTPass::visitDomainExpr(DomainExpr *node) {
  node->main_expr_->visit(this);
  return {};
}

Symbol ASTPass::visitIdentityNode(IdentityNode *node) { return {}; }

Symbol ASTPass::visitNullNode(NullNode *node) { return {}; }
Symbol ASTPass::visitBreakNode(BreakNode *node) { return {}; }

Symbol ASTPass::visitContinueNode(ContinueNode *node) { return {}; }

Symbol ASTPass::visitReturnNode(ReturnNode *node) {
  if (node->return_value_)
    node->return_value_->visit(this);
  return {};
}

Symbol ASTPass::visitFileNode(FileNode *node) {
  for (auto &child : node->children_) {
    child->visit(this);
  }
  return {};
}
Symbol ASTPass::visitFilterExpr(FilterExpr *node) {
  node->domain_->visit(this);
  for (auto &i : node->sub_exprs_) {
    i->visit(this);
  }
  return {};
}

Symbol ASTPass::visitFunctionCallNode(FunctionCallNode *node) {
  for (auto &i : node->args_) {
    i->visit(this);
  }
  return {};
}

Symbol ASTPass::visitFunctionDeclNode(FunctionDeclNode *node) {
  for (auto &i : node->params_) {
    i->visit(this);
  }
  node->return_type_->visit(this);
  if (node->body_)
    node->body_->visit(this);
  return {};
}

Symbol ASTPass::visitFunctionParamNode(FunctionParamNode *node) {
  node->type_->visit(this);
  return {};
}

Symbol ASTPass::visitGeneratorExpr(GeneratorExpr *node) {
  for (auto &i : node->domains_) {
    i->visit(this);
  }
  node->main_expr_->visit(this);
  return {};
}

Symbol ASTPass::visitIdNode(IdNode *node) {
  switch (node->token_) {
  case Token::ID_MATRIX_INDEX:
    node->index0_->visit(this);
    node->index1_->visit(this);
    break;
  case Token::ID_VECTOR_INDEX:
    node->index0_->visit(this);
    break;
  case Token::ID_TUPLE_ID_INDEX:
    break;
  case Token::ID_TUPLE_INT_INDEX_VECTOR:
    node->index0_->visit(this);
    break;
  case Token::ID_TUPLE_INT_INDEX_MATRIX:
    node->index0_->visit(this);
    node->index1_->visit(this);
    break;
  case Token::ID_TUPLE_INT_INDEX:
    break;
  case Token::ID_TUPLE_ID_INDEX_VECTOR:
    node->index0_->visit(this);
    break;
  case Token::ID_TUPLE_ID_INDEX_MATRIX:
    node->index0_->visit(this);
    node->index1_->visit(this);
    break;
  case Token::ID_EXPR:
    break;
  default:
    throw PanicError(); // Invalid lvalue type
  }
  return {};
}

Symbol ASTPass::visitLoop(Loop *node) {
  if (node->predicate_expr_) {
    node->predicate_expr_->visit(this);
  }
  for (auto &i : node->domains_) {
    i->visit(this);
  }
  node->block_->visit(this);
  return {};
}

Symbol ASTPass::visitProcedureCall(ProcedureCall *node) {
  for (auto &i : node->args_) {
    i->visit(this);
  }
  return {};
}

Symbol ASTPass::visitProcedureDecl(ProcedureDecl *node) {
  for (auto &i : node->params_) {
    i->visit(this);
  }
  if (node->return_type_)
    node->return_type_->visit(this);
  if (node->body_)
    node->body_->visit(this);
  return {};
}

Symbol ASTPass::visitProcedureParam(ProcedureParam *node) {
  node->type_->visit(this);
  return {};
}

Symbol ASTPass::visitStream(Stream *node) {
  switch (node->token_) {
  case Token::INSTREAM:
    node->stream_lvalue_->visit(this);
    break;
  case Token::OUTSTREAM:
    node->stream_expr_->visit(this);
    break;
  default:
    throw PanicError(); // Invalid stream type
  }
  return {};
}

Symbol ASTPass::visitTuple_member(TupleMember *node) {
  node->type_->visit(this);
  return {};
}

Symbol ASTPass::visitTuple_type(TupleType *node) {
  for (auto &i : node->types_) {
    i->visit(this);
  }
  return {};
}

Symbol ASTPass::visitTypeNode(TypeNode *node) { return {}; }

Symbol ASTPass::visitTypeCast(TypeCast *node) {
  node->value_->visit(this);
  node->target_type_->visit(this);
  return {};
}

Symbol ASTPass::visitTypeDef(TypeDef *node) {
  node->base_type_->visit(this);
  return {};
}

Symbol ASTPass::visitUnaryExpr(UnaryExpr *node) {
  node->expr_->visit(this);
  return {};
}

} // namespace gazprea