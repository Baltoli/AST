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
    if(*it == ':' || *it == '(' || *it == ')' || 
        std::iscntrl(*it) || std::isspace(*it)) {
      break;
    }

    ss << *it;
  }

  if(ss.str().empty()) {
    return ParseResult<Symbol>{};
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

ParseResult<Composite> CompositeParser::get() const
{
  auto it = skip_whitespace(begin_);

  if(*it != '(') {
    return ParseResult<Composite>{};
  }
  it++;

  Composite c;

  std::unique_ptr<Expression> next = nullptr;
  while(true) {
    it = skip_whitespace(it);

    if(auto sym = SymbolParser(it, end_).get()) {
      it = sym.end();
      next = std::unique_ptr<Expression>(sym.data.release());
    } else if(auto comp = CompositeParser(it, end_).get()) {
      it = comp.end();
      next = std::unique_ptr<Expression>(comp.data.release());
    }

    if(!next) {
      break;
    }
    
    c.add_member(std::move(next));
  }

  it = skip_whitespace(it);
  if(*it != ')') {
    return ParseResult<Composite>{};
  }

  return ParseResult<Composite>(c, it+1);
}

}
