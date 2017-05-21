#include <ast/visitor.h>

namespace ast {

void Visitor::on(Matcher m, std::function<void (const Expression&)> f)
{
  functions_[m] = f;
}

void Visitor::visit(const Expression& expr) const
{
  for(auto&& pair : functions_) {
    if(pair.first.match(expr)) {
      pair.second(expr);
    }
  }

  if(auto comp = dynamic_cast<const Composite*>(&expr)) {
    for(auto&& child : *comp) {
      visit(*child);
    }
  }
}

}
