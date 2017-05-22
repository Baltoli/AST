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

ast::Matcher op_expr();
ast::Matcher if_expr();
ast::Matcher assign_expr();
ast::Matcher deref_expr();
ast::Matcher skip_expr();
ast::Matcher seq_expr();
ast::Matcher while_expr();

#endif
