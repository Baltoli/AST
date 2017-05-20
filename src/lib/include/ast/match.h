#ifndef AST_MATCH_H
#define AST_MATCH_H

#include <ast/ast.h>

namespace ast {

class MatchExpression {
public:
  virtual bool match(Expression *e) const = 0;
};

class Exact : public MatchExpression {
public:
  Exact(const Symbol& sym) :
    symbol_(sym) {}

  virtual bool match(Expression *e) const override;
private:
  const Symbol& symbol_;
};

class Either : public MatchExpression {
public:
  Either(MatchExpression *l, MatchExpression *r) :
    left_(l), right_(r) {}

  virtual bool match(Expression *e) const override;
private:
  const MatchExpression *left_;
  const MatchExpression *right_;
};

}

#endif
