#include "ASTBuilder.h"
#include "AST.h"

#include "ASTNodes.h"

#include <cstring>
#include <memory>
#include <utility>

// TODO: REMOVE IOSTREAM
#include <iostream>

namespace gazprea {
std::any ASTBuilder::visitFile(GazpreaParser::FileContext *ctx) {
  FileNode *file_node = new FileNode();
  // Visit children
  for (auto *child : ctx->children) {
    file_node->addChild(
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(child))));
  }

  file_node->node_id_ = node_counter_++;
  file_node->node_line_ = ctx->getStart()->getLine();
  return file_node;
}

// Types
std::any ASTBuilder::visitQualifier(GazpreaParser::QualifierContext *ctx) {
  if (ctx->VAR())
    return Qualifier::VAR;
  else
    return Qualifier::CONST;
}

std::any ASTBuilder::visitSimple_type(GazpreaParser::Simple_typeContext *ctx) {
  TypeNode *type_node = new TypeNode(ctx->getText());

  type_node->node_id_ = node_counter_++;
  type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)type_node;
}

std::any ASTBuilder::visitString_type(GazpreaParser::String_typeContext *ctx) {
  TypeNode *string_type_node = new TypeNode(ctx->STRING()->getText());

  if (ctx->expr()) {
    string_type_node->size0_ = std::stoi(ctx->expr()->getText());

    // TODO: convert sizes to nodes
    // string_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
    // *>(visit(ctx->expr())));
  }

  string_type_node->node_id_ = node_counter_++;
  string_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)string_type_node;
}

std::any ASTBuilder::visitVector_type(GazpreaParser::Vector_typeContext *ctx) {
  TypeNode *vector_type_node =
      static_cast<TypeNode *>(std::any_cast<AST *>(visit(ctx->simple_type())));
  vector_type_node->type_ = Type::VECTOR;

  vector_type_node->size0_ = std::stoi(ctx->expr()->getText());
  // TODO: convert sizes to nodes
  // vector_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
  // *>(visit(ctx->expr())));

  vector_type_node->node_id_ = node_counter_++;
  vector_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)vector_type_node;
}

std::any ASTBuilder::visitMatrix_type(GazpreaParser::Matrix_typeContext *ctx) {
  TypeNode *matrix_type_node =
      static_cast<TypeNode *>(std::any_cast<AST *>(visit(ctx->simple_type())));
  matrix_type_node->type_ = Type::MATRIX;

  matrix_type_node->size0_ = std::stoi(ctx->expr(0)->getText());
  matrix_type_node->size1_ = std::stoi(ctx->expr(1)->getText());
  // TODO: convert sizes to nodes
  // matrix_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
  // *>(visit(ctx->expr(0)))); matrix_type_node->size1_ =
  // std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  matrix_type_node->node_id_ = node_counter_++;
  matrix_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)matrix_type_node;
}

std::any
ASTBuilder::visitTuple_member(GazpreaParser::Tuple_memberContext *ctx) {
  std::string id = "";
  if (ctx->IDENTIFIER()) {
    // gets IdNode, get the string
    id = ctx->IDENTIFIER()->getText();
  }

  TypeNode *type =
      static_cast<TypeNode *>(std::any_cast<AST *>(visit(ctx->type())));

  TupleMember *tuple_member =
      new TupleMember(id, std::unique_ptr<TypeNode>(type));

  tuple_member->node_id_ = node_counter_++;
  tuple_member->node_line_ = ctx->getStart()->getLine();
  return tuple_member;
}

std::any ASTBuilder::visitTuple_type(GazpreaParser::Tuple_typeContext *ctx) {
  TupleType *tuple_type = new TupleType();

  for (auto *tuple_member : ctx->tuple_member()) {
    tuple_type->addType(std::unique_ptr<TupleMember>(
        std::any_cast<TupleMember *>(visit(tuple_member))));
  }

  tuple_type->node_id_ = node_counter_++;
  tuple_type->node_line_ = ctx->getStart()->getLine();
  return (AST *)tuple_type;
}

std::any
ASTBuilder::visitInterval_type(GazpreaParser::Interval_typeContext *ctx) {
  TypeNode *internal_type_node = new TypeNode(ctx->INTERVAL()->getText());

  internal_type_node->node_id_ = node_counter_++;
  internal_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)internal_type_node;
}

std::any
ASTBuilder::visitVectorInferred(GazpreaParser::VectorInferredContext *ctx) {
  TypeNode *vector_type_node =
      static_cast<TypeNode *>(std::any_cast<AST *>(visit(ctx->simple_type())));
  vector_type_node->type_ = Type::VECTOR;

  vector_type_node->size0_ = -1lu;
  // TODO: convert sizes to nodes
  // vector_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
  // *>(visit(ctx->expr())));

  vector_type_node->node_id_ = node_counter_++;
  vector_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)vector_type_node;
}

std::any
ASTBuilder::visitMatrixInferred(GazpreaParser::MatrixInferredContext *ctx) {
  TypeNode *matrix_type_node =
      static_cast<TypeNode *>(std::any_cast<AST *>(visit(ctx->simple_type())));
  matrix_type_node->type_ = Type::MATRIX;

  matrix_type_node->size0_ = -1lu;
  matrix_type_node->size1_ = -1lu;
  // TODO: convert sizes to nodes
  // matrix_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
  // *>(visit(ctx->expr(0)))); matrix_type_node->size1_ =
  // std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  matrix_type_node->node_id_ = node_counter_++;
  matrix_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)matrix_type_node;
}

std::any ASTBuilder::visitMatrixFirstInferred(
    GazpreaParser::MatrixFirstInferredContext *ctx) {
  TypeNode *matrix_type_node =
      static_cast<TypeNode *>(std::any_cast<AST *>(visit(ctx->simple_type())));
  matrix_type_node->type_ = Type::MATRIX;

  matrix_type_node->size0_ = -1lu;
  matrix_type_node->size1_ = std::stoi(ctx->expr()->getText());
  // TODO: convert sizes to nodes
  // matrix_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
  // *>(visit(ctx->expr(0)))); matrix_type_node->size1_ =
  // std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  matrix_type_node->node_id_ = node_counter_++;
  matrix_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)matrix_type_node;
}

std::any ASTBuilder::visitMatrixSecondInferred(
    GazpreaParser::MatrixSecondInferredContext *ctx) {
  TypeNode *matrix_type_node =
      static_cast<TypeNode *>(std::any_cast<AST *>(visit(ctx->simple_type())));
  matrix_type_node->type_ = Type::MATRIX;

  matrix_type_node->size0_ = std::stoi(ctx->expr()->getText());
  matrix_type_node->size1_ = -1lu;
  // TODO: convert sizes to nodes
  // matrix_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
  // *>(visit(ctx->expr(0)))); matrix_type_node->size1_ =
  // std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  matrix_type_node->node_id_ = node_counter_++;
  matrix_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)matrix_type_node;
}

std::any
ASTBuilder::visitStringInferred(GazpreaParser::StringInferredContext *ctx) {
  TypeNode *string_type_node = new TypeNode(ctx->STRING()->getText());

  string_type_node->size0_ = -1lu;
  // TODO: convert sizes to nodes
  // string_type_node->size0_ = std::unique_ptr<AST>(std::any_cast<AST
  // *>(visit(ctx->expr())));

  string_type_node->node_id_ = node_counter_++;
  string_type_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)string_type_node;
}

// Statements
std::any ASTBuilder::visitTypedef(GazpreaParser::TypedefContext *ctx) {
  TypeDef *typedef_node = new TypeDef();

  // Set ID
  typedef_node->id_ = ctx->IDENTIFIER()->getText();

  // Set base type
  typedef_node->setBaseType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  typedef_node->node_id_ = node_counter_++;
  typedef_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)typedef_node;
}

std::any ASTBuilder::visitDeclare(GazpreaParser::DeclareContext *ctx) {
  DeclareStatement *decl_node = new DeclareStatement();

  // Set the qualifier, if applicable
  if (ctx->qualifier()) {
    decl_node->qualifier_ = std::any_cast<Qualifier>(visit(ctx->qualifier()));
  } else {
    decl_node->qualifier_ = Qualifier::VAR;
  }
  // Set type
  decl_node->type_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->sized_type())));

  // Set ID
  decl_node->id_ = ctx->IDENTIFIER()->getText();

  // Set expression, if applicable
  if (ctx->expr())
    decl_node->main_expr_ =
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  decl_node->node_id_ = node_counter_++;
  decl_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)decl_node;
}

std::any ASTBuilder::visitDeclareSize(GazpreaParser::DeclareSizeContext *ctx) {
  DeclareStatement *decl_node = new DeclareStatement();

  // Set the qualifier, if applicable
  if (ctx->qualifier())
    decl_node->qualifier_ = std::any_cast<Qualifier>(visit(ctx->qualifier()));

  // Set type
  decl_node->type_ = std::unique_ptr<AST>(
      std::any_cast<AST *>(visit(ctx->size_inferred_type())));

  // Set ID
  decl_node->id_ = ctx->IDENTIFIER()->getText();

  // Set expression
  decl_node->main_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  decl_node->node_id_ = node_counter_++;
  decl_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)decl_node;
}

std::any
ASTBuilder::visitDeclareInferred(GazpreaParser::DeclareInferredContext *ctx) {
  DeclareStatement *decl_node = new DeclareStatement();

  // Set the qualifier
  decl_node->qualifier_ = std::any_cast<Qualifier>(visit(ctx->qualifier()));

  // Set ID
  decl_node->id_ = ctx->IDENTIFIER()->getText();

  // Set expression
  decl_node->main_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  decl_node->node_id_ = node_counter_++;
  decl_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)decl_node;
}

std::any ASTBuilder::visitAssign(GazpreaParser::AssignContext *ctx) {
  AssignStatement *assign_node = new AssignStatement();

  // Get lvalues
  for (auto *lvalue : ctx->id()) {
    assign_node->addLValue(std::unique_ptr<IdNode>(
        static_cast<IdNode *>(std::any_cast<AST *>(visit(lvalue)))));
  }

  // Set expression
  assign_node->expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  assign_node->node_id_ = node_counter_++;
  assign_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)assign_node;
}

std::any ASTBuilder::visitConditional(GazpreaParser::ConditionalContext *ctx) {
  ConditionStatement *condition_node = new ConditionStatement();

  // Set expression
  condition_node->condition_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->comp())));

  // Set true block/statement
  condition_node->true_block_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block(0))));

  // Set false block/statement, if applicable
  if (ctx->block(1)) {
    condition_node->false_block_ =
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block(1))));
    condition_node->token_ = Token::IF_ELSE;
  }

  condition_node->node_id_ = node_counter_++;
  condition_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)condition_node;
}

std::any
ASTBuilder::visitLoopInfinite(GazpreaParser::LoopInfiniteContext *ctx) {
  Loop *loop_node = new Loop(Token::INF_LOOP);

  // Set block
  loop_node->block_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block())));

  loop_node->node_id_ = node_counter_++;
  loop_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)loop_node;
}

std::any
ASTBuilder::visitLoopPrePredicate(GazpreaParser::LoopPrePredicateContext *ctx) {
  Loop *loop_node = new Loop(Token::PRED_LOOP);

  // Set predicate expression
  loop_node->predicate_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->comp())));

  // Set block
  loop_node->block_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block())));

  loop_node->node_id_ = node_counter_++;
  loop_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)loop_node;
}

std::any ASTBuilder::visitLoopPostPredicate(
    GazpreaParser::LoopPostPredicateContext *ctx) {
  Loop *loop_node = new Loop(Token::POST_PRED_LOOP);

  // Set predicate expression
  loop_node->predicate_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->comp())));

  // Set block
  loop_node->block_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block())));

  loop_node->node_id_ = node_counter_++;
  loop_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)loop_node;
}

std::any
ASTBuilder::visitLoopIterator(GazpreaParser::LoopIteratorContext *ctx) {
  Loop *loop_node = new Loop(Token::ITER_LOOP);

  // Get domains
  for (auto *domain : ctx->domain()) {
    loop_node->addDomain(std::unique_ptr<DomainExpr>(
        static_cast<DomainExpr *>(std::any_cast<AST *>(visit(domain)))));
  }

  // Set block
  loop_node->block_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block())));

  loop_node->node_id_ = node_counter_++;
  loop_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)loop_node;
}

std::any ASTBuilder::visitBreaks(GazpreaParser::BreaksContext *ctx) {
  BreakNode *break_node = new BreakNode();
  break_node->node_id_ = node_counter_++;
  break_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)break_node;
}

std::any ASTBuilder::visitContinues(GazpreaParser::ContinuesContext *ctx) {
  ContinueNode *continue_node = new ContinueNode();
  continue_node->node_id_ = node_counter_++;
  continue_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)continue_node;
}

std::any
ASTBuilder::visitReturn_statement(GazpreaParser::Return_statementContext *ctx) {
  ReturnNode *return_node = new ReturnNode();

  // Add expression, if applicable
  if (ctx->expr())
    return_node->return_value_ =
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  return_node->node_id_ = node_counter_++;
  return_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)return_node;
}

std::any ASTBuilder::visitOutput(GazpreaParser::OutputContext *ctx) {
  Stream *stream_node = new Stream(Token::OUTSTREAM);

  // Add expression
  stream_node->stream_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  stream_node->node_id_ = node_counter_++;
  stream_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)stream_node;
}

std::any ASTBuilder::visitInput(GazpreaParser::InputContext *ctx) {
  Stream *stream_node = new Stream(Token::INSTREAM);

  // Add lvalue
  stream_node->stream_lvalue_ = std::unique_ptr<IdNode>(
      static_cast<IdNode *>(std::any_cast<AST *>(visit(ctx->id()))));

  stream_node->node_id_ = node_counter_++;
  stream_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)stream_node;
}

std::any ASTBuilder::visitBlock(GazpreaParser::BlockContext *ctx) {
  Block *block_node = new Block();

  for (auto *statement : ctx->children) {
    if (statement->getTreeType() == antlr4::tree::ParseTreeType::RULE) {
      block_node->addStatement(
          std::unique_ptr<AST>(std::any_cast<AST *>(visit(statement))));
    }
  }

  block_node->node_id_ = node_counter_++;
  block_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)block_node;
}

std::any ASTBuilder::visitDomain(GazpreaParser::DomainContext *ctx) {
  DomainExpr *domain_node = new DomainExpr();

  // Set id
  domain_node->id_ = ctx->IDENTIFIER()->getText();

  // Set expression
  domain_node->main_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  domain_node->node_id_ = node_counter_++;
  domain_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)domain_node;
}

// Functions
std::any
ASTBuilder::visitFunctionForward(GazpreaParser::FunctionForwardContext *ctx) {
  FunctionDeclNode *function_node = new FunctionDeclNode();

  // Add id
  function_node->id_ = ctx->IDENTIFIER()->getText();

  // Add parameters
  for (auto *param : ctx->function_param()) {
    function_node->addParam(std::unique_ptr<FunctionParamNode>(
        std::any_cast<FunctionParamNode *>(visit(param))));
  }

  // Add return type
  function_node->setReturnType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  function_node->node_id_ = node_counter_++;
  function_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)function_node;
}

std::any
ASTBuilder::visitFunctionSingle(GazpreaParser::FunctionSingleContext *ctx) {
  FunctionDeclNode *function_node = new FunctionDeclNode();

  // Add id
  function_node->id_ = ctx->IDENTIFIER()->getText();

  // Add parameters
  for (auto *param : ctx->function_param()) {
    function_node->addParam(std::unique_ptr<FunctionParamNode>(
        std::any_cast<FunctionParamNode *>(visit(param))));
  }

  // Add return type
  function_node->setReturnType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  // Add body
  function_node->setBody(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr()))));

  function_node->node_id_ = node_counter_++;
  function_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)function_node;
}

std::any
ASTBuilder::visitFunctionBlock(GazpreaParser::FunctionBlockContext *ctx) {
  FunctionDeclNode *function_node = new FunctionDeclNode();

  // Add id
  function_node->id_ = ctx->IDENTIFIER()->getText();

  // Add parameters
  for (auto *param : ctx->function_param()) {
    function_node->addParam(std::unique_ptr<FunctionParamNode>(
        std::any_cast<FunctionParamNode *>(visit(param))));
  }

  // Add return type
  function_node->setReturnType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  // Add body
  function_node->setBody(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block()))));

  function_node->node_id_ = node_counter_++;
  function_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)function_node;
}

std::any
ASTBuilder::visitFunction_param(GazpreaParser::Function_paramContext *ctx) {
  FunctionParamNode *param_node = new FunctionParamNode();

  // Get id
  param_node->id_ = ctx->IDENTIFIER()->getText();

  // Get type
  param_node->setType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  param_node->node_id_ = node_counter_++;
  param_node->node_line_ = ctx->getStart()->getLine();
  return param_node;
}

// Procedures
std::any
ASTBuilder::visitProcedureForward(GazpreaParser::ProcedureForwardContext *ctx) {
  ProcedureDecl *procedure_node = new ProcedureDecl();

  // Add id
  procedure_node->id_ = ctx->IDENTIFIER()->getText();

  // Add parameters
  for (auto *param : ctx->procedure_param()) {
    procedure_node->addParam(std::unique_ptr<ProcedureParam>(
        std::any_cast<ProcedureParam *>(visit(param))));
  }

  procedure_node->node_id_ = node_counter_++;
  procedure_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)procedure_node;
}

std::any ASTBuilder::visitProcedureFowardReturn(
    GazpreaParser::ProcedureFowardReturnContext *ctx) {
  ProcedureDecl *procedure_node = new ProcedureDecl();

  // Add id
  procedure_node->id_ = ctx->IDENTIFIER()->getText();

  // Add parameters
  for (auto *param : ctx->procedure_param()) {
    procedure_node->addParam(std::unique_ptr<ProcedureParam>(
        std::any_cast<ProcedureParam *>(visit(param))));
  }

  // Add return type
  procedure_node->setReturnType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  procedure_node->node_id_ = node_counter_++;
  procedure_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)procedure_node;
}

std::any ASTBuilder::visitProcedureNoReturn(
    GazpreaParser::ProcedureNoReturnContext *ctx) {
  ProcedureDecl *procedure_node = new ProcedureDecl();

  // Add id
  procedure_node->id_ = ctx->IDENTIFIER()->getText();

  // Add parameters
  for (auto *param : ctx->procedure_param()) {
    procedure_node->addParam(std::unique_ptr<ProcedureParam>(
        std::any_cast<ProcedureParam *>(visit(param))));
  }

  // Visit body
  procedure_node->setBody(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block()))));

  procedure_node->node_id_ = node_counter_++;
  procedure_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)procedure_node;
}

std::any
ASTBuilder::visitProcedureReturn(GazpreaParser::ProcedureReturnContext *ctx) {
  ProcedureDecl *procedure_node = new ProcedureDecl();

  // Add id
  procedure_node->id_ = ctx->IDENTIFIER()->getText();

  // Add parameters
  for (auto *param : ctx->procedure_param()) {
    procedure_node->addParam(std::unique_ptr<ProcedureParam>(
        std::any_cast<ProcedureParam *>(visit(param))));
  }

  // Visit body
  procedure_node->setBody(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->block()))));

  // Add return type
  procedure_node->setReturnType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  procedure_node->node_id_ = node_counter_++;
  procedure_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)procedure_node;
}

std::any
ASTBuilder::visitProcedure_param(GazpreaParser::Procedure_paramContext *ctx) {
  ProcedureParam *param_node = new ProcedureParam();

  // Get id
  param_node->id_ = ctx->IDENTIFIER()->getText();

  // Get type
  param_node->setType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->type()))));

  // Set qualifier, if applicable
  if (ctx->qualifier())
    param_node->setQualifier(std::any_cast<Qualifier>(visit(ctx->qualifier())));

  param_node->node_id_ = node_counter_++;
  param_node->node_line_ = ctx->getStart()->getLine();
  return param_node;
}

std::any ASTBuilder::visitProc_call(GazpreaParser::Proc_callContext *ctx) {
  if (ctx->STREAM_STATE()) {
    BuiltInCall *builtin_call_node = new BuiltInCall();

    // Get id
    builtin_call_node->id_ = ctx->STREAM_STATE()->getText();

    // Assign token
    builtin_call_node->token_ = Token::STREAM_STATE;

    builtin_call_node->node_id_ = node_counter_++;
    builtin_call_node->node_line_ = ctx->getStart()->getLine();
    return (AST *)builtin_call_node;
  }

  ProcedureCall *proc_call_node = new ProcedureCall();

  // Get id
  proc_call_node->id_ = ctx->IDENTIFIER()->getText();

  // Add arguments
  for (auto *expr : ctx->expr()) {
    proc_call_node->addArg(
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(expr))));
  }

  proc_call_node->node_id_ = node_counter_++;
  proc_call_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)proc_call_node;
}

// Expressions
std::any ASTBuilder::visitParenExpr(GazpreaParser::ParenExprContext *ctx) {
  return visit(ctx->expr());
}

std::any ASTBuilder::visitComp(GazpreaParser::CompContext *ctx) {
  return visit(ctx->expr());
}

std::any ASTBuilder::visitCast(GazpreaParser::CastContext *ctx) {
  TypeCast *typecast_node = new TypeCast();

  // Set expression
  typecast_node->setValue(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr()))));

  // Set target type
  typecast_node->setTargetType(
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->cast_type()))));

  typecast_node->node_id_ = node_counter_++;
  typecast_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)typecast_node;
}

std::any ASTBuilder::visitCall(GazpreaParser::CallContext *ctx) {
  if (ctx->IDENTIFIER()) {
    FunctionCallNode *call_node =
        new FunctionCallNode(ctx->IDENTIFIER()->getText());

    // Add arguments
    for (auto *expr : ctx->expr()) {
      call_node->addArg(
          std::unique_ptr<AST>(std::any_cast<AST *>(visit(expr))));
    }

    call_node->node_id_ = node_counter_++;
    call_node->node_line_ = ctx->getStart()->getLine();
    return (AST *)call_node;
  }

  BuiltInCall *builtin_call_node = new BuiltInCall();

  if (ctx->LENGTH()) {
    builtin_call_node->id_ = ctx->LENGTH()->getText();
    builtin_call_node->token_ = Token::LENGTH;
  } else if (ctx->ROWS()) {
    builtin_call_node->id_ = ctx->ROWS()->getText();
    builtin_call_node->token_ = Token::ROWS;
  } else if (ctx->COLUMNS()) {
    builtin_call_node->id_ = ctx->COLUMNS()->getText();
    builtin_call_node->token_ = Token::COLUMNS;
  } else if (ctx->REVERSE()) {
    builtin_call_node->id_ = ctx->REVERSE()->getText();
    builtin_call_node->token_ = Token::REVERSE;
  } else {
    builtin_call_node->id_ = ctx->STREAM_STATE()->getText();
    builtin_call_node->token_ = Token::STREAM_STATE;
  }

  // Add argument, if applicable
  if (ctx->expr(0)) {
    builtin_call_node->arg_ =
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(0))));
  }

  builtin_call_node->node_id_ = node_counter_++;
  builtin_call_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)builtin_call_node;
}

std::any ASTBuilder::visitBinaryExpr(GazpreaParser::BinaryExprContext *ctx) {
  BinaryExpr *binary_node = new BinaryExpr();

  // Get token
  if (ctx->EXP())
    binary_node->token_ = Token::EXP;
  else if (ctx->BY())
    binary_node->token_ = Token::BY;
  else if (ctx->AND())
    binary_node->token_ = Token::AND;
  else if (ctx->CAT())
    binary_node->token_ = Token::CAT;
  else if (ctx->op)
    binary_node->token_ = antlrToGazpreaToken(ctx->op->getType());

  // Add subexpressions
  binary_node->left_sub_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(0))));
  binary_node->right_sub_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  binary_node->node_id_ = node_counter_++;
  binary_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)binary_node;
}

std::any ASTBuilder::visitUnaryExpr(GazpreaParser::UnaryExprContext *ctx) {
  UnaryExpr *unary_node = new UnaryExpr();

  // Get token
  unary_node->token_ = antlrToGazpreaToken(ctx->op->getType());

  // Get expression
  unary_node->expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  unary_node->node_id_ = node_counter_++;
  unary_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)unary_node;
}

std::any
ASTBuilder::visitGeneratorExpr(GazpreaParser::GeneratorExprContext *ctx) {
  GeneratorExpr *generator_node = new GeneratorExpr();

  // Get domains
  for (auto *domain : ctx->domain()) {
    generator_node->addDomain(std::unique_ptr<DomainExpr>(
        static_cast<DomainExpr *>(std::any_cast<AST *>(visit(domain)))));
  }

  // Get expression
  generator_node->main_expr_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  generator_node->node_id_ = node_counter_++;
  generator_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)generator_node;
}

std::any ASTBuilder::visitFilterExpr(GazpreaParser::FilterExprContext *ctx) {
  FilterExpr *filter_node = new FilterExpr();

  // Get domain
  filter_node->domain_ = std::unique_ptr<DomainExpr>(
      static_cast<DomainExpr *>(std::any_cast<AST *>(visit(ctx->domain()))));

  // Get expressions
  for (auto *expr : ctx->expr()) {
    filter_node->addSubExpr(
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(expr))));
  }

  filter_node->node_id_ = node_counter_++;
  filter_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)filter_node;
}

// Ids
std::any ASTBuilder::visitVarId(GazpreaParser::VarIdContext *ctx) {
  IdNode *id_node = new IdNode();
  id_node->token_ = Token::ID_EXPR;

  // Get id
  std::string id = ctx->IDENTIFIER()->getText();
  id_node->id_name_ = id;

  id_node->node_id_ = node_counter_++;
  id_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)id_node;
}

std::any ASTBuilder::visitVectorId(GazpreaParser::VectorIdContext *ctx) {
  IdNode *id_node = new IdNode();
  id_node->token_ = Token::ID_VECTOR_INDEX;

  // Get id
  std::string id = ctx->IDENTIFIER()->getText();
  id_node->id_name_ = id;

  // Get index
  id_node->index0_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  id_node->node_id_ = node_counter_++;
  id_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)id_node;
}

std::any ASTBuilder::visitMatrixId(GazpreaParser::MatrixIdContext *ctx) {
  IdNode *id_node = new IdNode();
  id_node->token_ = Token::ID_MATRIX_INDEX;

  // Get id
  std::string id = ctx->IDENTIFIER()->getText();
  id_node->id_name_ = id;

  // Get indices
  id_node->index0_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(0))));
  id_node->index1_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  id_node->node_id_ = node_counter_++;
  id_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)id_node;
}

std::any ASTBuilder::visitTupleId(GazpreaParser::TupleIdContext *ctx) {
  IdNode *id_node = new IdNode();

  // Parse string
  std::stringstream text(ctx->TUPLE_ACCESS()->getText());
  std::string id;
  std::string index;
  std::getline(text, id, '.');
  std::getline(text, index, '.');

  id_node->id_name_ = id;

  try {
    id_node->int_index_ = std::stoul(index);
    id_node->token_ = Token::ID_TUPLE_INT_INDEX;
  } catch (std::invalid_argument &) {
    id_node->id_index_ = index;
    id_node->token_ = Token::ID_TUPLE_ID_INDEX;
  }

  id_node->node_id_ = node_counter_++;
  id_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)id_node;
}

std::any ASTBuilder::visitTupleVectorAccess(
    GazpreaParser::TupleVectorAccessContext *ctx) {
  IdNode *id_node = new IdNode();
  // Parse string
  std::stringstream text(ctx->TUPLE_ACCESS()->getText());
  std::string id;
  std::string index;
  std::getline(text, id, '.');
  std::getline(text, index, '.');

  id_node->id_name_ = id;

  try {
    id_node->int_index_ = std::stoul(index);
    id_node->token_ = Token::ID_TUPLE_INT_INDEX_VECTOR;
  } catch (std::invalid_argument &) {
    id_node->id_index_ = index;
    id_node->token_ = Token::ID_TUPLE_ID_INDEX_VECTOR;
  }

  // Get index
  id_node->index0_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr())));

  id_node->node_id_ = node_counter_++;
  id_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)id_node;
}

std::any ASTBuilder::visitTupleMatrixAccess(
    GazpreaParser::TupleMatrixAccessContext *ctx) {
  IdNode *id_node = new IdNode();

  // Parse string
  std::stringstream text(ctx->TUPLE_ACCESS()->getText());
  std::string id;
  std::string index;
  std::getline(text, id, '.');
  std::getline(text, index, '.');

  id_node->id_name_ = id;

  try {
    id_node->int_index_ = std::stoul(index);
    id_node->token_ = Token::ID_TUPLE_INT_INDEX_MATRIX;
  } catch (std::invalid_argument &) {
    id_node->id_index_ = index;
    id_node->token_ = Token::ID_TUPLE_ID_INDEX_MATRIX;
  }

  // Get indices
  id_node->index0_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(0))));
  id_node->index1_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  id_node->node_id_ = node_counter_++;
  id_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)id_node;
}

// Literals
std::any
ASTBuilder::visitIdentityLiteral(GazpreaParser::IdentityLiteralContext *ctx) {
  IdentityNode *identity_node = new IdentityNode();
  identity_node->node_id_ = node_counter_++;
  identity_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)identity_node;
}

std::any ASTBuilder::visitNullLiteral(GazpreaParser::NullLiteralContext *ctx) {
  NullNode *null_node = new NullNode();
  null_node->node_id_ = node_counter_++;
  null_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)null_node;
}

std::any ASTBuilder::visitIntLiteral(GazpreaParser::IntLiteralContext *ctx) {
  int value = std::stoi(ctx->getText());
  IntNode *int_node = new IntNode(value);
  int_node->node_id_ = node_counter_++;
  int_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)int_node;
}

std::any
ASTBuilder::visitIntervalLiteral(GazpreaParser::IntervalLiteralContext *ctx) {
  IntervalNode *interval_node = new IntervalNode();

  interval_node->lowerbound_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(0))));
  interval_node->upperbound_ =
      std::unique_ptr<AST>(std::any_cast<AST *>(visit(ctx->expr(1))));

  interval_node->node_id_ = node_counter_++;
  interval_node->node_line_ = ctx->getStart()->getLine();

  return (AST *)interval_node;
}

std::any
ASTBuilder::visitBoolean_literal(GazpreaParser::Boolean_literalContext *ctx) {
  BooleanNode *boolean_node;

  if (ctx->TRUE() != nullptr) {
    boolean_node = new BooleanNode(true);
  } else {
    boolean_node = new BooleanNode(false);
  }

  boolean_node->node_id_ = node_counter_++;
  boolean_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)boolean_node;
}

std::any ASTBuilder::visitCharacter_literal(
    GazpreaParser::Character_literalContext *ctx) {
  CharacterNode *character_node;
  // first get the value as a string
  std::string value_str = ctx->getText();

  // ignore first character [0], which is single quote '

  // if second character is a backslack \, that means the character is an escape
  // sequence
  if (value_str[1] == '\\') {
    // check third character if string matches one of the Gazprea supported
    // character escape sequences
    if (value_str[2] == '0') {
      character_node = new CharacterNode('\0');
    } else if (value_str[2] == 'a') {
      character_node = new CharacterNode('\a');
    } else if (value_str[2] == 'b') {
      character_node = new CharacterNode('\b');
    } else if (value_str[2] == 't') {
      character_node = new CharacterNode('\t');
    } else if (value_str[2] == 'n') {
      character_node = new CharacterNode('\n');
    } else if (value_str[2] == 'r') {
      character_node = new CharacterNode('\r');
    } else if (value_str[2] == '"') {
      character_node = new CharacterNode('\"');
    } else if (value_str[2] == 39) { // single quote
      character_node = new CharacterNode('\'');
    } else if (value_str[2] == 92) { // backslash
      character_node = new CharacterNode('\\');
    }
  } else { // any other character
    character_node = new CharacterNode(value_str[1]);
  }

  character_node->node_id_ = node_counter_++;
  character_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)character_node;
}

std::any
ASTBuilder::visitString_literal(GazpreaParser::String_literalContext *ctx) {
  std::string value = ctx->getText();

  // remove first and last quotation marks
  value.erase(value.begin(), value.begin() + 1);
  value.erase(value.end() - 1, value.end());

  StringNode *string_node = new StringNode(value);
  string_node->node_id_ = node_counter_++;
  string_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)string_node;
}

std::any
ASTBuilder::visitFloat_literal(GazpreaParser::Float_literalContext *ctx) {
  RealNode *real_node;
  std::string raw_str = ctx->getText();

  // if real number contains an exponent
  if (raw_str.find('e') != std::string::npos) {
    // split string by the "e" character to get the digits and the exponent
    char *ptr = std::strtok((char *)raw_str.c_str(), "e");
    float value = std::stof(ptr);
    ptr = std::strtok(NULL, "e");
    int exponent = std::stoi(ptr);
    // multiply number by the exponent
    value = value * pow(10, exponent);
    real_node = new RealNode(value);
  } else {
    float value = std::stof(ctx->getText());
    real_node = new RealNode(value);
  }

  real_node->node_id_ = node_counter_++;
  real_node->node_line_ = ctx->getStart()->getLine();
  return (AST *)real_node;
}

std::any
ASTBuilder::visitTuple_literal(GazpreaParser::Tuple_literalContext *ctx) {
  TupleNode *tuple_node = new TupleNode();

  for (auto *expr : ctx->expr()) {
    tuple_node->addValue(
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(expr))));
  }

  tuple_node->node_id_ = node_counter_++;
  tuple_node->node_line_ = ctx->getStart()->getLine();
  tuple_node->type_ = {Type::TUPLE};
  return (AST *)tuple_node;
}

std::any
ASTBuilder::visitVector_literal(GazpreaParser::Vector_literalContext *ctx) {
  VectorNode *vector_node = new VectorNode();

  for (auto *expr : ctx->expr()) {
    vector_node->addValue(
        std::unique_ptr<AST>(std::any_cast<AST *>(visit(expr))));
  }

  vector_node->node_id_ = node_counter_++;
  vector_node->node_line_ = ctx->getStart()->getLine();
  vector_node->type_ = {Type::VECTOR};
  return (AST *)vector_node;
}

// Helper
Token ASTBuilder::antlrToGazpreaToken(size_t antlrToken) {
  switch (antlrToken) {
  case GazpreaParser::ADD:
    return Token::ADD;
  case GazpreaParser::SUB:
    return Token::SUB;
  case GazpreaParser::NOT:
    return Token::NOT;
  case GazpreaParser::MUL:
    return Token::MUL;
  case GazpreaParser::DIV:
    return Token::DIV;
  case GazpreaParser::MOD:
    return Token::MOD;
  case GazpreaParser::DOT_PROD:
    return Token::DOT_PROD;
  case GazpreaParser::LT:
    return Token::LT;
  case GazpreaParser::GT:
    return Token::GT;
  case GazpreaParser::LE:
    return Token::LE;
  case GazpreaParser::GE:
    return Token::GE;
  case GazpreaParser::EQ:
    return Token::EQ;
  case GazpreaParser::NE:
    return Token::NE;
  case GazpreaParser::OR:
    return Token::OR;
  case GazpreaParser::XOR:
    return Token::XOR;
  default:
    return Token::NONE;
  }
}
} // namespace gazprea