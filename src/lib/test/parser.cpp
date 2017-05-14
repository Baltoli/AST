#include <ast/parser.h>

#include "catch.h"

TEST_CASE("symbols can be parsed") {
  SECTION("unquoted symbols") {
    auto sym = ast::SymbolParser(":hello").get();
    REQUIRE(sym);
    REQUIRE(sym.data->id == "hello");

    auto sym2 = ast::SymbolParser(":v").get();
    REQUIRE(sym2);
    REQUIRE(sym2.data->id == "v");
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
  }

  SECTION("quoted symbols") {
    auto sym = ast::SymbolParser(":\"hello\"").get();
    REQUIRE(sym);
    REQUIRE(sym.data->id == "hello");

    auto sym2 = ast::SymbolParser(":\"hi world\"").get();
    REQUIRE(sym2);
    REQUIRE(sym2.data->id == "hi world");

    auto sym3 = ast::SymbolParser(":\":\"").get();
    REQUIRE(sym3);
    REQUIRE(sym3.data->id == ":");

    auto sym4 = ast::SymbolParser(":\"\"").get();
    REQUIRE(sym4);
    REQUIRE(sym4.data->id == "");

    auto sym5 = ast::SymbolParser(":\"\n\"").get();
    REQUIRE(sym5);
    REQUIRE(sym5.data->id == "\n");
  }

  SECTION("invalid quoted symbols") {
    auto sym = ast::SymbolParser(":\"").get();
    REQUIRE(!sym);

    auto sym2 = ast::SymbolParser(": \"ewfieiof\"").get();
    REQUIRE(!sym2);
  }
}
