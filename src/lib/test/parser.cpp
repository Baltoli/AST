#include <ast/parser.h>

#include "catch.h"

using namespace ast;

TEST_CASE("symbols can be parsed") {
  SECTION("unquoted symbols") {
    auto sym = ast::SymbolParser(":hello").get();
    REQUIRE(sym);
    REQUIRE(static_cast<Symbol *>(sym.data.get())->id == "hello");

    auto sym2 = ast::SymbolParser(":v").get();
    REQUIRE(sym2);
    REQUIRE(static_cast<Symbol *>(sym2.data.get())->id == "v");
  }

  SECTION("invalid unquoted symbols") {
    auto sym = ast::SymbolParser("::jweif").get();
    REQUIRE(!sym);

    auto sym2 = ast::SymbolParser("").get();
    REQUIRE(!sym2);

    auto sym3 = ast::SymbolParser(":").get();
    REQUIRE(!sym3);
  }

  SECTION("stop parsing at failure") {
    auto sym4 = ast::SymbolParser(":fewioj wefioh").get();
    REQUIRE(sym4);
    REQUIRE(*sym4.end() == ' ');

    auto sym5 = ast::SymbolParser(":wef:").get();
    REQUIRE(sym5);
    REQUIRE(*sym5.end() == ':');

    auto sym6 = ast::SymbolParser(":jef(").get();
    REQUIRE(sym6);
    REQUIRE(*sym6.end() == '(');
  }

  SECTION("quoted symbols") {
    auto sym = ast::SymbolParser(":\"hello\"").get();
    REQUIRE(sym);
    REQUIRE(static_cast<Symbol *>(sym.data.get())->id == "hello");

    auto sym2 = ast::SymbolParser(":\"hi world\"").get();
    REQUIRE(sym2);
    REQUIRE(static_cast<Symbol *>(sym2.data.get())->id == "hi world");

    auto sym3 = ast::SymbolParser(":\":\"").get();
    REQUIRE(sym3);
    REQUIRE(static_cast<Symbol *>(sym3.data.get())->id == ":");

    auto sym4 = ast::SymbolParser(":\"\"").get();
    REQUIRE(sym4);
    REQUIRE(static_cast<Symbol *>(sym4.data.get())->id == "");

    auto sym5 = ast::SymbolParser(":\"\n\"").get();
    REQUIRE(sym5);
    REQUIRE(static_cast<Symbol *>(sym5.data.get())->id == "\n");
  }

  SECTION("invalid quoted symbols") {
    auto sym = ast::SymbolParser(":\"").get();
    REQUIRE(!sym);

    auto sym2 = ast::SymbolParser(": \"ewfieiof\"").get();
    REQUIRE(!sym2);
  }
}

TEST_CASE("symbols survive printing") {
  auto c = ast::Symbol("sja");
  auto c2 = ast::Symbol(":eijw");
  auto c3 = ast::Symbol("fewi ewfhio");

  for(auto&& s : { c, c2, c3 }) {
    auto str = s.str();
    auto p = ast::SymbolParser(str).get();

    REQUIRE(p);
    REQUIRE(s == *static_cast<Symbol *>(p.data.get()));
  }
}

TEST_CASE("composites can be parsed") {
  SECTION("empty composite") {
    auto c = ast::CompositeParser("()").get();
    REQUIRE(c);
    REQUIRE(static_cast<Composite *>(c.data.get())->size() == 0);
  }

  SECTION("simple composites") {
    auto c = ast::CompositeParser("(:hello)").get();
    REQUIRE(c);
    REQUIRE(static_cast<Composite *>(c.data.get())->size() == 1);

    auto c2 = ast::CompositeParser("(  :hello\t \n :lol )").get();
    REQUIRE(c2);
    REQUIRE(static_cast<Composite *>(c2.data.get())->size() == 2);

    auto c3 = ast::CompositeParser("((:hello) :lol)").get();
    REQUIRE(c3);
    REQUIRE(static_cast<Composite *>(c3.data.get())->size() == 2);

    auto c4 = ast::CompositeParser("((()))").get();
    REQUIRE(c4);
    REQUIRE(static_cast<Composite *>(c4.data.get())->size() == 1);
  }

  SECTION("leading whitespace") {
    auto c = ast::CompositeParser(" \n\t\t ()").get();
    REQUIRE(c);
    REQUIRE(static_cast<Composite *>(c.data.get())->size() == 0);
  }

  SECTION("quotes, nesting") {
    auto c = ast::CompositeParser("(:\":::\" (((:\"efwji\")\t\t\t)))").get();
    REQUIRE(c);
  }
}

TEST_CASE("composites survive printing") {
  auto c = ast::Composite{};
  c.add_member(ast::Symbol("ew"));
  c.add_member(ast::Symbol("few[ :"));
  c.add_member(ast::Symbol(": \tfoke"));
  auto c2 = ast::Composite{};
  c.add_member(c2);
  auto c3 = ast::Composite{};
  c3.add_member(ast::Symbol("fejwo"));
  c.add_member(c3);

  auto str = c.str();
  auto p = ast::CompositeParser(str).get();
  
  REQUIRE(p);
  REQUIRE(c == *static_cast<Composite *>(p.data.get()));
}
