#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include <ast/ast.h>
#include <ast/match.h>

#include <map>

namespace ast {

class Visitor {
public:
  void visit(const Expression&) const;

protected:
  void on(Matcher, std::function<void (const Expression&)>);

private:
  std::map<Matcher, std::function<void (const Expression&)>> functions_;
};

};

#endif
