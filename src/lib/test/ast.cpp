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

TEST_CASE("symbols can be ordered") {
  ast::Symbol s1("hello");
  ast::Symbol s2("hellode");
  ast::Symbol s3("aaaaa");
  ast::Symbol s4("world");

  REQUIRE(s1 < s2);
  REQUIRE(!(s1 < s1));
  REQUIRE(s3 < s1);
  REQUIRE(s3 < s2);
  REQUIRE(s1 < s4);
  REQUIRE(s2 < s4);
  REQUIRE(s3 < s4);
}

TEST_CASE("composites can be constructed") {
  SECTION("they can be default constructed") {
    ast::Composite c;
    REQUIRE(c.size() == 0);
  }

  SECTION("they can be constructed from iterators") {
    std::vector<std::unique_ptr<ast::Expression>> v{};
    v.emplace_back(new ast::Symbol("a"));
    v.emplace_back(new ast::Symbol("b"));
    v.emplace_back(new ast::Composite);

    ast::Composite c(std::begin(v), std::end(v));
    REQUIRE(c.size() == 3);
  }

  SECTION("they can have new members added") {
    ast::Composite c;
    c.add_member(ast::Symbol("a"));
    c.add_member(ast::Composite{});
    REQUIRE(c.size() == 2);
  }
}

TEST_CASE("composites can be compared for equality") {
  SECTION("empty composites are equal") {
    ast::Composite c1;
    ast::Composite c2;
    REQUIRE(c1 == c2);
  }

  SECTION("composites with symbols are equal") {
    ast::Composite c1;
    c1.add_member(ast::Symbol("a"));

    ast::Composite c2;
    c2.add_member(ast::Symbol("a"));

    REQUIRE(c1 == c2);
  }

  SECTION("composites with different sizes are not equal") {
    ast::Composite c1;
    c1.add_member(ast::Symbol("a"));

    ast::Composite c2;
    c2.add_member(ast::Symbol("a"));
    c2.add_member(ast::Symbol("a"));

    REQUIRE(c1 != c2);
  }

  SECTION("equality requires ordering") {
    ast::Composite c1;
    c1.add_member(ast::Symbol("a"));
    c1.add_member(ast::Symbol("b"));

    ast::Composite c2;
    c2.add_member(ast::Symbol("b"));
    c2.add_member(ast::Symbol("a"));

    REQUIRE(c1 != c2);
  }

  SECTION("composites with composites are equal") {
    ast::Composite c1;
    ast::Composite c11;
    c11.add_member(ast::Symbol("a"));
    c1.add_member(c11);

    ast::Composite c2;
    ast::Composite c21;
    c21.add_member(ast::Symbol("a"));
    c2.add_member(c21);

    REQUIRE(c1 == c2);
  }
}
