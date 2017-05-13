#include <ast/parser.h>

#include "catch.h"

TEST_CASE("symbols can be parsed") {
  SECTION("unquoted symbols") {
    auto sym = ast::SymbolParser(":hello").get();

    REQUIRE(sym != nullptr);
    REQUIRE(sym->id == "hello");
  }

  SECTION("invalid unquoted symbols") {
    auto sym = ast::SymbolParser("::jweif").get();
    REQUIRE(sym == nullptr);

    auto sym2 = ast::SymbolParser("").get();
    REQUIRE(sym2 == nullptr);

    auto sym3 = ast::SymbolParser(":").get();
    REQUIRE(sym3 == nullptr);
  }
}
