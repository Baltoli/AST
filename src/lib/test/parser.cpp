#include <ast/parser.h>

#include "catch.h"

TEST_CASE("symbols can be parsed") {
  SECTION("unquoted symbols") {
    auto sym = ast::SymbolParser(":hello").get();
    REQUIRE(sym != nullptr);
    REQUIRE(sym->id == "hello");

    auto sym2 = ast::SymbolParser(":v").get();
    REQUIRE(sym2 != nullptr);
    REQUIRE(sym2->id == "v");
  }

  SECTION("invalid unquoted symbols") {
    auto sym = ast::SymbolParser("::jweif").get();
    REQUIRE(sym == nullptr);

    auto sym2 = ast::SymbolParser("").get();
    REQUIRE(sym2 == nullptr);

    auto sym3 = ast::SymbolParser(":").get();
    REQUIRE(sym3 == nullptr);

    auto sym4 = ast::SymbolParser(":fewioj wefioh").get();
    REQUIRE(sym4 == nullptr);

    auto sym5 = ast::SymbolParser(":wef:").get();
    REQUIRE(sym5 == nullptr);
  }

  SECTION("quoted symbols") {
    auto sym = ast::SymbolParser(":\"hello\"").get();
    REQUIRE(sym != nullptr);
    REQUIRE(sym->id == "hello");

    auto sym2 = ast::SymbolParser(":\"hi world\"").get();
    REQUIRE(sym2 != nullptr);
    REQUIRE(sym2->id == "hi world");

    auto sym3 = ast::SymbolParser(":\":\"").get();
    REQUIRE(sym3 != nullptr);
    REQUIRE(sym3->id == ":");

    auto sym4 = ast::SymbolParser(":\"\"").get();
    REQUIRE(sym4 != nullptr);
    REQUIRE(sym4->id == "");

    auto sym5 = ast::SymbolParser(":\"\n\"").get();
    REQUIRE(sym5 != nullptr);
    REQUIRE(sym5->id == "\n");
  }

  SECTION("invalid quoted symbols") {
    auto sym = ast::SymbolParser(":\"").get();
    REQUIRE(sym == nullptr);

    auto sym2 = ast::SymbolParser(": \"ewfieiof\"").get();
    REQUIRE(sym2 == nullptr);
  }
}
