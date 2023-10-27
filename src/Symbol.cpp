#include "Symbol.h"
#include "Exceptions.h"
#include "Token.h"
namespace gazprea {
namespace TypeHelpers {
std::unordered_map<Type, std::string> type_names = {
    std::make_pair(Type::NONE, "none"),
    std::make_pair(Type::_NULL_, "null"),
    std::make_pair(Type::IDENTITY, "identity"),
    std::make_pair(Type::BOOLEAN, "boolean"),
    std::make_pair(Type::CHARACTER, "character"),
    std::make_pair(Type::INTEGER, "integer"),
    std::make_pair(Type::REAL, "real"),
    std::make_pair(Type::VECTOR, "none"),
    std::make_pair(Type::VECTOR_BOOLEAN, "boolean"),
    std::make_pair(Type::VECTOR_CHARACTER, "character"),
    std::make_pair(Type::VECTOR_INTEGER, "integer"),
    std::make_pair(Type::VECTOR_REAL, "real"),
    std::make_pair(Type::MATRIX, "none"),
    std::make_pair(Type::MATRIX_BOOLEAN, "boolean"),
    std::make_pair(Type::MATRIX_CHARACTER, "character"),
    std::make_pair(Type::MATRIX_INTEGER, "integer"),
    std::make_pair(Type::MATRIX_REAL, "real"),
    std::make_pair(Type::TUPLE, "tuple"),
    std::make_pair(Type::INTERVAL, "interval"),
    std::make_pair(Type::FUNCTION, "function"),
    std::make_pair(Type::PROCEDURE, "procedure"),
    std::make_pair(Type::STRING, "string")};

std::unordered_map<Type, Type> base_types = {
    {Type::VECTOR_BOOLEAN, Type::BOOLEAN},
    {Type::VECTOR_CHARACTER, Type::CHARACTER},
    {Type::VECTOR_INTEGER, Type::INTEGER},
    {Type::VECTOR_REAL, Type::REAL},
    {Type::MATRIX_BOOLEAN, Type::BOOLEAN},
    {Type::MATRIX_CHARACTER, Type::CHARACTER},
    {Type::MATRIX_INTEGER, Type::INTEGER},
    {Type::MATRIX_REAL, Type::REAL},
    {Type::INTERVAL, Type::INTEGER},
};

bool isVector(Type type) {
  std::array<Type, 5> vector_types = {Type::VECTOR, Type::VECTOR_BOOLEAN,
                                      Type::VECTOR_CHARACTER,
                                      Type::VECTOR_INTEGER, Type::VECTOR_REAL};
  if (std::any_of(vector_types.begin(), vector_types.end(),
                  [type, vector_types](Type other) { return type == other; })) {
    return true;
  }
  return false;
}

bool isMatrix(Type type) {
  std::array<Type, 5> matrix_types = {Type::MATRIX, Type::MATRIX_BOOLEAN,
                                      Type::MATRIX_CHARACTER,
                                      Type::MATRIX_INTEGER, Type::MATRIX_REAL};

  if (std::any_of(matrix_types.begin(), matrix_types.end(),
                  [type, matrix_types](Type other) { return type == other; })) {
    return true;
  }
  return false;
}

bool isScalar(Type type) {
  std::array<Type, 6> scalar_types = {Type::_NULL_,  Type::IDENTITY,
                                      Type::BOOLEAN, Type::INTEGER,
                                      Type::REAL,    Type::CHARACTER};

  if (std::any_of(scalar_types.begin(), scalar_types.end(),
                  [type, scalar_types](Type other) { return type == other; })) {
    return true;
  }
  return false;
}

bool isValidTupleMemberOrOutstreamType(Type type) {
  std::array<Type, 4> invalid_types = {Type::NONE, Type::TUPLE, Type::FUNCTION,
                                       Type::PROCEDURE};

  if (std::any_of(
          invalid_types.begin(), invalid_types.end(),
          [type, invalid_types](Type other) { return type == other; })) {
    return false;
  }
  return true;
}

Type scalarToVector(Type type) {
  switch (type) {
  case Type::BOOLEAN:
    return Type::VECTOR_BOOLEAN;
  case Type::INTEGER:
    return Type::VECTOR_INTEGER;
  case Type::CHARACTER:
    return Type::VECTOR_CHARACTER;
  case Type::REAL:
    return Type::VECTOR_REAL;
  case Type::_NULL_:
    return Type::VECTOR;
  case Type::IDENTITY:
    return Type::VECTOR;
  default:
    return Type::NONE;
  }
}

Type scalarToMatrix(Type type) {
  switch (type) {
  case Type::BOOLEAN:
    return Type::MATRIX_BOOLEAN;
  case Type::INTEGER:
    return Type::MATRIX_INTEGER;
  case Type::CHARACTER:
    return Type::MATRIX_CHARACTER;
  case Type::REAL:
    return Type::MATRIX_REAL;
  case Type::_NULL_:
    return Type::MATRIX;
  case Type::IDENTITY:
    return Type::MATRIX;
  default:
    return Type::NONE;
  }
}

Type vectorToScalar(Type type) {
  switch (type) {
  case Type::VECTOR_BOOLEAN:
    return Type::BOOLEAN;
  case Type::VECTOR_INTEGER:
    return Type::INTEGER;
  case Type::VECTOR_CHARACTER:
    return Type::CHARACTER;
  case Type::VECTOR_REAL:
    return Type::REAL;
  case Type::VECTOR:
    return Type::IDENTITY;
  default:
    return Type::NONE;
  }
}

Type vectorToMatrix(Type type) {
  switch (type) {
  case Type::VECTOR_BOOLEAN:
    return Type::MATRIX_BOOLEAN;
  case Type::VECTOR_INTEGER:
    return Type::MATRIX_INTEGER;
  case Type::VECTOR_CHARACTER:
    return Type::MATRIX_CHARACTER;
  case Type::VECTOR_REAL:
    return Type::MATRIX_REAL;
  case Type::VECTOR:
    return Type::MATRIX;
  default:
    return Type::NONE;
  }
}

Type matrixToVector(Type type) {
  switch (type) {
  case Type::MATRIX_BOOLEAN:
    return Type::VECTOR_BOOLEAN;
  case Type::MATRIX_INTEGER:
    return Type::VECTOR_INTEGER;
  case Type::MATRIX_CHARACTER:
    return Type::VECTOR_CHARACTER;
  case Type::MATRIX_REAL:
    return Type::VECTOR_REAL;
  case Type::MATRIX:
    return Type::VECTOR;
  default:
    return Type::NONE;
  }
}

Type matrixToScalar(Type type) {
  switch (type) {
  case Type::MATRIX_BOOLEAN:
    return Type::BOOLEAN;
  case Type::MATRIX_INTEGER:
    return Type::INTEGER;
  case Type::MATRIX_CHARACTER:
    return Type::CHARACTER;
  case Type::MATRIX_REAL:
    return Type::REAL;
  case Type::MATRIX:
    return Type::IDENTITY;
  default:
    return Type::NONE;
  }
}

Type getBaseType(Type type) {
  auto iter = base_types.find(type);
  if (iter != base_types.end()) {
    return iter->second;
  }
  return Type::NONE;
}
} // namespace TypeHelpers

std::string to_string(const gazprea::Symbol &value) {
  std::ostringstream ss;
  ss << gazprea::TypeHelpers::type_names.at(value.type_);

  if (gazprea::TypeHelpers::isVector(value.type_)) {
    ss << '[';
    if (value.size0_ != -1lu) {
      ss << value.size0_;
    } else {
      ss << '*';
    }
    ss << ']';
  } else if (gazprea::TypeHelpers::isMatrix(value.type_)) {
    ss << '[';
    if (value.size0_ != -1lu) {
      ss << value.size0_;
    } else {
      ss << '*';
    }
    ss << ',';
    if (value.size1_ != -1lu) {
      ss << value.size1_;
    } else {
      ss << '*';
    }
    ss << ']';
  } else if (value.type_ == gazprea::Type::TUPLE) {
    ss << '(';
    for (auto child : value.children_) {
      ss << to_string(child.second) << ' ';
    }
    ss << ')';
  }

  return ss.str();
}
} // namespace gazprea