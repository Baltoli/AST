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
    op_expr(),
    if_expr(),
    assign_expr(),
    deref_expr(),
    skip_expr(),
    seq_expr(),
    while_expr()
  };
}

ast::Matcher op_expr()
{
  return AllOf{
    NumChildren(3),
    Child(0, Recursive(expression)),
    Child(1, operation()),
    Child(2, Recursive(expression))
  };
}

ast::Matcher if_expr()
{
  return AllOf{
    NumChildren(4),
    Child(0, Exact(Symbol("if"))),
    Child(1, Recursive(expression)),
    Child(2, Recursive(expression)),
    Child(3, Recursive(expression)),
  };
}

ast::Matcher assign_expr()
{
  return AllOf{
    NumChildren(3),
    Child(0, Exact(Symbol("assign"))),
    Child(1, location()),
    Child(2, Recursive(expression))
  };
}

ast::Matcher deref_expr()
{
  return AllOf{
    NumChildren(2),
    Child(0, Exact(Symbol("deref"))),
    Child(1, location())
  };
}

ast::Matcher skip_expr()
{
  return AllOf{
    NumChildren(1),
    Child(0, Exact(Symbol("skip")))
  };
}

ast::Matcher seq_expr()
{
  return AllOf{
    Child(0, Exact(Symbol("seq"))),
    Tail(Recursive(expression))
  };
}

ast::Matcher while_expr()
{
  return AllOf{
    NumChildren(3),
    Child(0, Exact(Symbol("while"))),
    Child(1, Recursive(expression)),
    Child(2, Recursive(expression))
  };
}
