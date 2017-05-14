#ifndef AST_PARSER_H
#define AST_PARSER_H

#include <ast/ast.h>

#include <iostream>
#include <string>

namespace ast {

template<class T>
class ParseResult {
public:
  ParseResult() :
    data(nullptr) {}

  ParseResult(T t, std::string::iterator end) :
    data(new T(t)), end_(end) {}

  ParseResult(const ParseResult<T>& other) :
    data(new T(*other.data)), end_(other.end_) {}

  ParseResult<T>& operator=(ParseResult<T> other) {
    std::swap(data, other.data);
    std::swap(end_, other.end_);
    return *this;
  }

  auto end() const { 
    assert(data && "Accessing end with no data!");
    return end_; 
  }

  const std::unique_ptr<const T> data;

  operator bool() const {
    return static_cast<bool>(data);
  }
private:
  std::string::iterator end_;
};

class SymbolParser {
public:
  template<class Iter>
  SymbolParser(Iter begin, Iter end);

  SymbolParser(std::string s) :
    SymbolParser(std::begin(s), std::end(s)) {}

  ParseResult<Symbol> get() const;
private:
  ParseResult<Symbol> get_unquoted() const;
  ParseResult<Symbol> get_quoted() const;

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
