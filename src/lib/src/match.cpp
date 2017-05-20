#include <ast/match.h>

namespace ast {

bool Any::match(Expression *e) const
{
  return true;
}

bool Exact::match(Expression *e) const
{
  if(auto sym = dynamic_cast<Symbol *>(e)) {
    return *sym == symbol_;
  }

  return false;
}

bool Either::match(Expression *e) const
{
  return left_->match(e) || right_->match(e);
}

bool HasChild::match(Expression *e) const
{
  if(auto comp = dynamic_cast<Composite *>(e)) {
    return std::any_of(std::cbegin(*comp), std::cend(*comp), [&](auto&& ch) {
      return expr_->match(ch.get());
    });
  }

  return false;
}

}
