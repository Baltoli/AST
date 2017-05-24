#ifndef AST_AST_H
#define AST_AST_H

#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace ast {

class Symbol;
class Composite;

class Expression {
public:
  virtual std::string str() const = 0;

  virtual Expression *clone() const = 0;

  virtual Symbol* symbol() = 0;
  virtual const Symbol* symbol() const = 0;
  virtual Composite* composite() = 0;
  virtual const Composite* composite() const = 0;

  virtual ~Expression() {}
};

class Symbol : public Expression {
public:
  Symbol(std::string id);

  const std::string id;

  std::string str() const override;

  Symbol *clone() const override;

  virtual Symbol* symbol() override { return this; }
  virtual const Symbol* symbol() const override { return this; }
  virtual Composite* composite() override { return nullptr; }
  virtual const Composite* composite() const override { return nullptr; }
};

class Composite : public Expression {
public:
  Composite() {};

  template<class T, class... Ts>
  explicit Composite(T&& t, Ts&&... rest);

  Composite(const Composite& other) {
    for(auto&& e : other) {
      members_.emplace_back(e->clone());
    }
  }

  Composite& operator=(Composite other) {
    std::swap(members_, other.members_);
    return *this;
  }

  void add_member(const Expression& e);

  void add_member(std::unique_ptr<Expression> e);

  std::string str() const override;

  Composite *clone() const override;

  virtual Symbol* symbol() override { return nullptr; }
  virtual const Symbol* symbol() const override { return nullptr; }
  virtual Composite* composite() override { return this; }
  virtual const Composite* composite() const override { return this; }

  const std::unique_ptr<Expression>& operator [](std::size_t idx) const;
private:
  std::vector<std::unique_ptr<Expression>> members_;

public:
  using iterator = decltype(members_)::iterator;
  using const_iterator = decltype(members_)::const_iterator;

  iterator begin() noexcept { return std::begin(members_); }
  iterator end() noexcept { return std::end(members_); }

  const_iterator begin() const noexcept { return std::begin(members_); }
  const_iterator end() const noexcept { return std::end(members_); }

  auto size() const { return end() - begin(); }
};

bool operator== (const Symbol& rhs, const Symbol& lhs);
bool operator!= (const Symbol& rhs, const Symbol& lhs);
bool operator< (const Symbol& rhs, const Symbol& lhs);

bool operator== (const Composite& rhs, const Composite& lhs);
bool operator!= (const Composite& rhs, const Composite& lhs);

template<class T, class... Ts>
Composite::Composite(T&& t, Ts&&... rest) :
  Composite(rest...)
{
  members_.emplace(std::begin(members_), t.clone());
}

}

#endif
