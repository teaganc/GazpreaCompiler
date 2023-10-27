#include "Stream.h"
#include "ASTPass.h"

#include <utility>

namespace gazprea {

Stream::Stream(Token token) : AST() {
  token_ = token; // Should be of type INSTREAM or OUTSTREAM
}

Stream::Stream(Token token, std::unique_ptr<AST> stream_expr) {
  token_ = token; // Should be of type INSTREAM or OUTSTREAM
  stream_expr_ = std::move(stream_expr);
}

void Stream::setStreamExpr(std::unique_ptr<AST> stream_expr) {
  stream_expr_ = std::move(stream_expr);
}

Symbol Stream::visit(ASTPass *pass) { return pass->visitStream(this); }

} // namespace gazprea
