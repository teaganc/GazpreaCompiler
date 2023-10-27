#pragma once

#include "GazpreaBaseVisitor.h"
#include "Token.h"
#include <string>
#include <unordered_map>

namespace gazprea {

class ASTBuilder : public GazpreaBaseVisitor {
public:
  size_t node_counter_ = 0;

  virtual std::any visitFile(GazpreaParser::FileContext *ctx) override;

  // Types
  virtual std::any
  visitQualifier(GazpreaParser::QualifierContext *ctx) override;
  virtual std::any
  visitSimple_type(GazpreaParser::Simple_typeContext *ctx) override;
  virtual std::any
  visitString_type(GazpreaParser::String_typeContext *ctx) override;
  virtual std::any
  visitVector_type(GazpreaParser::Vector_typeContext *ctx) override;
  virtual std::any
  visitMatrix_type(GazpreaParser::Matrix_typeContext *ctx) override;
  virtual std::any
  visitTuple_member(GazpreaParser::Tuple_memberContext *ctx) override;
  virtual std::any
  visitTuple_type(GazpreaParser::Tuple_typeContext *ctx) override;
  virtual std::any
  visitInterval_type(GazpreaParser::Interval_typeContext *ctx) override;
  virtual std::any
  visitVectorInferred(GazpreaParser::VectorInferredContext *ctx) override;
  virtual std::any
  visitMatrixInferred(GazpreaParser::MatrixInferredContext *ctx) override;
  virtual std::any visitMatrixFirstInferred(
      GazpreaParser::MatrixFirstInferredContext *ctx) override;
  virtual std::any visitMatrixSecondInferred(
      GazpreaParser::MatrixSecondInferredContext *ctx) override;
  virtual std::any
  visitStringInferred(GazpreaParser::StringInferredContext *ctx) override;

  // Statements
  virtual std::any visitTypedef(GazpreaParser::TypedefContext *ctx) override;
  virtual std::any visitDeclare(GazpreaParser::DeclareContext *ctx) override;
  virtual std::any
  visitDeclareSize(GazpreaParser::DeclareSizeContext *ctx) override;
  virtual std::any
  visitDeclareInferred(GazpreaParser::DeclareInferredContext *ctx) override;
  virtual std::any visitAssign(GazpreaParser::AssignContext *ctx) override;
  virtual std::any
  visitConditional(GazpreaParser::ConditionalContext *ctx) override;
  virtual std::any
  visitLoopInfinite(GazpreaParser::LoopInfiniteContext *ctx) override;
  virtual std::any
  visitLoopPrePredicate(GazpreaParser::LoopPrePredicateContext *ctx) override;
  virtual std::any
  visitLoopPostPredicate(GazpreaParser::LoopPostPredicateContext *ctx) override;
  virtual std::any
  visitLoopIterator(GazpreaParser::LoopIteratorContext *ctx) override;
  virtual std::any visitBreaks(GazpreaParser::BreaksContext *ctx) override;
  virtual std::any
  visitContinues(GazpreaParser::ContinuesContext *ctx) override;
  virtual std::any
  visitReturn_statement(GazpreaParser::Return_statementContext *ctx) override;
  virtual std::any visitOutput(GazpreaParser::OutputContext *ctx) override;
  virtual std::any visitInput(GazpreaParser::InputContext *ctx) override;
  virtual std::any visitBlock(GazpreaParser::BlockContext *ctx) override;
  virtual std::any visitDomain(GazpreaParser::DomainContext *ctx) override;

  // Functions
  virtual std::any
  visitFunctionForward(GazpreaParser::FunctionForwardContext *ctx) override;
  virtual std::any
  visitFunctionSingle(GazpreaParser::FunctionSingleContext *ctx) override;
  virtual std::any
  visitFunctionBlock(GazpreaParser::FunctionBlockContext *ctx) override;
  virtual std::any
  visitFunction_param(GazpreaParser::Function_paramContext *ctx) override;

  // Procedures
  virtual std::any
  visitProcedureForward(GazpreaParser::ProcedureForwardContext *ctx) override;
  virtual std::any visitProcedureFowardReturn(
      GazpreaParser::ProcedureFowardReturnContext *ctx) override;
  virtual std::any
  visitProcedureNoReturn(GazpreaParser::ProcedureNoReturnContext *ctx) override;
  virtual std::any
  visitProcedureReturn(GazpreaParser::ProcedureReturnContext *ctx) override;
  virtual std::any
  visitProcedure_param(GazpreaParser::Procedure_paramContext *ctx) override;
  virtual std::any
  visitProc_call(GazpreaParser::Proc_callContext *ctx) override;

  // Expressions
  virtual std::any
  visitParenExpr(GazpreaParser::ParenExprContext *ctx) override;
  virtual std::any visitComp(GazpreaParser::CompContext *ctx) override;
  virtual std::any visitCast(GazpreaParser::CastContext *ctx) override;
  virtual std::any visitCall(GazpreaParser::CallContext *ctx) override;
  virtual std::any
  visitBinaryExpr(GazpreaParser::BinaryExprContext *ctx) override;
  virtual std::any
  visitUnaryExpr(GazpreaParser::UnaryExprContext *ctx) override;
  virtual std::any
  visitGeneratorExpr(GazpreaParser::GeneratorExprContext *ctx) override;
  virtual std::any
  visitFilterExpr(GazpreaParser::FilterExprContext *ctx) override;

  // Ids
  virtual std::any visitVarId(GazpreaParser::VarIdContext *ctx) override;
  virtual std::any visitVectorId(GazpreaParser::VectorIdContext *ctx) override;
  virtual std::any visitMatrixId(GazpreaParser::MatrixIdContext *ctx) override;
  virtual std::any visitTupleId(GazpreaParser::TupleIdContext *ctx) override;
  virtual std::any
  visitTupleVectorAccess(GazpreaParser::TupleVectorAccessContext *ctx) override;
  virtual std::any
  visitTupleMatrixAccess(GazpreaParser::TupleMatrixAccessContext *ctx) override;

  // Literals
  virtual std::any
  visitIdentityLiteral(GazpreaParser::IdentityLiteralContext *ctx) override;
  virtual std::any
  visitNullLiteral(GazpreaParser::NullLiteralContext *ctx) override;
  virtual std::any
  visitIntLiteral(GazpreaParser::IntLiteralContext *ctx) override;
  virtual std::any
  visitIntervalLiteral(GazpreaParser::IntervalLiteralContext *ctx) override;
  virtual std::any
  visitBoolean_literal(GazpreaParser::Boolean_literalContext *ctx) override;
  virtual std::any
  visitCharacter_literal(GazpreaParser::Character_literalContext *ctx) override;
  virtual std::any
  visitString_literal(GazpreaParser::String_literalContext *ctx) override;
  virtual std::any
  visitFloat_literal(GazpreaParser::Float_literalContext *ctx) override;
  virtual std::any
  visitTuple_literal(GazpreaParser::Tuple_literalContext *ctx) override;
  virtual std::any
  visitVector_literal(GazpreaParser::Vector_literalContext *ctx) override;

  // Helper
  Token antlrToGazpreaToken(size_t antlrToken);
};

} // namespace gazprea