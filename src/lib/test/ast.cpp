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

TEST_CASE("symbols can be cloned") {
  auto e = std::make_unique<ast::Symbol>("hello");
  auto e2 = std::unique_ptr<ast::Symbol>(e->clone());

  REQUIRE(e != e2);
  REQUIRE(*e == *e2);

  REQUIRE(e2->id == "hello");
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

  SECTION("they can be constructed variadically") {
    ast::Composite c{
      ast::Symbol("a"),
      ast::Symbol("b"),
      ast::Composite{
        ast::Symbol("c")
      }
    };

    REQUIRE(c.size() == 3);
    REQUIRE(static_cast<ast::Composite *>(c[2].get())->size() == 1);
  }

  SECTION("they can have new members added") {
    ast::Composite c;
    c.add_member(ast::Symbol("a"));
    c.add_member(ast::Composite());
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

TEST_CASE("composites can be cloned") {
  auto c = std::make_unique<ast::Composite>();
  auto c2 = ast::Composite{};

  auto s = ast::Symbol("a");
  c->add_member(s);

  auto s2 = ast::Symbol("b");
  c2.add_member(s2);
  c->add_member(c2);

  auto clone = std::unique_ptr<ast::Composite>(c->clone());

  REQUIRE(clone->size() == 2);
  REQUIRE(clone != c);
  REQUIRE(*c == *clone);
}

TEST_CASE("expressions can be cast") {
  SECTION("symbols") {
    std::unique_ptr<ast::Expression> s = std::make_unique<ast::Symbol>("a");

    auto s2 = s->symbol();
    REQUIRE(s2);

    auto c = s->composite();
    REQUIRE(!c);
  }

  SECTION("composites") {
    std::unique_ptr<ast::Expression> c = std::make_unique<ast::Composite>();

    auto c2 = c->composite();
    REQUIRE(c2);

    auto s = c->symbol();
    REQUIRE(!s);
  }
}
