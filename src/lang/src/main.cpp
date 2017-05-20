#include "language.h"

#include <ast/parser.h>

#include <iostream>
#include <sstream>

int main()
{
  std::stringstream ss;

  for(std::string line; std::getline(std::cin, line); ) {
    ss << line << '\n';
  }

  auto result = ast::CompositeParser(ss.str()).get();
  if(!result) {
    std::cerr << "Syntax error!\n";
  }

  if(statement()->match(*result.data)) {
  }

  return 0;
}
