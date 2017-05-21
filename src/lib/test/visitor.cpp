#include <ast/visitor.h>

#include "catch.h"

using namespace ast;

#include <iostream>

TEST_CASE("visiting") {
  Visitor v;

  int as = 0;
  int cs = 0;
  v.on(Exact(Symbol("a")), [&](auto&&) { ++as; });
  v.on(IsComposite(), [&](auto&&) { ++cs; });

  v.visit(Composite{
    Symbol("a"),
    Composite{
      Symbol("b"),
      Composite{Symbol("a")}
    }
  });

  REQUIRE(as == 2);
  REQUIRE(cs == 3);
}
