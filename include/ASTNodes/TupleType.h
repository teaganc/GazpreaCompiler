#pragma once

#include "AST.h"
#include "Token.h"
#include "TypeNode.h"

#include <memory>
#include <vector>

namespace gazprea {

// Helper class for TupleType
class TupleMember : public AST {
public:
  std::string id_ = "";
  std::unique_ptr<TypeNode> type_;

  TupleMember() {}
  TupleMember(std::unique_ptr<TypeNode> type);
  TupleMember(std::string id, std::unique_ptr<TypeNode> type);

  virtual Symbol visit(ASTPass *pass) override;
};

class TupleType : public AST {
public:
  std::vector<std::unique_ptr<TupleMember>> types_;
  void addType(std::unique_ptr<TupleMember> t);

  TupleType();

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea
