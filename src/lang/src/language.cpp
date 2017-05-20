#include "language.h"

using namespace ast;

std::unique_ptr<MatchExpression> statement()
{
  return std::make_unique<Either>(
    Child(0, Exact(Symbol("store"))),
    Child(0, Exact(Symbol("print")))
  );
}
