#include "BuiltInCall.h"
#include "ASTPass.h"

namespace gazprea {

BuiltInCall::BuiltInCall() {}

Symbol BuiltInCall::visit(ASTPass *pass) {
  return pass->visitBuiltInCall(this);
}

} // namespace gazprea