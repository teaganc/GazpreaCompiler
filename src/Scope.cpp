#include "Scope.h"

namespace gazprea {

void Scope::declare(std::string name, Symbol symbol) {
  symbols_.insert_or_assign(name, symbol);
}

Symbol Scope::resolve(std::string name) {
  auto search = symbols_.find(name);
  if (search != symbols_.end()) {
    return search->second;
  }
  if (parent_ != nullptr) {
    return parent_->resolve(name);
  }
  return {};
}

Symbol Scope::resolveMember(std::string name, std::string member) {
  auto symbol = resolve(name);
  std::vector<Type> types = {Type::FUNCTION, Type::PROCEDURE, Type::TUPLE};
  if (std::any_of(types.begin(), types.end(),
                  [symbol](Type t) { return t == symbol.type_; })) {
    auto search = std::find_if(symbol.children_.begin(), symbol.children_.end(),
                               [member](std::pair<std::string, Symbol> x) {
                                 return x.first == member;
                               });
    if (search != symbol.children_.end()) {
      return search->second;
    }
  }
  return {};
}

Symbol Scope::resolveMember(std::string name, size_t member) {
  member--;
  auto symbol = resolve(name);
  std::vector<Type> types = {Type::FUNCTION, Type::PROCEDURE, Type::TUPLE};
  if (std::any_of(types.begin(), types.end(),
                  [symbol](Type t) { return t == symbol.type_; })) {
    if (symbol.children_.size() > member) {
      return symbol.children_[member].second;
    }
  }
  return {};
}

bool Scope::isDefined(std::string name) {
  // If a name is defined in the current scope (without resolving to parent
  // scopes)
  auto search = symbols_.find(name);
  if (search != symbols_.end()) {
    return true;
  }
  return false;
}

std::unordered_map<size_t, Scope *> Scope::scopes_;

} // namespace gazprea