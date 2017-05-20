#include <ast/match.h>

#include "catch.h"

using namespace ast;

TEST_CASE("any matches") {
  auto a = Any();

  REQUIRE(a.match(Symbol("dj")));
  REQUIRE(a.match(Composite()));
}

TEST_CASE("is symbol matches") {
  auto ex = IsSymbol();

  REQUIRE(ex.match(Symbol("j")));
  REQUIRE(!ex.match(Composite()));
}

TEST_CASE("is composite matches") {
  auto ex = IsComposite();

  REQUIRE(!ex.match(Symbol("j")));
  REQUIRE(ex.match(Composite()));
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
  auto e = Either(Exact(Symbol("a")), Exact(Symbol("b")));

  REQUIRE(e.match(Symbol("a")));
  REQUIRE(e.match(Symbol("b")));
  REQUIRE(!e.match(Symbol("c")));
}

TEST_CASE("both matches") {
  auto a = Exact(Symbol("a"));
  auto b = Exact(Symbol("b"));
  auto c = Both(HasChild(a), HasChild(b));

  auto comp = Composite();
  comp.add_member(Symbol("a"));
  REQUIRE(!c.match(comp));

  comp.add_member(Symbol("b"));
  REQUIRE(c.match(comp));
}

TEST_CASE("has child matches") {
  auto ch = Exact(Symbol("sym"));
  auto ex = HasChild(ch);

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

TEST_CASE("num children matches") {
  auto c = Composite();
  auto ex = NumChildren(3);
  REQUIRE(!ex.match(c));

  c.add_member(Composite());
  REQUIRE(!ex.match(c));

  c.add_member(Symbol("a"));
  REQUIRE(!ex.match(c));

  c.add_member(Symbol("v"));
  REQUIRE(ex.match(c));

  REQUIRE(!ex.match(Symbol("wij")));
}

TEST_CASE("nth children matches") {
  auto c = Composite();
  auto ex = Child(1, Exact(Symbol("hf")));
  REQUIRE(!ex.match(c));

  c.add_member(Symbol("hf"));
  REQUIRE(!ex.match(c));

  c.add_member(Symbol("hf"));
  REQUIRE(ex.match(c));

  c.add_member(Symbol("fewh"));
  REQUIRE(ex.match(c));

  REQUIRE(!ex.match(Symbol("ewijof")));
}

TEST_CASE("searching") {
  SECTION("in a symbol") {
    auto ex = Exact(Symbol("abc"));
    auto sym = Symbol("abc");
    auto results = search(sym, ex);

    REQUIRE(results.size() == 1);
    REQUIRE(static_cast<const Symbol&>(results[0].expr) == sym);
  }

  SECTION("in a composite") {
    auto ex = Exact(Symbol("abc"));
    auto c = Composite();
    c.add_member(Symbol("abc"));
    c.add_member(Symbol("nope"));

    auto c2 = Composite();
    c2.add_member(Symbol("abc"));
    c.add_member(c2);

    auto results = search(c, ex);
    REQUIRE(results.size() == 2);
    REQUIRE(std::all_of(std::begin(results), std::end(results), [&](auto r) {
      return static_cast<const Symbol&>(r.expr) == Symbol("abc");
    }));
  }
}
