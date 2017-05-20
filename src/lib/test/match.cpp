#include <ast/match.h>

#include "catch.h"

TEST_CASE("exact matches") {
  auto ex = ast::Exact(ast::Symbol("sym"));

  auto s = std::make_unique<ast::Symbol>("sym");
  REQUIRE(ex.match(s.get()));

  auto t = std::make_unique<ast::Symbol>("jefw");
  REQUIRE(!ex.match(t.get()));

  auto c = std::make_unique<ast::Composite>();
  c->add_member(ast::Symbol("sym"));
  REQUIRE(!ex.match(c.get()));
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
