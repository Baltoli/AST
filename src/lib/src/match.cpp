#include <ast/match.h>

namespace ast {

bool Any::match(const Expression &e) const
{
  return true;
}

bool IsSymbol::match(const Expression &e) const
{
  return dynamic_cast<const Symbol *>(&e);
}

bool IsComposite::match(const Expression &e) const
{
  return dynamic_cast<const Composite *>(&e);
}

bool Exact::match(const Expression &e) const
{
  if(auto sym = dynamic_cast<const Symbol *>(&e)) {
    return *sym == symbol_;
  }

  return false;
}

bool Either::match(const Expression &e) const
{
  return left_.match(e) || right_.match(e);
}

bool Both::match(const Expression &e) const
{
  return left_.match(e) && right_.match(e);
}

bool HasChild::match(const Expression &e) const
{
  if(auto comp = dynamic_cast<const Composite *>(&e)) {
    return std::any_of(std::cbegin(*comp), std::cend(*comp), [&](auto&& ch) {
      return expr_.match(*ch);
    });
  }

  return false;
}

bool NumChildren::match(const Expression &e) const
{
  if(auto comp = dynamic_cast<const Composite *>(&e)) {
    return comp->size() == num_;
  }

  return false;
}

}
