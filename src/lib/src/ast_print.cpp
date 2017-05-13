#include <ast/ast.h>

#include <regex>
#include <sstream>

namespace {

std::vector<std::string> split(const std::string& input, const std::string& regex)
{
  std::regex re(regex);
  std::sregex_token_iterator
    first{input.begin(), input.end(), re, -1},
    last;
  return {first, last};
}

}

namespace ast {

std::string Symbol::str() const
{
  return ":" + id;
}

std::string Composite::str() const
{
  std::stringstream ss;
  ss << "(\n";
  for(auto&& m : *this) {
    auto lines = split(m->str(), "\n");
    for(auto&& line : lines) {
      ss << "  " << line << '\n';
    }
  }
  ss << ')';
  return ss.str();
}

}
