#ifndef L1_LANGUAGE_H
#define L1_LANGUAGE_H

#include <ast/match.h>

bool is_integer(std::string s);

ast::Either statement();
ast::Both store_statement();
ast::Both location();

#endif
