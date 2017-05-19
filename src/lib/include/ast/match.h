#ifndef AST_MATCH_H
#define AST_MATCH_H

#include <ast/ast.h>

namespace ast {

class MatchExpression {
public:
  virtual bool match() const = 0;
};

class Exact : public MatchExpression {
public:
  Exact(const Symbol& sym) :
    sym_(sym) {}

  virtual bool match() const override;
private:
  const Symbol& sym_;
};

}

#endif
