#ifndef AST_MATCH_H
#define AST_MATCH_H

#include <ast/ast.h>

namespace ast {

class MatchExpression {
public:
  virtual bool match(const Expression &e) const = 0;
};

class Any : public MatchExpression {
public:
  Any() {}

  virtual bool match(const Expression &e) const override;
};

class Exact : public MatchExpression {
public:
  Exact(const Symbol& sym) :
    symbol_(sym) {}

  virtual bool match(const Expression &e) const override;
private:
  const Symbol& symbol_;
};

class Either : public MatchExpression {
public:
  Either(const MatchExpression &l, const MatchExpression &r) :
    left_(l), right_(r) {}

  virtual bool match(const Expression &e) const override;
private:
  const MatchExpression &left_;
  const MatchExpression &right_;
};

class Both : public MatchExpression {
public:
  Both(const MatchExpression &l, const MatchExpression &r) :
    left_(l), right_(r) {}

  virtual bool match(const Expression &e) const override;
private:
  const MatchExpression &left_;
  const MatchExpression &right_;
};

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
