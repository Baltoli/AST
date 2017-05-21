#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include <ast/ast.h>
#include <ast/match.h>

#include <map>

namespace ast {

class Visitor {
public:
  void on(Matcher, std::function<void (const Expression&)>);
  void visit(const Expression&) const;
private:
  std::map<Matcher, std::function<void (const Expression&)>> functions_;
};

};

#endif
