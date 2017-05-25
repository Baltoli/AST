#ifndef L1_INTERPRET_H
#define L1_INTERPRET_H

#include "language.h"

#include <ast/transform.h>

#include <iostream>
#include <string>

class Interpreter {
public:
  Interpreter(const ast::Expression& ex)
    : transform_(ex)
  {
    transform_.run_on(op_expr(), [](auto& ex) {
      auto comp = ex->composite();

      auto& l = (*comp)[0];
      auto& r = (*comp)[2];

      auto li = Interpreter(*l);
      auto lr = li.result().symbol();

      auto ri = Interpreter(*r);
      auto rr = ri.result().symbol();

      if(!lr || !rr) { return; }

      auto lv = std::stoi(lr->id);
      auto rv = std::stoi(rr->id);
      std::cout << lv << "+" << rv << "= " << (lv + rv) << '\n';
    });
  }

  const ast::Expression& result() const { return transform_.result(); }
private:
  ast::Transformer transform_;
};

#endif
