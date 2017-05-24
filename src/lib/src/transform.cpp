#include <ast/transform.h>

namespace ast {

void Transformer::transform(Expression& e, Matcher m, std::function<void (Expression&)> f)
{
  if(m.match(e)) {
    f(e);
  }

  if(auto comp = e.composite()) {
    for(auto&& child : *comp) {
      transform(*child, m, f);
    }
  }
}

void Transformer::run_on(Matcher m, std::function<void (Expression&)> f)
{
  transform(*expr_, m, f);
}

}
