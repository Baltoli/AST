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
    Exact(Symbol(">="))
  };
}

ast::Matcher expression()
{
  return AnyOf{
    integer(),
    boolean(),
    AllOf{
      NumChildren(3),
      Child(0, Recursive(expression)),
      Child(1, operation()),
      Child(2, Recursive(expression))
    },
    AllOf{
      NumChildren(4),
      Child(0, Exact(Symbol("if"))),
      Child(1, Recursive(expression)),
      Child(2, Recursive(expression)),
      Child(3, Recursive(expression)),
    },
    AllOf{
      NumChildren(3),
      Child(0, Exact(Symbol("assign"))),
      Child(1, location()),
      Child(2, Recursive(expression))
    },
    AllOf{
      NumChildren(2),
      Child(0, Exact(Symbol("deref"))),
      Child(1, location())
    },
    AllOf{
      NumChildren(1),
      Child(0, Exact(Symbol("skip")))
    },
    AllOf{
      Child(0, Exact(Symbol("seq"))),
      Tail(Recursive(expression))
    },
    AllOf{
      NumChildren(3),
      Child(0, Exact(Symbol("while"))),
      Child(1, Recursive(expression)),
      Child(2, Recursive(expression))
    }
  };
}
