#include "interpret.h"
#include "language.h"
#include "typecheck.h"

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

  if(expression().match(*result.data)) {
    Interpreter i(*result.data);
    auto& r = i.result();

    std::cout << r.str() << '\n';
  } else {
    std::cerr << "Not a statement\n";
  }

  return 0;
}
