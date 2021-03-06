#include <ast/ast.h>

#include <iomanip>
#include <regex>
#include <sstream>

namespace {

std::vector<std::string> split(std::string input, std::string regex)
{
  std::regex re(regex);
  std::sregex_token_iterator
    first{input.begin(), input.end(), re, -1},
    last;
  return {first, last};
}

bool needs_quote(std::string sym)
{
  return std::any_of(std::begin(sym), std::end(sym), [](auto c) {
    return (c == ':') || std::iscntrl(c) || std::isspace(c);
  }) || sym.empty();
}

}

namespace ast {

std::string Symbol::str() const
{
  std::stringstream ss;
  ss << ":";

  if(needs_quote(id)) {
    ss << std::quoted(id);
  } else {
    ss << id;
  }
  
  return ss.str();
}

std::string Composite::str() const
{
  if(size() == 0) {
    return "()";
  }

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
