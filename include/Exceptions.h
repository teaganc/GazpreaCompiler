#pragma once

#include <sstream>
#include <string>

namespace gazprea {

class TypeError : public std::exception {
private:
  std::string msg;

public:
  TypeError(std::string lhs, std::string rhs, size_t line) {
    std::stringstream sstream;
    sstream << "Type error: Cannot convert between " << lhs << " and " << rhs
            << " on line " << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class SyntaxError : public std::exception {
private:
  std::string msg;

public:
  SyntaxError(std::string msg_, size_t line, size_t charPositionInLine)
      : msg() {
    std::stringstream sstream;
    sstream << "Syntax error: " << msg_ << " on line " << line
            << " at position " << charPositionInLine << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class ReferenceError : public std::exception {
private:
  std::string msg;

public:
  ReferenceError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Reference error: name " << var_name << " referenced on line "
            << line << " is not declared\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class RedeclarationError : public std::exception {
private:
  std::string msg;

public:
  RedeclarationError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Redeclaration error: name " << var_name << " declared on line "
            << line << " has already been declared in this scope\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class ReservedNameError : public std::exception {
private:
  std::string msg;

public:
  ReservedNameError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Reserved name error: name " << var_name << " declared on line "
            << line
            << " is reserved as a built-in function and cannot be used\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class UndefinedTypeError : public std::exception {
private:
  std::string msg;

public:
  UndefinedTypeError(std::string type_name, size_t line) {
    std::stringstream sstream;
    sstream << "Undefined type error: Type " << type_name << " on line " << line
            << " is not a valid type\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class PredicateTypeError : public std::exception {
private:
  std::string msg;

public:
  PredicateTypeError(size_t line) {
    std::stringstream sstream;
    sstream << "Invalid type error: Expression predicates on line " << line
            << " for loops and if statements and filter expressions must "
               "return a boolean value\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidStatementTypeError : public std::exception {
private:
  std::string msg;

public:
  InvalidStatementTypeError(std::string statement_type, size_t line,
                            std::string context_type)
      : msg() {
    std::stringstream sstream;
    sstream << "Invalid statement type error: statement of type "
            << statement_type << " on line " << line
            << " is not valid in context " << context_type << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidVectorTypeError : public std::exception {
private:
  std::string msg;

public:
  InvalidVectorTypeError(std::string member_type, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid vector type error: member of type " << member_type
            << " on line " << line << " is not valid in vectors\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidMatrixTypeError : public std::exception {
private:
  std::string msg;

public:
  InvalidMatrixTypeError(std::string member_type, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid matrix type error: member of type " << member_type
            << " on line " << line << " is not valid in matrices\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidTupleTypeError : public std::exception {
private:
  std::string msg;

public:
  InvalidTupleTypeError(std::string member_type, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid tuple type error: member of type " << member_type
            << " on line " << line << " is not valid in tuples\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class ConstAssignError : public std::exception {
private:
  std::string msg;

public:
  ConstAssignError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Constant assignment error: Cannot assign constant variable "
            << var_name << " on line " << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class GlobalNonConstError : public std::exception {
private:
  std::string msg;

public:
  GlobalNonConstError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Global non-constant error: Global " << var_name
            << " declared on line " << line << " is not a constant\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class FunctionDeclTypeError : public std::exception {
private:
  std::string msg;

public:
  FunctionDeclTypeError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Function declaration type error: Function " << var_name
            << " redeclared on line " << line
            << " with the wrong number of arguments or return type\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class FunctionDeclArgTypeError : public std::exception {
private:
  std::string msg;

public:
  FunctionDeclArgTypeError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Function decl type error: Function " << var_name
            << " redeclared on line " << line << " with wrong argument type\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class FunctionCallArgTypeError : public std::exception {
private:
  std::string msg;

public:
  FunctionCallArgTypeError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Function call type error: Function " << var_name
            << " called on line " << line << " with wrong argument type\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class FunctionRedefineError : public std::exception {
private:
  std::string msg;

public:
  FunctionRedefineError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Function redefinition error: Function " << var_name
            << " on line " << line << " has been redefined\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class FunctionUndefinedError : public std::exception {
private:
  std::string msg;

public:
  FunctionUndefinedError(std::string var_name) : msg() {
    std::stringstream sstream;
    sstream << "Undefined function: Function " << var_name
            << " has been declared but not defined\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class TypeInferenceError : public std::exception {
private:
  std::string msg;

public:
  TypeInferenceError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Type inference error: Type of " << var_name << " on line "
            << line << " can not be determined\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class BadIndexError : public std::exception {
private:
  std::string msg;

public:
  BadIndexError(std::string var_name, std::string type_name, size_t line)
      : msg() {
    std::stringstream sstream;
    sstream << "Bad Index Error: Cannot index into " << var_name << " on line "
            << line << " as type " << type_name << " cannot be indexed\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class TypeSizingError : public std::exception {
private:
  std::string msg;

public:
  TypeSizingError(std::string type_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Type sizing error: Type of " << type_name << " on line " << line
            << " already has size and can not be sized again\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class IncompatibleSizeError : public std::exception {
private:
  std::string msg;

public:
  IncompatibleSizeError(size_t line) : msg() {
    std::stringstream sstream;
    sstream
        << "Incompatible size error: Binary operation cannot be done on line "
        << line << " as the operands have incompatible sizes\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class NonIterableDomainError : public std::exception {
private:
  std::string msg;

public:
  NonIterableDomainError(std::string domain_type, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Non-iterable domain error: Domain of type " << domain_type
            << " on line " << line << " is not iterable\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class IncompatibleSizeAssignmentError : public std::exception {
private:
  std::string msg;

public:
  IncompatibleSizeAssignmentError(std::string source_type,
                                  std::string target_type, size_t line)
      : msg() {
    std::stringstream sstream;
    sstream << "Incompatible assignment size error: Cannot assign "
            << source_type << " to " << target_type << " on line " << line
            << " as the operands have incompatible types\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InoperableTypeError : public std::exception {
private:
  std::string msg;

public:
  InoperableTypeError(std::string lhs, std::string rhs, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Inoperable types error: Operation between type " << lhs
            << " and type " << rhs << " on line " << line << " is not valid\n";
    msg = sstream.str();
  }
  InoperableTypeError(std::string var, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Inoperable types error: Unary operation on type " << var
            << " on line " << line << " is not valid\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class UnpackingError : public std::exception {
private:
  std::string msg;

public:
  UnpackingError(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Unpacking error: cannot unpack expression on line" << line
            << "as it has an improper type\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class OutOfBoundsError : public std::exception {
private:
  std::string msg;

public:
  OutOfBoundsError(std::string var_name, size_t index0, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Out of bounds error: cannot access index " << index0 << " of "
            << var_name << " on line " << line << " as that is out of bounds\n";
    msg = sstream.str();
  }
  OutOfBoundsError(std::string var_name, size_t index0, size_t index1,
                   size_t line)
      : msg() {
    std::stringstream sstream;
    sstream << "Out of bounds error: cannot access index " << index0 << ", "
            << index1 << " of " << var_name << " on line " << line
            << " as that is out of bounds\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class MemberReferenceError : public std::exception {
private:
  std::string msg;

public:
  MemberReferenceError(std::string var_name, std::string member_name,
                       size_t line)
      : msg() {
    std::stringstream sstream;
    sstream << "Member reference error: cannot access member " << member_name
            << " of " << var_name << "on line" << line
            << "as that is not defined\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class NullIdentityCastError : public std::exception {
private:
  std::string msg;

public:
  NullIdentityCastError(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Null/Identity typecast error: typecast on line" << line
            << "is invalid as null or identity values cannot be typecast\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class NonScalarStreamLValue : public std::exception {
private:
  std::string msg;

public:
  NonScalarStreamLValue(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Bad stream l-value: in-stream l-value on line" << line
            << "does not have scalar type\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidOutStreamType : public std::exception {
private:
  std::string msg;

public:
  InvalidOutStreamType(std::string out_type, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid our-stream type: " << out_type << "type on line" << line
            << "cannot be printed\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class IncorrectReturnType : public std::exception {
private:
  std::string msg;

public:
  IncorrectReturnType(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Incorrect return type error: Return statement on line" << line
            << "returns incorrect type\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class ReturnOutsideDeclError : public std::exception {
private:
  std::string msg;

public:
  ReturnOutsideDeclError(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Return outside declaration error: Return statement on line"
            << line << "is outside a function or procedure definition\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidCallError : public std::exception {
private:
  std::string msg;

public:
  InvalidCallError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid call error: Variable " << var_name << " on line "
            << line << " is not a function/procedure\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidProcedureCallError : public std::exception {
private:
  std::string msg;

public:
  InvalidProcedureCallError(std::string var_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid call error: Variable " << var_name << " on line "
            << line << " is not a procedure\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class ConstRefError : public std::exception {
private:
  std::string msg;

public:
  ConstRefError(std::string var_name, size_t argument, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Const reference error: Gazprea cannot create const references "
               "so call of "
            << var_name << " on line " << line
            << " cannot take value passed in argument " << argument << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class BadMainError : public std::exception {
private:
  std::string msg;

public:
  BadMainError() : msg() {
    std::stringstream sstream;
    sstream << "Main is not defined or has the wrong signature\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

/* This error is thrown when control reaches an impossible state,
   by default this should never be thrown*/
class PanicError : public std::exception {
private:
  std::string msg;

public:
  PanicError() : msg() {
    std::stringstream sstream;
    sstream << "This should never throw an error\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class JumpStatementError : public std::exception {
private:
  std::string msg;

public:
  JumpStatementError(std::string statement_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Jump statement error: " << statement_name
            << " statement on line " << line << " is outside of a loop block\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class PrintTypeError : public std::exception {
private:
  std::string msg;

public:
  PrintTypeError(std::string type_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Print type error: Cannot print values of type" << type_name
            << " on line " << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InputTypeError : public std::exception {
private:
  std::string msg;

public:
  InputTypeError(std::string type_name, size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Input error: Cannot assign input values of type" << type_name
            << " on line " << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidFunctionCall : public std::exception {
private:
  std::string msg;

public:
  InvalidFunctionCall(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid function call: Function called in global scope on line "
            << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidProcedureCall : public std::exception {
private:
  std::string msg;

public:
  InvalidProcedureCall(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Invalid procedure call: Procedure called in global scope, a "
               "function or a binary expression on line "
            << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class MissingReturn : public std::exception {
private:
  std::string msg;

public:
  MissingReturn(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Missing return error: Function or procedure does not return on "
               "all branches on line "
            << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class IoInFunction : public std::exception {
private:
  std::string msg;

public:
  IoInFunction(size_t line) : msg() {
    std::stringstream sstream;
    sstream << "Io in function error: Function uses stream operation on line "
            << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

class InvalidIntervalInitialization : public std::exception {
private:
  std::string msg;

public:
  InvalidIntervalInitialization(std::string type0, std::string type1,
                                size_t line)
      : msg() {
    std::stringstream sstream;
    sstream << "Invalid interaval initialization error: Initalization interval "
               "with type "
            << type0 << " and " << type1 << " on line " << line << "\n";
    msg = sstream.str();
  }
  virtual const char *what() const throw() { return msg.c_str(); }
};

} // namespace gazprea