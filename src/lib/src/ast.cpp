#include <ast/ast.h>

namespace ast {

Symbol::Symbol(std::string id) :
  id(id)
{
}

Symbol *Symbol::clone() const
{
  return new Symbol(id);
}

Composite *Composite::clone() const
{
  auto c = new Composite;
  for(auto&& e : *this) {
    c->members_.push_back(std::move(std::unique_ptr<Expression>(e->clone())));
  }
  return c;
}

void Composite::add_member(std::unique_ptr<Expression> e)
{
  members_.push_back(std::move(e));
}

void Composite::add_member(const Expression& e)
{
  members_.emplace_back(e.clone());
}

const std::unique_ptr<Expression>& Composite::operator[](std::size_t idx) const
{
  return members_.at(idx);
}

bool operator==(const Symbol& rhs, const Symbol& lhs)
{
  return rhs.id == lhs.id;
}

bool operator!= (const Symbol& rhs, const Symbol& lhs)
{
  return !(rhs == lhs);
}

bool operator< (const Symbol& rhs, const Symbol& lhs)
{
  return rhs.id < lhs.id;
}

bool operator== (const Composite& rhs, const Composite& lhs)
{
  if(rhs.size() != lhs.size()) {
    return false;
  }

  auto all_match = true;

  for(auto i = 0; i < rhs.size(); ++i) {
    if(!all_match) {
      return false;
    }

    if(auto r = dynamic_cast<Symbol *>(rhs[i].get())) {
      if(auto l = dynamic_cast<Symbol *>(lhs[i].get())) {
        all_match = all_match && (*r == *l);
      } else {
        all_match = false;
      }
    }

    if(auto r = dynamic_cast<Composite *>(rhs[i].get())) {
      if(auto l = dynamic_cast<Composite *>(lhs[i].get())) {
        all_match = all_match && (*r == *l);
      } else {
        all_match = false;
      }
    }
  }

  return all_match;
}

bool operator!= (const Composite& rhs, const Composite& lhs)
{
  return !(rhs == lhs);
}

}
