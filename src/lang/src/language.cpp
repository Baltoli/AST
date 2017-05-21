#include "language.h"

using namespace ast;

bool is_integer(std::string s)
{
  return std::all_of(std::begin(s), std::end(s), [](auto c) {
    return std::isdigit(c);
  });
}

ast::Either statement()
{
  return Either(
    store_statement(),
    Child(0, Exact(Symbol("print")))
  );
}

ast::Both store_statement()
{
  return Both(
    NumChildren(2), Both(
    Child(0, Exact(Symbol("store"))),
    Child(1, location())
  ));
}

ast::Both location()
{
  return Both(
    NumChildren(2), Both (
    Child(0, Exact(Symbol("loc"))),
    Child(1, Predicate(is_integer))
  ));
}
