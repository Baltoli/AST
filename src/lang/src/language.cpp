#include "language.h"

using namespace ast;

bool is_integer(std::string s)
{
  return std::all_of(std::begin(s), std::end(s), [](auto c) {
    return std::isdigit(c);
  });
}

ast::Matcher statement()
{
  return AnyOf{
    store_statement()
  };
}

ast::Matcher store_statement()
{
  return AllOf{
    NumChildren(2),
    Child(0, Exact(Symbol("store"))),
    Child(1, location())
  };
}

ast::Matcher location()
{
  return AllOf{
    NumChildren(2),
    Child(0, Exact(Symbol("loc"))),
    Child(1, Predicate(is_integer))
  };
}
