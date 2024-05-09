#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Givens.h"
enum token get_token(char *str);

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);


#endif