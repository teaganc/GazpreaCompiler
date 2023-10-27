#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "ASTNodes.h"
#include "ASTPass.h"
#include "Scope.h"
#include "Symbol.h"
#include "Token.h"

namespace gazprea {

class DefRef : public ASTPass {
  Scope *curr_scope_;

  std::unordered_map<std::string, Symbol> typedefs_;

  std::unordered_map<std::tuple<Token, Type, Type>,
                     std::pair<std::string, Type>,
                     TripleHash<Token, Type, Type>>
      binary_functions_;

  std::unordered_map<std::pair<Token, Type>, std::string, PairHash<Token, Type>>
      unary_functions_;

  Symbol curr_function_;

public:
  DefRef();
  void end() override;

  // File node
  Symbol visitFileNode(FileNode *node) override;

  // Scoped nodes
  Symbol visitFunctionDeclNode(FunctionDeclNode *node) override;
  Symbol visitFunctionParamNode(FunctionParamNode *node) override;
  Symbol visitProcedureDecl(ProcedureDecl *node) override;
  Symbol visitProcedureParam(ProcedureParam *node) override;
  Symbol visitLoop(Loop *node) override;
  Symbol visitConditionStatement(ConditionStatement *node) override;
  Symbol visitBlock(Block *node) override;
  Symbol visitGeneratorExpr(GeneratorExpr *node) override;
  Symbol visitFilterExpr(FilterExpr *node) override;

  // Other statements
  Symbol visitTypeDef(TypeDef *node) override;
  Symbol visitAssignStatement(AssignStatement *node) override;
  Symbol visitDeclareStatement(DeclareStatement *node) override;
  Symbol visitStream(Stream *node) override;
  Symbol visitReturnNode(ReturnNode *node) override;

  // Expressions
  Symbol visitBinaryExpr(BinaryExpr *node) override;
  Symbol visitUnaryExpr(UnaryExpr *node) override;
  Symbol visitBuiltInCall(BuiltInCall *node) override;
  Symbol visitFunctionCallNode(FunctionCallNode *node) override;
  Symbol visitProcedureCall(ProcedureCall *node) override;
  Symbol visitTypeCast(TypeCast *node) override;
  Symbol visitDomainExpr(DomainExpr *node) override;

  // Leaf nodes
  Symbol visitTypeNode(TypeNode *node) override;
  Symbol visitTuple_type(TupleType *node) override;
  Symbol visitTuple_member(TupleMember *node) override;
  Symbol visitIdNode(IdNode *node) override;
  Symbol visitIntNode(IntNode *node) override;
  Symbol visitBooleanNode(BooleanNode *node) override;
  Symbol visitCharacterNode(CharacterNode *node) override;
  Symbol visitRealNode(RealNode *node) override;
  Symbol visitIdentityNode(IdentityNode *node) override;
  Symbol visitNullNode(NullNode *node) override;
  Symbol visitIntervalNode(IntervalNode *node);
  Symbol visitStringNode(StringNode *node) override;
  Symbol visitTupleNode(TupleNode *node) override;
  Symbol visitVectorNode(VectorNode *node) override;

  // Helpers
  TypeNode *symbolToTypeNode(Symbol symbol);
  TupleType *symbolToTupleTypeNode(Symbol symbol);
  bool isBuiltin(std::string name);
  bool insertTypecast(Symbol source_symbol, Symbol target_symbol,
                      size_t node_line);
  bool compatibleSizes(Symbol source_symbol, Symbol target_symbol);
  bool canPromoteTo(Type source, Type target);
  bool canCastTo(Type source, Type target);
};

} // namespace gazprea