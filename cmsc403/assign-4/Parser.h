#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"

_Bool parser(struct lexics *someLexics, int numberOfLexics);

// helper functions 
_Bool function(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool header(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool arg_decl(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool body(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool statement_list(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool statement(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool while_loop(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool return_key(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool assignment(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool expression(struct lexics *someLexics, int *index, int numberOfLexics);
_Bool term(struct lexics *someLexics, int *index, int numberOfLexics);

#endif