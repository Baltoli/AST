#ifndef AST_PARSER_H
#define AST_PARSER_H

#include <ast/ast.h>

#include <iostream>
#include <string>

namespace ast {

class SymbolParser {
public:
  template<class Iter>
  SymbolParser(Iter begin, Iter end);

  SymbolParser(std::string s) :
    SymbolParser(std::begin(s), std::end(s)) {}

  std::unique_ptr<Symbol> get() const;
private:
  std::unique_ptr<Symbol> get_unquoted() const;
  std::unique_ptr<Symbol> get_quoted() const;

  const std::string::iterator begin_;
  const std::string::iterator end_;
};

template<class Iter>
SymbolParser::SymbolParser(Iter begin, Iter end) :
  begin_(begin), end_(end)
{
}

}

#endif
