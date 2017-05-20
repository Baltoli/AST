#ifndef AST_MATCH_H
#define AST_MATCH_H

#include <ast/ast.h>

namespace ast {

/**
 * Abstract base class from which all other match types inherit.
 */
class MatchExpression {
public:
  virtual bool match(const Expression &e) const = 0;
};

/**
 * Matches any expression.
 */
class Any : public MatchExpression {
public:
  Any() {}

  virtual bool match(const Expression &e) const override;
};

/**
 * Matches any symbol.
 */
class IsSymbol : public MatchExpression {
public:
  IsSymbol() {}

  virtual bool match(const Expression &e) const override;
};

/**
 * Matches any composite.
 */
class IsComposite : public MatchExpression {
public:
  IsComposite() {}

  virtual bool match(const Expression &e) const override;
};

/**
 * Matches a single expression by equality.
 */
class Exact : public MatchExpression {
public:
  Exact(const Symbol& sym) :
    symbol_(sym) {}

  virtual bool match(const Expression &e) const override;
private:
  const Symbol& symbol_;
};

/**
 * Matches either of two subexpressions.
 */
class Either : public MatchExpression {
public:
  Either(const MatchExpression &l, const MatchExpression &r) :
    left_(l), right_(r) {}

  virtual bool match(const Expression &e) const override;
private:
  const MatchExpression &left_;
  const MatchExpression &right_;
};

/**
 * Matches both of two subexpressions.
 */
class Both : public MatchExpression {
public:
  Both(const MatchExpression &l, const MatchExpression &r) :
    left_(l), right_(r) {}

  virtual bool match(const Expression &e) const override;
private:
  const MatchExpression &left_;
  const MatchExpression &right_;
};

/**
 * Matches a composite with a child that matches the subexpression.
 */
class HasChild : public MatchExpression {
public:
  HasChild(const MatchExpression &e) :
    expr_(e) {}

  virtual bool match(const Expression &e) const override;

private:
  const MatchExpression &expr_;
};

}

#endif
