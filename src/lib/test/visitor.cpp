#include <ast/visitor.h>

#include "catch.h"

using namespace ast;

#include <iostream>

class TestVisitor : public Visitor {
public:
  TestVisitor() {
    on(Exact(Symbol("a")), [&](auto&&) { ++as; });
    on(IsComposite(), [&](auto&&) { ++cs; });
  }

  int as = 0;
  int cs = 0;
};

TEST_CASE("visiting") {
  TestVisitor v;

  v.visit(Composite{
    Symbol("a"),
    Composite{
      Symbol("b"),
      Composite{Symbol("a")}
    }
  });

  REQUIRE(v.as == 2);
  REQUIRE(v.cs == 3);
}
