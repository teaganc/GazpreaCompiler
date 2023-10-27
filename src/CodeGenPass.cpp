#include "CodeGenPass.h"
#include "Exceptions.h"
#include "Symbol.h"

#include "llvm/IR/Constant.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"

//#define DEBUG
#ifdef DEBUG
#include <iostream>
#define DEBUG_FUNC_ENTRY std::cerr << "Enter: " << __PRETTY_FUNCTION__ << '\n';
#define DEBUG_FUNC_EXIT std::cerr << "Exit: " << __PRETTY_FUNCTION__ << '\n';
#else
#define DEBUG_FUNC_ENTRY
#define DEBUG_FUNC_EXIT
#endif

namespace gazprea {
// TODO: USE TOKENS FOR QUICK UNDERSTANDING OF AST STRUCTURE PLS
// TODO: zero indexing is not true in gazprea, its 1 indexed :)
llvm::Value *CodeGenPass::createAlloca(llvm::Type *type) {
  DEBUG_FUNC_ENTRY
  auto block = ir_.GetInsertBlock();
  ir_.SetInsertPoint(current_function_,
                     current_function_->getFirstInsertionPt());
  auto ret = ir_.CreateAlloca(type);
  ir_.SetInsertPoint(block);
  DEBUG_FUNC_EXIT
  return ret;
}

llvm::Value *CodeGenPass::createGlobal(llvm::Type *type, std::string name,
                                       AST *expr) {
  DEBUG_FUNC_ENTRY
  auto block = ir_.GetInsertBlock();
  ir_.SetInsertPoint(entry_, entry_->getFirstInsertionPt());

  auto ret = mod_.getOrInsertGlobal(name, type);
  auto value = expr->visit(this);

  llvm::GlobalVariable *gVar = mod_.getNamedGlobal(name);
  llvm::Constant *constant = llvm::dyn_cast<llvm::Constant>(value.value_);
  if (!constant) {
    gVar->setInitializer(llvm::Constant::getNullValue(type));
    ir_.CreateStore(value.value_, gVar);
  } else {
    gVar->setInitializer(constant);
  }

  ir_.SetInsertPoint(block);
  DEBUG_FUNC_EXIT
  return ret;
}

void CodeGenPass::pushScope(size_t node_id) {
  DEBUG_FUNC_ENTRY
  scopes_.push_back(Scope::scopes_.at(node_id));
  scopes_.back()->parent_ = current_scope_;
  current_scope_ = scopes_.back();
  DEBUG_FUNC_EXIT
}

void CodeGenPass::popScope() {
  DEBUG_FUNC_ENTRY
  scopes_.pop_back();
  if (scopes_.size() != 0) {
    current_scope_ = scopes_.back();
  } else {
    current_scope_ = nullptr;
  }
  DEBUG_FUNC_EXIT
}

// TODO: remove these and replace with functions in Symbol.cpp
bool CodeGenPass::isVectorType(Type type) {
  DEBUG_FUNC_ENTRY
  std::vector<Type> pointer_types = {Type::VECTOR_CHARACTER,
                                     Type::VECTOR_BOOLEAN, Type::VECTOR_INTEGER,
                                     Type::VECTOR_REAL};
  if (std::any_of(pointer_types.begin(), pointer_types.end(),
                  [type](Type in) { return in == type; })) {
    DEBUG_FUNC_EXIT
    return true;
  }
  DEBUG_FUNC_EXIT
  return false;
}
bool CodeGenPass::isMatrixType(Type type) {
  DEBUG_FUNC_ENTRY
  std::vector<Type> pointer_types = {Type::MATRIX_BOOLEAN,
                                     Type::MATRIX_CHARACTER,
                                     Type::MATRIX_INTEGER, Type::MATRIX_REAL};
  if (std::any_of(pointer_types.begin(), pointer_types.end(),
                  [type](Type in) { return in == type; })) {
    DEBUG_FUNC_EXIT
    return true;
  }
  DEBUG_FUNC_EXIT
  return false;
}

bool CodeGenPass::isScalarType(Type type) {
  DEBUG_FUNC_ENTRY
  std::vector<Type> scalar_types = {Type::REAL, Type::BOOLEAN, Type::CHARACTER,
                                    Type::INTEGER};
  if (std::any_of(scalar_types.begin(), scalar_types.end(),
                  [type](Type in) { return in == type; })) {
    DEBUG_FUNC_EXIT
    return true;
  }
  DEBUG_FUNC_EXIT
  return false;
}

Symbol CodeGenPass::defaultConstruct(Symbol symbol) {
  DEBUG_FUNC_ENTRY
  if (symbol.type_ == Type::TUPLE) {
    // get malloced ptr
    llvm::FunctionType *malloc_ty =
        llvm::FunctionType::get(ir_.getInt8PtrTy(), {ir_.getInt32Ty()}, false);
    llvm::Function *malloc_func = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("malloc", malloc_ty).getCallee());

    symbol.value_ = ir_.CreateCall(malloc_func,
                                   {ir_.getInt32(symbol.children_.size() * 4)});
    // iterate over children in tuple and malloc memory before assigning back to
    // symbol children
    for (size_t i = 0; i < symbol.children_.size(); ++i) {
      llvm::Value *child = defaultConstruct(symbol.children_[i].second).value_;

      llvm::Type *type = type_map_.at(symbol.children_[i].second.type_);
      std::string type_name = type_names_.at(symbol.children_[i].second.type_);

      llvm::FunctionType *store_ty = llvm::FunctionType::get(
          type->getPointerTo(0), {ir_.getInt8PtrTy(), ir_.getInt32Ty(), type},
          false);
      llvm::Function *store = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("createStore" + type_name, store_ty)
              .getCallee());

      symbol.children_[i].second.value_ =
          ir_.CreateCall(store, {symbol.value_, ir_.getInt32(i + 1), child});
    }
  } else if (isMatrixType(symbol.type_)) {
    // memory = {type}* init_matrix_{type} (size, size)
    llvm::Type *type = type_map_.at(symbol.type_);
    std::string type_name = type_names_.at(symbol.type_);

    llvm::FunctionType *init_ty = llvm::FunctionType::get(
        type, {ir_.getInt32Ty(), ir_.getInt32Ty()}, false);
    llvm::Function *init = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("init" + type_name, init_ty).getCallee());

    symbol.value_ = ir_.CreateCall(
        init, {ir_.getInt32(symbol.size0_), ir_.getInt32(symbol.size1_)});
  } else if (isVectorType(symbol.type_)) {
    // memory = {type}* init_vector_{type} (size)
    std::string type_name = type_names_.at(symbol.type_);
    llvm::Type *type = type_map_.at(symbol.type_);

    llvm::FunctionType *init_ty =
        llvm::FunctionType::get(type, {ir_.getInt32Ty()}, false);
    llvm::Function *init = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("init" + type_name, init_ty).getCallee());

    symbol.value_ = ir_.CreateCall(init, {ir_.getInt32(symbol.size0_)});
  } else if (symbol.type_ == Type::INTERVAL) {
    llvm::Type *type = type_map_.at(symbol.type_);

    llvm::FunctionType *init_ty = llvm::FunctionType::get(
        type, {ir_.getInt32Ty(), ir_.getInt32Ty()}, false);
    llvm::Function *init = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("defaultConstructInterval", init_ty)
            .getCallee());

    symbol.value_ = ir_.CreateCall(init, {ir_.getInt32(0), ir_.getInt32(0)});
  } else if (symbol.type_ == Type::STRING) {
    llvm::FunctionType *func_ty = llvm::FunctionType::get(
        llvm::Type::getInt8PtrTy(global_ctx_),
        {llvm::Type::getInt8PtrTy(global_ctx_), ir_.getInt32Ty()}, false);
    llvm::Function *func = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("initAndWriteString", func_ty).getCallee());

    symbol.value_ =
        ir_.CreateCall(func, {ir_.CreateGlobalStringPtr(""), ir_.getInt32(0)});
  } else if (isScalarType(symbol.type_)) {
    symbol.value_ = default_values_.at(symbol.type_);
  } else {
    throw PanicError();
  }
  DEBUG_FUNC_EXIT
  return symbol;
}

void CodeGenPass::assignSymbol(IdNode *node, Symbol original_sym,
                               Symbol new_sym) {
  DEBUG_FUNC_ENTRY
  switch (node->token_) {
  case Token::ID_MATRIX_INDEX: {
    // matrix index assignment
    // TODO: also handles m[1,[2,3]] = [4,5]; once changed in builder
    auto index0 = node->index0_->visit(this);
    auto index1 = node->index1_->visit(this);

    std::string type_name = type_names_.at(original_sym.type_);
    llvm::Type *ptr_type = type_map_.at(original_sym.type_);
    llvm::Type *base_type =
        type_map_.at(TypeHelpers::getBaseType(original_sym.type_));

    llvm::FunctionType *write_ty = llvm::FunctionType::get(
        ir_.getVoidTy(),
        {base_type, ptr_type, ir_.getInt32Ty(), ir_.getInt32Ty()}, false);
    llvm::Function *write = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("write" + type_name, write_ty).getCallee());

    auto load = ir_.CreateLoad(original_sym.value_);

    ir_.CreateCall(write, {new_sym.value_, load, index0.value_, index1.value_});
    break;
  }
  case Token::ID_VECTOR_INDEX: {
    // vector index assignment
    // TODO: also handles m[[1,2]] = [4,5]; once changed in builder
    auto index0 = node->index0_->visit(this);

    std::string type_name = type_names_.at(original_sym.type_);
    llvm::Type *ptr_type = type_map_.at(original_sym.type_);
    llvm::Type *base_type =
        type_map_.at(TypeHelpers::getBaseType(original_sym.type_));

    llvm::FunctionType *write_ty = llvm::FunctionType::get(
        ir_.getVoidTy(), {base_type, ptr_type, ir_.getInt32Ty()}, false);
    llvm::Function *write = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("write" + type_name, write_ty).getCallee());

    auto load = ir_.CreateLoad(original_sym.value_);

    ir_.CreateCall(write, {new_sym.value_, load, index0.value_});
    break;
  }
  case Token::ID_TUPLE_INT_INDEX: {
    // tuple int index assignment
    Symbol symbol = original_sym.children_[node->int_index_ - 1].second;
    symbol = assignSymbolHelper(symbol, new_sym);
    original_sym.children_[node->int_index_ - 1].second = symbol;
    current_scope_->declare(node->id_name_, original_sym);
    break;
  }
  case Token::ID_TUPLE_ID_INDEX: {
    // tuple id index assignment
    auto iter = std::find_if(
        original_sym.children_.begin(), original_sym.children_.end(),
        [node](auto i) { return node->id_index_ == i.first; });
    auto index = iter - original_sym.children_.begin();
    Symbol symbol = original_sym.children_[index].second;
    symbol = assignSymbolHelper(symbol, new_sym);
    original_sym.children_[index].second = symbol;
    current_scope_->declare(node->id_name_, original_sym);
    break;
  }
  case Token::ID_EXPR: {
    // normal assignments
    original_sym = assignSymbolHelper(original_sym, new_sym);
    current_scope_->declare(node->id_name_, original_sym);
    break;
  }
  default:
    throw PanicError();
  }
  DEBUG_FUNC_EXIT
}

Symbol CodeGenPass::assignSymbolHelper(Symbol original_sym, Symbol new_sym) {
  DEBUG_FUNC_ENTRY
  if (original_sym.type_ == Type::TUPLE) {
    // free the memory children of tuple if vector/matrix
    for (auto &i : original_sym.children_) {
      if (isMatrixType(original_sym.type_) ||
          isVectorType(original_sym.type_)) {
        llvm::FunctionType *free_ty = llvm::FunctionType::get(
            ir_.getVoidTy(), {ir_.getInt8PtrTy()}, false);
        llvm::Function *free_fun = llvm::cast<llvm::Function>(
            mod_.getOrInsertFunction("free", free_ty).getCallee());
        llvm::Value *load = ir_.CreateLoad(i.second.value_);
        load = ir_.CreatePointerCast(load, ir_.getInt8PtrTy());
        ir_.CreateCall(free_fun, {load});
      }
    }
    // free the pointer that the tuple points to
    llvm::FunctionType *free_ty =
        llvm::FunctionType::get(ir_.getVoidTy(), {ir_.getInt8PtrTy()}, false);
    llvm::Function *free_fun = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("free", free_ty).getCallee());
    llvm::Value *load = ir_.CreateLoad(original_sym.value_);
    load = ir_.CreatePointerCast(load, ir_.getInt8PtrTy());
    ir_.CreateCall(free_fun, {load});
    // redeclare with new children
    for (size_t i = 0; i < original_sym.children_.size(); i++) {
      new_sym.children_[i].first = original_sym.children_[i].first;
    }
    original_sym.children_ = new_sym.children_;
  } else if (isMatrixType(original_sym.type_) ||
             isVectorType(original_sym.type_)) {
    llvm::FunctionType *free_ty =
        llvm::FunctionType::get(ir_.getVoidTy(), {ir_.getInt8PtrTy()}, false);
    llvm::Function *free_fun = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("free", free_ty).getCallee());
    llvm::Value *load = ir_.CreateLoad(original_sym.value_);
    load = ir_.CreatePointerCast(load, ir_.getInt8PtrTy());
    ir_.CreateCall(free_fun, {load});
  }

  ir_.CreateStore(new_sym.value_, original_sym.value_);
  DEBUG_FUNC_EXIT
  return original_sym;
}

Symbol CodeGenPass::copySymbol(Symbol symbol) {
  DEBUG_FUNC_ENTRY
  std::string type_name = type_names_.at(symbol.type_);
  llvm::Type *type = type_map_.at(symbol.type_);

  if (isMatrixType(symbol.type_) || isVectorType(symbol.type_) ||
      symbol.type_ == Type::INTERVAL || symbol.type_ == Type::STRING) {
    auto pointer = ir_.CreateLoad(type, symbol.value_);

    llvm::FunctionType *copy_ty = llvm::FunctionType::get(type, {type}, false);
    llvm::Function *copy = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("copy" + type_name, copy_ty).getCallee());

    symbol.value_ = ir_.CreateCall(copy, {pointer});
  } else if (isScalarType(symbol.type_)) { // scalar case
    symbol.value_ = ir_.CreateLoad(type, symbol.value_);
  } else {
    throw PanicError();
  }
  DEBUG_FUNC_EXIT
  return symbol;
}

llvm::Value *CodeGenPass::typeCastSymbol(Symbol src, Symbol dst) {
  DEBUG_FUNC_ENTRY
  if (src.type_ == Type::_NULL_) {
    src.type_ = Type::INTEGER;
    src.value_ = ir_.getInt32(0);
  } else if (src.type_ == Type::IDENTITY) {
    src.type_ = Type::INTEGER;
    src.value_ = ir_.getInt32(1);
  }
  std::string operation =
      "cast" + type_names_.at(src.type_) + type_names_.at(dst.type_);
  // std::string operation = typecast_map_.at({src.type_, dst.type_});
  llvm::Type *src_type = type_map_.at(src.type_);
  llvm::Type *dst_type = type_map_.at(dst.type_);

  if (TypeHelpers::isVector(dst.type_) || dst.type_ == Type::STRING) {
    llvm::FunctionType *variable_ty =
        llvm::FunctionType::get(dst_type, {src_type, ir_.getInt32Ty()}, false);
    auto f = mod_.getOrInsertFunction(operation, variable_ty).getCallee();
    llvm::Function *variable = llvm::cast<llvm::Function>(f);
    dst.value_ =
        ir_.CreateCall(variable, {src.value_, ir_.getInt32(dst.size0_)});
  } else if (TypeHelpers::isMatrix(dst.type_)) {
    llvm::FunctionType *variable_ty = llvm::FunctionType::get(
        dst_type, {src_type, ir_.getInt32Ty(), ir_.getInt32Ty()}, false);
    auto f = mod_.getOrInsertFunction(operation, variable_ty).getCallee();
    llvm::Function *variable = llvm::cast<llvm::Function>(f);
    dst.value_ = ir_.CreateCall(variable, {src.value_, ir_.getInt32(dst.size0_),
                                           ir_.getInt32(dst.size1_)});
  } else if (TypeHelpers::isScalar(dst.type_)) {
    llvm::FunctionType *variable_ty =
        llvm::FunctionType::get(dst_type, {src_type}, false);
    auto f = mod_.getOrInsertFunction(operation, variable_ty).getCallee();
    llvm::Function *variable = llvm::cast<llvm::Function>(f);
    dst.value_ = ir_.CreateCall(variable, {src.value_});
  } else {
    throw PanicError();
  }
  DEBUG_FUNC_EXIT
  return dst.value_;
}

CodeGenPass::CodeGenPass(std::ostream &file)
    : global_ctx_(), ir_(global_ctx_), mod_("gazprea", global_ctx_),
      ll_err_(std::cerr), ll_out_(file) {
  DEBUG_FUNC_ENTRY

  llvm::Type *structTy =
      llvm::StructType::create(global_ctx_,
                               {ir_.getInt32Ty(), ir_.getInt32Ty()}, "struct")
          ->getPointerTo(0);

  type_map_.insert({Type::NONE, ir_.getVoidTy()});
  type_map_.insert({Type::_NULL_, ir_.getVoidTy()});
  // This is type system abuse to make printing work
  // maybe we should just turn implicit casts of identity/null to explicit in
  // defref
  type_map_.insert({Type::IDENTITY, ir_.getInt16Ty()});
  type_map_.insert({Type::INTEGER, llvm::Type::getInt32Ty(global_ctx_)});
  type_map_.insert({Type::REAL, llvm::Type::getFloatTy(global_ctx_)});
  type_map_.insert({Type::CHARACTER, llvm::Type::getInt8Ty(global_ctx_)});
  type_map_.insert({Type::BOOLEAN, llvm::Type::getInt1Ty(global_ctx_)});

  type_map_.insert({Type::VECTOR, llvm::Type::getInt32PtrTy(global_ctx_)});
  type_map_.insert(
      {Type::VECTOR_INTEGER, llvm::Type::getInt32PtrTy(global_ctx_)});
  type_map_.insert({Type::VECTOR_REAL, llvm::Type::getFloatPtrTy(global_ctx_)});
  type_map_.insert(
      {Type::VECTOR_CHARACTER, llvm::Type::getInt8PtrTy(global_ctx_)});
  type_map_.insert(
      {Type::VECTOR_BOOLEAN, llvm::Type::getInt1PtrTy(global_ctx_)});

  type_map_.insert({Type::MATRIX, llvm::Type::getInt32PtrTy(global_ctx_)});
  type_map_.insert(
      {Type::MATRIX_INTEGER, llvm::Type::getInt32PtrTy(global_ctx_)});
  type_map_.insert({Type::MATRIX_REAL, llvm::Type::getFloatPtrTy(global_ctx_)});
  type_map_.insert(
      {Type::MATRIX_CHARACTER, llvm::Type::getInt8PtrTy(global_ctx_)});
  type_map_.insert(
      {Type::MATRIX_BOOLEAN, llvm::Type::getInt1PtrTy(global_ctx_)});

  type_map_.insert({Type::INTERVAL, structTy});
  type_map_.insert({Type::STRING, llvm::Type::getInt8PtrTy(global_ctx_)});

  type_map_.insert({Type::TUPLE, llvm::Type::getInt8PtrTy(global_ctx_)});

  // Built-in functions
  // Length
  built_in_functions_.insert(
      {{Token::LENGTH, Type::VECTOR_INTEGER}, "lengthIntVec"});
  built_in_functions_.insert(
      {{Token::LENGTH, Type::VECTOR_BOOLEAN}, "lengthBoolVec"});
  built_in_functions_.insert(
      {{Token::LENGTH, Type::VECTOR_CHARACTER}, "lengthCharVec"});
  built_in_functions_.insert(
      {{Token::LENGTH, Type::VECTOR_REAL}, "lengthRealVec"});
  built_in_functions_.insert(
      {{Token::LENGTH, Type::INTERVAL}, "lengthInterval"});
  built_in_functions_.insert({{Token::LENGTH, Type::STRING}, "lengthCharVec"});

  // Reverse
  built_in_functions_.insert(
      {{Token::REVERSE, Type::VECTOR_INTEGER}, "reverseIntVec"});
  built_in_functions_.insert(
      {{Token::REVERSE, Type::VECTOR_BOOLEAN}, "reverseBoolVec"});
  built_in_functions_.insert(
      {{Token::REVERSE, Type::VECTOR_CHARACTER}, "reverseCharVec"});
  built_in_functions_.insert(
      {{Token::REVERSE, Type::VECTOR_REAL}, "reverseRealVec"});

  // Row
  built_in_functions_.insert(
      {{Token::ROWS, Type::MATRIX_INTEGER}, "rowIntMatrix"});
  built_in_functions_.insert(
      {{Token::ROWS, Type::MATRIX_BOOLEAN}, "rowBoolMatrix"});
  built_in_functions_.insert(
      {{Token::ROWS, Type::MATRIX_CHARACTER}, "rowCharMatrix"});
  built_in_functions_.insert(
      {{Token::ROWS, Type::MATRIX_REAL}, "rowRealMatrix"});

  // Column
  built_in_functions_.insert(
      {{Token::COLUMNS, Type::MATRIX_INTEGER}, "colIntMatrix"});
  built_in_functions_.insert(
      {{Token::COLUMNS, Type::MATRIX_BOOLEAN}, "colBoolMatrix"});
  built_in_functions_.insert(
      {{Token::COLUMNS, Type::MATRIX_CHARACTER}, "colCharMatrix"});
  built_in_functions_.insert(
      {{Token::COLUMNS, Type::MATRIX_REAL}, "colRealMatrix"});

  // Stream state
  built_in_functions_.insert(
      {{Token::STREAM_STATE, Type::NONE}, "streamState"});

  // Unary functions
  // Scalar
  unary_functions_.insert({{Token::NOT, Type::BOOLEAN}, "unaryNotBool"});
  unary_functions_.insert({{Token::ADD, Type::INTEGER}, "unaryPlusInt"});
  unary_functions_.insert({{Token::ADD, Type::REAL}, "unaryPlusFloat"});
  unary_functions_.insert({{Token::SUB, Type::INTEGER}, "unaryMinusInt"});
  unary_functions_.insert({{Token::SUB, Type::REAL}, "unaryMinusFloat"});
  // Vector
  unary_functions_.insert(
      {{Token::NOT, Type::VECTOR_BOOLEAN}, "unaryNotBoolVec"});
  unary_functions_.insert(
      {{Token::ADD, Type::VECTOR_INTEGER}, "unaryPlusIntVec"});
  unary_functions_.insert(
      {{Token::ADD, Type::VECTOR_REAL}, "unaryPlusFloatVec"});
  unary_functions_.insert(
      {{Token::SUB, Type::VECTOR_INTEGER}, "unaryMinusIntVec"});
  unary_functions_.insert(
      {{Token::SUB, Type::VECTOR_REAL}, "unaryMinusFloatVec"});
  // Matrix
  unary_functions_.insert(
      {{Token::NOT, Type::MATRIX_BOOLEAN}, "unaryNotBoolMat"});
  unary_functions_.insert(
      {{Token::ADD, Type::MATRIX_INTEGER}, "unaryPlusIntMat"});
  unary_functions_.insert(
      {{Token::ADD, Type::MATRIX_REAL}, "unaryPlusFloatMat"});
  unary_functions_.insert(
      {{Token::SUB, Type::MATRIX_INTEGER}, "unaryMinusIntMat"});
  unary_functions_.insert(
      {{Token::SUB, Type::MATRIX_REAL}, "unaryMinusFloatMat"});
  // Interval
  unary_functions_.insert({{Token::ADD, Type::INTERVAL}, "unaryMinusInterval"});
  unary_functions_.insert({{Token::SUB, Type::INTERVAL}, "unaryMinusInterval"});

  // Scalar Binary Functions
  binary_functions_.insert({{Token::ADD, Type::INTEGER, Type::INTEGER},
                            {"binaryAddInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::ADD, Type::REAL, Type::REAL}, {"binaryAddFloat", Type::REAL}});
  binary_functions_.insert({{Token::SUB, Type::INTEGER, Type::INTEGER},
                            {"binarySubInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::SUB, Type::REAL, Type::REAL}, {"binarySubFloat", Type::REAL}});
  binary_functions_.insert({{Token::MUL, Type::INTEGER, Type::INTEGER},
                            {"binaryMulInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::MUL, Type::REAL, Type::REAL}, {"binaryMulFloat", Type::REAL}});
  binary_functions_.insert({{Token::DIV, Type::INTEGER, Type::INTEGER},
                            {"binaryDivInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::DIV, Type::REAL, Type::REAL}, {"binaryDivFloat", Type::REAL}});
  binary_functions_.insert({{Token::MOD, Type::INTEGER, Type::INTEGER},
                            {"binaryModInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::MOD, Type::REAL, Type::REAL}, {"binaryModFloat", Type::REAL}});
  binary_functions_.insert({{Token::EXP, Type::INTEGER, Type::INTEGER},
                            {"binaryExpInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::EXP, Type::REAL, Type::REAL}, {"binaryExpFloat", Type::REAL}});

  // Scalar Comparison operations
  binary_functions_.insert({{Token::LT, Type::INTEGER, Type::INTEGER},
                            {"binaryLTInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::LT, Type::REAL, Type::REAL}, {"binaryLTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::INTEGER, Type::INTEGER},
                            {"binaryLEInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::REAL, Type::REAL}, {"binaryLEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::INTEGER, Type::INTEGER},
                            {"binaryGTInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::REAL, Type::REAL}, {"binaryGTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::INTEGER, Type::INTEGER},
                            {"binaryGEInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::REAL, Type::REAL}, {"binaryGEFloat", Type::BOOLEAN}});

  // Scalar Equality operations
  binary_functions_.insert({{Token::EQ, Type::INTEGER, Type::INTEGER},
                            {"binaryEQInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::EQ, Type::REAL, Type::REAL}, {"binaryEQFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::BOOLEAN, Type::BOOLEAN},
                            {"binaryEQBool", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTEGER, Type::INTEGER},
                            {"binaryNEInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::REAL, Type::REAL}, {"binaryNEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::BOOLEAN, Type::BOOLEAN},
                            {"binaryNEBool", Type::BOOLEAN}});

  // Scalar boolean specific operations
  binary_functions_.insert({{Token::AND, Type::BOOLEAN, Type::BOOLEAN},
                            {"binaryAndBool", Type::BOOLEAN}});
  binary_functions_.insert({{Token::OR, Type::BOOLEAN, Type::BOOLEAN},
                            {"binaryOrBool", Type::BOOLEAN}});
  binary_functions_.insert({{Token::XOR, Type::BOOLEAN, Type::BOOLEAN},
                            {"binaryXorBool", Type::BOOLEAN}});

  // Vector Binary Functions

  // Vector arithmetic operations
  binary_functions_.insert(
      {{Token::ADD, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::ADD, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binarySubIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binarySubFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryMulIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryMulFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryDivIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryDivFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryModIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryModFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryExpIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryExpFloatVec", Type::VECTOR_REAL}});

  // Vector Comparison operations
  binary_functions_.insert(
      {{Token::LT, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryLTIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryLTFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryLEIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryLEFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryGTIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryGTFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryGEIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryGEFloatVec", Type::VECTOR_BOOLEAN}});

  // Vector Equality operations
  binary_functions_.insert(
      {{Token::EQ, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryEQIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryEQFloatVec", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::EQ, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"binaryEQBoolVec", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryNEIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryNEFloatVec", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"binaryNEBoolVec", Type::BOOLEAN}});

  // Vector boolean specific operations
  binary_functions_.insert(
      {{Token::AND, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"binaryAndBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::OR, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"binaryOrBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::XOR, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"binaryXorBoolVec", Type::VECTOR_BOOLEAN}});

  // Matrix Binary Functions

  // Matrix arithmetic operations
  binary_functions_.insert(
      {{Token::ADD, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryAddIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::ADD, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binarySubIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binarySubFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryMulIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryMulFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryDivIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryDivFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryModIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryModFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryExpIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryExpFloatMat", Type::MATRIX_REAL}});

  // Matrix Comparison operations
  binary_functions_.insert(
      {{Token::LT, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryLTIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryLTFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryLEIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryLEFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryGTIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryGTFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryGEIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryGEFloatMat", Type::MATRIX_BOOLEAN}});

  // Matrix Equality operations
  binary_functions_.insert(
      {{Token::EQ, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryEQIntMat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryEQFloatMat", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::EQ, Type::MATRIX_BOOLEAN, Type::MATRIX_BOOLEAN},
       {"binaryEQBoolMat", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryNEIntMat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryNEFloatMat", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::MATRIX_BOOLEAN, Type::MATRIX_BOOLEAN},
       {"binaryNEBoolMat", Type::BOOLEAN}});

  // Matrix boolean specific operations
  binary_functions_.insert(
      {{Token::AND, Type::MATRIX_BOOLEAN, Type::MATRIX_BOOLEAN},
       {"binaryAndBoolMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::OR, Type::MATRIX_BOOLEAN, Type::MATRIX_BOOLEAN},
       {"binaryOrBoolMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::XOR, Type::MATRIX_BOOLEAN, Type::MATRIX_BOOLEAN},
       {"binaryXorBoolMat", Type::MATRIX_BOOLEAN}});

  // Interval binary operations
  binary_functions_.insert({{Token::ADD, Type::INTERVAL, Type::INTERVAL},
                            {"binaryAddInterval", Type::INTERVAL}});
  binary_functions_.insert({{Token::SUB, Type::INTERVAL, Type::INTERVAL},
                            {"binarySubInterval", Type::INTERVAL}});
  binary_functions_.insert({{Token::MUL, Type::INTERVAL, Type::INTERVAL},
                            {"binaryMulInterval", Type::INTERVAL}});
  binary_functions_.insert({{Token::EQ, Type::INTERVAL, Type::INTERVAL},
                            {"binaryEQInterval", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTERVAL, Type::INTERVAL},
                            {"binaryNEInterval", Type::BOOLEAN}});

  // concat operations
  binary_functions_.insert(
      {{Token::CAT, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"concatIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::CAT, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"concatFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::CAT, Type::VECTOR_CHARACTER, Type::VECTOR_CHARACTER},
       {"concatCharVec", Type::VECTOR_CHARACTER}});
  binary_functions_.insert(
      {{Token::CAT, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"concatBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::CAT, Type::STRING, Type::STRING},
                            {"concatString", Type::STRING}});

  // dot operations
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"dotIntVec", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::VECTOR_REAL, Type::VECTOR_REAL},
       {"dotFloatVec", Type::REAL}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"dotIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::MATRIX_REAL, Type::MATRIX_REAL},
       {"dotFloatMat", Type::MATRIX_REAL}});

  // by operations
  binary_functions_.insert({{Token::BY, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"byIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::BY, Type::VECTOR_REAL, Type::INTEGER},
                            {"byFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::BY, Type::VECTOR_CHARACTER, Type::INTEGER},
                            {"byCharVec", Type::VECTOR_CHARACTER}});
  binary_functions_.insert({{Token::BY, Type::VECTOR_BOOLEAN, Type::INTEGER},
                            {"byBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::BY, Type::INTERVAL, Type::INTEGER},
                            {"byInterval", Type::VECTOR_INTEGER}});

  // scalar function extensions
  type_names_.insert({Type::_NULL_, "Null"});
  type_names_.insert({Type::IDENTITY, "Identity"});
  type_names_.insert({Type::BOOLEAN, "Bool"});
  type_names_.insert({Type::CHARACTER, "Char"});
  type_names_.insert({Type::INTEGER, "Int"});
  type_names_.insert({Type::REAL, "Float"});

  // vector function extensions
  type_names_.insert({Type::VECTOR, "NoneVec"});
  type_names_.insert({Type::VECTOR_BOOLEAN, "BoolVec"});
  type_names_.insert({Type::VECTOR_CHARACTER, "CharVec"});
  type_names_.insert({Type::VECTOR_INTEGER, "IntVec"});
  type_names_.insert({Type::VECTOR_REAL, "FloatVec"});
  type_names_.insert({Type::STRING, "CharVec"});
  type_names_.insert({Type::INTERVAL, "Interval"});

  // matrix function extensions
  type_names_.insert({Type::MATRIX, "NoneMat"});
  type_names_.insert({Type::MATRIX_BOOLEAN, "BoolMat"});
  type_names_.insert({Type::MATRIX_CHARACTER, "CharMat"});
  type_names_.insert({Type::MATRIX_INTEGER, "IntMat"});
  type_names_.insert({Type::MATRIX_REAL, "FloatMat"});

  // default values in llvm for declarations
  default_values_.insert({Type::INTEGER, ir_.getInt32(0)});
  default_values_.insert(
      {Type::REAL, llvm::ConstantFP::get(ir_.getFloatTy(), 0)});
  default_values_.insert({Type::CHARACTER, ir_.getInt8(0)});
  default_values_.insert({Type::BOOLEAN, ir_.getInt1(0)});

  // TODO: idk where these are supposed to be but probably somewhere
  default_values_.insert(
      {Type::VECTOR_BOOLEAN,
       llvm::ConstantPointerNull::get(llvm::Type::getInt1PtrTy(global_ctx_))});
  default_values_.insert(
      {Type::VECTOR_CHARACTER,
       llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(global_ctx_))});
  default_values_.insert(
      {Type::VECTOR_INTEGER,
       llvm::ConstantPointerNull::get(llvm::Type::getInt32PtrTy(global_ctx_))});
  default_values_.insert(
      {Type::VECTOR_REAL,
       llvm::ConstantPointerNull::get(llvm::Type::getFloatPtrTy(global_ctx_))});
  default_values_.insert(
      {Type::STRING,
       llvm::ConstantPointerNull::get(llvm::Type::getFloatPtrTy(global_ctx_))});
  default_values_.insert({Type::INTERVAL, llvm::ConstantPointerNull::get(
                                              structTy->getPointerTo(0))});
  default_values_.insert(
      {Type::MATRIX_BOOLEAN,
       llvm::ConstantPointerNull::get(llvm::Type::getInt1PtrTy(global_ctx_))});
  default_values_.insert(
      {Type::MATRIX_CHARACTER,
       llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(global_ctx_))});
  default_values_.insert(
      {Type::MATRIX_INTEGER,
       llvm::ConstantPointerNull::get(llvm::Type::getInt32PtrTy(global_ctx_))});
  default_values_.insert(
      {Type::MATRIX_REAL,
       llvm::ConstantPointerNull::get(llvm::Type::getFloatPtrTy(global_ctx_))});
  default_values_.insert(
      {Type::TUPLE,
       llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(global_ctx_))});
};

void CodeGenPass::begin() {
  DEBUG_FUNC_ENTRY
  // entry function specific for getting global scope set up, not a proper
  // function/procedure from input
  llvm::FunctionType *entry_ty =
      llvm::FunctionType::get(ir_.getInt32Ty(), false);
  llvm::Function *entry = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("0entry", entry_ty).getCallee());
  entry_ = llvm::BasicBlock::Create(global_ctx_, "entry", entry);
  ir_.SetInsertPoint(entry_);
  llvm::FunctionType *main_ty =
      llvm::FunctionType::get(ir_.getInt32Ty(), false);
  llvm::Function *main = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("main", main_ty).getCallee());

  auto ret = ir_.CreateCall(main);
  ir_.CreateRet(ret);
  DEBUG_FUNC_EXIT
}

void CodeGenPass::end() {
  DEBUG_FUNC_ENTRY
  llvm::verifyModule(mod_, &ll_err_);
  ll_out_ << mod_;
  DEBUG_FUNC_EXIT
}

Symbol CodeGenPass::visitAssignStatement(AssignStatement *node) {
  DEBUG_FUNC_ENTRY
  auto new_sym = node->expr_->visit(this);
  Symbol original_sym;
  if (node->lValues_.size() > 1) {
    // tuple unpacking
    for (size_t i = 0; i < node->lValues_.size(); ++i) {
      original_sym = current_scope_->resolve(node->lValues_[i]->id_name_);

      auto new_sym_child = new_sym.children_[i].second;
      llvm::Type *child_type = type_map_.at(new_sym_child.type_);
      new_sym_child.value_ =
          ir_.CreateLoad(child_type->getPointerTo(0), new_sym_child.value_);

      assignSymbol(node->lValues_[i].get(), original_sym, new_sym_child);
    }
  } else {
    original_sym = current_scope_->resolve(node->lValues_[0]->id_name_);
    assignSymbol(node->lValues_[0].get(), original_sym, new_sym);
  }

  DEBUG_FUNC_EXIT
  return original_sym;
}

Symbol CodeGenPass::visitIntNode(IntNode *node) {
  DEBUG_FUNC_ENTRY
  auto value = ir_.getInt32(node->value_);
  DEBUG_FUNC_EXIT
  return {Type::INTEGER, value};
}

Symbol CodeGenPass::visitBooleanNode(BooleanNode *node) {
  DEBUG_FUNC_ENTRY
  auto value = ir_.getInt1(node->value_);
  DEBUG_FUNC_EXIT
  return {Type::BOOLEAN, value};
}

Symbol CodeGenPass::visitCharacterNode(CharacterNode *node) {
  DEBUG_FUNC_ENTRY
  auto value = ir_.getInt8(node->value_);
  DEBUG_FUNC_EXIT
  return {Type::CHARACTER, value};
}

Symbol CodeGenPass::visitRealNode(RealNode *node) {
  DEBUG_FUNC_ENTRY
  auto value = llvm::ConstantFP::get(ir_.getFloatTy(), node->value_);
  DEBUG_FUNC_EXIT
  return {Type::REAL, value};
}

Symbol CodeGenPass::visitTupleNode(TupleNode *node) {
  DEBUG_FUNC_ENTRY
  auto symbol = node->type_;

  // malloc tuple ptr
  llvm::FunctionType *malloc_ty =
      llvm::FunctionType::get(ir_.getInt8PtrTy(), {ir_.getInt32Ty()}, false);
  llvm::Function *malloc_func = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("malloc", malloc_ty).getCallee());

  symbol.value_ =
      ir_.CreateCall(malloc_func, {ir_.getInt32(symbol.children_.size() * 4)});
  // iterate over children to store
  for (size_t i = 0; i < symbol.children_.size(); ++i) {
    symbol.children_[i].second = node->values_[i]->visit(this);

    llvm::Type *child_type = type_map_.at(symbol.children_[i].second.type_);
    std::string child_type_name =
        type_names_.at(symbol.children_[i].second.type_);

    llvm::FunctionType *store_ty = llvm::FunctionType::get(
        child_type->getPointerTo(0),
        {llvm::Type::getInt8PtrTy(global_ctx_), ir_.getInt32Ty(), child_type},
        false);
    llvm::Function *store = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("createStore" + child_type_name, store_ty)
            .getCallee());

    symbol.children_[i].second.value_ =
        ir_.CreateCall(store, {symbol.value_, ir_.getInt32(i + 1),
                               symbol.children_[i].second.value_});
  }
  DEBUG_FUNC_EXIT
  return symbol;
}

Symbol CodeGenPass::visitVectorNode(VectorNode *node) {
  DEBUG_FUNC_ENTRY
  if (node->token_ == Token::MATRIX_ATOM) {
    // TODO: father forgive me for I have sinned
    // malloc memory
    std::string type_name = type_names_.at(node->type_.type_);
    llvm::Type *type = type_map_.at(node->type_.type_);

    llvm::FunctionType *init_ty = llvm::FunctionType::get(
        type, {ir_.getInt32Ty(), ir_.getInt32Ty()}, false);
    llvm::Function *init = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("init" + type_name, init_ty).getCallee());

    auto call = ir_.CreateCall(init, {ir_.getInt32(node->type_.size0_),
                                      ir_.getInt32(node->type_.size1_)});

    // copy memory
    for (size_t i = 0; i < node->values_.size(); ++i) {
      auto symbol = node->values_[i]->visit(this);
      llvm::Type *child_type = type_map_.at(symbol.type_);

      llvm::FunctionType *write_ty = llvm::FunctionType::get(
          ir_.getVoidTy(), {child_type, type, ir_.getInt32Ty()}, false);
      llvm::Function *write = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("write" + type_name + "Vec", write_ty)
              .getCallee());

      ir_.CreateCall(write, {symbol.value_, call, ir_.getInt32(i + 1)});
    }
    // return symbol
    Symbol ret = node->type_;
    ret.value_ = call;
    DEBUG_FUNC_EXIT
    return ret;
  }
  // malloc memory
  std::string type_name = type_names_.at(node->type_.type_);
  llvm::Type *type = type_map_.at(node->type_.type_);

  llvm::FunctionType *init_ty =
      llvm::FunctionType::get(type, {ir_.getInt32Ty()}, false);
  llvm::Function *init = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("init" + type_name, init_ty).getCallee());

  auto call = ir_.CreateCall(init, {ir_.getInt32(node->type_.size0_)});

  // copy memory
  for (size_t i = 0; i < node->values_.size(); ++i) {
    auto symbol = node->values_[i]->visit(this);
    if (symbol.type_ == Type::_NULL_) {
      llvm::FunctionType *write_ty = llvm::FunctionType::get(
          ir_.getVoidTy(),
          {ir_.getInt32Ty(), llvm::Type::getInt32PtrTy(global_ctx_),
           ir_.getInt32Ty()},
          false);
      llvm::Function *write = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("writeIntVec", write_ty).getCallee());

      ir_.CreateCall(write, {ir_.getInt32(0), call, ir_.getInt32(i + 1)});
    } else if (symbol.type_ == Type::IDENTITY) {
      llvm::FunctionType *write_ty = llvm::FunctionType::get(
          ir_.getVoidTy(),
          {ir_.getInt32Ty(), llvm::Type::getInt32PtrTy(global_ctx_),
           ir_.getInt32Ty()},
          false);
      llvm::Function *write = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("writeIntVec", write_ty).getCallee());

      ir_.CreateCall(write, {ir_.getInt32(1), call, ir_.getInt32(i + 1)});
    } else {
      llvm::Type *child_type = type_map_.at(symbol.type_);
      llvm::FunctionType *write_ty = llvm::FunctionType::get(
          ir_.getVoidTy(), {child_type, type, ir_.getInt32Ty()}, false);
      llvm::Function *write = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("write" + type_name, write_ty).getCallee());

      ir_.CreateCall(write, {symbol.value_, call, ir_.getInt32(i + 1)});
    }
  }
  // return symbol
  Symbol ret = node->type_;
  ret.value_ = call;
  DEBUG_FUNC_EXIT
  return ret;
}

Symbol CodeGenPass::visitStringNode(StringNode *node) {
  DEBUG_FUNC_ENTRY
  llvm::FunctionType *func_ty = llvm::FunctionType::get(
      llvm::Type::getInt8PtrTy(global_ctx_),
      {llvm::Type::getInt8PtrTy(global_ctx_), ir_.getInt32Ty()}, false);
  llvm::Function *func = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("initAndWriteString", func_ty).getCallee());

  auto call =
      ir_.CreateCall(func, {ir_.CreateGlobalStringPtr(node->value_.c_str()),
                            ir_.getInt32(node->value_.size())});
  DEBUG_FUNC_EXIT
  return {Type::STRING, call, Qualifier::CONST, node->value_.size()};
}

Symbol CodeGenPass::visitBinaryExpr(BinaryExpr *node) {
  DEBUG_FUNC_ENTRY
  auto lhs = node->left_sub_expr_->visit(this);
  auto rhs = node->right_sub_expr_->visit(this);

  llvm::Value *value;

  // handles NEQ and EQ for tuple comparison
  if (lhs.type_ == Type::TUPLE && rhs.type_ == Type::TUPLE) {
    if (node->token_ == Token::NE) {
      value = ir_.getInt1(false);
    } else if (node->token_ == Token::EQ) {
      value = ir_.getInt1(true);
    } else {
      throw PanicError();
    }
    for (size_t i = 0; i < lhs.children_.size(); ++i) {
      auto function =
          binary_functions_.at({node->token_, lhs.children_[i].second.type_,
                                rhs.children_[i].second.type_});

      llvm::Type *lhs_type = type_map_.at(lhs.children_[i].second.type_);
      llvm::Type *rhs_type = type_map_.at(rhs.children_[i].second.type_);

      llvm::FunctionType *variable_ty =
          llvm::FunctionType::get(ir_.getInt1Ty(), {lhs_type, rhs_type}, false);
      llvm::Function *variable = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction(function.first, variable_ty).getCallee());

      auto lhs_load = ir_.CreateLoad(lhs_type, lhs.value_);
      auto rhs_load = ir_.CreateLoad(rhs_type, rhs.value_);
      auto call = ir_.CreateCall(variable, {lhs_load, rhs_load});

      if (node->token_ == Token::NE) {
        value = ir_.CreateOr(value, call);
      } else if (node->token_ == Token::EQ) {
        value = ir_.CreateAnd(value, call);
      }
    }
    DEBUG_FUNC_EXIT
    return {Type::BOOLEAN, value};
  } else {
    auto function = binary_functions_.at({node->token_, lhs.type_, rhs.type_});

    llvm::Type *return_type = type_map_.at(function.second);
    llvm::Type *lhs_type = type_map_.at(lhs.type_);
    llvm::Type *rhs_type = type_map_.at(rhs.type_);

    llvm::FunctionType *variable_ty =
        llvm::FunctionType::get(return_type, {lhs_type, rhs_type}, false);
    llvm::Function *variable = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction(function.first, variable_ty).getCallee());

    value = ir_.CreateCall(variable, {lhs.value_, rhs.value_});
    DEBUG_FUNC_EXIT
    return {function.second, value};
  }
}

Symbol CodeGenPass::visitBlock(Block *node) {
  DEBUG_FUNC_ENTRY
  pushScope(node->node_id_);
  for (auto &statement : node->statements_) {
    statement->visit(this);
  }
  popScope();
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitConditionStatement(ConditionStatement *node) {
  DEBUG_FUNC_ENTRY
  auto value = node->condition_expr_->visit(this);
  // basic block pointer creation
  llvm::Function *func = ir_.GetInsertBlock()->getParent();
  llvm::BasicBlock *if_body =
      llvm::BasicBlock::Create(global_ctx_, "if_body", func);
  llvm::BasicBlock *else_body;
  if (node->false_block_ != nullptr) {
    else_body = llvm::BasicBlock::Create(global_ctx_, "else_body", func);
  }
  llvm::BasicBlock *exit = llvm::BasicBlock::Create(global_ctx_, "exit");

  // conditional
  llvm::Value *lhs = ir_.getInt1(0);
  llvm::Value *rhs = value.value_;
  llvm::Value *cmp = ir_.CreateICmpNE(lhs, rhs);
  if (node->false_block_ != nullptr) {
    ir_.CreateCondBr(cmp, if_body, else_body);
  } else {
    ir_.CreateCondBr(cmp, if_body, exit);
  }

  // if block
  ir_.SetInsertPoint(if_body);
  node->true_block_->visit(this);
  ir_.CreateBr(exit);

  // else block
  if (node->false_block_ != nullptr) {
    ir_.SetInsertPoint(else_body);
    node->false_block_->visit(this);
    ir_.CreateBr(exit);
  }

  // exit the if statement
  func->getBasicBlockList().push_back(exit);
  ir_.SetInsertPoint(exit);

  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitDeclareStatement(DeclareStatement *node) {
  DEBUG_FUNC_ENTRY
  auto variable = current_scope_->resolve(node->id_);
  // Global variable
  if (current_function_ == nullptr) {
    llvm::Type *type = type_map_.at(variable.type_);
    auto value = createGlobal(type, node->id_, node->main_expr_.get());
    variable.value_ = value;
    // we are currently in global scope so variable has to be declared in
    // current scope
    current_scope_->declare(node->id_, variable);
    DEBUG_FUNC_EXIT
    return {};
  }

  Symbol value = variable;

  if (node->main_expr_ != nullptr) {
    value = node->main_expr_->visit(this);
  } else {
    value = defaultConstruct(variable);
  }
  llvm::Type *type = type_map_.at(variable.type_);
  llvm::Value *memory;
  memory = createAlloca(type);
  ir_.CreateStore(value.value_, memory);

  variable.value_ = memory;
  variable.children_ = value.children_;
  current_scope_->declare(node->id_, variable);
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitDomainExpr(DomainExpr *node) {
  DEBUG_FUNC_ENTRY
  DEBUG_FUNC_EXIT
  return node->main_expr_->visit(this);
}
Symbol CodeGenPass::visitIdentityNode(IdentityNode *node) {
  DEBUG_FUNC_ENTRY
  DEBUG_FUNC_EXIT
  return {Type::IDENTITY};
}

Symbol CodeGenPass::visitIntervalNode(IntervalNode *node) {
  DEBUG_FUNC_ENTRY
  llvm::Type *type = type_map_.at(Type::INTERVAL);

  llvm::FunctionType *init_ty = llvm::FunctionType::get(
      type, {ir_.getInt32Ty(), ir_.getInt32Ty()}, false);
  llvm::Function *init = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("defaultConstructInterval", init_ty)
          .getCallee());

  auto lower = node->lowerbound_->visit(this);
  auto upper = node->upperbound_->visit(this);

  auto call = ir_.CreateCall(init, {lower.value_, upper.value_});

  DEBUG_FUNC_EXIT
  return {Type::INTERVAL, call};
}

Symbol CodeGenPass::visitNullNode(NullNode *node) {
  DEBUG_FUNC_ENTRY
  DEBUG_FUNC_EXIT
  return {Type::_NULL_};
}
Symbol CodeGenPass::visitBreakNode(BreakNode *node) {
  DEBUG_FUNC_ENTRY
  if (loop_exit_.size() == 0) {
    throw JumpStatementError("break", node->node_line_);
  }
  auto jump_point = loop_exit_.back();
  ir_.CreateBr(jump_point);
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitContinueNode(ContinueNode *node) {
  DEBUG_FUNC_ENTRY
  if (loop_entry_.size() == 0) {
    throw JumpStatementError("continue", node->node_line_);
  }
  auto jump_point = loop_entry_.back();
  ir_.CreateBr(jump_point);
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitReturnNode(ReturnNode *node) {
  DEBUG_FUNC_ENTRY
  if (node->return_value_ == nullptr) {
    ir_.CreateRetVoid();
    DEBUG_FUNC_EXIT
    return {};
  }
  auto symbol = node->return_value_->visit(this);
  ir_.CreateRet(symbol.value_);
  DEBUG_FUNC_EXIT
  return {};
}

Symbol CodeGenPass::visitFileNode(FileNode *node) {
  DEBUG_FUNC_ENTRY
  pushScope(node->node_id_);
  for (auto &i : node->children_) {
    i->visit(this);
  }
  popScope();
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitFilterExpr(FilterExpr *node) {
  DEBUG_FUNC_ENTRY
  llvm::Function *func = ir_.GetInsertBlock()->getParent();

  pushScope(node->node_id_);

  Symbol ret = {Type::TUPLE};

  auto domain = node->domain_->visit(this);

  // malloc tuple ptr
  llvm::FunctionType *malloc_ty =
      llvm::FunctionType::get(ir_.getInt8PtrTy(), {ir_.getInt32Ty()}, false);
  llvm::Function *malloc_func = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("malloc", malloc_ty).getCallee());

  ret.value_ =
      ir_.CreateCall(malloc_func, {ir_.getInt32(node->sub_exprs_.size() * 4)});

  llvm::Type *type = type_map_.at(domain.type_);
  std::string type_name = type_names_.at(domain.type_);
  llvm::Type *base_type = type_map_.at(TypeHelpers::getBaseType(domain.type_));
  std::string base_type_name =
      type_names_.at(TypeHelpers::getBaseType(domain.type_));

  for (size_t i = 0; i <= node->sub_exprs_.size(); ++i) {

    // malloc memory for vector
    llvm::FunctionType *init_ty = llvm::FunctionType::get(type, {type}, false);
    llvm::Function *init = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("init" + type_name + "Vec", init_ty)
            .getCallee());
    ret.children_.push_back({"", {}});
    ret.children_[i].second.value_ = ir_.CreateCall(init, {domain.value_});

    // store vector pointer into tuple and store correct pointer and type in
    // children
    llvm::FunctionType *store_ty = llvm::FunctionType::get(
        type->getPointerTo(0),
        {llvm::Type::getInt8PtrTy(global_ctx_), ir_.getInt32Ty(), type}, false);
    llvm::Function *store = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("createStore" + type_name, store_ty)
            .getCallee());

    ret.children_[i].second.type_ = domain.type_;
    ret.children_[i].second.value_ =
        ir_.CreateCall(store, {ret.value_, ir_.getInt32(i + 1),
                               ret.children_[i].second.value_});
  }

  // alloca write pointers
  std::vector<llvm::Value *> indices;
  for (size_t i = 0; i <= node->sub_exprs_.size(); i++) {
    indices.push_back(createAlloca(ir_.getInt32Ty()));
    ir_.CreateStore(ir_.getInt32(0), indices[i]);
  }

  auto index = createAlloca(ir_.getInt32Ty());
  ir_.CreateStore(ir_.getInt32(-1), index);
  auto sentinel = createAlloca(ir_.getInt32Ty());

  // get length of domain expr
  llvm::FunctionType *length_ty =
      llvm::FunctionType::get(ir_.getInt32Ty(), {type}, false);
  llvm::Function *length = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("length" + type_name, length_ty).getCallee());
  auto call_length = ir_.CreateCall(length, domain.value_);

  ir_.CreateStore(call_length, sentinel);

  // start iterator loop
  llvm::BasicBlock *for_comp =
      llvm::BasicBlock::Create(global_ctx_, "for_check", func);
  llvm::BasicBlock *body =
      llvm::BasicBlock::Create(global_ctx_, "for_body", func);
  llvm::BasicBlock *exit =
      llvm::BasicBlock::Create(global_ctx_, "for_exit", func);

  auto symbol = current_scope_->resolve(node->domain_->id_);

  // alloca domain identifier
  symbol.value_ = createAlloca(base_type);
  current_scope_->declare(node->domain_->id_, symbol);

  ir_.CreateBr(for_comp);
  ir_.SetInsertPoint(for_comp);

  llvm::Value *value = ir_.CreateLoad(ir_.getInt32Ty(), index);
  value = ir_.CreateAdd(value, ir_.getInt32(1));
  ir_.CreateStore(value, index);

  // create comparison
  llvm::Value *rhs = ir_.CreateLoad(sentinel);
  llvm::Value *cmp = ir_.CreateICmpNE(value, rhs);
  ir_.CreateCondBr(cmp, body, exit);
  ir_.SetInsertPoint(body);

  llvm::FunctionType *load_ty =
      llvm::FunctionType::get(base_type, {type, ir_.getInt32Ty()}, false);
  llvm::Function *load = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("get" + type_name, load_ty).getCallee());
  auto call_load = ir_.CreateCall(load, {domain.value_, value});

  ir_.CreateStore(call_load, symbol.value_);

  // get domain[i] where i is the loop iterator
  llvm::FunctionType *get_ty =
      llvm::FunctionType::get(base_type, {type, ir_.getInt32Ty()}, false);
  llvm::Function *get = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("get" + type_name, get_ty).getCallee());
  auto read_value = ir_.CreateCall(get, {domain.value_, value});

  llvm::Value *false_for_all = ir_.getInt1(false);

  for (size_t i = 0; i < node->sub_exprs_.size(); i++) {
    auto expr = node->sub_exprs_[i]->visit(this);
    false_for_all = ir_.CreateOr(false_for_all, expr.value_);
    // if value
    llvm::BasicBlock *if_block =
        llvm::BasicBlock::Create(global_ctx_, "if_block", func);
    llvm::BasicBlock *if_exit =
        llvm::BasicBlock::Create(global_ctx_, "if_exit", func);

    llvm::Value *lhs = ir_.getInt1(0);
    llvm::Value *cmp = ir_.CreateICmpNE(lhs, expr.value_);

    ir_.CreateCondBr(cmp, if_block, if_exit);
    ir_.SetInsertPoint(if_block);

    auto write_ptr = ir_.CreateLoad(type, ret.children_[i].second.value_);
    llvm::Value *data_index = ir_.CreateLoad(ir_.getInt32Ty(), indices[i]);

    // write read value to the correct vector in the tuple
    llvm::FunctionType *write_type = llvm::FunctionType::get(
        ir_.getVoidTy(), {base_type, type, ir_.getInt32Ty()}, false);
    llvm::Function *write = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("write" + type_name, write_type).getCallee());
    ir_.CreateCall(write, {read_value, write_ptr, data_index});

    // increment the write index
    data_index = ir_.CreateAdd(data_index, ir_.getInt32(1));
    ir_.CreateStore(data_index, indices[i]);

    ir_.CreateBr(if_exit);
    ir_.SetInsertPoint(if_exit);
  }

  llvm::BasicBlock *if_block =
      llvm::BasicBlock::Create(global_ctx_, "if_block", func);
  llvm::BasicBlock *if_exit =
      llvm::BasicBlock::Create(global_ctx_, "if_exit", func);

  llvm::Value *lhs = ir_.getInt1(0);
  llvm::Value *compare = ir_.CreateICmpNE(lhs, false_for_all);

  ir_.CreateCondBr(compare, if_block, if_exit);
  ir_.SetInsertPoint(if_block);

  // if false for all store into end vector
  auto write_ptr = ir_.CreateLoad(
      type, ret.children_[node->sub_exprs_.size()].second.value_);
  llvm::Value *data_index =
      ir_.CreateLoad(ir_.getInt32Ty(), indices[node->sub_exprs_.size()]);

  // write read value to the correct
  llvm::FunctionType *write_type = llvm::FunctionType::get(
      ir_.getVoidTy(), {base_type, type, ir_.getInt32Ty()}, false);
  llvm::Function *write = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction("write" + type_name, write_type).getCallee());
  ir_.CreateCall(write, {read_value, write_ptr, data_index});

  // increment the write index
  data_index = ir_.CreateAdd(data_index, ir_.getInt32(1));
  ir_.CreateStore(data_index, indices[node->sub_exprs_.size()]);

  ir_.CreateBr(if_exit);
  ir_.SetInsertPoint(if_exit);
  ir_.CreateBr(for_comp);

  ir_.SetInsertPoint(exit);

  popScope();
  DEBUG_FUNC_EXIT
  return ret;
}

Symbol CodeGenPass::visitBuiltInCall(BuiltInCall *node) {
  DEBUG_FUNC_ENTRY
  Symbol arg;
  if (node->arg_)
    arg = node->arg_->visit(this);
  llvm::Type *type = type_map_.at(arg.type_);

  // TODO: case of null or identity vector
  llvm::Type *return_type = type_map_.at(node->return_type_);

  std::string func_name = built_in_functions_.at({node->token_, arg.type_});

  llvm::FunctionType *function_ty =
      llvm::FunctionType::get(return_type, {type}, false);
  llvm::Function *function = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction(func_name, function_ty).getCallee());

  auto value = ir_.CreateCall(function, {arg.value_});

  DEBUG_FUNC_EXIT
  return {node->return_type_, value};
}
Symbol CodeGenPass::visitFunctionCallNode(FunctionCallNode *node) {
  DEBUG_FUNC_ENTRY
  auto function_symbol = current_scope_->resolve(node->id_);
  std::vector<llvm::Type *> argument_types;
  std::vector<llvm::Value *> arguments;
  for (auto &i : node->args_) {
    auto arg = i->visit(this);
    llvm::Type *type = type_map_.at(arg.type_);
    argument_types.push_back(type);
    arguments.push_back(arg.value_);
  }

  llvm::Type *return_type = type_map_.at(function_symbol.return_type_);
  llvm::FunctionType *function_ty =
      llvm::FunctionType::get(return_type, argument_types, false);
  llvm::Function *function = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction(node->id_, function_ty).getCallee());

  auto value = ir_.CreateCall(function, arguments);

  // TODO: check if this test is needed
  if (function_symbol.return_type_ != Type::NONE) {
    DEBUG_FUNC_EXIT
    return {function_symbol.return_type_, value};
  }
  DEBUG_FUNC_EXIT
  return {function_symbol.return_type_, nullptr};
}
Symbol CodeGenPass::visitFunctionDeclNode(FunctionDeclNode *node) {
  DEBUG_FUNC_ENTRY
  auto function = current_scope_->resolve(node->id_);
  auto return_type = node->return_type_->visit(this);
  pushScope(node->node_id_);

  std::vector<llvm::Type *> types;
  for (auto &i : function.children_) {
    types.push_back(type_map_.at(i.second.type_));
  }
  llvm::FunctionType *func_ty =
      llvm::FunctionType::get(type_map_.at(return_type.type_), types, false);
  llvm::Function *llvm_function = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction(node->id_, func_ty).getCallee());

  if (node->body_ != nullptr) {
    llvm::BasicBlock *block = llvm::BasicBlock::Create(
        global_ctx_, "entry",
        llvm_function); // check if this is correct: "entry"
    current_function_ = block;
    ir_.SetInsertPoint(block);
    for (size_t i = 0; i < node->params_.size(); i++) {
      auto arg_pointer = llvm_function->getArg(i);
      arg_pointer->setName(function.children_[i].first);
      llvm::Type *type = type_map_.at(function.children_[i].second.type_);
      auto stack_ptr = createAlloca(type);
      ir_.CreateStore(arg_pointer, stack_ptr);
      function.children_[i].second.value_ = stack_ptr;
      current_scope_->declare(function.children_[i].first,
                              function.children_[i].second);
    }

    if (node->body_->token_ == Token::BLOCK) {
      node->body_->visit(this);
      // do we need to change insertion point after the visit?
    } else {
      auto symbol = node->body_->visit(this);
      ir_.CreateRet(symbol.value_);
      // do we need to change insertion point after the visit?
    }
  }
  current_function_ = nullptr;
  popScope();
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitFunctionParamNode(FunctionParamNode *node) {
  // dont need to visit this
  return {};
}
Symbol CodeGenPass::visitGeneratorExpr(GeneratorExpr *node) {
  DEBUG_FUNC_ENTRY

  llvm::Function *func = ir_.GetInsertBlock()->getParent();
  pushScope(node->node_id_);

  std::vector<llvm::BasicBlock *> for_comps;
  std::vector<llvm::BasicBlock *> bodies;
  std::vector<llvm::BasicBlock *> exits;

  std::vector<Symbol> domains;
  for (auto &i : node->domains_) {
    domains.push_back(i->visit(this));
  }

  Symbol ret;
  if (node->domains_.size() == 1) {
    if (domains[0].type_ == Type::INTERVAL) {
      ret.type_ = Type::VECTOR_INTEGER;

      llvm::FunctionType *init_vec_ty =
          llvm::FunctionType::get(llvm::Type::getInt32PtrTy(global_ctx_),
                                  {type_map_.at(Type::INTERVAL)}, false);
      llvm::Function *init_vec = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("initInterval", init_vec_ty).getCallee());
      ret.value_ = ir_.CreateCall(init_vec, domains[0].value_);
    } else {
      ret.type_ = domains[0].type_;
      ret.size0_ = domains[0].size0_;
      ret.value_ = domains[0].value_;
    }
  }
  if (node->domains_.size() == 2) {
    if (domains[0].type_ == Type::INTERVAL &&
        domains[1].type_ == Type::INTERVAL) {
      ret.type_ = Type::MATRIX_INTEGER;
      ret.size0_ = domains[0].size0_;
      ret.size1_ = domains[1].size0_;

      llvm::Type *type = type_map_.at(ret.type_);
      std::string type_name = type_names_.at(ret.type_);

      llvm::Type *interval_type = type_map_.at(Type::INTERVAL);

      llvm::FunctionType *init_vec_ty =
          llvm::FunctionType::get(type, {interval_type, interval_type}, false);
      llvm::Function *init_vec = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("init" + type_name + "IntervalInterval",
                                   init_vec_ty)
              .getCallee());
      ret.value_ =
          ir_.CreateCall(init_vec, {domains[0].value_, domains[1].value_});
    } else if (domains[0].type_ == Type::INTERVAL) {
      ret.type_ = Type::VECTOR_INTEGER;
      ret.size0_ = domains[0].size0_;
      ret.size1_ = domains[1].size0_;

      llvm::Type *type = type_map_.at(ret.type_);
      std::string type_name = type_names_.at(ret.type_);

      llvm::FunctionType *init_vec_ty = llvm::FunctionType::get(
          type, {type_map_.at(Type::INTERVAL), ir_.getInt32Ty()}, false);
      llvm::Function *init_vec = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("init" + type_name + "IntervalVec",
                                   init_vec_ty)
              .getCallee());
      ret.value_ =
          ir_.CreateCall(init_vec, {domains[0].value_, domains[1].value_});
    } else if (domains[1].type_ == Type::INTERVAL) {
      ret.type_ = Type::VECTOR_INTEGER;
      ret.size0_ = domains[0].size0_;
      ret.size1_ = domains[1].size0_;

      llvm::Type *type = type_map_.at(ret.type_);
      std::string type_name = type_names_.at(ret.type_);

      llvm::FunctionType *init_vec_ty = llvm::FunctionType::get(
          type, {ir_.getInt32Ty(), type_map_.at(Type::INTERVAL)}, false);
      llvm::Function *init_vec = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("init" + type_name + "VecInterval",
                                   init_vec_ty)
              .getCallee());
      ret.value_ =
          ir_.CreateCall(init_vec, {domains[0].value_, domains[1].value_});
    } else {
      ret.type_ = TypeHelpers::vectorToMatrix(domains[0].type_);
      ret.size0_ = domains[0].size0_;
      ret.size1_ = domains[1].size0_;

      llvm::Type *type = type_map_.at(ret.type_);
      std::string type_name = type_names_.at(ret.type_);

      llvm::FunctionType *init_vec_ty =
          llvm::FunctionType::get(type, {ir_.getInt32Ty()}, false);
      llvm::Function *init_vec = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("init" + type_name + "VecVec", init_vec_ty)
              .getCallee());
      ret.value_ =
          ir_.CreateCall(init_vec, {domains[0].value_, domains[1].value_});
    }
  }

  std::vector<llvm::Value *> lengths;
  std::vector<llvm::Value *> indices(2);

  for (size_t i = 0; i < node->domains_.size(); i++) {
    std::string ptr_type_name = type_names_.at(domains[i].type_);
    auto ptr_type = type_map_.at(domains[i].type_);
    auto type = type_map_.at(TypeHelpers::getBaseType(domains[i].type_));
    auto symbol = current_scope_->resolve(node->domains_[i]->id_);

    // alloca domain identifier
    symbol.value_ = createAlloca(type);
    current_scope_->declare(node->domains_[i]->id_, symbol);

    indices[i] = createAlloca(ir_.getInt32Ty());
    // get length of domain expr
    llvm::FunctionType *length_ty =
        llvm::FunctionType::get(ir_.getInt32Ty(), {ptr_type}, false);
    llvm::Function *length = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("length" + ptr_type_name, length_ty)
            .getCallee());
    llvm::Value *call_length = ir_.CreateCall(length, domains[i].value_);
    lengths.push_back(ir_.CreateAdd(call_length, ir_.getInt32(1)));

    ir_.CreateStore(lengths[i], indices[i]);
  }

  // iterating over all existing domains in loop
  for (size_t i = 0; i < node->domains_.size(); i++) {
    if (exits.size()) {
      exits.push_back(for_comps.back());
    } else {
      exits.push_back(llvm::BasicBlock::Create(global_ctx_, "for_exit"));
    }
    for_comps.push_back(
        llvm::BasicBlock::Create(global_ctx_, "for_check", func));
    bodies.push_back(llvm::BasicBlock::Create(global_ctx_, "for_body", func));

    std::string ptr_type_name = type_names_.at(domains[i].type_);
    auto ptr_type = type_map_.at(domains[i].type_);
    auto type = type_map_.at(TypeHelpers::getBaseType(domains[i].type_));
    auto symbol = current_scope_->resolve(node->domains_[i]->id_);

    ir_.CreateBr(for_comps.back());
    ir_.SetInsertPoint(for_comps.back());

    llvm::Value *value = ir_.CreateLoad(ir_.getInt32Ty(), indices[i]);
    value = ir_.CreateSub(value, ir_.getInt32(1));
    ir_.CreateStore(value, indices[i]);

    if (i == 0 && node->domains_.size() == 2) {
      ir_.CreateStore(lengths[1], indices[1]);
    }

    // create comparison
    llvm::Value *lhs = ir_.getInt32(0);
    llvm::Value *rhs = value;
    llvm::Value *cmp = ir_.CreateICmpNE(lhs, rhs);
    ir_.CreateCondBr(cmp, bodies.back(), exits.back());
    ir_.SetInsertPoint(bodies.back());

    llvm::FunctionType *load_ty =
        llvm::FunctionType::get(type, {ptr_type, ir_.getInt32Ty()}, false);
    llvm::Function *load = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("get" + ptr_type_name, load_ty).getCallee());
    auto call_load = ir_.CreateCall(load, {domains[i].value_, value});

    ir_.CreateStore(call_load, symbol.value_);
  }

  loop_entry_.push_back(for_comps[0]);
  loop_exit_.push_back(exits[0]);

  auto value = node->main_expr_->visit(this);

  if (TypeHelpers::isMatrix(ret.type_)) {
    auto base_type = type_map_.at(TypeHelpers::getBaseType(ret.type_));
    auto type = type_map_.at(ret.type_);
    std::string type_name = type_names_.at(ret.type_);

    llvm::FunctionType *write_type = llvm::FunctionType::get(
        ir_.getVoidTy(), {base_type, type, ir_.getInt32Ty(), ir_.getInt32Ty()},
        false);
    llvm::Function *write = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("write" + type_name, write_type).getCallee());
    auto load0 = ir_.CreateLoad(indices[0]);
    auto load1 = ir_.CreateLoad(indices[1]);
    ir_.CreateCall(write, {value.value_, ret.value_, load0, load1});
  } else if (TypeHelpers::isVector(ret.type_)) {
    auto base_type = type_map_.at(TypeHelpers::getBaseType(ret.type_));
    auto type = type_map_.at(ret.type_);
    std::string type_name = type_names_.at(ret.type_);

    llvm::FunctionType *write_type = llvm::FunctionType::get(
        ir_.getVoidTy(), {base_type, type, ir_.getInt32Ty()}, false);
    llvm::Function *write = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("write" + type_name, write_type).getCallee());
    auto load = ir_.CreateLoad(indices[0]);
    ir_.CreateCall(write, {value.value_, ret.value_, load});
  }

  ir_.CreateBr(for_comps.back());

  func->getBasicBlockList().push_back(exits[0]);
  ir_.SetInsertPoint(exits[0]);

  popScope();
  DEBUG_FUNC_EXIT
  return ret;
}

Symbol CodeGenPass::visitIdNode(IdNode *node) {
  DEBUG_FUNC_ENTRY
  auto symbol = current_scope_->resolve(node->id_name_);

  std::string type_name;
  if (symbol.type_ != Type::TUPLE) {
    type_name = type_names_.at(symbol.type_);
  }
  switch (node->token_) {
  case Token::ID_EXPR: {
    if (symbol.type_ == Type::TUPLE) {
      // malloc tuple ptr
      llvm::FunctionType *malloc_ty = llvm::FunctionType::get(
          ir_.getInt8PtrTy(), {ir_.getInt32Ty()}, false);
      llvm::Function *malloc_func = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("malloc", malloc_ty).getCallee());

      symbol.value_ = ir_.CreateCall(
          malloc_func, {ir_.getInt32(symbol.children_.size() * 4)});
      // iterate over children to store
      for (size_t i = 0; i < symbol.children_.size(); ++i) {
        symbol.children_[i].second = copySymbol(symbol.children_[i].second);

        llvm::Type *child_type = type_map_.at(symbol.children_[i].second.type_);
        std::string child_type_name =
            type_names_.at(symbol.children_[i].second.type_);

        llvm::FunctionType *store_ty =
            llvm::FunctionType::get(child_type->getPointerTo(0),
                                    {llvm::Type::getInt8PtrTy(global_ctx_),
                                     ir_.getInt32Ty(), child_type},
                                    false);
        llvm::Function *store = llvm::cast<llvm::Function>(
            mod_.getOrInsertFunction("createStore" + child_type_name, store_ty)
                .getCallee());

        symbol.children_[i].second.value_ =
            ir_.CreateCall(store, {symbol.value_, ir_.getInt32(i + 1),
                                   symbol.children_[i].second.value_});
      }
    } else {
      symbol = copySymbol(symbol);
    }
    break;
  }
  case Token::ID_TUPLE_INT_INDEX: {
    symbol = symbol.children_[node->int_index_].second;
    llvm::Type *child_type = type_map_.at(symbol.type_);
    symbol.value_ = ir_.CreateLoad(child_type->getPointerTo(0), symbol.value_);
    symbol = copySymbol(symbol);
    break;
  }
  case Token::ID_TUPLE_ID_INDEX: {
    auto iter =
        std::find_if(symbol.children_.begin(), symbol.children_.end(),
                     [node](auto i) { return node->id_index_ == i.first; });
    symbol = iter->second;
    llvm::Type *child_type = type_map_.at(symbol.type_);
    symbol.value_ = ir_.CreateLoad(child_type->getPointerTo(0), symbol.value_);
    symbol = copySymbol(symbol);
    break;
  }
  case Token::ID_VECTOR_INDEX: {
    // get index and symbol values
    auto index = node->index0_->visit(this);
    auto index_type = type_map_.at(index.type_);
    std::string index_name = type_names_.at(index.type_);

    auto symbol_type = type_map_.at(symbol.type_);
    std::string symbol_name = type_names_.at(symbol.type_);
    Type ret_type = symbol.type_;

    // if index is scalar
    if (TypeHelpers::isScalar(index.type_)) {
      index_name = "";
      ret_type = TypeHelpers::getBaseType(symbol.type_);
    }
    auto llvm_ret_type = type_map_.at(ret_type);

    llvm::FunctionType *get_ty = llvm::FunctionType::get(
        llvm_ret_type, {symbol_type, index_type}, false);
    llvm::Function *get = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("get" + symbol_name + index_name, get_ty)
            .getCallee());

    auto load = ir_.CreateLoad(symbol.value_);

    symbol.value_ = ir_.CreateCall(get, {load, index.value_});
    symbol.type_ = ret_type;
    symbol.size0_ = index.size0_;
    break;
  }
  case Token::ID_MATRIX_INDEX: {
    // get indexes and symbol values
    auto index0 = node->index0_->visit(this);
    auto index0_type = type_map_.at(index0.type_);
    std::string index0_name = type_names_.at(index0.type_);

    auto index1 = node->index1_->visit(this);
    auto index1_type = type_map_.at(index1.type_);
    std::string index1_name = type_names_.at(index1.type_);

    auto symbol_type = type_map_.at(symbol.type_);
    std::string symbol_name = type_names_.at(symbol.type_);
    Type ret_type = TypeHelpers::matrixToVector(symbol.type_);

    if (TypeHelpers::isScalar(index0.type_) &&
        TypeHelpers::isScalar(index1.type_)) {
      index0_name = "";
      index1_name = "";
      ret_type = TypeHelpers::getBaseType(symbol.type_);
    } else if (TypeHelpers::isVector(index0.type_) &&
               TypeHelpers::isVector(index1.type_)) {
      ret_type = symbol.type_;
    }
    auto llvm_ret_type = type_map_.at(ret_type);

    llvm::FunctionType *get_ty = llvm::FunctionType::get(
        llvm_ret_type, {symbol_type, index0_type, index1_type}, false);
    llvm::Function *get = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction(
                "get" + symbol_name + index0_name + index1_name, get_ty)
            .getCallee());

    auto load = ir_.CreateLoad(symbol.value_);

    symbol.value_ = ir_.CreateCall(get, {load, index0.value_, index1.value_});
    symbol.type_ = ret_type;
    symbol.size0_ = index0.size0_;
    symbol.size1_ = index1.size0_;
    break;
  }
  case Token::ID_TUPLE_ID_INDEX_VECTOR: {
    auto iter =
        std::find_if(symbol.children_.begin(), symbol.children_.end(),
                     [node](auto &i) { return node->id_index_ == i.first; });
    symbol = iter->second;
    llvm::Type *child_type = type_map_.at(symbol.type_);
    symbol.value_ = ir_.CreateLoad(child_type->getPointerTo(0), symbol.value_);

    auto index = node->index0_->visit(this);
    auto index_type = type_map_.at(index.type_);
    std::string index_name = type_names_.at(index.type_);

    auto symbol_type = type_map_.at(symbol.type_);
    std::string symbol_name = type_names_.at(symbol.type_);
    auto ret_type = type_map_.at(symbol.type_);

    if (TypeHelpers::isScalar(index.type_)) {
      index_name = "";
      ret_type = type_map_.at(TypeHelpers::getBaseType(symbol.type_));
    }

    llvm::FunctionType *get_ty =
        llvm::FunctionType::get(ret_type, {symbol_type, index_type}, false);
    llvm::Function *get = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("get" + symbol_name + index_name, get_ty)
            .getCallee());

    symbol.value_ = ir_.CreateCall(get, {symbol.value_, index.value_});
    symbol.type_ = index.type_;
    symbol.size0_ = index.size0_;
    break;
  }
  case Token::ID_TUPLE_ID_INDEX_MATRIX: {
    symbol = symbol.children_[node->int_index_].second;
    llvm::Type *child_type = type_map_.at(symbol.type_);
    symbol.value_ = ir_.CreateLoad(child_type->getPointerTo(0), symbol.value_);

    auto index0 = node->index0_->visit(this);
    auto index0_type = type_map_.at(index0.type_);
    std::string index0_name = type_names_.at(index0.type_);

    auto index1 = node->index1_->visit(this);
    auto index1_type = type_map_.at(index1.type_);
    std::string index1_name = type_names_.at(index1.type_);

    auto symbol_type = type_map_.at(symbol.type_);
    std::string symbol_name = type_names_.at(symbol.type_);
    Type ret_type = TypeHelpers::matrixToVector(symbol.type_);

    if (TypeHelpers::isScalar(index0.type_) &&
        TypeHelpers::isScalar(index1.type_)) {
      index0_name = "";
      index1_name = "";
      ret_type = TypeHelpers::getBaseType(symbol.type_);
    } else if (TypeHelpers::isVector(index0.type_) &&
               TypeHelpers::isVector(index1.type_)) {
      ret_type = symbol.type_;
    }
    auto llvm_ret_type = type_map_.at(ret_type);

    llvm::FunctionType *get_ty = llvm::FunctionType::get(
        llvm_ret_type, {symbol_type, index0_type, index1_type}, false);
    llvm::Function *get = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction(
                "get" + symbol_name + index0_name + index1_name, get_ty)
            .getCallee());

    symbol.value_ =
        ir_.CreateCall(get, {symbol.value_, index0.value_, index1.value_});
    symbol.type_ = ret_type;
    symbol.size0_ = index0.size0_;
    symbol.size1_ = index1.size0_;
    break;
  }
  default:
    throw PanicError();
  }
  DEBUG_FUNC_EXIT
  return symbol;
}
Symbol CodeGenPass::visitLoop(Loop *node) {
  DEBUG_FUNC_ENTRY
  llvm::Function *func = ir_.GetInsertBlock()->getParent();
  pushScope(node->node_id_);

  // create comparison
  if (node->token_ == Token::PRED_LOOP) {
    // set initial loop instructions
    llvm::BasicBlock *for_comp =
        llvm::BasicBlock::Create(global_ctx_, "for_check", func);
    llvm::BasicBlock *body =
        llvm::BasicBlock::Create(global_ctx_, "for_body", func);
    llvm::BasicBlock *exit = llvm::BasicBlock::Create(global_ctx_, "for_exit");

    loop_entry_.push_back(for_comp);
    loop_exit_.push_back(exit);

    ir_.CreateBr(for_comp);
    ir_.SetInsertPoint(for_comp);
    auto value = node->predicate_expr_->visit(this);
    llvm::Value *lhs = ir_.getInt1(0);
    llvm::Value *rhs = value.value_;
    llvm::Value *cmp = ir_.CreateICmpNE(lhs, rhs);
    ir_.CreateCondBr(cmp, body, exit);
    // create block
    ir_.SetInsertPoint(body);
    node->block_->visit(this);
    ir_.CreateBr(for_comp);
    // create exit
    func->getBasicBlockList().push_back(exit);
    ir_.SetInsertPoint(exit);
  } else if (node->token_ == Token::POST_PRED_LOOP) {
    // set initial loop instructions

    llvm::BasicBlock *body =
        llvm::BasicBlock::Create(global_ctx_, "for_body", func);
    llvm::BasicBlock *exit = llvm::BasicBlock::Create(global_ctx_, "for_exit");
    // create block
    loop_entry_.push_back(body);
    loop_exit_.push_back(exit);

    ir_.CreateBr(body);

    ir_.SetInsertPoint(body);
    node->block_->visit(this);

    auto value = node->predicate_expr_->visit(this);
    llvm::Value *lhs = ir_.getInt1(0);
    llvm::Value *rhs = value.value_;
    llvm::Value *cmp = ir_.CreateICmpNE(lhs, rhs);
    ir_.CreateCondBr(cmp, body, exit);
    // create exit
    func->getBasicBlockList().push_back(exit);
    ir_.SetInsertPoint(exit);
  } else if (node->token_ == Token::ITER_LOOP) {
    std::vector<llvm::BasicBlock *> for_comps;
    std::vector<llvm::BasicBlock *> bodies;
    std::vector<llvm::BasicBlock *> exits;
    // iterating over all existing domains in loop
    std::vector<Symbol> domains;
    std::vector<llvm::Value *> indices;
    std::vector<llvm::Value *> max_indices;
    for (size_t i = 0; i < node->domains_.size(); i++) {
      domains.push_back(node->domains_[i]->visit(this));
      std::string ptr_type_name = type_names_.at(domains[i].type_);
      auto ptr_type = type_map_.at(domains[i].type_);
      auto type = type_map_.at(TypeHelpers::getBaseType(domains[i].type_));
      auto symbol = current_scope_->resolve(node->domains_[i]->id_);

      // alloca domain identifier
      symbol.value_ = createAlloca(type);
      current_scope_->declare(node->domains_[i]->id_, symbol);

      indices.push_back(createAlloca(ir_.getInt32Ty()));
      // get length of domain expr
      llvm::FunctionType *length_ty =
          llvm::FunctionType::get(ir_.getInt32Ty(), {ptr_type}, false);
      llvm::Function *length = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("length" + ptr_type_name, length_ty)
              .getCallee());
      max_indices.push_back(ir_.CreateCall(length, domains[i].value_));

      ir_.CreateStore(ir_.getInt32(0), indices[i]);
    }

    for (size_t i = 0; i < node->domains_.size(); i++) {
      if (exits.size()) {
        exits.push_back(for_comps.back());
      } else {
        exits.push_back(llvm::BasicBlock::Create(global_ctx_, "for_exit"));
      }
      for_comps.push_back(
          llvm::BasicBlock::Create(global_ctx_, "for_check", func));
      bodies.push_back(llvm::BasicBlock::Create(global_ctx_, "for_body", func));

      auto ptr_type = type_map_.at(domains[i].type_);
      auto type = type_map_.at(TypeHelpers::getBaseType(domains[i].type_));
      auto symbol = current_scope_->resolve(node->domains_[i]->id_);
      auto ptr_type_name = type_names_.at(domains[i].type_);

      ir_.CreateBr(for_comps.back());
      ir_.SetInsertPoint(for_comps.back());

      llvm::Value *value = ir_.CreateLoad(ir_.getInt32Ty(), indices[i]);
      value = ir_.CreateAdd(value, ir_.getInt32(1));
      ir_.CreateStore(value, indices[i]);

      for (size_t j = i + 1; j < indices.size(); j++) {
        ir_.CreateStore(ir_.getInt32(0), indices[j]);
      }

      // create comparison
      llvm::Value *lhs = value;
      llvm::Value *rhs = max_indices[i];
      llvm::Value *cmp = ir_.CreateICmpSLE(lhs, rhs);
      ir_.CreateCondBr(cmp, bodies.back(), exits.back());
      ir_.SetInsertPoint(bodies.back());

      llvm::FunctionType *load_ty =
          llvm::FunctionType::get(type, {ptr_type, ir_.getInt32Ty()}, false);
      llvm::Function *load = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("get" + ptr_type_name, load_ty).getCallee());
      auto call_load = ir_.CreateCall(load, {domains[i].value_, value});

      ir_.CreateStore(call_load, symbol.value_);
    }

    loop_entry_.push_back(for_comps[0]);
    loop_exit_.push_back(exits[0]);

    node->block_->visit(this);

    ir_.CreateBr(for_comps.back());

    func->getBasicBlockList().push_back(exits[0]);
    ir_.SetInsertPoint(exits[0]);
  } else if (node->token_ == Token::INF_LOOP) { // infinite loop
    llvm::BasicBlock *for_comp =
        llvm::BasicBlock::Create(global_ctx_, "for_check", func);
    llvm::BasicBlock *body =
        llvm::BasicBlock::Create(global_ctx_, "for_body", func);
    llvm::BasicBlock *exit = llvm::BasicBlock::Create(global_ctx_, "for_exit");

    loop_entry_.push_back(for_comp);
    loop_exit_.push_back(exit);

    ir_.CreateBr(for_comp);
    ir_.SetInsertPoint(for_comp);
    ir_.CreateBr(body);
    // create block
    ir_.SetInsertPoint(body);
    node->block_->visit(this);
    ir_.CreateBr(for_comp);
    // create exit
    func->getBasicBlockList().push_back(exit);
    ir_.SetInsertPoint(exit);
  } else {
    throw PanicError();
  }

  popScope();

  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitProcedureCall(ProcedureCall *node) {
  DEBUG_FUNC_ENTRY
  auto function_symbol = current_scope_->resolve(node->id_);
  std::vector<llvm::Type *> argument_types;
  std::vector<llvm::Value *> arguments;

  for (auto &i : node->args_) {
    auto arg = i->visit(this);
    llvm::Type *type = type_map_.at(arg.type_);
    argument_types.push_back(type);
    arguments.push_back(arg.value_);
  }

  llvm::Type *return_type = ir_.getVoidTy();
  if (function_symbol.return_type_ != Type::NONE) {
    return_type = type_map_.at(function_symbol.return_type_);
  }
  llvm::FunctionType *function_ty =
      llvm::FunctionType::get(return_type, argument_types, false);
  llvm::Function *function = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction(node->id_, function_ty).getCallee());

  auto value = ir_.CreateCall(function, arguments);

  // TODO: check if this test is needed
  if (function_symbol.return_type_ != Type::NONE) {
    DEBUG_FUNC_EXIT
    return {function_symbol.return_type_, value};
  }
  DEBUG_FUNC_EXIT
  return {function_symbol.return_type_, nullptr};
}
Symbol CodeGenPass::visitProcedureDecl(ProcedureDecl *node) {
  DEBUG_FUNC_ENTRY
  auto function = current_scope_->resolve(node->id_);
  auto return_type = Symbol(Type::NONE);
  if (node->return_type_ != nullptr) {
    return_type = node->return_type_->visit(this);
  }
  pushScope(node->node_id_);

  std::vector<llvm::Type *> types;
  for (auto &i : function.children_) {
    types.push_back(type_map_.at(i.second.type_));
  }
  llvm::FunctionType *func_ty =
      llvm::FunctionType::get(type_map_.at(return_type.type_), types, false);
  llvm::Function *llvm_function = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction(node->id_, func_ty).getCallee());

  if (node->body_ != nullptr) {
    llvm::BasicBlock *block = llvm::BasicBlock::Create(
        global_ctx_, "entry",
        llvm_function); // check if this is correct: "entry"
    current_function_ = block;
    ir_.SetInsertPoint(block);

    for (size_t i = 0; i < node->params_.size(); i++) {
      auto arg_pointer = llvm_function->getArg(i);
      arg_pointer->setName(function.children_[i].first);
      llvm::Type *type = type_map_.at(function.children_[i].second.type_);
      // TODO: if qualifier is var, it is pass by reference not by value
      // probably passed everything by value here
      auto stack_ptr = createAlloca(type);
      ir_.CreateStore(arg_pointer, stack_ptr);
      function.children_[i].second.value_ = stack_ptr;
      current_scope_->declare(function.children_[i].first,
                              function.children_[i].second);
    }
    node->body_->visit(this);

    if (node->return_type_ == nullptr) {
      ir_.CreateRetVoid();
    }
    // do we need to change insertion point after the visit?
  }

  current_function_ = nullptr;
  popScope();
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitProcedureParam(ProcedureParam *node) {
  // don't need to visit
  return {};
}

Symbol CodeGenPass::visitStream(Stream *node) {
  DEBUG_FUNC_ENTRY

  if (node->token_ == Token::INSTREAM) {
    auto original_symbol =
        current_scope_->resolve(node->stream_lvalue_->id_name_);
    // def ref should check to make sure l-value has been previously declared
    auto symbol = original_symbol;

    size_t tuple_index;
    if (symbol.type_ == Type::TUPLE) {
      if (!node->stream_lvalue_->id_index_.empty()) {
        // Def ref should check if tuple variable/index exists for tuples
        auto search =
            std::find_if(symbol.children_.begin(), symbol.children_.end(),
                         [node](std::pair<std::string, Symbol> x) {
                           return x.first == node->stream_lvalue_->id_index_;
                         });
        tuple_index = search - symbol.children_.begin();
      } else {
        tuple_index = node->stream_lvalue_->int_index_ - 1;
      }
      symbol = symbol.children_[tuple_index].second;
    }

    std::string type_name = type_names_.at(symbol.type_);
    llvm::Type *return_type = type_map_.at(symbol.type_);

    Symbol new_symbol = {symbol.type_};

    if (TypeHelpers::isVector(symbol.type_) ||
        TypeHelpers::isMatrix(symbol.type_)) {
      type_name = type_names_.at(TypeHelpers::getBaseType(symbol.type_));
      return_type = type_map_.at(TypeHelpers::getBaseType(symbol.type_));
      new_symbol.type_ = TypeHelpers::getBaseType(symbol.type_);
    }

    llvm::FunctionType *variable_ty =
        llvm::FunctionType::get(return_type, false);
    llvm::Function *variable = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("input" + type_name, variable_ty).getCallee());
    auto call = ir_.CreateCall(variable);

    new_symbol.value_ = call;

    assignSymbol(node->stream_lvalue_.get(), original_symbol, new_symbol);

    /*
    // different writing methods depending on l-value
    // Tuple
    if (node->stream_lvalue_->int_index_ > 0 ||
    !node->stream_lvalue_->id_index_.empty()) {
      // Def ref makes sure these are only scalar values
      ir_.CreateStore(call, symbol.children_[tuple_index].second.value_);
      current_scope_->declare(node->stream_lvalue_->id_name_, symbol);
    }
    // Matrix
    else if (node->stream_lvalue_->index1_) {
      llvm::FunctionType *matrix_write_type =
        llvm::FunctionType::get(ir_.getVoidTy(), {return_type,
    return_type->getPointerTo(), ir_.getInt32Ty(), ir_.getInt32Ty()}, false);
      llvm::Function *matrix_write = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("write" + type_name + "Mat",
    matrix_write_type).getCallee());

      auto index0 = node->stream_lvalue_->index0_->visit(this);
      auto index1 = node->stream_lvalue_->index1_->visit(this);

      ir_.CreateCall(matrix_write, {call, symbol.value_, index0.value_,
    index1.value_});
    }
    // Vector
    else if (node->stream_lvalue_->index0_) {
      llvm::FunctionType *vector_write_type =
        llvm::FunctionType::get(ir_.getVoidTy(), {return_type,
    return_type->getPointerTo(), ir_.getInt32Ty()}, false); llvm::Function
    *vector_write = llvm::cast<llvm::Function>( mod_.getOrInsertFunction("write"
    + type_name + "Vec", vector_write_type).getCallee());

      auto index0 = node->stream_lvalue_->index0_->visit(this);

      ir_.CreateCall(vector_write, {call, symbol.value_, index0.value_});
    }
    // Simple type
    else {
      ir_.CreateStore(call, symbol.value_);
    }
    */
  } else if (node->token_ == Token::OUTSTREAM) {
    // TODO: add vector printing/index printing
    auto symbol = node->stream_expr_->visit(this);
    std::string type_name = type_names_.at(symbol.type_);

    if (symbol.type_ == Type::STRING) {
      type_name = "String";
    }
    if (symbol.type_ == Type::_NULL_ || symbol.type_ == Type::IDENTITY) {
      llvm::FunctionType *variable_ty =
          llvm::FunctionType::get(ir_.getVoidTy(), false);
      ;
      llvm::Function *variable = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("print" + type_name, variable_ty)
              .getCallee());
      ir_.CreateCall(variable);
    } else {
      llvm::Type *type = type_map_.at(symbol.type_);
      llvm::FunctionType *variable_ty =
          llvm::FunctionType::get(ir_.getVoidTy(), {type}, false);
      llvm::Function *variable = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("print" + type_name, variable_ty)
              .getCallee());
      ir_.CreateCall(variable, {symbol.value_});
    }
  }
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitTypeNode(TypeNode *node) {
  DEBUG_FUNC_ENTRY
  // TODO: Doesn't currently work for tuples
  Type type = node->type_;
  DEBUG_FUNC_EXIT
  return {type, nullptr, Qualifier::CONST, node->size0_, node->size1_};
}

Symbol CodeGenPass::visitTypeCast(TypeCast *node) {
  DEBUG_FUNC_ENTRY
  auto src = node->value_->visit(this);
  auto dst = node->target_type_->visit(this);

  if (dst.type_ == Type::TUPLE) {
    llvm::FunctionType *malloc_ty =
        llvm::FunctionType::get(ir_.getInt8PtrTy(), {ir_.getInt32Ty()}, false);
    llvm::Function *malloc_func = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("malloc", malloc_ty).getCallee());

    dst.value_ =
        ir_.CreateCall(malloc_func, {ir_.getInt32(dst.children_.size() * 4)});
    // iterate over children and cast
    for (size_t i = 0; i < dst.children_.size(); ++i) {
      dst.children_[i].second.value_ =
          typeCastSymbol(src.children_[i].second, dst.children_[i].second);

      llvm::Type *child_type = type_map_.at(dst.children_[i].second.type_);
      std::string child_type_name =
          type_names_.at(dst.children_[i].second.type_);

      llvm::FunctionType *store_ty = llvm::FunctionType::get(
          child_type->getPointerTo(0),
          {llvm::Type::getInt8PtrTy(global_ctx_), ir_.getInt32Ty(), child_type},
          false);
      llvm::Function *store = llvm::cast<llvm::Function>(
          mod_.getOrInsertFunction("createStore" + child_type_name, store_ty)
              .getCallee());

      dst.children_[i].second.value_ =
          ir_.CreateCall(store, {dst.value_, ir_.getInt32(i + 1),
                                 dst.children_[i].second.value_});
    }
    // free old pointer
    llvm::FunctionType *free_ty =
        llvm::FunctionType::get(ir_.getVoidTy(), {ir_.getInt8PtrTy()}, false);
    llvm::Function *free_fun = llvm::cast<llvm::Function>(
        mod_.getOrInsertFunction("free", free_ty).getCallee());
    llvm::Value *load = ir_.CreatePointerCast(src.value_, ir_.getInt8PtrTy());
    ir_.CreateCall(free_fun, {load});
  } else {
    dst.value_ = typeCastSymbol(src, dst);
  }

  DEBUG_FUNC_EXIT
  return dst;
}
Symbol CodeGenPass::visitTypeDef(TypeDef *node) {
  DEBUG_FUNC_ENTRY
  DEBUG_FUNC_EXIT
  return {};
}
Symbol CodeGenPass::visitUnaryExpr(UnaryExpr *node) {
  DEBUG_FUNC_ENTRY
  auto symbol = node->expr_->visit(this);

  llvm::Type *type = type_map_.at(symbol.type_);
  std::string func = unary_functions_.at({node->token_, symbol.type_});

  llvm::FunctionType *variable_ty =
      llvm::FunctionType::get(type, {type}, false);
  llvm::Function *variable = llvm::cast<llvm::Function>(
      mod_.getOrInsertFunction(func, variable_ty).getCallee());

  auto value = ir_.CreateCall(variable, {symbol.value_});
  symbol.value_ = value;
  DEBUG_FUNC_EXIT
  return symbol;
}
} // namespace gazprea