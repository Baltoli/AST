#include <ast/parser.h>

#include <ast/ast.h>

#include <iostream>
#include <sstream>

namespace ast {

ParseResult<Symbol> SymbolParser::get() const
{
  auto it = begin_;

  if(*it != ':') {
    return ParseResult<Symbol>{};
  }
  it++;

  if(*it == '"') {
    return get_quoted();
  } else {
    return get_unquoted();
  }
}

ParseResult<Symbol> SymbolParser::get_unquoted() const
{
  if(end_ - begin_ <= 1) {
    return ParseResult<Symbol>{};
  }

  std::stringstream ss;
  auto it = begin_ + 1;
  for(; it != end_; ++it) {
    if(*it == ':' || std::iscntrl(*it) || std::isspace(*it)) {
      return ParseResult<Symbol>{};
    }

    ss << *it;
  }

  return ParseResult<Symbol>(Symbol(ss.str()), it);
}

ParseResult<Symbol> SymbolParser::get_quoted() const
{
  if(end_ - begin_ <= 2) {
    return ParseResult<Symbol>{};
  }

  if(*begin_ != ':' || *(begin_ + 1) != '"') {
    return ParseResult<Symbol>{};
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

  return ParseResult<Symbol>(Symbol(ss.str()), it);
}

}
