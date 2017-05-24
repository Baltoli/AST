#ifndef AST_TRANSFORM_H
#define AST_TRANSFORM_H

#include <ast/match.h>

namespace ast {

class Transformer {
public:
  Transformer(const Expression& e) :
    expr_(e.clone()) {}

  void run_on(Matcher m, std::function<void (Expression&)>);

  const Expression& result() const { return *expr_; }
private:
  void transform(Expression& e, Matcher m, std::function<void (Expression&)>);
  std::unique_ptr<Expression> expr_;
};

}

#endif
