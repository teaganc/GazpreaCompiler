#pragma once

#include "Qualifier.h"
#include "llvm/IR/Value.h"
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace gazprea {

enum class Type : unsigned int {
  NONE,
  _NULL_,
  IDENTITY,
  BOOLEAN,
  CHARACTER,
  INTEGER,
  REAL,
  VECTOR,
  VECTOR_BOOLEAN,
  VECTOR_CHARACTER,
  VECTOR_INTEGER,
  VECTOR_REAL,
  MATRIX,
  MATRIX_BOOLEAN,
  MATRIX_CHARACTER,
  MATRIX_INTEGER,
  MATRIX_REAL,
  TUPLE,
  INTERVAL,
  FUNCTION,
  PROCEDURE,
  STRING
};

class Scope;

class Symbol {
public:
  Type type_;
  llvm::Value *value_;
  Qualifier qualifier_;
  size_t size0_;
  size_t size1_;
  // should probably have separate class for function/procedure/tuple that use
  // this
  std::vector<std::pair<std::string, Symbol>> children_;
  Type return_type_;

  Symbol()
      : type_(Type::NONE), value_(nullptr), qualifier_(Qualifier::CONST),
        size0_(-1), size1_(-1), return_type_(Type::NONE) {}

  Symbol(Type type, llvm::Value *value = nullptr,
         Qualifier qualifier = Qualifier::CONST, size_t size0 = -1,
         size_t size1 = -1,
         std::vector<std::pair<std::string, Symbol>> children = {},
         Type return_type = Type::NONE)
      : type_(type), value_(value), qualifier_(qualifier), size0_(size0),
        size1_(size1), children_(children), return_type_(return_type) {}

  bool operator==(const Symbol &other) const {
    return other.type_ == type_ && other.size0_ == size0_ &&
           other.size1_ == size1_ && other.qualifier_ == qualifier_;
  }

  bool operator!=(const Symbol &other) const { return !(*this == other); }

  void addChild(std::string name, Symbol symbol) {
    children_.emplace_back(name, symbol);
  }

  bool operator!() const { return type_ == Type::NONE ? true : false; };

  operator bool() const { return type_ == Type::NONE ? false : true; };
};

namespace TypeHelpers {
extern std::unordered_map<Type, std::string> type_names;
extern std::unordered_map<Type, Type> base_types;

bool isVector(Type type);
bool isMatrix(Type type);
bool isScalar(Type type);
bool isValidTupleMemberOrOutstreamType(Type type);
Type scalarToVector(Type type);
Type scalarToMatrix(Type type);
Type vectorToScalar(Type type);
Type vectorToMatrix(Type type);
Type matrixToVector(Type type);
Type matrixToScalar(Type type);
Type getBaseType(Type type);
} // namespace TypeHelpers

// Prints out vectors and matrix types to string dynamically for errors

std::string to_string(const gazprea::Symbol &value);

} // namespace gazprea
