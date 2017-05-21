#ifndef AST_MATCH_H
#define AST_MATCH_H

#include <ast/ast.h>

#include <vector>

namespace ast {

/**
 * Abstract base class from which all other match types inherit.
 */
class MatchExpression {
public:
  virtual bool match(const Expression &e) const = 0;

  virtual MatchExpression* clone() const = 0;
};

/**
 * Matches any expression.
 */
class Any : public MatchExpression {
public:
  Any() {}

  virtual bool match(const Expression &e) const override;
  virtual Any* clone() const override { return new Any(); }
};

/**
 * Matches any symbol.
 */
class IsSymbol : public MatchExpression {
public:
  IsSymbol() {}

  virtual bool match(const Expression &e) const override;
  virtual IsSymbol* clone() const override { return new IsSymbol(); }
};

/**
 * Matches any composite.
 */
class IsComposite : public MatchExpression {
public:
  IsComposite() {}

  virtual bool match(const Expression &e) const override;
  virtual IsComposite* clone() const override { return new IsComposite(); }
};

/**
 * Matches a single expression by equality.
 */
class Exact : public MatchExpression {
public:
  Exact(Symbol sym) :
    symbol_(sym) {}

  virtual bool match(const Expression &e) const override;
  virtual Exact* clone() const override { return new Exact(symbol_); }
private:
  Symbol symbol_;
};

/**
 * Matches either of two subexpressions.
 */
class Either : public MatchExpression {
public:
  Either(const MatchExpression &l, const MatchExpression &r) :
    left_(l.clone()), right_(r.clone()) {}

  virtual bool match(const Expression &e) const override;
  virtual Either* clone() const override { return new Either(*left_, *right_); }
private:
  std::unique_ptr<MatchExpression> left_;
  std::unique_ptr<MatchExpression> right_;
};

class AnyOf : public MatchExpression {
public:
  AnyOf() = default;

  template<class T, class... Ts>
  AnyOf(T&& t, Ts&&... rest);

  virtual bool match(const Expression &e) const override;
  virtual AnyOf* clone() const override;
private:
  std::vector<std::unique_ptr<MatchExpression>> exprs_;
};

template<class T, class... Ts>
AnyOf::AnyOf(T&& t, Ts&&... rest) :
  AnyOf(rest...)
{
  exprs_.emplace_back(std::move(t).clone());
}

class AllOf : public MatchExpression {
public:
  AllOf() = default;

  template<class T, class... Ts>
  AllOf(T&& t, Ts&&... rest);

  virtual bool match(const Expression &e) const override;
  virtual AllOf* clone() const override;
private:
  std::vector<std::unique_ptr<MatchExpression>> exprs_;
};

template<class T, class... Ts>
AllOf::AllOf(T&& t, Ts&&... rest) :
  AllOf(rest...)
{
  exprs_.emplace_back(std::move(t).clone());
}

/**
 * Matches both of two subexpressions.
 */
class Both : public MatchExpression {
public:
  Both(const MatchExpression &l, const MatchExpression &r) :
    left_(l.clone()), right_(r.clone()) {}

  virtual bool match(const Expression &e) const override;
  virtual Both* clone() const override { return new Both(*left_, *right_); }
private:
  std::unique_ptr<MatchExpression> left_;
  std::unique_ptr<MatchExpression> right_;
};

/**
 * Matches a composite with a child that matches the subexpression.
 */
class HasChild : public MatchExpression {
public:
  HasChild(const MatchExpression &e) :
    expr_(e.clone()) {}

  virtual bool match(const Expression &e) const override;
  virtual HasChild* clone() const override { return new HasChild(*expr_); }
private:
  std::unique_ptr<MatchExpression> expr_;
};

class NumChildren : public MatchExpression {
public:
  NumChildren(size_t n) :
    num_(n) {}

  virtual bool match(const Expression &e) const override;
  virtual NumChildren* clone() const override { return new NumChildren(num_); }
private:
  size_t num_;
};

class Child : public MatchExpression {
public:
  Child(size_t n, const MatchExpression &e) :
    num_(n), expr_(e.clone()) {}

  /* Child(const Child& other) : */
  /*   expr_(other.expr_->clone()) {} */

  virtual bool match(const Expression &e) const override;
  virtual Child* clone() const override { return new Child(num_, *expr_); }
private:
  size_t num_;
  std::unique_ptr<MatchExpression> expr_;
};

class Matcher : public MatchExpression {
public:
  Matcher(const MatchExpression& e) :
    expr_(e.clone()) {}

  virtual bool match(const Expression &e) const override;
  virtual Matcher* clone() const override { return new Matcher(*expr_); }
private:
  std::unique_ptr<MatchExpression> expr_;
};

struct MatchResult {
  MatchResult(const Expression& e) :
    expr(e) {}

  const Expression& expr;
};

std::vector<MatchResult> search(const Expression& e, const MatchExpression& expr);

}

#endif
