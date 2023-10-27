#pragma once

#include "AST.h"
#include "ASTNodes/DomainExpr.h"
#include "Token.h"

#include <memory>
#include <vector>

namespace gazprea {

class Loop : public AST {
public:
  std::unique_ptr<AST>
      predicate_expr_; // The predicate expression (possibly null)
  std::vector<std::unique_ptr<DomainExpr>>
      domains_; // The domains to iterate through (possibly empty)
  std::unique_ptr<AST> block_; // The block node

  Loop();
  Loop(Token token);
  Loop(Token token,
       std::unique_ptr<AST> block); // To initialize infinite of iterator loop
  Loop(std::unique_ptr<AST> predicate_expr,
       std::unique_ptr<AST> block); // To initialize predicated lops

  void addDomain(std::unique_ptr<DomainExpr> domain);
  void setPredicateExpr(std::unique_ptr<AST> predicate_expr);
  void setBlock(std::unique_ptr<AST> block);

  virtual Symbol visit(ASTPass *pass) override;
};

} // namespace gazprea