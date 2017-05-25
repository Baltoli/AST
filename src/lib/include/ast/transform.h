#ifndef AST_TRANSFORM_H
#define AST_TRANSFORM_H

#include <ast/match.h>

namespace ast {

class Transformer {
public:
  Transformer(const Expression& e) :
    expr_(e.clone()) {}

  void run_on(Matcher m, 
              std::function<void (std::unique_ptr<Expression>&)>);

  const Expression& result() const { return *expr_; }

private:
  void transform(std::unique_ptr<Expression>& e, 
                 Matcher m, 
                 std::function<void (std::unique_ptr<Expression>&)>);

  std::unique_ptr<Expression> expr_;
};

}

#endif
