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
    NumChildren(3),
    Child(0, Exact(Symbol("store"))),
    Child(1, location()),
    Child(2, value())
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

ast::Matcher value()
{
  return AnyOf{
    literal(),
    deref()
  };
}

ast::Matcher literal()
{
  return AllOf{
    NumChildren(2),
    Child(0, Exact(Symbol("lit"))),
    Child(1, Predicate(is_integer))
  };
}

ast::Matcher deref()
{
  return AllOf{
    NumChildren(2),
    Child(0, Exact(Symbol("deref"))),
    Child(1, location())
  };
}
