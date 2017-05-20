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
