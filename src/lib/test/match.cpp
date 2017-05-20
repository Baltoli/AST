#include <ast/match.h>

#include "catch.h"

TEST_CASE("any matches") {
  auto a = ast::Any();

  auto s = std::make_unique<ast::Symbol>("dj");
  REQUIRE(a.match(s.get()));

  auto c = std::make_unique<ast::Composite>();
  REQUIRE(a.match(c.get()));
}

TEST_CASE("exact matches") {
  auto ex = ast::Exact(ast::Symbol("sym"));

  auto s = std::make_unique<ast::Symbol>("sym");
  REQUIRE(ex.match(s.get()));

  auto t = std::make_unique<ast::Symbol>("jefw");
  REQUIRE(!ex.match(t.get()));

  auto c = ast::Composite();
  c.add_member(ast::Symbol("sym"));
  REQUIRE(!ex.match(&c));
}

TEST_CASE("either matches") {
  auto a = std::make_unique<ast::Exact>(ast::Symbol("a"));
  auto b = std::make_unique<ast::Exact>(ast::Symbol("b"));
  auto e = ast::Either(a.get(), b.get());

  auto s = std::make_unique<ast::Symbol>("a");
  REQUIRE(e.match(s.get()));

  auto t = std::make_unique<ast::Symbol>("b");
  REQUIRE(e.match(t.get()));

  auto u = std::make_unique<ast::Symbol>("c");
  REQUIRE(!e.match(u.get()));
}

TEST_CASE("has child matches") {
  auto ch = ast::Exact(ast::Symbol("sym"));
  auto ex = ast::HasChild(&ch);

  auto c = ast::Composite();
  c.add_member(ast::Symbol("sym"));
  REQUIRE(ex.match(&c));

  auto d = ast::Composite();
  REQUIRE(!ex.match(&d));
  
  auto e = ast::Symbol("sym");
  REQUIRE(!ex.match(&e));

  auto f = ast::Composite();
  f.add_member(ast::Symbol("ewoi"));
  f.add_member(ast::Symbol("sym"));
  REQUIRE(ex.match(&f));
}
