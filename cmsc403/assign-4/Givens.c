// Givens.c includes constants for TRUE and FALSE, an enum
// containing all token values in the given lexical structure, a constant for the max size of a lexeme, and the
// definition for a struct named lexics, which consists of an enum token property named token and a character
// array property named lexeme. The lexics struct is used to store both a token and its corresponding lexeme.
// Givens.c also provides two functions which return a boolean value indicating if the given String matches a
// specified regular expression.

#include "Givens.h"

_Bool validNumber(char* aLexeme){
	regex_t numberRegex;
	regcomp(&numberRegex, "^[0-9][0-9]*$", REG_EXTENDED);
	return !regexec(&numberRegex, aLexeme, 0, 0, 0);	
}

_Bool validIdentifier(char * aLexeme){
	regex_t identifierRegex;
	regcomp(&identifierRegex, "^[a-zA-Z][a-zA-Z0-9]*$", REG_EXTENDED);
	return !regexec(&identifierRegex, aLexeme, 0, 0, 0);
}