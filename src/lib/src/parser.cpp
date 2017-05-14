#include <ast/parser.h>

#include <ast/ast.h>

#include <iostream>
#include <sstream>

namespace ast {

std::unique_ptr<Symbol> SymbolParser::get() const
{
  auto it = begin_;

  if(*it != ':') {
    return nullptr;
  }
  it++;

  if(*it == '"') {
    return get_quoted();
  } else {
    return get_unquoted();
  }
}

std::unique_ptr<Symbol> SymbolParser::get_unquoted() const
{
  if(end_ - begin_ <= 1) {
    return nullptr;
  }

  std::stringstream ss;
  for(auto it = begin_ + 1; it != end_; ++it) {
    if(*it == ':' || std::iscntrl(*it) || std::isspace(*it)) {
      return nullptr;
    }

    ss << *it;
  }

  return std::unique_ptr<Symbol>(new Symbol(ss.str()));
}

std::unique_ptr<Symbol> SymbolParser::get_quoted() const
{
  if(end_ - begin_ <= 2) {
    return nullptr;
  }

  if(*begin_ != ':' || *(begin_ + 1) != '"') {
    return nullptr;
  }

  std::stringstream ss;
  auto it = begin_ + 2;

  for(; it != end_; ++it) {
    if(*it == '"') {
      it++;
      break;
    }

    ss << *it;
  }

  return std::unique_ptr<Symbol>(new Symbol(ss.str()));
}

}
