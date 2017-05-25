#include <ast/transform.h>

namespace ast {

void Transformer::transform(std::unique_ptr<Expression>& e, 
                            Matcher m, 
                            std::function<void (std::unique_ptr<Expression>&)> f)
{
  if(m.match(*e)) {
    f(e);
  }

  if(auto comp = e->composite()) {
    for(auto& child : *comp) {
      transform(child, m, f);
    }
  }
}

void Transformer::run_on(Matcher m, 
                         std::function<void (std::unique_ptr<Expression>&)> f)
{
  transform(expr_, m, f);
}

}
