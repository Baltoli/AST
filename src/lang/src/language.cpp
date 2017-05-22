#include "language.h"

#include <iostream>

using namespace ast;

bool is_integer(std::string s)
{
  return std::all_of(std::begin(s), std::end(s), [](auto c) {
    return std::isdigit(c);
  });
}

ast::Matcher boolean()
{
  return AnyOf{
    Exact(Symbol("true")),
    Exact(Symbol("false"))
  };
}

ast::Matcher integer()
{
  return Predicate(is_integer);
}

ast::Matcher location()
{
  return AllOf{
    Child(0, Exact(Symbol("loc"))),
    Child(1, integer())
  };
}

ast::Matcher operation()
{
  return AnyOf{
    Exact(Symbol("+")),
    Exact(Symbol("*"))
  };
}

ast::Matcher expression()
{
  return AnyOf{
    integer(),
    boolean(),
    AllOf{
      Child(0, expression()),
      Child(1, operation()),
      Child(2, expression())
    }
  };
}
