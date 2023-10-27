#include "DefRef.h"
#include "Exceptions.h"

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

DefRef::DefRef() {
  DEBUG_FUNC_ENTRY
  // Initialize typedef table
  Symbol bool_type;
  bool_type.type_ = Type::BOOLEAN;
  typedefs_.insert_or_assign("boolean", bool_type);

  Symbol char_type;
  char_type.type_ = Type::CHARACTER;
  typedefs_.insert_or_assign("character", char_type);

  Symbol int_type;
  int_type.type_ = Type::INTEGER;
  typedefs_.insert_or_assign("integer", int_type);

  Symbol real_type;
  real_type.type_ = Type::REAL;
  typedefs_.insert_or_assign("real", real_type);

  Symbol interval_type;
  interval_type.type_ = Type::INTERVAL;
  typedefs_.insert_or_assign("interval", interval_type);

  Symbol string_type;
  string_type.type_ = Type::STRING;
  typedefs_.insert_or_assign("string", string_type);

  // Scalar Binary Functions
  binary_functions_.insert({{Token::ADD, Type::INTEGER, Type::INTEGER},
                            {"binaryAddInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::ADD, Type::REAL, Type::REAL}, {"binaryAddFloat", Type::REAL}});
  binary_functions_.insert({{Token::ADD, Type::INTEGER, Type::REAL},
                            {"binaryAddFloat", Type::REAL}});
  binary_functions_.insert({{Token::ADD, Type::REAL, Type::INTEGER},
                            {"binaryAddFloat", Type::REAL}});
  binary_functions_.insert({{Token::SUB, Type::INTEGER, Type::INTEGER},
                            {"binarySubInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::SUB, Type::REAL, Type::REAL}, {"binarySubFloat", Type::REAL}});
  binary_functions_.insert({{Token::SUB, Type::INTEGER, Type::REAL},
                            {"binarySubFloat", Type::REAL}});
  binary_functions_.insert({{Token::SUB, Type::REAL, Type::INTEGER},
                            {"binarySubFloat", Type::REAL}});
  binary_functions_.insert({{Token::MUL, Type::INTEGER, Type::INTEGER},
                            {"binaryMulInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::MUL, Type::REAL, Type::REAL}, {"binaryMulFloat", Type::REAL}});
  binary_functions_.insert({{Token::MUL, Type::INTEGER, Type::REAL},
                            {"binaryMulFloat", Type::REAL}});
  binary_functions_.insert({{Token::MUL, Type::REAL, Type::INTEGER},
                            {"binaryAddFloat", Type::REAL}});
  binary_functions_.insert({{Token::DIV, Type::INTEGER, Type::INTEGER},
                            {"binaryDivInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::DIV, Type::REAL, Type::REAL}, {"binaryDivFloat", Type::REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::INTEGER, Type::REAL}, {"binaryDivFloa", Type::REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::REAL, Type::INTEGER}, {"binaryDivFloa", Type::REAL}});
  binary_functions_.insert({{Token::MOD, Type::INTEGER, Type::INTEGER},
                            {"binaryModInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::MOD, Type::REAL, Type::REAL}, {"binaryModFloat", Type::REAL}});
  binary_functions_.insert({{Token::MOD, Type::INTEGER, Type::REAL},
                            {"binaryModFloat", Type::REAL}});
  binary_functions_.insert({{Token::MOD, Type::REAL, Type::INTEGER},
                            {"binaryModFloat", Type::REAL}});
  binary_functions_.insert({{Token::EXP, Type::INTEGER, Type::INTEGER},
                            {"binaryExpInt", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::EXP, Type::REAL, Type::REAL}, {"binaryExpFloat", Type::REAL}});
  binary_functions_.insert({{Token::EXP, Type::INTEGER, Type::REAL},
                            {"binaryExpFloat", Type::REAL}});
  binary_functions_.insert({{Token::EXP, Type::REAL, Type::INTEGER},
                            {"binaryExpFloat", Type::REAL}});

  // Scalar Comparison operations
  binary_functions_.insert({{Token::LT, Type::INTEGER, Type::INTEGER},
                            {"binaryLTInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::LT, Type::REAL, Type::REAL}, {"binaryLTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::INTEGER, Type::REAL},
                            {"binaryLTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::REAL, Type::INTEGER},
                            {"binaryLTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::INTEGER, Type::INTEGER},
                            {"binaryLEInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::REAL, Type::REAL}, {"binaryLEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::INTEGER, Type::REAL},
                            {"binaryLEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::REAL, Type::INTEGER},
                            {"binaryLEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::INTEGER, Type::INTEGER},
                            {"binaryGTInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::REAL, Type::REAL}, {"binaryGTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::INTEGER, Type::REAL},
                            {"binaryGTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::REAL, Type::INTEGER},
                            {"binaryGTFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::INTEGER, Type::INTEGER},
                            {"binaryGEInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::REAL, Type::REAL}, {"binaryGEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::INTEGER, Type::REAL},
                            {"binaryGEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::REAL, Type::INTEGER},
                            {"binaryGEFloat", Type::BOOLEAN}});

  // Scalar Equality operations
  binary_functions_.insert({{Token::EQ, Type::INTEGER, Type::INTEGER},
                            {"binaryEQInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::EQ, Type::REAL, Type::REAL}, {"binaryEQFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::BOOLEAN, Type::BOOLEAN},
                            {"binaryEQBool", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::INTEGER, Type::REAL},
                            {"binaryEQFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::REAL, Type::INTEGER},
                            {"binaryEQFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTEGER, Type::INTEGER},
                            {"binaryNEInt", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::REAL, Type::REAL}, {"binaryNEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::BOOLEAN, Type::BOOLEAN},
                            {"binaryNEBool", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTEGER, Type::REAL},
                            {"binaryNEFloat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::REAL, Type::INTEGER},
                            {"binaryNEFloat", Type::BOOLEAN}});

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
      {{Token::ADD, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::ADD, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binarySubIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binarySubFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binarySubFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binarySubFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryMulIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryMulFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryMulFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryMulFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryDivIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryDivFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryDivFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryDivFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryModIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryModFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryModFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryModFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryExpIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryExpFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryExpFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryExpFloatVec", Type::VECTOR_REAL}});

  // Vector with scalar arithmetic
  binary_functions_.insert({{Token::ADD, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::ADD, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::ADD, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::ADD, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::ADD, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::ADD, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::ADD, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::ADD, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::SUB, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::SUB, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::SUB, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::SUB, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::SUB, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::SUB, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MUL, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MUL, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MUL, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MUL, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MUL, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MUL, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::DIV, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::DIV, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::DIV, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::DIV, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::DIV, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::DIV, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MOD, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MOD, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MOD, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MOD, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MOD, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::MOD, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::EXP, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::EXP, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::EXP, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::EXP, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::EXP, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::EXP, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_REAL}});

  // Vector Comparison operations
  binary_functions_.insert(
      {{Token::LT, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryLTIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryLTFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LT, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LT, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryLEIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryLEFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryGTIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryGTFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryGEIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryGEFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});

  // Vector with scalar comparisons
  binary_functions_.insert({{Token::LT, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});

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
      {{Token::EQ, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::EQ, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"binaryNEIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::VECTOR_REAL, Type::VECTOR_REAL},
                            {"binaryNEFloatVec", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"binaryNEBoolVec", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"binaryAddIntVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"binaryAddFloatVec", Type::VECTOR_BOOLEAN}});

  // Vector with scalar equality operations
  binary_functions_.insert({{Token::EQ, Type::TUPLE, Type::TUPLE},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::BOOLEAN, Type::VECTOR_BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::VECTOR_BOOLEAN, Type::BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::TUPLE, Type::TUPLE},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::VECTOR_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::VECTOR_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::VECTOR_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::REAL, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::REAL, Type::VECTOR_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTEGER, Type::VECTOR_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::BOOLEAN, Type::VECTOR_BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::VECTOR_BOOLEAN, Type::BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});

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

  // Vector with scalar boolean specific operations
  binary_functions_.insert({{Token::AND, Type::VECTOR_BOOLEAN, Type::BOOLEAN},
                            {"binaryAndBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::OR, Type::VECTOR_BOOLEAN, Type::BOOLEAN},
                            {"binaryOrBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::XOR, Type::VECTOR_BOOLEAN, Type::BOOLEAN},
                            {"binaryXorBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::AND, Type::BOOLEAN, Type::VECTOR_BOOLEAN},
                            {"binaryAndBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::OR, Type::BOOLEAN, Type::VECTOR_BOOLEAN},
                            {"binaryOrBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::XOR, Type::BOOLEAN, Type::VECTOR_BOOLEAN},
                            {"binaryXorBoolVec", Type::VECTOR_BOOLEAN}});

  // Matrix Binary Functions

  // Matrix arithmetic operations
  binary_functions_.insert(
      {{Token::ADD, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryAddIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::ADD, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::ADD, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::ADD, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binarySubIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binarySubFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::SUB, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryMulIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryMulFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MUL, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryDivIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryDivFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::DIV, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryModIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryModFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::MOD, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryExpIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryExpFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::EXP, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_REAL}});

  // Matrix with scalar arithmetic
  binary_functions_.insert({{Token::ADD, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::ADD, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::ADD, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::ADD, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::ADD, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::ADD, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::ADD, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::ADD, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::SUB, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::SUB, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::SUB, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::SUB, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::SUB, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::SUB, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::SUB, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MUL, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MUL, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MUL, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MUL, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MUL, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MUL, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MUL, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::DIV, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::DIV, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::DIV, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::DIV, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::DIV, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::DIV, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::DIV, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MOD, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MOD, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MOD, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MOD, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::MOD, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MOD, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::MOD, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::EXP, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::EXP, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::EXP, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::EXP, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_INTEGER}});
  binary_functions_.insert({{Token::EXP, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::EXP, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_REAL}});
  binary_functions_.insert({{Token::EXP, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_REAL}});

  // Matrix Comparison operations
  binary_functions_.insert(
      {{Token::LT, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryLTIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryLTFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LT, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LT, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryLEIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryLEFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::LE, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryGTIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryGTFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GT, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryGEIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryGEFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::GE, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_BOOLEAN}});

  // Matrix with scalar comparisons
  binary_functions_.insert({{Token::LT, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LT, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::LE, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GT, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::GE, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::MATRIX_BOOLEAN}});

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
      {{Token::EQ, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::EQ, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"binaryNEIntMat", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::MATRIX_REAL, Type::MATRIX_REAL},
                            {"binaryNEFloatMat", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::MATRIX_BOOLEAN, Type::MATRIX_BOOLEAN},
       {"binaryNEBoolMat", Type::BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"binaryAddIntMat", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert(
      {{Token::NE, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
       {"binaryAddFloatMat", Type::MATRIX_BOOLEAN}});

  // Matrix with scalar equality operations
  binary_functions_.insert({{Token::EQ, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::BOOLEAN, Type::MATRIX_BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::EQ, Type::MATRIX_BOOLEAN, Type::BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});

  binary_functions_.insert({{Token::NE, Type::MATRIX_INTEGER, Type::INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::MATRIX_REAL, Type::REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::MATRIX_INTEGER, Type::REAL},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::MATRIX_REAL, Type::INTEGER},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTEGER, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::REAL, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::REAL, Type::MATRIX_INTEGER},
                            {"binaryAddIntVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::INTEGER, Type::MATRIX_REAL},
                            {"binaryAddFloatVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::BOOLEAN, Type::MATRIX_BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});
  binary_functions_.insert({{Token::NE, Type::MATRIX_BOOLEAN, Type::BOOLEAN},
                            {"binaryEQBoolVec", Type::BOOLEAN}});

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

  // Matrix with scalar boolean specific operations
  binary_functions_.insert({{Token::AND, Type::MATRIX_BOOLEAN, Type::BOOLEAN},
                            {"binaryAndBoolVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::OR, Type::MATRIX_BOOLEAN, Type::BOOLEAN},
                            {"binaryOrBoolVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::XOR, Type::MATRIX_BOOLEAN, Type::BOOLEAN},
                            {"binaryXorBoolVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::AND, Type::BOOLEAN, Type::MATRIX_BOOLEAN},
                            {"binaryAndBoolVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::OR, Type::BOOLEAN, Type::MATRIX_BOOLEAN},
                            {"binaryOrBoolVec", Type::MATRIX_BOOLEAN}});
  binary_functions_.insert({{Token::XOR, Type::BOOLEAN, Type::MATRIX_BOOLEAN},
                            {"binaryXorBoolVec", Type::MATRIX_BOOLEAN}});

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
      {{Token::CAT, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"concatIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::CAT, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"concatFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::CAT, Type::VECTOR_CHARACTER, Type::VECTOR_CHARACTER},
       {"concatCharVec", Type::VECTOR_CHARACTER}});
  binary_functions_.insert(
      {{Token::CAT, Type::VECTOR_BOOLEAN, Type::VECTOR_BOOLEAN},
       {"concatBoolVec", Type::VECTOR_BOOLEAN}});
  binary_functions_.insert({{Token::CAT, Type::STRING, Type::STRING},
                            {"concatString", Type::STRING}});
  binary_functions_.insert({{Token::CAT, Type::STRING, Type::VECTOR_CHARACTER},
                            {"concatString", Type::STRING}});
  binary_functions_.insert({{Token::CAT, Type::VECTOR_CHARACTER, Type::STRING},
                            {"concatString", Type::STRING}});

  // vector with scalar concat operations

  binary_functions_.insert({{Token::CAT, Type::INTEGER, Type::VECTOR_INTEGER},
                            {"concatIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::CAT, Type::REAL, Type::VECTOR_REAL},
                            {"concatFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::CAT, Type::INTEGER, Type::VECTOR_REAL},
                            {"concatIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::CAT, Type::REAL, Type::VECTOR_INTEGER},
                            {"concatFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::CAT, Type::CHARACTER, Type::VECTOR_CHARACTER},
       {"concatCharVec", Type::VECTOR_CHARACTER}});
  binary_functions_.insert({{Token::CAT, Type::CHARACTER, Type::STRING},
                            {"concatCharVec", Type::STRING}});
  binary_functions_.insert({{Token::CAT, Type::BOOLEAN, Type::VECTOR_BOOLEAN},
                            {"concatBoolVec", Type::VECTOR_BOOLEAN}});

  binary_functions_.insert({{Token::CAT, Type::VECTOR_INTEGER, Type::INTEGER},
                            {"concatIntVec", Type::VECTOR_INTEGER}});
  binary_functions_.insert({{Token::CAT, Type::VECTOR_REAL, Type::REAL},
                            {"concatFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::CAT, Type::VECTOR_INTEGER, Type::REAL},
                            {"concatIntVec", Type::VECTOR_REAL}});
  binary_functions_.insert({{Token::CAT, Type::VECTOR_REAL, Type::INTEGER},
                            {"concatFloatVec", Type::VECTOR_REAL}});
  binary_functions_.insert(
      {{Token::CAT, Type::VECTOR_CHARACTER, Type::CHARACTER},
       {"concatCharVec", Type::VECTOR_CHARACTER}});
  binary_functions_.insert({{Token::CAT, Type::STRING, Type::CHARACTER},
                            {"concatCharVec", Type::STRING}});
  binary_functions_.insert({{Token::CAT, Type::VECTOR_BOOLEAN, Type::BOOLEAN},
                            {"concatBoolVec", Type::VECTOR_BOOLEAN}});

  // dot operations
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::VECTOR_INTEGER, Type::VECTOR_INTEGER},
       {"dotIntVec", Type::INTEGER}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::VECTOR_REAL, Type::VECTOR_REAL},
       {"dotFloatVec", Type::REAL}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::VECTOR_INTEGER, Type::VECTOR_REAL},
       {"concatIntVec", Type::REAL}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::VECTOR_REAL, Type::VECTOR_INTEGER},
       {"concatFloatVec", Type::REAL}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::MATRIX_INTEGER, Type::MATRIX_INTEGER},
       {"dotIntMat", Type::MATRIX_INTEGER}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::MATRIX_REAL, Type::MATRIX_REAL},
       {"dotFloatMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::MATRIX_INTEGER, Type::MATRIX_REAL},
       {"dotIntMat", Type::MATRIX_REAL}});
  binary_functions_.insert(
      {{Token::DOT_PROD, Type::MATRIX_REAL, Type::MATRIX_INTEGER},
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

  DEBUG_FUNC_EXIT
}

void DefRef::end() {
  DEBUG_FUNC_ENTRY
  // Ensure main is declared and valid
  auto main = curr_scope_->resolve("main");
  if (main.type_ != Type::PROCEDURE || main.return_type_ != Type::INTEGER ||
      main.children_.size() != 0) {
    throw BadMainError();
  }

  // Ensure all declared functions/procedures are defined
  for (auto &symbol : curr_scope_->symbols_) {
    Symbol global = symbol.second;
    if ((global.type_ == Type::FUNCTION || global.type_ == Type::PROCEDURE) &&
        global.value_ != (llvm::Value *)-1) {
      throw FunctionUndefinedError(symbol.first);
    }
  }
  DEBUG_FUNC_EXIT
};

// File node
Symbol DefRef::visitFileNode(FileNode *node) {
  DEBUG_FUNC_ENTRY
  // Create global scope
  curr_scope_ = new Scope();

  // Add global scope to map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Visit children
  for (auto &child : node->children_) {
    child->visit(this);
  }
  DEBUG_FUNC_EXIT
  return {};
}

// Scoped nodes
Symbol DefRef::visitFunctionDeclNode(FunctionDeclNode *node) {
  DEBUG_FUNC_ENTRY
  // Create + push function scope
  Scope *function_scope = new Scope();
  function_scope->parent_ = curr_scope_;
  curr_scope_ = function_scope;
  auto old_function = curr_scope_->resolve(node->id_);

  // Add to scope map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Create function symbol
  Symbol function_symbol;
  function_symbol.type_ = Type::FUNCTION;

  // Visit params and add to scope + add to children
  for (auto &param : node->params_) {
    // Get param information
    std::string param_name = param->id_;
    Symbol param_type = param->visit(this);

    // Add to symbol children
    function_symbol.addChild(param_name, param_type);
  }

  // Get return type
  Symbol return_type = node->return_type_->visit(this);
  function_symbol.return_type_ = return_type.type_;
  function_symbol.size0_ = return_type.size0_;
  function_symbol.size1_ = return_type.size1_;

  // Visit block or statement, if not forward declared
  curr_function_ = function_symbol;
  if (node->body_ != nullptr) {
    if (old_function.value_ == (llvm::Value *)-1) {
      throw FunctionRedefineError(node->id_, node->node_line_);
    }
    function_symbol.value_ = (llvm::Value *)-1;
    node->body_->visit(this);
  }
  curr_function_ = {};

  // Pop scope
  curr_scope_ = curr_scope_->parent_;

  // Get name
  std::string function_name = node->id_;

  // Check if using built-in name
  if (isBuiltin(function_name)) {
    throw ReservedNameError(function_name, node->node_line_);
  }

  // Check if invalid forward declaration
  if (old_function) {
    if (old_function.return_type_ != function_symbol.return_type_ ||
        old_function.children_.size() != function_symbol.children_.size()) {
      throw FunctionDeclTypeError(function_name, node->node_line_);
    }
    for (size_t i = 0; i < old_function.children_.size(); ++i) {
      if (old_function.children_[i].second !=
          function_symbol.children_[i].second) {
        throw FunctionDeclArgTypeError(function_name, node->node_line_);
      }
    }
  }

  // Add to global scope symbol table
  curr_scope_->declare(function_name, function_symbol);
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitFunctionParamNode(FunctionParamNode *node) {
  DEBUG_FUNC_ENTRY
  // Get param information
  std::string param_name = node->id_;
  Symbol param_type = node->type_->visit(this);

  // Add to scope
  curr_scope_->declare(param_name, param_type);
  DEBUG_FUNC_EXIT
  return param_type;
};

Symbol DefRef::visitProcedureDecl(ProcedureDecl *node) {
  DEBUG_FUNC_ENTRY
  // Create + push procedure scope
  Scope *procedure_scope = new Scope();
  procedure_scope->parent_ = curr_scope_;
  curr_scope_ = procedure_scope;
  auto old_procedure = curr_scope_->resolve(node->id_);

  // Add to scope map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Create symbol
  Symbol procedure_symbol;
  procedure_symbol.type_ = Type::PROCEDURE;

  // Visit params and add to scope + add to children
  for (auto &param : node->params_) {
    // Get param information
    std::string param_name = param->id_;
    Symbol param_type = param->visit(this);

    // Add to symbol children
    procedure_symbol.addChild(param_name, param_type);
  }

  // Get return type, if it exists
  if (node->return_type_ != nullptr) {
    Symbol return_type = node->return_type_->visit(this);
    procedure_symbol.return_type_ = return_type.type_;
    procedure_symbol.size0_ = return_type.size0_;
    procedure_symbol.size1_ = return_type.size1_;
  }

  // Visit block or statement, if not forward declared
  curr_function_ = procedure_symbol;
  if (node->body_ != nullptr) {
    if (old_procedure.value_ == (llvm::Value *)-1) {
      throw FunctionRedefineError(node->id_, node->node_line_);
    }
    procedure_symbol.value_ = (llvm::Value *)-1;
    node->body_->visit(this);
  }
  curr_function_ = {};

  // Pop scope
  curr_scope_ = curr_scope_->parent_;

  // Get name
  std::string procedure_name = node->id_;

  // Check if using built-in name
  if (isBuiltin(procedure_name)) {
    throw ReservedNameError(procedure_name, node->node_line_);
  }

  // Check if invalid forward declaration
  if (old_procedure) {
    if (old_procedure.return_type_ != procedure_symbol.return_type_ ||
        old_procedure.children_.size() != procedure_symbol.children_.size()) {
      throw FunctionDeclTypeError(procedure_name, node->node_line_);
    }
    for (size_t i = 0; i < old_procedure.children_.size(); ++i) {
      if (old_procedure.children_[i].second !=
          procedure_symbol.children_[i].second) {
        throw FunctionDeclArgTypeError(procedure_name, node->node_line_);
      }
    }
  }

  // Add to global scope symbol table
  curr_scope_->declare(procedure_name, procedure_symbol);
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitProcedureParam(ProcedureParam *node) {
  DEBUG_FUNC_ENTRY
  // Get param information
  std::string param_name = node->id_;
  Symbol param_type = node->type_->visit(this);

  // Set type qualifier
  param_type.qualifier_ = node->qualifier_;

  // Add to scope
  curr_scope_->declare(param_name, param_type);
  DEBUG_FUNC_EXIT
  return param_type;
};

Symbol DefRef::visitLoop(Loop *node) {
  DEBUG_FUNC_ENTRY
  // Create + push loop scope
  Scope *loop_scope = new Scope();
  loop_scope->parent_ = curr_scope_;
  curr_scope_ = loop_scope;

  // Add to scope map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Visit condition, if applicable
  if (node->predicate_expr_) {
    auto symbol = node->predicate_expr_->visit(this);
    // value must be of type boolean
    if (symbol.type_ == Type::_NULL_) {
      symbol.type_ = Type::BOOLEAN;
      node->setPredicateExpr(std::make_unique<BooleanNode>(false));
    } else if (symbol.type_ == Type::IDENTITY) {
      symbol.type_ = Type::BOOLEAN;
      node->setPredicateExpr(std::make_unique<BooleanNode>(true));
    } else if (symbol.type_ != Type::BOOLEAN) {
      throw PredicateTypeError(node->node_line_);
    }
  }

  // Visit domains, if applicable
  // First visit, to determine if expressions valid
  std::vector<std::pair<std::string, Symbol>> domains;
  for (auto &domain : node->domains_) {
    domains.emplace_back(domain->id_, domain->visit(this));
  }
  // Then, declare in scope
  for (auto domain : domains) {
    // Add to scope
    if (domain.second.type_ == Type::INTERVAL) {
      curr_scope_->declare(domain.first, {Type::INTEGER});
    } else {
      curr_scope_->declare(domain.first,
                           {TypeHelpers::vectorToScalar(domain.second.type_)});
    }
  }

  // Visit body
  node->block_->visit(this);

  // Pop scope
  curr_scope_ = curr_scope_->parent_;
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitConditionStatement(ConditionStatement *node) {
  DEBUG_FUNC_ENTRY
  // Create + push condition scope
  Scope *condition_scope = new Scope();
  condition_scope->parent_ = curr_scope_;
  curr_scope_ = condition_scope;

  // Add to scope map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Visit condition
  auto symbol = node->condition_expr_->visit(this);
  // value must be of type boolean
  if (symbol.type_ == Type::_NULL_) {
    symbol.type_ = Type::BOOLEAN;
    node->condition_expr_ = std::make_unique<BooleanNode>(false);
  } else if (symbol.type_ == Type::IDENTITY) {
    symbol.type_ = Type::BOOLEAN;
    node->condition_expr_ = std::make_unique<BooleanNode>(true);
  } else if (symbol.type_ != Type::BOOLEAN) {
    throw PredicateTypeError(node->node_line_);
  }

  // Visit body/bodies
  node->true_block_->visit(this);
  if (node->false_block_ != nullptr) {
    node->false_block_->visit(this);
  }

  // Pop scope
  curr_scope_ = curr_scope_->parent_;
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitBlock(Block *node) {
  DEBUG_FUNC_ENTRY
  // NOTE: Blocks define a new scope. This means that if a function/
  // procedure/loop/etc. has a block, it will push an additonal scope
  // on top of the scope those nodes define. This is fine, as when we
  // resolve anything in the function/ procedure/loop/etc. such as
  // parameters or conditions, it should travel down the scope stack anyway

  // Create + push block scope
  Scope *block_scope = new Scope();
  block_scope->parent_ = curr_scope_;
  curr_scope_ = block_scope;

  // Add to scope map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Visit statements
  for (auto &statement : node->statements_) {
    statement->visit(this);
  }

  // Pop scope
  curr_scope_ = curr_scope_->parent_;
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitGeneratorExpr(GeneratorExpr *node) {
  DEBUG_FUNC_ENTRY

  // Create + push loop scope
  Scope *generator_scope = new Scope();
  generator_scope->parent_ = curr_scope_;
  curr_scope_ = generator_scope;

  // Add to scope map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Visit domains
  // First visit, to determine if expressions valid
  std::vector<std::pair<std::string, Symbol>> domains;
  for (auto &domain : node->domains_) {
    domains.emplace_back(domain->id_, domain->visit(this));
  }
  // Then, declare in scope
  for (auto domain : domains) {
    // Add to scope
    if (domain.second.type_ == Type::INTERVAL) {
      curr_scope_->declare(domain.first, {Type::INTEGER});
    } else {
      curr_scope_->declare(domain.first,
                           {TypeHelpers::vectorToScalar(domain.second.type_)});
    }
  }

  // Visit expression
  Symbol expression = node->main_expr_->visit(this);

  Symbol result_symbol;
  if (node->domains_.size() == 1) {
    // Vector Generator
    result_symbol.type_ = TypeHelpers::scalarToVector(expression.type_);
    result_symbol.size0_ = domains[0].second.size0_;
  } else if (node->domains_.size() == 2) {
    // Matrix Generator
    result_symbol.type_ = TypeHelpers::scalarToMatrix(expression.type_);
    result_symbol.size0_ = domains[0].second.size0_;
    result_symbol.size1_ = domains[1].second.size1_;
  } else {
    throw PanicError();
  }

  // Pop scope
  curr_scope_ = curr_scope_->parent_;

  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitFilterExpr(FilterExpr *node) {
  DEBUG_FUNC_ENTRY

  // Create + push loop scope
  Scope *filter_scope = new Scope();
  filter_scope->parent_ = curr_scope_;
  curr_scope_ = filter_scope;

  // Add to scope map
  Scope::scopes_.insert_or_assign(node->node_id_, curr_scope_);

  // Visit domain
  Symbol domain_symbol = node->domain_->visit(this);
  std::string domain_id = node->domain_->id_;

  if (domain_symbol.type_ == Type::INTERVAL) {
    curr_scope_->declare(domain_id, {Type::INTEGER});
  } else {
    curr_scope_->declare(domain_id,
                         {TypeHelpers::vectorToScalar(domain_symbol.type_)});
  }

  Symbol result_symbol;
  result_symbol.type_ = Type::TUPLE;

  Symbol vector_symbol;
  vector_symbol.type_ = domain_symbol.type_;

  // Visit expressions
  for (auto &sub_expr : node->sub_exprs_) {
    Symbol expression = sub_expr->visit(this);
    if (expression.type_ != Type::BOOLEAN) {
      throw PredicateTypeError(node->node_line_);
    }

    result_symbol.addChild("", vector_symbol);
  }

  // For false tuple member
  result_symbol.addChild("", vector_symbol);

  // Pop scope
  curr_scope_ = curr_scope_->parent_;

  DEBUG_FUNC_EXIT
  return result_symbol;
}

// Other statements
Symbol DefRef::visitTypeDef(TypeDef *node) {
  DEBUG_FUNC_ENTRY
  // Get defined type name
  std::string type_name = node->id_;

  // Get the base type
  Symbol base_type = node->base_type_->visit(this);

  // Add to typedef table
  typedefs_.insert_or_assign(type_name, base_type);
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitAssignStatement(AssignStatement *node) {
  DEBUG_FUNC_ENTRY
  if (node->lValues_.size() == 1) {
    // For only one l-value
    // Get target symbol
    Symbol target = node->lValues_[0]->visit(this);

    if (target.qualifier_ == Qualifier::CONST) {
      throw ConstAssignError(node->lValues_[0]->id_name_, node->node_line_);
    }

    // Visit expression
    Symbol expression = node->expr_->visit(this);

    // Insert explicit typecast here, if needed
    if (insertTypecast(expression, target, node->node_line_)) {
      std::unique_ptr<AST> target_type =
          std::unique_ptr<AST>(symbolToTypeNode(target));
      TypeCast *typecast = new TypeCast();
      typecast->target_type_ = std::move(target_type);
      typecast->value_ = std::move(node->expr_);
      node->expr_ = std::unique_ptr<AST>(typecast);
    }
  } else {
    // Multiple l-values (tuple unpacking)
    // Visit expression
    Symbol expression = node->expr_->visit(this);

    // If not tuple type, or sizes do not correspond, cannot unpack
    if (expression.type_ != Type::TUPLE ||
        expression.children_.size() != node->lValues_.size()) {
      throw UnpackingError(node->node_line_);
    }

    // Store target types, if needed for type-casting
    bool typecast_needed = false;

    Symbol target_tuple;
    target_tuple.type_ = Type::TUPLE;

    for (size_t i = 0; i < node->lValues_.size(); i++) {
      // Get target symbol
      Symbol target = node->lValues_[i]->visit(this);
      target_tuple.addChild("", target);

      if (target.qualifier_ == Qualifier::CONST) {
        throw ConstAssignError(node->lValues_[i]->id_name_, node->node_line_);
      }

      // Get expression child symbol
      Symbol child = expression.children_[i].second;

      // Determine if type promotion is needed
      if (child != target) {
        // Check if expression can be promoted to symbol beforehand's type
        if (!canPromoteTo(child.type_, target.type_) ||
            !compatibleSizes(child, target)) {
          throw TypeError(to_string(target), to_string(child),
                          node->node_line_);
        }
        typecast_needed = true;
      }
    }

    // Insert explicit typecast here, if needed
    if (typecast_needed) {
      std::unique_ptr<AST> target_type =
          std::unique_ptr<AST>(symbolToTupleTypeNode(target_tuple));
      TypeCast *typecast = new TypeCast();
      typecast->target_type_ = std::move(target_type);
      typecast->value_ = std::move(node->expr_);
      node->expr_ = std::unique_ptr<AST>(typecast);
    }
  }

  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitDeclareStatement(DeclareStatement *node) {
  DEBUG_FUNC_ENTRY
  // Get name
  std::string name = node->id_;

  // If re-declaring in same scope
  if (curr_scope_->isDefined(name)) {
    throw RedeclarationError(node->id_, node->node_line_);
  }

  // If using built-in name
  if (isBuiltin(name)) {
    throw ReservedNameError(name, node->node_line_);
  }

  Symbol target_type;
  if (node->type_) {
    target_type = node->type_->visit(this);
  }

  // Visit expression
  if (node->main_expr_) {
    Symbol expression = node->main_expr_->visit(this);

    // Get type
    if (node->type_) {
      // If type specified
      // Insert explicit typecast here, if needed
      if (insertTypecast(expression, target_type, node->node_line_)) {
        std::unique_ptr<AST> target =
            std::unique_ptr<AST>(symbolToTypeNode(target_type));
        TypeCast *typecast = new TypeCast();
        typecast->target_type_ = std::move(target);
        typecast->value_ = std::move(node->main_expr_);
        node->main_expr_ = std::unique_ptr<AST>(typecast);
      }
    } else {
      // If type inferred
      target_type = expression;
    }
  }

  // Get qualifier
  target_type.qualifier_ = node->qualifier_;

  if (curr_scope_->parent_ == nullptr &&
      target_type.qualifier_ != Qualifier::CONST) {
    throw GlobalNonConstError(name, node->node_line_);
  }

  std::array<Type, 5> unspecified_types = {
      Type::NONE, Type::_NULL_, Type::IDENTITY, Type::VECTOR, Type::MATRIX};

  if (std::any_of(unspecified_types.begin(), unspecified_types.end(),
                  [target_type, unspecified_types](Type other) {
                    return target_type.type_ == other;
                  })) {
    // you have infered lhs type and no rhs expr
    throw TypeInferenceError(name, node->node_line_);
  }

  // Add symbol to symbol table
  curr_scope_->declare(name, target_type);
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitStream(Stream *node) {
  DEBUG_FUNC_ENTRY
  if (node->token_ == Token::INSTREAM) {
    if (!node->stream_lvalue_) {
      throw PanicError(); // should always have l-value
    }

    Symbol l_value = node->stream_lvalue_->visit(this);

    if (!TypeHelpers::isScalar(l_value.type_)) {
      throw NonScalarStreamLValue(node->node_line_);
    }

    if (l_value.qualifier_ == Qualifier::CONST) {
      throw ConstAssignError(node->stream_lvalue_->id_name_, node->node_line_);
    }
  } else {
    if (!node->stream_expr_) {
      throw PanicError(); // should always have expression
    }

    Symbol expr = node->stream_expr_->visit(this);

    if (!TypeHelpers::isValidTupleMemberOrOutstreamType(expr.type_)) {
      throw InvalidOutStreamType(to_string(expr), node->node_line_);
    }
  }

  DEBUG_FUNC_EXIT
  return {};
};

Symbol DefRef::visitReturnNode(ReturnNode *node) {
  DEBUG_FUNC_ENTRY
  if (curr_function_.type_ != Type::FUNCTION &&
      curr_function_.type_ != Type::PROCEDURE) {
    // Return outside of function/procedure definition
    throw ReturnOutsideDeclError(node->node_line_);
  }

  if (curr_function_.return_type_ != Type::NONE) {
    if (!node->return_value_) {
      // No returned value when there should be
      throw IncorrectReturnType(node->node_line_);
    }

    Symbol target = curr_function_;
    target.type_ = curr_function_.return_type_;
    Symbol expression = node->return_value_->visit(this);

    // Insert explicit typecast here, if needed
    if (insertTypecast(expression, target, node->node_line_)) {
      std::unique_ptr<AST> target_type =
          std::unique_ptr<AST>(symbolToTypeNode(target));
      TypeCast *typecast = new TypeCast();
      typecast->target_type_ = std::move(target_type);
      typecast->value_ = std::move(node->return_value_);
      node->return_value_ = std::unique_ptr<AST>(typecast);
    }
  } else {
    if (node->return_value_) {
      // Returned value when there shouldn't be
      throw IncorrectReturnType(node->node_line_);
    }
  }

  DEBUG_FUNC_EXIT
  return {};
};

// Expressions
Symbol DefRef::visitBinaryExpr(BinaryExpr *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;

  // Visit sub-expressions
  Symbol left_symbol = node->left_sub_expr_->visit(this);
  Symbol right_symbol = node->right_sub_expr_->visit(this);

  // Make both const
  left_symbol.qualifier_ = Qualifier::CONST;
  right_symbol.qualifier_ = Qualifier::CONST;

  // Get result type
  auto iter = binary_functions_.find(
      {node->token_, left_symbol.type_, right_symbol.type_});
  if (iter != binary_functions_.end()) {
    result_symbol.type_ = iter->second.second;
  } else { // types arent operable
    throw InoperableTypeError(to_string(left_symbol), to_string(right_symbol),
                              node->node_line_);
  }

  // Tuples
  if (left_symbol.type_ == Type::TUPLE && right_symbol.type_ == Type::TUPLE) {
    // Incompatible tuple sizes
    if (left_symbol.children_.size() != right_symbol.children_.size()) {
      throw InoperableTypeError(to_string(left_symbol), to_string(right_symbol),
                                node->node_line_);
    }

    for (size_t i = 0; i < left_symbol.children_.size(); i++) {
      Symbol left_child = left_symbol.children_[i].second;
      Symbol right_child = right_symbol.children_[i].second;
      left_child.qualifier_ = Qualifier::CONST;
      right_child.qualifier_ = Qualifier::CONST;
      if (left_child != right_child) {
        if (!compatibleSizes(left_child, right_child) ||
            !compatibleSizes(right_child, left_child) ||
            left_child.type_ != right_child.type_) {
          throw InoperableTypeError(to_string(left_child),
                                    to_string(right_child), node->node_line_);
        }
      }
    }
    return result_symbol;
  } else if (node->token_ == Token::BY) {
  } else {
    if (left_symbol.type_ != right_symbol.type_) {
      // Typecast to appropriate type
      if (canPromoteTo(left_symbol.type_, right_symbol.type_)) {
        // Insert explicit typecast here
        if (!compatibleSizes(left_symbol, right_symbol)) {
          throw IncompatibleSizeError(node->node_line_);
        }
        auto symbol = right_symbol;
        if (!TypeHelpers::isScalar(left_symbol.type_)) {
          symbol.size0_ = -1lu;
          symbol.size1_ = -1lu;
        } else {
          left_symbol.size0_ = right_symbol.size0_;
          left_symbol.size1_ = right_symbol.size1_;
        }

        std::unique_ptr<AST> new_type =
            std::unique_ptr<AST>(symbolToTypeNode(symbol));
        TypeCast *typecast = new TypeCast();
        typecast->target_type_ = std::move(new_type);
        typecast->value_ = std::move(node->left_sub_expr_);
        node->left_sub_expr_ = std::unique_ptr<AST>(typecast);
      } else if (canPromoteTo(right_symbol.type_, left_symbol.type_)) {
        // If the right symbol can be implicitly cast to the left
        // Insert explicit typecast here
        if (!compatibleSizes(left_symbol, right_symbol)) {
          throw IncompatibleSizeError(node->node_line_);
        }
        auto symbol = left_symbol;
        if (!TypeHelpers::isScalar(right_symbol.type_)) {
          symbol.size0_ = -1lu;
          symbol.size1_ = -1lu;
        } else {
          right_symbol.size0_ = left_symbol.size0_;
          right_symbol.size1_ = left_symbol.size1_;
        }
        std::unique_ptr<AST> new_type =
            std::unique_ptr<AST>(symbolToTypeNode(symbol));
        TypeCast *typecast = new TypeCast();
        typecast->target_type_ = std::move(new_type);
        typecast->value_ = std::move(node->right_sub_expr_);
        node->right_sub_expr_ = std::unique_ptr<AST>(typecast);
      } else {
        throw PanicError(); // in one table but not another
      }
    }

    if (node->token_ == Token::CAT) {
      if (left_symbol.size0_ == -1lu || right_symbol.size0_ == -1lu) {
        if (TypeHelpers::isScalar(left_symbol.type_)) {
          Symbol symbol = right_symbol;
          symbol.size0_ = 1lu;
          result_symbol.size0_ = right_symbol.size0_;
          std::unique_ptr<AST> new_type =
              std::unique_ptr<AST>(symbolToTypeNode(symbol));
          TypeCast *typecast = new TypeCast();
          typecast->target_type_ = std::move(new_type);
          typecast->value_ = std::move(node->left_sub_expr_);
          node->left_sub_expr_ = std::unique_ptr<AST>(typecast);
        } else if (TypeHelpers::isScalar(right_symbol.type_)) {
          Symbol symbol = left_symbol;
          symbol.size0_ = 1lu;
          result_symbol.size0_ = left_symbol.size0_;
          std::unique_ptr<AST> new_type =
              std::unique_ptr<AST>(symbolToTypeNode(symbol));
          TypeCast *typecast = new TypeCast();
          typecast->target_type_ = std::move(new_type);
          typecast->value_ = std::move(node->left_sub_expr_);
          node->left_sub_expr_ = std::unique_ptr<AST>(typecast);
        } else {
          result_symbol.size0_ = -1lu;
        }
      } else {
        result_symbol.size0_ = left_symbol.size0_ + right_symbol.size0_;
      }
    } else if (node->token_ == Token::DOT_PROD) {
      if (TypeHelpers::isMatrix(right_symbol.type_)) {
        if (left_symbol.size1_ != right_symbol.size0_ &&
            left_symbol.size1_ != -1lu && right_symbol.size0_ != -1lu) {
          throw IncompatibleSizeError(node->node_line_);
        }
        result_symbol.size0_ = left_symbol.size0_;
        result_symbol.size1_ = left_symbol.size1_;
      } else if (TypeHelpers::isVector(right_symbol.type_)) {
        if (left_symbol.size0_ != right_symbol.size0_ &&
            left_symbol.size0_ != -1lu && right_symbol.size0_ != -1lu) {
          throw IncompatibleSizeError(node->node_line_);
        }
      } else {
        throw PanicError();
      }
    } else {
      result_symbol.size0_ = right_symbol.size0_;
      result_symbol.size1_ = right_symbol.size1_;

      // Resolve sizes
      if (left_symbol.size0_ != right_symbol.size0_) {
        if (left_symbol.size0_ == -1lu || right_symbol.size0_ == -1lu) {
          result_symbol.size0_ = -1lu;
        } else {
          throw IncompatibleSizeError(node->node_line_);
        }
      } else if (left_symbol.size1_ != right_symbol.size1_) {
        if (left_symbol.size1_ == -1lu || right_symbol.size1_ == -1lu) {
          result_symbol.size1_ = -1lu;
        } else {
          throw IncompatibleSizeError(node->node_line_);
        }
      }
    }
  }

  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitUnaryExpr(UnaryExpr *node) {
  DEBUG_FUNC_ENTRY
  // Visit sub-expressions
  Symbol expr_symbol = node->expr_->visit(this);

  // Determine if it can undergo unary operations
  // Get result type
  auto iter = unary_functions_.find({node->token_, expr_symbol.type_});
  if (iter == unary_functions_.end()) {
    throw InoperableTypeError(to_string(expr_symbol), node->node_line_);
  }

  DEBUG_FUNC_EXIT
  return expr_symbol;
}

Symbol DefRef::visitBuiltInCall(BuiltInCall *node) {
  DEBUG_FUNC_ENTRY
  switch (node->token_) {
  case Token::LENGTH: {
    if (!node->arg_) {
      throw FunctionCallArgTypeError(node->id_, node->node_line_);
    }

    Symbol argument = node->arg_->visit(this);

    if (!TypeHelpers::isVector(argument.type_) &&
        argument.type_ != Type::INTERVAL && argument.type_ != Type::STRING) {
      throw FunctionCallArgTypeError(node->id_, node->node_line_);
    }

    node->return_type_ = Type::INTEGER;
    break;
  }
  case Token::REVERSE: {
    if (!node->arg_) {
      throw FunctionCallArgTypeError(node->id_, node->node_line_);
    }

    Symbol argument = node->arg_->visit(this);

    if (argument.type_ == Type::STRING) {
      node->return_type_ = Type::VECTOR_CHARACTER;
      std::unique_ptr<AST> target_type =
          std::unique_ptr<AST>(symbolToTypeNode({Type::VECTOR_CHARACTER}));
      TypeCast *typecast = new TypeCast();
      typecast->target_type_ = std::move(target_type);
      typecast->value_ = std::move(node->arg_);
      node->arg_ = std::unique_ptr<AST>(typecast);
    } else if (argument.type_ == Type::INTERVAL) {
      node->return_type_ = Type::VECTOR_INTEGER;
      std::unique_ptr<AST> target_type =
          std::unique_ptr<AST>(symbolToTypeNode({Type::VECTOR_INTEGER}));
      TypeCast *typecast = new TypeCast();
      typecast->target_type_ = std::move(target_type);
      typecast->value_ = std::move(node->arg_);
      node->arg_ = std::unique_ptr<AST>(typecast);
    } else if (TypeHelpers::isVector(argument.type_)) {
      node->return_type_ = argument.type_;
    } else {
      throw FunctionCallArgTypeError(node->id_, node->node_line_);
    }

    break;
  }
  case Token::ROWS:
  case Token::COLUMNS: {
    if (!node->arg_) {
      throw FunctionCallArgTypeError(node->id_, node->node_line_);
    }

    Symbol argument = node->arg_->visit(this);

    if (!TypeHelpers::isMatrix(argument.type_)) {
      throw FunctionCallArgTypeError(node->id_, node->node_line_);
    }

    node->return_type_ = Type::INTEGER;
    break;
  }
  case Token::STREAM_STATE:
    if (node->arg_) {
      throw FunctionCallArgTypeError(node->id_, node->node_line_);
    }

    node->return_type_ = Type::NONE;
    break;
  default:
    throw PanicError();
  }

  DEBUG_FUNC_EXIT
  return {node->return_type_};
}

Symbol DefRef::visitFunctionCallNode(FunctionCallNode *node) {
  DEBUG_FUNC_ENTRY
  // NOTE: even though it's called a function call, this can
  // also be a procedure expression call

  // Get function name
  std::string function_name = node->id_;

  // Resolve function/procedure symbol
  Symbol function_symbol = curr_scope_->resolve(function_name);
  if (!function_symbol) {
    throw ReferenceError(function_name, node->node_line_);
  }

  // Verify that it's a function/procedure
  if (function_symbol.type_ != Type::FUNCTION &&
      function_symbol.type_ != Type::PROCEDURE) {
    throw InvalidCallError(function_name, node->node_line_);
  }

  // Verify that args and params have the same length
  if (node->args_.size() != function_symbol.children_.size()) {
    throw FunctionCallArgTypeError(function_name, node->node_id_);
  }

  // Visit arg expressions
  for (size_t i = 0; i < node->args_.size(); i++) {
    // Visit that argument
    Symbol expression = node->args_[i]->visit(this);
    Symbol target_type = function_symbol.children_[i].second;

    /*
    bool is_var_id_node = node->args_[i]->token_ == Token::ID_EXPR &&
                          expression.qualifier_ != Qualifier::CONST;
    bool is_var_index_node = node->args_[i]->token_ == Token::ID_MATRIX_INDEX &&
                          expression.qualifier_ != Qualifier::CONST;
    */

    if (target_type.qualifier_ == Qualifier::VAR &&
        expression.qualifier_ == Qualifier::CONST) {
      throw ConstRefError(function_name, i + 1, node->node_line_);
    }

    if (expression.type_ != target_type.type_) {
      // Verify that arg type is promotable to function/procedure param type
      if (!canPromoteTo(expression.type_, target_type.type_)) {
        throw FunctionCallArgTypeError(function_name, node->node_id_);
      } else {
        // Insert explicit typecast here
        std::unique_ptr<AST> new_type =
            std::unique_ptr<AST>(symbolToTypeNode(target_type));
        TypeCast *typecast = new TypeCast();
        typecast->target_type_ = std::move(new_type);
        typecast->value_ = std::move(node->args_[i]);
        node->args_[i] = std::unique_ptr<AST>(typecast);
      }
    }
  }

  // Get resolved symbol return type
  Symbol return_type;
  return_type.type_ = function_symbol.return_type_;
  return_type.size0_ = function_symbol.size0_;
  return_type.size1_ = function_symbol.size1_;
  DEBUG_FUNC_EXIT
  return return_type;
}

Symbol DefRef::visitProcedureCall(ProcedureCall *node) {
  DEBUG_FUNC_ENTRY
  // Get function name
  std::string procedure_name = node->id_;

  // Resolve function/procedure symbol
  Symbol procedure_symbol = curr_scope_->resolve(procedure_name);
  if (!procedure_symbol) {
    throw ReferenceError(procedure_name, node->node_line_);
  }

  // Verify that it's a procedure
  if (procedure_symbol.type_ != Type::PROCEDURE) {
    throw InvalidProcedureCallError(procedure_name, node->node_line_);
  }

  // Verify that args and params have the same length
  if (node->args_.size() != procedure_symbol.children_.size()) {
    throw FunctionCallArgTypeError(procedure_name, node->node_id_);
  }

  // Visit arg expressions
  for (size_t i = 0; i < node->args_.size(); i++) {
    // Visit that argument
    Symbol expression = node->args_[i]->visit(this);
    Symbol target_type = procedure_symbol.children_[i].second;

    // bool is_var_id_node = node->args_[i]->token_ == Token::ID_EXPR &&
    //                       expression.qualifier_ != Qualifier::CONST;
    // bool is_var_index_node = node->args_[i]->token_ == Token::INDEX_EXPR &&
    //                       expression.qualifier_ != Qualifier::CONST;

    if (target_type.qualifier_ == Qualifier::VAR &&
        expression.qualifier_ == Qualifier::CONST) {
      throw ConstRefError(procedure_name, i + 1, node->node_line_);
    }

    if (expression.type_ != target_type.type_) {
      // Verify that arg type is promotable to function/procedure param type
      if (!canPromoteTo(expression.type_, target_type.type_)) {
        throw FunctionCallArgTypeError(procedure_name, node->node_id_);
      } else {
        // Insert explicit typecast here
        std::unique_ptr<AST> new_type =
            std::unique_ptr<AST>(symbolToTypeNode(target_type));
        TypeCast *typecast = new TypeCast();
        typecast->target_type_ = std::move(new_type);
        typecast->value_ = std::move(node->args_[i]);
        node->args_[i] = std::unique_ptr<AST>(typecast);
      }
    }
  }
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitTypeCast(TypeCast *node) {
  DEBUG_FUNC_ENTRY
  // Get target type
  Symbol target_type = node->target_type_->visit(this);

  // Visit expression
  Symbol expression = node->value_->visit(this);

  if (expression.type_ == Type::_NULL_ || expression.type_ == Type::IDENTITY) {
    // Null/identity types
    throw NullIdentityCastError(node->node_line_);
  }

  // Check if expression can be promoted to target type
  if (!canCastTo(expression.type_, target_type.type_)) {
    throw TypeError(to_string(expression), to_string(target_type),
                    node->node_line_);
  }

  // Resolve sizes
  if (TypeHelpers::isVector(target_type.type_) && target_type.size0_ == -1lu) {
    if (TypeHelpers::isScalar(expression.type_)) {
      throw TypeError(to_string(expression), to_string(target_type),
                      node->node_line_);
    }

    target_type.size0_ = expression.size0_;
  } else if (TypeHelpers::isMatrix(target_type.type_) &&
             (target_type.size0_ == -1lu || target_type.size1_ == -1lu)) {
    if (TypeHelpers::isScalar(expression.type_)) {
      throw TypeError(to_string(expression), to_string(target_type),
                      node->node_line_);
    }

    if (target_type.size0_ == -1lu) {
      target_type.size0_ = expression.size0_;
    }

    if (target_type.size1_ == -1lu) {
      target_type.size1_ = expression.size1_;
    }
  }

  DEBUG_FUNC_EXIT
  return target_type;
}

Symbol DefRef::visitDomainExpr(DomainExpr *node) {
  DEBUG_FUNC_ENTRY
  // Visit expression to ensure that type is iterable
  Symbol expression = node->main_expr_->visit(this);
  Symbol result_symbol;
  // Get resulting symbol type
  if ((TypeHelpers::isVector(expression.type_) ||
       expression.type_ == Type::INTERVAL) &&
      expression.type_ != Type::VECTOR) {
    result_symbol.type_ = expression.type_;
  } else {
    throw NonIterableDomainError(to_string(expression), node->node_line_);
  }

  result_symbol.size0_ = expression.size0_;

  node->base_type_ = result_symbol;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

// Leaf nodes
Symbol DefRef::visitTypeNode(TypeNode *node) {
  DEBUG_FUNC_ENTRY
  // Get type name
  std::string type_name = node->id_;

  // Find in typedef table
  auto search = typedefs_.find(type_name);
  if (search != typedefs_.end()) {
    Symbol type_symbol = search->second;
    // Resolve sizes
    if (TypeHelpers::isMatrix(node->type_)) {
      // Check if we're sizing a sized type
      if (!TypeHelpers::isScalar(type_symbol.type_)) {
        throw TypeSizingError(type_name, node->node_line_);
      }

      // Convert to matrix
      type_symbol.type_ = TypeHelpers::scalarToMatrix(type_symbol.type_);

      type_symbol.size0_ = node->size0_;
      type_symbol.size1_ = node->size1_;
    } else if (TypeHelpers::isVector(node->type_)) {
      // Check if we're sizing a sized type
      if (!TypeHelpers::isScalar(type_symbol.type_)) {
        throw TypeSizingError(type_name, node->node_line_);
      }

      // Convert to vector
      type_symbol.type_ = TypeHelpers::scalarToVector(type_symbol.type_);

      type_symbol.size0_ = node->size0_;
    }

    node->type_ = type_symbol.type_;

    DEBUG_FUNC_EXIT
    return type_symbol;
  } else {
    throw UndefinedTypeError(type_name, node->node_line_);
  }
  DEBUG_FUNC_EXIT
  return {};
}

Symbol DefRef::visitTuple_type(TupleType *node) {
  DEBUG_FUNC_ENTRY
  Symbol tuple_type;
  tuple_type.type_ = Type::TUPLE;

  for (auto &member : node->types_) {
    Symbol member_symbol = member->visit(this);
    tuple_type.addChild(member->id_, member_symbol);
  }

  DEBUG_FUNC_EXIT
  return tuple_type;
}

Symbol DefRef::visitTuple_member(TupleMember *node) {
  DEBUG_FUNC_ENTRY
  Symbol member = node->type_->visit(this);

  if (!TypeHelpers::isValidTupleMemberOrOutstreamType(member.type_)) {
    throw InvalidTupleTypeError(to_string(member), node->node_line_);
  }
  DEBUG_FUNC_EXIT
  return member;
}

Symbol DefRef::visitIntNode(IntNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::INTEGER;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitBooleanNode(BooleanNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::BOOLEAN;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitCharacterNode(CharacterNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::CHARACTER;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitRealNode(RealNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::REAL;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitIdentityNode(IdentityNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::IDENTITY;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitNullNode(NullNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::_NULL_;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitIntervalNode(IntervalNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  auto lower_bound = node->lowerbound_->visit(this);
  auto upper_bound = node->upperbound_->visit(this);
  if (lower_bound.type_ != Type::INTEGER ||
      upper_bound.type_ != Type::INTEGER) {
    throw InvalidIntervalInitialization(
        to_string(lower_bound), to_string(upper_bound), node->node_line_);
  }
  result_symbol.type_ = Type::INTERVAL;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitStringNode(StringNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::STRING;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitIdNode(IdNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  // TODO: in theory this is wrong. If Idnode is an lvalue is var if its
  // a rvalue its const. The only time we care about constness of a
  // rvalue is in procedure calls with var variables though
  // and we already havent handled that anyways
  // In theory all lvalue calls need to visit a diff function probably
  // but this hacky solution works for now
  result_symbol.qualifier_ = Qualifier::VAR;
  switch (node->token_) {
  case Token::ID_EXPR:
    result_symbol = curr_scope_->resolve(node->id_name_);
    if (!result_symbol) {
      throw ReferenceError(node->id_name_, node->node_line_);
    }
    break;
  case Token::ID_TUPLE_INT_INDEX:
    result_symbol =
        curr_scope_->resolveMember(node->id_name_, node->int_index_);
    if (!result_symbol) {
      throw OutOfBoundsError(node->id_name_, node->int_index_,
                             node->node_line_);
    }
    break;
  case Token::ID_TUPLE_INT_INDEX_VECTOR: {
    Symbol iterable_symbol =
        curr_scope_->resolveMember(node->id_name_, node->int_index_);
    if (!iterable_symbol) {
      throw OutOfBoundsError(node->id_name_, node->int_index_,
                             node->node_line_);
    }

    Symbol index_symbol = node->index0_->visit(this);

    if (!TypeHelpers::isVector(iterable_symbol.type_)) {
      throw BadIndexError(node->id_name_, to_string(iterable_symbol),
                          node->node_line_);
    }

    if (index_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::vectorToScalar(iterable_symbol.type_);
    } else if (index_symbol.type_ == Type::VECTOR_INTEGER ||
               index_symbol.type_ == Type::INTERVAL) {
      result_symbol.type_ = iterable_symbol.type_;
      result_symbol.size0_ = index_symbol.size0_;
    } else {
      throw BadIndexError(node->id_name_, to_string(iterable_symbol),
                          node->node_line_);
    }

    break;
  }
  case Token::ID_TUPLE_INT_INDEX_MATRIX: {
    Symbol matrix_symbol =
        curr_scope_->resolveMember(node->id_name_, node->int_index_);
    if (!matrix_symbol) {
      throw OutOfBoundsError(node->id_name_, node->int_index_,
                             node->node_line_);
    }

    Symbol index0_symbol = node->index0_->visit(this);
    Symbol index1_symbol = node->index1_->visit(this);

    if (!TypeHelpers::isMatrix(matrix_symbol.type_)) {
      throw BadIndexError(node->id_name_, to_string(matrix_symbol),
                          node->node_line_);
    }

    if (index0_symbol.type_ == Type::INTEGER &&
        index1_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::matrixToScalar(matrix_symbol.type_);
    } else if ((index0_symbol.type_ == Type::VECTOR_INTEGER ||
                index0_symbol.type_ == Type::INTERVAL) &&
               index1_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::matrixToVector(matrix_symbol.type_);
      result_symbol.size0_ = index0_symbol.size0_;
      result_symbol.size1_ = matrix_symbol.size1_;
    } else if (index0_symbol.type_ == Type::INTEGER &&
               (index1_symbol.type_ == Type::VECTOR_INTEGER ||
                index1_symbol.type_ == Type::INTERVAL)) {
      result_symbol.type_ = TypeHelpers::matrixToVector(matrix_symbol.type_);
      result_symbol.size0_ = matrix_symbol.size0_;
      result_symbol.size1_ = index1_symbol.size0_;
    } else if ((index0_symbol.type_ == Type::VECTOR_INTEGER ||
                index0_symbol.type_ == Type::INTERVAL) &&
               (index1_symbol.type_ == Type::VECTOR_INTEGER ||
                index1_symbol.type_ == Type::INTERVAL)) {
      result_symbol.type_ = matrix_symbol.type_;
      result_symbol.size0_ = index0_symbol.size0_;
      result_symbol.size1_ = index1_symbol.size0_;
    } else {
      throw BadIndexError(node->id_name_, to_string(matrix_symbol),
                          node->node_line_);
    }
    break;
  }
  case Token::ID_TUPLE_ID_INDEX:
    result_symbol = curr_scope_->resolveMember(node->id_name_, node->id_index_);
    if (!result_symbol) {
      throw MemberReferenceError(node->id_name_, node->id_index_,
                                 node->node_line_);
    }
    break;
  case Token::ID_TUPLE_ID_INDEX_VECTOR: {
    Symbol iterable_symbol =
        curr_scope_->resolveMember(node->id_name_, node->id_index_);
    if (!iterable_symbol) {
      throw MemberReferenceError(node->id_name_, node->id_index_,
                                 node->node_line_);
    }

    Symbol index_symbol = node->index0_->visit(this);

    if (!TypeHelpers::isVector(iterable_symbol.type_)) {
      throw BadIndexError(node->id_name_, to_string(iterable_symbol),
                          node->node_line_);
    }

    if (index_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::vectorToScalar(iterable_symbol.type_);
    } else if (index_symbol.type_ == Type::VECTOR_INTEGER ||
               index_symbol.type_ == Type::INTERVAL) {
      result_symbol.type_ = iterable_symbol.type_;
      result_symbol.size0_ = index_symbol.size0_;
    } else {
      throw BadIndexError(node->id_name_, to_string(iterable_symbol),
                          node->node_line_);
    }

    break;
  }
  case Token::ID_TUPLE_ID_INDEX_MATRIX: {
    Symbol matrix_symbol =
        curr_scope_->resolveMember(node->id_name_, node->id_index_);
    if (!matrix_symbol) {
      throw MemberReferenceError(node->id_name_, node->id_index_,
                                 node->node_line_);
    }

    Symbol index0_symbol = node->index0_->visit(this);
    Symbol index1_symbol = node->index1_->visit(this);

    if (!TypeHelpers::isMatrix(matrix_symbol.type_)) {
      throw BadIndexError(node->id_name_, to_string(matrix_symbol),
                          node->node_line_);
    }

    if (index0_symbol.type_ == Type::INTEGER &&
        index1_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::matrixToScalar(matrix_symbol.type_);
    } else if ((index0_symbol.type_ == Type::VECTOR_INTEGER ||
                index0_symbol.type_ == Type::INTERVAL) &&
               index1_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::matrixToVector(matrix_symbol.type_);
      result_symbol.size0_ = index0_symbol.size0_;
      result_symbol.size1_ = matrix_symbol.size1_;
    } else if (index0_symbol.type_ == Type::INTEGER &&
               (index1_symbol.type_ == Type::VECTOR_INTEGER ||
                index1_symbol.type_ == Type::INTERVAL)) {
      result_symbol.type_ = TypeHelpers::matrixToVector(matrix_symbol.type_);
      result_symbol.size0_ = matrix_symbol.size0_;
      result_symbol.size1_ = index1_symbol.size0_;
    } else if ((index0_symbol.type_ == Type::VECTOR_INTEGER ||
                index0_symbol.type_ == Type::INTERVAL) &&
               (index1_symbol.type_ == Type::VECTOR_INTEGER ||
                index1_symbol.type_ == Type::INTERVAL)) {
      result_symbol.type_ = matrix_symbol.type_;
      result_symbol.size0_ = index0_symbol.size0_;
      result_symbol.size1_ = index1_symbol.size0_;
    } else {
      throw BadIndexError(node->id_name_, to_string(matrix_symbol),
                          node->node_line_);
    }
    break;
  }
  case Token::ID_VECTOR_INDEX: {
    Symbol iterable_symbol = curr_scope_->resolve(node->id_name_);
    if (!iterable_symbol) {
      throw ReferenceError(node->id_name_, node->node_line_);
    }

    Symbol index_symbol = node->index0_->visit(this);

    if (!TypeHelpers::isVector(iterable_symbol.type_)) {
      throw BadIndexError(node->id_name_, to_string(iterable_symbol),
                          node->node_line_);
    }

    if (index_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::vectorToScalar(iterable_symbol.type_);
    } else if (index_symbol.type_ == Type::VECTOR_INTEGER ||
               index_symbol.type_ == Type::INTERVAL) {
      result_symbol.type_ = iterable_symbol.type_;
      result_symbol.size0_ = index_symbol.size0_;
    } else {
      throw BadIndexError(node->id_name_, to_string(iterable_symbol),
                          node->node_line_);
    }

    break;
  }
  case Token::ID_MATRIX_INDEX: {
    Symbol matrix_symbol = curr_scope_->resolve(node->id_name_);
    if (!matrix_symbol) {
      throw ReferenceError(node->id_name_, node->node_line_);
    }

    Symbol index0_symbol = node->index0_->visit(this);
    Symbol index1_symbol = node->index1_->visit(this);

    if (!TypeHelpers::isMatrix(matrix_symbol.type_)) {
      throw BadIndexError(node->id_name_, to_string(matrix_symbol),
                          node->node_line_);
    }

    if (index0_symbol.type_ == Type::INTEGER &&
        index1_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::matrixToScalar(matrix_symbol.type_);
    } else if ((index0_symbol.type_ == Type::VECTOR_INTEGER ||
                index0_symbol.type_ == Type::INTERVAL) &&
               index1_symbol.type_ == Type::INTEGER) {
      result_symbol.type_ = TypeHelpers::matrixToVector(matrix_symbol.type_);
      result_symbol.size0_ = index0_symbol.size0_;
      result_symbol.size1_ = matrix_symbol.size1_;
    } else if (index0_symbol.type_ == Type::INTEGER &&
               (index1_symbol.type_ == Type::VECTOR_INTEGER ||
                index1_symbol.type_ == Type::INTERVAL)) {
      result_symbol.type_ = TypeHelpers::matrixToVector(matrix_symbol.type_);
      result_symbol.size0_ = matrix_symbol.size0_;
      result_symbol.size1_ = index1_symbol.size0_;
    } else if ((index0_symbol.type_ == Type::VECTOR_INTEGER ||
                index0_symbol.type_ == Type::INTERVAL) &&
               (index1_symbol.type_ == Type::VECTOR_INTEGER ||
                index1_symbol.type_ == Type::INTERVAL)) {
      result_symbol.type_ = matrix_symbol.type_;
      result_symbol.size0_ = index0_symbol.size0_;
      result_symbol.size1_ = index1_symbol.size0_;
    } else {
      throw BadIndexError(node->id_name_, to_string(matrix_symbol),
                          node->node_line_);
    }
    break;
  }
  default:
    // Should never be here
    throw PanicError();
  }
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitTupleNode(TupleNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.type_ = Type::TUPLE;

  // Visit members
  for (auto &value : node->values_) {
    Symbol member = value->visit(this);

    // Check that it's a valid tuple type
    if (!TypeHelpers::isValidTupleMemberOrOutstreamType(member.type_)) {
      throw InvalidTupleTypeError(to_string(member), node->node_line_);
    }

    // Add to result symbol
    result_symbol.addChild("", member);
  }

  node->type_ = result_symbol;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

Symbol DefRef::visitVectorNode(VectorNode *node) {
  DEBUG_FUNC_ENTRY
  Symbol result_symbol;
  result_symbol.size0_ = 0;

  // Empty vector/matrix
  if (node->values_.size() == 0) {
    result_symbol.type_ = node->type_.type_;
    node->type_ = result_symbol;
    DEBUG_FUNC_EXIT
    return result_symbol;
  }

  bool isMatrix = false;

  // Base type
  Symbol member_symbol;
  member_symbol.type_ = Type::NONE;

  // Visit members and determine type
  std::vector<Symbol> members;
  for (auto &value : node->values_) {
    Symbol member = value->visit(this);
    if (member_symbol.type_ == Type::NONE) {
      // Determine if vector or matrix based on base child
      if (TypeHelpers::isScalar(member.type_)) {
        // Vector base type
        member_symbol.type_ = Type::_NULL_;
      } else if (TypeHelpers::isVector(member.type_)) {
        // Matrix base type
        member_symbol.type_ = Type::VECTOR;
        isMatrix = true;
        node->token_ = Token::MATRIX_ATOM;
      } else {
        throw InvalidVectorTypeError(to_string(member), node->node_line_);
      }
    }
    members.push_back(member);

    if (isMatrix) {
      // Check that it's a valid matrix type
      if (!TypeHelpers::isVector(member.type_)) {
        throw InvalidMatrixTypeError(to_string(member), node->node_line_);
      }

      // Resolve type
      if (member != member_symbol) {
        if (canPromoteTo(member_symbol.type_, member.type_)) {
          // promote, if appropriate
          member_symbol.type_ = member.type_;
        } else if (!canPromoteTo(member.type_, member_symbol.type_)) {
          throw InvalidMatrixTypeError(to_string(member), node->node_line_);
        }
      }

      // Resolve sizes
      result_symbol.size0_++;
      if (member_symbol.size0_ < member.size0_ ||
          member_symbol.size0_ == -1lu) {
        member_symbol.size0_ = member.size0_;
      }
    } else {
      // Check that it's a valid vector type
      if (!TypeHelpers::isScalar(member.type_)) {
        throw InvalidVectorTypeError(to_string(member), node->node_line_);
      }

      // Resolve type
      if (member != member_symbol) {
        if (canPromoteTo(member_symbol.type_, member.type_)) {
          // promote, if appropriate
          member_symbol.type_ = member.type_;
        } else if (!canPromoteTo(member.type_, member_symbol.type_)) {
          throw InvalidVectorTypeError(to_string(member), node->node_line_);
        }
      }

      // Resolve sizes
      result_symbol.size0_++;
    }
  }

  // Add typecast to any member that's not like the determined type
  for (size_t i = 0; i < members.size(); i++) {
    if (members[i] != member_symbol) {
      // Insert explicit typecast here
      std::unique_ptr<AST> target_type =
          std::unique_ptr<AST>(symbolToTypeNode(member_symbol));
      TypeCast *typecast = new TypeCast();
      typecast->target_type_ = std::move(target_type);
      typecast->value_ = std::move(node->values_[i]);
      node->values_[i] = std::unique_ptr<AST>(typecast);
    }
  }

  if (isMatrix) {
    result_symbol.type_ = TypeHelpers::vectorToMatrix(member_symbol.type_);
    result_symbol.size1_ = member_symbol.size0_;
  } else {
    result_symbol.type_ = TypeHelpers::scalarToVector(member_symbol.type_);
  }

  node->type_ = result_symbol;
  DEBUG_FUNC_EXIT
  return result_symbol;
}

// Helpers
TypeNode *DefRef::symbolToTypeNode(Symbol symbol) {
  DEBUG_FUNC_ENTRY
  TypeNode *type_node = new TypeNode();

  // Get type id
  type_node->id_ = to_string(symbol);

  // Add type
  type_node->type_ = symbol.type_;

  // Get sizes
  type_node->size0_ = symbol.size0_;
  type_node->size1_ = symbol.size1_;

  DEBUG_FUNC_EXIT
  return type_node;
}

TupleType *DefRef::symbolToTupleTypeNode(Symbol symbol) {
  DEBUG_FUNC_ENTRY
  TupleType *type_node = new TupleType();

  // Add children
  for (auto child : symbol.children_) {
    TupleMember *member = new TupleMember();
    member->id_ = child.first;
    member->type_ = std::unique_ptr<TypeNode>(symbolToTypeNode(child.second));
    type_node->addType(std::unique_ptr<TupleMember>(member));
  }

  DEBUG_FUNC_EXIT
  return type_node;
}

bool DefRef::isBuiltin(std::string name) {
  DEBUG_FUNC_ENTRY
  std::array<std::string, 5> built_ins_ = {"length", "rows", "columns",
                                           "reverse", "stream_state"};

  if (std::any_of(
          built_ins_.begin(), built_ins_.end(),
          [name, built_ins_](std::string other) { return name == other; })) {
    DEBUG_FUNC_EXIT
    return true;
  }
  DEBUG_FUNC_EXIT
  return false;
}

bool DefRef::insertTypecast(Symbol source_symbol, Symbol target_symbol,
                            size_t node_line) {
  DEBUG_FUNC_ENTRY
  bool typecast_needed = false;
  target_symbol.qualifier_ = source_symbol.qualifier_;

  if (target_symbol.type_ == Type::TUPLE &&
      source_symbol.type_ == Type::TUPLE) {
    // Tuples
    // Incompatible tuple sizes
    if (target_symbol.children_.size() != source_symbol.children_.size()) {
      throw TypeError(to_string(target_symbol), to_string(source_symbol),
                      node_line);
    }

    for (size_t i = 0; i < target_symbol.children_.size(); i++) {
      Symbol source_child = source_symbol.children_[i].second;
      Symbol target_child = target_symbol.children_[i].second;
      // Determine if type promotion is needed
      if (source_child != target_child) {
        // Check if source can be promoted to symbol beforehand's type
        if ((!canPromoteTo(source_symbol.type_, target_symbol.type_) ||
             !compatibleSizes(source_child, target_child)) &&
            !(source_symbol.type_ == Type::VECTOR &&
              source_symbol.size0_ == 0)) {
          throw TypeError(to_string(target_child), to_string(source_child),
                          node_line);
        }

        typecast_needed = true;
      }
    }
  } else if (source_symbol != target_symbol) {
    // Check if source can be promoted to symbol beforehand's type
    if ((!canPromoteTo(source_symbol.type_, target_symbol.type_) ||
         !compatibleSizes(source_symbol, target_symbol)) &&
        !(source_symbol.type_ == Type::VECTOR && source_symbol.size0_ == 0)) {
      throw TypeError(to_string(target_symbol), to_string(source_symbol),
                      node_line);
    }

    typecast_needed = true;
  }
  DEBUG_FUNC_EXIT
  return typecast_needed;
}

bool DefRef::compatibleSizes(Symbol source_symbol, Symbol target_symbol) {
  DEBUG_FUNC_ENTRY
  DEBUG_FUNC_EXIT
  return (source_symbol.size0_ <= target_symbol.size0_ ||
          target_symbol.size0_ == -1lu ||
          source_symbol.size0_ == -1lu) // Compatible first dim
         && (source_symbol.size1_ <= target_symbol.size1_ ||
             target_symbol.size1_ == -1lu ||
             source_symbol.size1_ == -1lu); // Compatible second dim
}

bool DefRef::canPromoteTo(Type source, Type target) {
  DEBUG_FUNC_ENTRY
  DEBUG_FUNC_EXIT
  return (source == target || source == Type::IDENTITY ||
          source == Type::_NULL_ ||
          (TypeHelpers::isScalar(source) &&
           (TypeHelpers::scalarToMatrix(source) == target ||
            TypeHelpers::scalarToVector(source) == target)) ||
          (source == Type::INTEGER && target == Type::REAL) ||
          (source == Type::VECTOR_INTEGER && target == Type::VECTOR_REAL) ||
          (source == Type::INTERVAL && target == Type::VECTOR_INTEGER) ||
          (source == Type::INTERVAL && target == Type::VECTOR_REAL) ||
          (source == Type::VECTOR && TypeHelpers::isVector(target)) ||
          (source == Type::MATRIX && TypeHelpers::isMatrix(target)) ||
          (source == Type::STRING && target == Type::VECTOR_CHARACTER) ||
          (source == Type::CHARACTER && target == Type::STRING));
}

bool DefRef::canCastTo(Type source, Type target) {
  DEBUG_FUNC_ENTRY
  DEBUG_FUNC_EXIT
  return (canPromoteTo(source, target) ||
          (TypeHelpers::isScalar(source) && TypeHelpers::isScalar(target) &&
           !(source == Type::REAL && target == Type::INTEGER)) ||
          canCastTo(TypeHelpers::matrixToScalar(source),
                    TypeHelpers::matrixToScalar(target)) ||
          canCastTo(TypeHelpers::vectorToScalar(source),
                    TypeHelpers::vectorToScalar(target)));
}
} // namespace gazprea