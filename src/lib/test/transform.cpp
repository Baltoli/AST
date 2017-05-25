#include <ast/transform.h>

#include <ast/match.h>

#include "catch.h"

using namespace ast;

TEST_CASE("basic transformations") {
  Symbol s("a");

  Transformer t(s);
  t.run_on(IsSymbol(), [](auto& ex) { 
    ex = std::make_unique<Symbol>("m");
  });

  auto s2 = t.result().symbol();
  REQUIRE(s2);
  REQUIRE(s2->id == "m");
  REQUIRE(*s2 != s);
}
