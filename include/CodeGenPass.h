#include "ASTPass.h"
#include "Scope.h"
#include "Symbol.h"
#include "Token.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_os_ostream.h"

#include <fstream>
#include <iostream>

#include <unordered_map>

template <> struct std::hash<gazprea::Symbol> {
  std::size_t operator()(gazprea::Symbol const &s) const noexcept {
    size_t h1 = std::hash<gazprea::Type>{}(s.type_);
    size_t size0 = s.size0_;
    size_t size1 = s.size1_;
    size_t h2 = size0 + (size1 << 32);
    return h1 ^ h2;
  }
};

namespace gazprea {

class CodeGenPass : public ASTPass {
private:
  // LLVM construction tools.
  llvm::LLVMContext global_ctx_;
  llvm::IRBuilder<> ir_;
  llvm::Module mod_;
  llvm::raw_os_ostream ll_err_;
  llvm::raw_os_ostream ll_out_;

  llvm::BasicBlock *current_function_ =
      nullptr; // entry point for current function
  std::vector<llvm::BasicBlock *> loop_entry_; // for continues
  std::vector<llvm::BasicBlock *> loop_exit_;  // for breaks
  llvm::BasicBlock *entry_;

  std::vector<Scope *> scopes_;
  Scope *current_scope_;
  std::unordered_map<Type, llvm::Type *> type_map_;
  // Goes from Token and Type to function name
  std::unordered_map<std::pair<Token, Type>, std::string, PairHash<Token, Type>>
      built_in_functions_;
  // Goes from Token and Type to function name
  std::unordered_map<std::pair<Token, Type>, std::string, PairHash<Token, Type>>
      unary_functions_;
  // Goes from token and operand types, to function name and return type
  std::unordered_map<std::tuple<Token, Type, Type>,
                     std::pair<std::string, Type>,
                     TripleHash<Token, Type, Type>>
      binary_functions_;
  // map from Type to thier names
  std::unordered_map<Type, std::string> type_names_;

  std::unordered_map<Type, llvm::Value *> default_values_;

  Symbol defaultConstruct(Symbol symbol);
  void assignSymbol(IdNode *node, Symbol original_sym, Symbol new_sym);
  Symbol assignSymbolHelper(Symbol original_sym, Symbol new_sym);
  Symbol copySymbol(Symbol symbol);
  llvm::Value *typeCastSymbol(Symbol src, Symbol dst);
  llvm::Value *createAlloca(llvm::Type *type);
  llvm::Value *createGlobal(llvm::Type *type, std::string name, AST *expr);
  void pushScope(size_t node_id);
  void popScope();

  bool isMatrixType(Type type);
  bool isVectorType(Type type);
  bool isScalarType(Type type);

public:
  CodeGenPass(std::ostream &file);

  virtual void begin();
  virtual void end();

  virtual Symbol visitAssignStatement(AssignStatement *node) override;
  virtual Symbol visitIntNode(IntNode *node) override;
  virtual Symbol visitBooleanNode(BooleanNode *node) override;
  virtual Symbol visitCharacterNode(CharacterNode *node) override;
  virtual Symbol visitRealNode(RealNode *node) override;
  virtual Symbol visitTupleNode(TupleNode *node) override;
  virtual Symbol visitVectorNode(VectorNode *node) override;
  virtual Symbol visitStringNode(StringNode *node) override;
  virtual Symbol visitBinaryExpr(BinaryExpr *node) override;
  virtual Symbol visitBlock(Block *node) override;
  virtual Symbol visitBuiltInCall(BuiltInCall *node) override;
  virtual Symbol visitConditionStatement(ConditionStatement *node) override;
  virtual Symbol visitDeclareStatement(DeclareStatement *node) override;
  virtual Symbol visitDomainExpr(DomainExpr *node) override;
  virtual Symbol visitIdentityNode(IdentityNode *node) override;
  virtual Symbol visitIntervalNode(IntervalNode *node) override;
  virtual Symbol visitNullNode(NullNode *node) override;
  virtual Symbol visitBreakNode(BreakNode *node) override;
  virtual Symbol visitContinueNode(ContinueNode *node) override;
  virtual Symbol visitReturnNode(ReturnNode *node) override;
  virtual Symbol visitFileNode(FileNode *node) override;
  virtual Symbol visitFilterExpr(FilterExpr *node) override;
  virtual Symbol visitFunctionCallNode(FunctionCallNode *node) override;
  virtual Symbol visitFunctionDeclNode(FunctionDeclNode *node) override;
  virtual Symbol visitFunctionParamNode(FunctionParamNode *node) override;
  virtual Symbol visitGeneratorExpr(GeneratorExpr *node) override;
  virtual Symbol visitIdNode(IdNode *node) override;
  virtual Symbol visitLoop(Loop *node) override;
  virtual Symbol visitProcedureCall(ProcedureCall *node);
  virtual Symbol visitProcedureDecl(ProcedureDecl *node) override;
  virtual Symbol visitProcedureParam(ProcedureParam *node) override;
  virtual Symbol visitStream(Stream *node) override;
  virtual Symbol visitTypeNode(TypeNode *node) override;
  virtual Symbol visitTypeCast(TypeCast *node) override;
  virtual Symbol visitTypeDef(TypeDef *node) override;
  virtual Symbol visitUnaryExpr(UnaryExpr *node) override;
};

} // namespace gazprea