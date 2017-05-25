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

TEST_CASE("nesting") {
  Composite c{
    Symbol("a"),
    Composite{ Symbol("b") }
  };

  Transformer t(c);
  t.run_on(Exact(Symbol("b")), [](auto& ex) {
    ex = std::make_unique<Symbol>("w");
  });

  auto c2 = t.result().composite();
  REQUIRE(c2);
  
  Composite cc{
    Symbol("a"),
    Composite{ Symbol("w") }
  };
  REQUIRE(*c2 == cc);
}

TEST_CASE("type switching") {
  Symbol s("a");

  Transformer t(s);
  t.run_on(Any(), [](auto& ex) {
    ex = std::make_unique<Composite>();
  });

  auto c = t.result().composite();
  REQUIRE(*c == Composite());
}

TEST_CASE("top goes first") {
  Composite c{
    Symbol("a"),
    Composite()
  };

  Transformer t(c);
  t.run_on(IsComposite(), [](auto& ex) {
    ex = std::make_unique<Symbol>("b");
  });

  auto s = t.result().symbol();
  REQUIRE(*s == Symbol("b"));
}
