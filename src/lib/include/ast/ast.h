#ifndef AST_AST_H
#define AST_AST_H

#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace ast {

class Expression {
public:
  virtual std::string str() const = 0;

  virtual Expression *clone() const = 0;

  virtual ~Expression() {}
};

class Symbol : public Expression {
public:
  Symbol(std::string id);

  const std::string id;

  std::string str() const override;

  Symbol *clone() const override;
};

class Composite : public Expression {
public:
  template<class Iterator>
  Composite(Iterator begin, Iterator end);

  Composite() {};

  Composite(const Composite& other) {
    for(auto&& e : other) {
      members_.push_back(std::unique_ptr<Expression>(e->clone()));
    }
  }

  Composite& operator=(Composite other) {
    std::swap(members_, other.members_);
    return *this;
  }

  template<class Expr>
  void add_member(Expr&& e);

  void add_member(std::unique_ptr<Expression> e);

  std::string str() const override;

  Composite *clone() const override;

  const std::unique_ptr<Expression>& operator [](std::size_t idx) const;
private:
  std::vector<std::unique_ptr<Expression>> members_;

public:
  using const_iterator = decltype(members_)::const_iterator;

  const_iterator begin() const noexcept { return std::begin(members_); }
  const_iterator end() const noexcept { return std::end(members_); }

  auto size() const { return end() - begin(); }
};

bool operator== (const Symbol& rhs, const Symbol& lhs);
bool operator!= (const Symbol& rhs, const Symbol& lhs);
bool operator< (const Symbol& rhs, const Symbol& lhs);

bool operator== (const Composite& rhs, const Composite& lhs);
bool operator!= (const Composite& rhs, const Composite& lhs);

template<class Iterator>
Composite::Composite(Iterator begin, Iterator end)
{
  for(auto it = begin; it != end; ++it) {
    members_.push_back(std::move(*it));
  }
}

template<class Expr>
void Composite::add_member(Expr&& e)
{
  members_.emplace_back(new typename std::remove_reference<Expr>::type (std::move(e)));
}

}

#endif
