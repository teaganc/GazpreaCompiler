#include "Block.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

Block::Block() { token_ = Token::BLOCK; }

void Block::addStatement(std::unique_ptr<AST> statement) {
  statements_.push_back(std::move(statement));
}

Symbol Block::visit(ASTPass *pass) { return pass->visitBlock(this); }

} // namespace gazprea