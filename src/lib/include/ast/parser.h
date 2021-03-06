#ifndef AST_PARSER_H
#define AST_PARSER_H

#include <ast/ast.h>

#include <cassert>
#include <string>

namespace ast {

class ParseResult {
public:
  ParseResult() :
    data(nullptr) {}

  ParseResult(const Expression& t, std::string::const_iterator end) :
    data(t.clone()), end_(end) {}

  ParseResult(const ParseResult& other) :
    data(other.data->clone()), end_(other.end_) {}

  ParseResult operator=(ParseResult other) {
    std::swap(data, other.data);
    std::swap(end_, other.end_);
    return *this;
  }

  auto end() const { 
    assert(data && "Accessing end with no data!");
    return end_; 
  }

  std::unique_ptr<Expression> data;

  operator bool() const {
    return static_cast<bool>(data);
  }
private:
  std::string::const_iterator end_;
};

class SymbolParser {
public:
  template<class Iter>
  SymbolParser(Iter begin, Iter end) :
    begin_(begin), end_(end) {}

  SymbolParser(const std::string& s) :
    SymbolParser(std::begin(s), std::end(s)) {}

  ParseResult get() const;
private:
  ParseResult get_unquoted() const;
  ParseResult get_quoted() const;

  const std::string::const_iterator begin_;
  const std::string::const_iterator end_;
};

class CompositeParser {
public:
  template<class Iter>
  CompositeParser(Iter begin, Iter end) :
    begin_(begin), end_(end) {}

  CompositeParser(const std::string& s) :
    CompositeParser(std::begin(s), std::end(s)) {}

  ParseResult get() const;
private:
  using iterator = std::string::const_iterator;

  iterator skip_whitespace(iterator it) const {
    while(std::isspace(*it)) { it++; }
    return it;
  }

  const iterator begin_;
  const iterator end_;
};

}

#endif
