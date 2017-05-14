#include <ast/ast.h>
#include <ast/parser.h>

#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
  std::stringstream ss;

  for(std::string line; std::getline(std::cin, line); ) {
    ss << line << '\n';
  }

  auto result = ast::CompositeParser(ss.str()).get();

  if(result) {
    std::cout << result.data->str() << '\n';
  } else {
    std::cout << "Syntax error!\n";
    return 1;
  }

  return 0;
}
