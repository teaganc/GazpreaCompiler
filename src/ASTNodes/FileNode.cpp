#include "FileNode.h"
#include "ASTPass.h"

namespace gazprea {

FileNode::FileNode() { token_ = Token::FILE_TOKEN; };

void FileNode::addChild(std::unique_ptr<AST> child) {
  children_.push_back(std::move(child));
}

Symbol FileNode::visit(ASTPass *pass) { return pass->visitFileNode(this); }

} // namespace gazprea
