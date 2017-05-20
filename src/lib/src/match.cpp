#include <ast/match.h>

namespace ast {

bool Exact::match(Expression *e) const
{
  if(auto sym = dynamic_cast<Symbol *>(e)) {
    return *sym == symbol_;
  }

  return false;
}

}
