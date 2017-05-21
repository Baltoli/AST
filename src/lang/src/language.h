#ifndef L1_LANGUAGE_H
#define L1_LANGUAGE_H

#include <ast/match.h>
#include <ast/visitor.h>

bool is_integer(std::string s);

ast::Matcher program();
ast::Matcher statement();
ast::Matcher store_statement();
ast::Matcher location();
ast::Matcher value();
ast::Matcher literal();
ast::Matcher deref();

ast::Visitor visitor();

#endif
