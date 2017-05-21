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
  return left_->match(e) || right_->match(e);
}

bool AnyOf::match(const Expression &e) const
{
  return std::any_of(std::begin(exprs_), std::end(exprs_), [&](auto& ex) {
    return ex->match(e);
  });
}

AnyOf* AnyOf::clone() const
{
  auto ret = new AnyOf();

  for(auto&& expr : exprs_) {
    ret->exprs_.emplace_back(expr->clone());
  }

  return ret;
}

bool Both::match(const Expression &e) const
{
  return left_->match(e) && right_->match(e);
}

bool HasChild::match(const Expression &e) const
{
  if(auto comp = dynamic_cast<const Composite *>(&e)) {
    return std::any_of(std::cbegin(*comp), std::cend(*comp), [&](auto&& ch) {
      return expr_->match(*ch);
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

bool Child::match(const Expression &e) const
{
  if(auto comp = dynamic_cast<const Composite *>(&e)) {
    if(comp->size() <= num_) {
      return false;
    }

    return expr_->match(*((*comp)[num_]));
  }

  return false;
}

bool Matcher::match(const Expression &e) const
{
  return expr_->match(e);
}

std::vector<MatchResult> search(const Expression& e, const MatchExpression& expr)
{
  std::vector<MatchResult> results;

  if(expr.match(e)) {
    results.emplace_back(e);
  }

  if(auto comp = dynamic_cast<const Composite *>(&e)) {
    for(auto&& child : *comp) {
      auto subs = search(*child, expr);
      std::copy(std::begin(subs), std::end(subs), std::back_inserter(results));
    }
  }

  return results;
}

}
