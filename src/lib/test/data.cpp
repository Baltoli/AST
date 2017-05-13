#include <ast/ast.h>

#include "catch.h"

TEST_CASE("symbols can be constructed") {
  ast::Symbol sym("hello");
  REQUIRE(sym.id == "hello");
}

TEST_CASE("symbols can be compared for equality") {
  ast::Symbol s1("hello");

  SECTION("symbols with the same id are equal") {
    ast::Symbol s2("hello");
    REQUIRE(s1 == s2);
  }

  SECTION("symbols with different id are not equal") {
    ast::Symbol s3("world");
    REQUIRE(s1 != s3);
  }
}
