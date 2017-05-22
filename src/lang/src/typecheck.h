#ifndef L1_TYPECHECK_H
#define L1_TYPECHECK_H

#include <ast/visitor.h>

#include "language.h"

class TypeChecker : public ast::Visitor {
public:
  enum Type {
    Error, Bool, Int, Void
  };

  TypeChecker()
  {
    recursive_ = false;
    on(integer(), on_int);
    on(boolean(), on_bool);
    on(op_expr(), on_op);
    on(if_expr(), on_if);
    on(assign_expr(), on_assign);
    on(deref_expr(), on_deref);
    on(skip_expr(), on_skip);
  }

  TypeChecker(const ast::Expression& e) :
    TypeChecker()
  {
    visit(e);
  }

  Type result() const { return type_; }

private:
  using callback = std::function<void (const ast::Expression&)>;

  Type type_ = Error;

  callback on_int = [&](auto&&) {
    type_ = Int;
  };

  callback on_bool = [&](auto&&) {
    type_ = Bool;
  };

  callback on_op = [&](auto&& ex) {
    auto comp = dynamic_cast<const ast::Composite *>(&ex);
    if(!comp) { return; }

    auto& l = (*comp)[0];
    auto& r = (*comp)[2];

    auto& op = (*comp)[1];
    if(auto sop = dynamic_cast<const ast::Symbol *>(op.get())) {
      auto lt = TypeChecker(*l).result();
      auto rt = TypeChecker(*r).result();

      if(lt == Int && rt == Int) {
        if(sop->id == "+") {
          type_ = Int;
        } else if(sop->id == ">=") {
          type_ = Bool;
        }
      }
    }
  };

  callback on_if = [&](auto&& ex) {
    auto comp = dynamic_cast<const ast::Composite *>(&ex);
    if(!comp) { return; }

    auto& c = (*comp)[1];
    auto& r = (*comp)[2];
    auto& l = (*comp)[3];

    auto ct = TypeChecker(*c).result();
    auto rt = TypeChecker(*r).result();
    auto lt = TypeChecker(*l).result();

    if(ct != Bool) { return; }
    if(lt != rt) { return; }

    type_ = lt;
  };

  callback on_assign = [&](auto&& ex) {
    type_ = Void;
  };

  callback on_deref = [&](auto&& ex) {
    type_ = Int;
  };

  callback on_skip = [&](auto&& ex) {
    type_ = Void;
  };
};

#endif
