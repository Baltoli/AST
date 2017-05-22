#ifndef L1_LANGUAGE_H
#define L1_LANGUAGE_H

#include <ast/match.h>
#include <ast/visitor.h>

bool is_integer(std::string s);

ast::Matcher boolean();
ast::Matcher integer();
ast::Matcher location();
ast::Matcher operation();
ast::Matcher expression();

#endif
