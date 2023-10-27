#pragma once
#include "ASTNodes.h"
#include "Symbol.h"

namespace gazprea {
template <typename T, typename U> struct PairHash {
  std::size_t operator()(const std::pair<T, U> &pair) const {
    return std::hash<T>{}(pair.first) ^ (std::hash<U>{}(pair.second) << 32);
  }
};

template <typename T, typename U, typename V> struct TripleHash {
  std::size_t operator()(const std::tuple<T, U, V> &tuple) const {
    return std::hash<T>{}(std::get<0>(tuple)) ^
           (std::hash<U>{}(std::get<1>(tuple)) << 16) ^
           (std::hash<V>{}(std::get<2>(tuple)) << 32);
  }
};

class ASTPass {
public:
  virtual void run(AST *node);
  virtual void begin(){};
  virtual void end(){};

  virtual Symbol visitAssignStatement(AssignStatement *node);
  virtual Symbol visitIntNode(IntNode *node);
  virtual Symbol visitBooleanNode(BooleanNode *node);
  virtual Symbol visitCharacterNode(CharacterNode *node);
  virtual Symbol visitRealNode(RealNode *node);
  virtual Symbol visitTupleNode(TupleNode *node);
  virtual Symbol visitVectorNode(VectorNode *node);
  virtual Symbol visitStringNode(StringNode *node);
  virtual Symbol visitBinaryExpr(BinaryExpr *node);
  virtual Symbol visitBlock(Block *node);
  virtual Symbol visitBuiltInCall(BuiltInCall *node);
  virtual Symbol visitConditionStatement(ConditionStatement *node);
  virtual Symbol visitDeclareStatement(DeclareStatement *node);
  virtual Symbol visitDomainExpr(DomainExpr *node);
  virtual Symbol visitIdentityNode(IdentityNode *node);
  virtual Symbol visitIntervalNode(IntervalNode *node);
  virtual Symbol visitNullNode(NullNode *node);
  virtual Symbol visitBreakNode(BreakNode *node);
  virtual Symbol visitContinueNode(ContinueNode *node);
  virtual Symbol visitReturnNode(ReturnNode *node);
  virtual Symbol visitFileNode(FileNode *node);
  virtual Symbol visitFilterExpr(FilterExpr *node);
  virtual Symbol visitFunctionCallNode(FunctionCallNode *node);
  virtual Symbol visitFunctionDeclNode(FunctionDeclNode *node);
  virtual Symbol visitFunctionParamNode(FunctionParamNode *node);
  virtual Symbol visitGeneratorExpr(GeneratorExpr *node);
  virtual Symbol visitIdNode(IdNode *node);
  virtual Symbol visitLoop(Loop *node);
  virtual Symbol visitProcedureCall(ProcedureCall *node);
  virtual Symbol visitProcedureDecl(ProcedureDecl *node);
  virtual Symbol visitProcedureParam(ProcedureParam *node);
  virtual Symbol visitStream(Stream *node);
  virtual Symbol visitTuple_member(TupleMember *node);
  virtual Symbol visitTuple_type(TupleType *node);
  virtual Symbol visitTypeNode(TypeNode *node);
  virtual Symbol visitTypeCast(TypeCast *node);
  virtual Symbol visitTypeDef(TypeDef *node);
  virtual Symbol visitUnaryExpr(UnaryExpr *node);
};

} // namespace gazprea