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

  if(program().match(*result.data)) {
    std::cout << result.data->str() << '\n';
    visitor().visit(*result.data);
  } else {
    std::cerr << "Not a statement\n";
  }

  return 0;
}
