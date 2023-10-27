#pragma once

#include "AST.h"
#include "Token.h"

#include <memory>
#include <string>

namespace gazprea {

class TypeNode : public AST {
public:
  std::string id_; // The identifier of the TypeNode
  Type type_;
  size_t size0_ = -1; // The first size of the TypeNode
  size_t size1_ = -1; // The second size of the TypeNode
  // TODO: convert sizes to nodes
  // std::unique_ptr<AST> size0_; // The first size of the TypeNode
  // std::unique_ptr<AST> size1_; // The second size of the TypeNode

  TypeNode();
  TypeNode(std::string id);
  TypeNode(std::string id, size_t first_dim);
  TypeNode(std::string id, size_t first_dim, size_t second_dim);

  void setId(std::string id);
  void setSize(size_t first_dim);
  void setSize(size_t first_dim, size_t second_dim);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea