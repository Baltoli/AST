#include <ast/ast.h>

#include "catch.h"

#include <regex>

TEST_CASE("symbols can be printed") {
  SECTION("simple symbols don't need quoted") {
    ast::Symbol s("hello");
    REQUIRE(s.str() == ":hello");
  }

  SECTION("special characters do need quoted") {
    ast::Symbol s("hello world");
    REQUIRE(s.str() == ":\"hello world\"");

    ast::Symbol s2("hello:world");
    REQUIRE(s2.str() == ":\"hello:world\"");

    ast::Symbol s3("hello\tworld");
    REQUIRE(s3.str() == ":\"hello\tworld\"");
  }
}

TEST_CASE("composites can be printed") {
  SECTION("empty composite") {
    ast::Composite c;
    REQUIRE(c.str() == "()");
  }

  SECTION("one symbol") {
    ast::Composite c;
    c.add_member(ast::Symbol("hello"));

    std::regex r("(\\s+:hello\\s+)");
    REQUIRE(std::regex_search(c.str(), r));
  }

  SECTION("several symbols") {
    ast::Composite c;
    c.add_member(ast::Symbol("one"));
    c.add_member(ast::Symbol("two"));

    std::regex r("(\\s+:one\n\\s+:two\\s+)");
    REQUIRE(std::regex_search(c.str(), r));
  }

  SECTION("nesting") {
    ast::Composite c;
    c.add_member(ast::Symbol("one"));

    ast::Composite c2;
    c2.add_member(ast::Symbol("two"));
    c.add_member(c2);

    std::regex r(":one");
    std::regex r2("(\n\\s+:two\n)");
    REQUIRE(std::regex_search(c.str(), r));
  }
}
