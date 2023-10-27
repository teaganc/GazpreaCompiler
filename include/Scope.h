#pragma once

#include <memory>
#include <unordered_map>

#include "Symbol.h"

namespace gazprea {

class Symbol;

class Scope {
public:
  Scope *parent_;
  std::unordered_map<std::string, Symbol> symbols_;

  void declare(std::string name, Symbol symbol);
  Symbol resolve(std::string name);
  Symbol resolveMember(std::string name, std::string member);
  Symbol resolveMember(std::string name, size_t member);
  bool isDefined(std::string name);

  static std::unordered_map<size_t, Scope *> scopes_;
};

} // namespace gazprea
