#include "IdNode.h"
#include "ASTPass.h"

namespace gazprea {

IdNode::IdNode() {}

Symbol IdNode::visit(ASTPass *pass) { return pass->visitIdNode(this); }

} // namespace gazprea
