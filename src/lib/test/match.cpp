#include <ast/match.h>

#include "catch.h"

using namespace ast;

TEST_CASE("any matches") {
  auto a = Any();

  REQUIRE(a.match(Symbol("dj")));
  REQUIRE(a.match(Composite()));
}

TEST_CASE("exact matches") {
  auto ex = Exact(Symbol("sym"));

  REQUIRE(ex.match(Symbol("sym")));
  REQUIRE(!ex.match(Symbol("jefw")));

  auto c = Composite();
  c.add_member(Symbol("sym"));
  REQUIRE(!ex.match(c));
}

TEST_CASE("either matches") {
  auto a = std::make_unique<Exact>(Symbol("a"));
  auto b = std::make_unique<Exact>(Symbol("b"));
  auto e = Either(a.get(), b.get());

  REQUIRE(e.match(Symbol("a")));
  REQUIRE(e.match(Symbol("b")));
  REQUIRE(!e.match(Symbol("c")));
}

TEST_CASE("both matches") {
  auto a = Exact(Symbol("a"));
  auto ca = HasChild(&a);

  auto b = Exact(Symbol("b"));
  auto cb = HasChild(&b);

  auto c = Both(&ca, &cb);

  auto comp = Composite();
  comp.add_member(Symbol("a"));
  REQUIRE(!c.match(comp));

  comp.add_member(Symbol("b"));
  REQUIRE(c.match(comp));
}

TEST_CASE("has child matches") {
  auto ch = Exact(Symbol("sym"));
  auto ex = HasChild(&ch);

  auto c = Composite();
  c.add_member(Symbol("sym"));
  REQUIRE(ex.match(c));

  REQUIRE(!ex.match(Composite()));
  REQUIRE(!ex.match(Symbol("sym")));

  auto f = Composite();
  f.add_member(Symbol("ewoi"));
  f.add_member(Symbol("sym"));
  REQUIRE(ex.match(f));
}
