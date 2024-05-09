/*
Name: Javeria Hanif
Date: Mar 1, 2024 
Course: CMSC 403 Spring 2024
Description: The Parser.c implements a recursive descent parser based on EBNF grammar rules.
The rules define the structure of the language and parser checks if a given sequence of tokens (in 
Tokenizer.c) adhere to the EBNF grammar rules. 
*/

#include "Parser.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// parser function initiates parsing by calling function 

// takes an array of type lexics and an int representing the number of tokens in the given lexics array
_Bool parser(struct lexics *someLexics, int numberOfLexics) {
    int index = 0;  // starts parsing from the first token
    return function(someLexics, &index, numberOfLexics);
}

// EBNF grammar rule implementation for function 	    --> header body

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool function(struct lexics *someLexics, int *index, int numberOfLexics) {
    
    // if header is found then checks for body
    if (header(someLexics, index, numberOfLexics)) {
        // if body is found then returns true 
       if (body(someLexics, index, numberOfLexics)) {
            // if lexeme index is equal to total numberOfLexics then return true
            if (*index == numberOfLexics) {
                return TRUE;
            }
        }   
    }
    // otherwise returns false 
    return FALSE;
}

//  EBNF grammar rule implementation for header 		    --> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool header(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if token is VARTYPE then increments lexeme index
    if (someLexics[*index].token == VARTYPE) {
        *index = *index +1;
        // if token is IDENTIFIER then increments lexeme index 
        if (someLexics[*index].token == IDENTIFIER) {
                *index = *index +1;
            // if token is LEFT_PARENTHESIS then increments lexeme index 
            if (someLexics[*index].token == LEFT_PARENTHESIS) {
                *index = *index +1;
                // if token is RIGHT_PARETHESIS then increments lexeme index 
                if (someLexics[*index].token == RIGHT_PARENTHESIS) {
                    *index = *index +1;
                    return TRUE; // returns true if VARTYPE IDENTIFIER LEFT_PARENTHESIS RIGHT_PARENTHESIS are found
                }
                // if arg-decl exist and the next token is RIGHT_PARENTHESIS
                else if (arg_decl(someLexics, index, numberOfLexics)) {
                    if (someLexics[*index].token == RIGHT_PARENTHESIS) {
                        *index = *index +1; // increments the lexeme index
                        return TRUE; // returns true if it follows the structure
                    }
                }
            }
        }
    }
    // otherwise returns false
    return FALSE;
}

// EBNF grammar rule implementation for arg-decl --> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool arg_decl(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if token is VARTYPE then increments lexeme index
    if (someLexics[*index].token == VARTYPE) {
        *index = *index + 1;
        // if token is IDENTIFIER then increments lexeme index 
        if (someLexics[*index].token == IDENTIFIER) {
            *index = *index + 1;

            // checks for optional COMMA, VARTYPE, IDENTIFIER sequence then increments lexeme index
            while (*index < numberOfLexics && someLexics[*index].token == COMMA) {
                *index = *index + 1;  

                // if token is VARTYPE then increments lexeme index
                if (someLexics[*index].token == VARTYPE) {
                    *index = *index + 1;
                    // if token is IDENTIFIER then increments lexeme index 
                    if (someLexics[*index].token == IDENTIFIER) {
                        *index = *index + 1;
                    } else {
                        return FALSE; // returns false if it COMMA VARTYPE IDENTIFIER sequence is not found
                    }
                } else {
                    return FALSE;  // returns false if it COMMA VARTYPE IDENTIFIER sequence is not found
                }
            }
            return TRUE; // returns true if it follows the structure
        }
    }
    return FALSE;  // returns false if it COMMA VARTYPE IDENTIFIER sequence is not found
}


// EBNF grammar rule implementation for body 		    --> LEFT_BRACKET [statement-list] RIGHT_BRACKET

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool body(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if token is LEFT_BRACKET then increments lexeme index
    if (someLexics[*index].token == LEFT_BRACKET) {
        *index = *index +1;
        // if token is RIGHT_BRACKET then increments lexeme index
        if (someLexics[*index].token == RIGHT_BRACKET) {
            *index = *index +1;
            return TRUE; // returns true if LEFT_BRACKET RIGHT_BRACKET are found
        }
        // if statement_list exist and the next token is RIGHT_BRACKET
        else if (statement_list(someLexics, index, numberOfLexics)) {
            if (someLexics[*index].token == RIGHT_BRACKET) {
                *index = *index +1; // increments the lexeme index
                return TRUE; // returns true if it follows the structure
            }
        }
    } // otherwise returns false
    return FALSE;
}


// EBNF grammar rule implementation for statement-list 	--> statement {statement}

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool statement_list(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if there's no statemet then returns false
    if (!statement(someLexics, index, numberOfLexics)) {
        return FALSE;
    }

    // if there are more statements returns true
    while (*index < numberOfLexics) {

        // breaks the loop if there's no more statements found
        if (!statement(someLexics, index, numberOfLexics)) {
            break; 
        }
    }
    return TRUE;
}

// EBNF grammar rule implementation for statement 		--> while-loop | return | assignment | body

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool statement(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if while-loop exist then returns true
    if (while_loop(someLexics, index, numberOfLexics)) {
        return TRUE;
    }
    // if return-key exist then returns true
    else if (return_key(someLexics, index, numberOfLexics)) {
        return TRUE;
    }
    // if assignment exist then returns true
    else if (assignment(someLexics, index, numberOfLexics)) {
        return TRUE;
    }
    // if body exist then returns true
    else if (body(someLexics, index, numberOfLexics)) {
        return TRUE;
    }
    // otherwise returns false
    return FALSE;
}

// EBNF grammar rule implementation for while-loop 		--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool while_loop(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if token is WHILE_KEYWORD then increments lexeme index
    if (someLexics[*index].token == WHILE_KEYWORD) {
        *index = *index +1;
        // if token is LEFT_PARENTHESIS then increments lexeme index
        if (someLexics[*index].token == LEFT_PARENTHESIS) {
                *index = *index +1;
                // if expression exist then returns true
                if (expression(someLexics, index, numberOfLexics)) {
                    // if token is RIGHT_PARENTHESIS then increments lexeme index
                    if (someLexics[*index].token == RIGHT_PARENTHESIS) {
                        *index = *index +1;
                        // if statement exist then returns true
                        if (statement(someLexics, index, numberOfLexics)) {
                            return TRUE;
                        }         
                } 
            }
        }
    }
    // otherwise returns false
    return FALSE;
}

// EBNF grammar rule implementation for return 		    --> RETURN_KEYWORD expression EOL

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool return_key(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if token is RETURN_KEYWORD then increments lexeme index
    if (someLexics[*index].token == RETURN_KEYWORD) {
        *index = *index +1;
        // if expression exist then returns true
        if (expression(someLexics, index, numberOfLexics)) {
            // if token is EOL then increments lexeme index
            if (someLexics[*index].token == EOL) {
                *index = *index +1;
                return TRUE; 
            } 
        }  
    } // otherwise returns false
    return FALSE;
}

// EBNF grammar rule implementation for assignment 		--> IDENTIFIER EQUAL expression EOL

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool assignment(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if token is IDENTIFIER then increments lexeme index
    if (someLexics[*index].token == IDENTIFIER) {
        *index = *index +1;
        // if token is EQUAL then increments lexeme index
        if (someLexics[*index].token == EQUAL) {
            *index = *index +1;
            // if expression exist then returns true
            if (expression(someLexics, index, numberOfLexics)) {
                // if token is EOL then increments lexeme index
                if (someLexics[*index].token == EOL) {
                    *index = *index +1;
                    return TRUE;
                } 
            } 
        }
    } // otherwise returns false
    return FALSE;
}

// EBNF grammar rule implementation for expression 		--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool expression(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if term exist then returns true
    if (term(someLexics, index, numberOfLexics)) {
        // checks for optional BINOP token then increments lexeme index
        while (*index < numberOfLexics && someLexics[*index].token == BINOP) {
                *index = *index + 1;  
                // if there's no term then returns false
                if (!term(someLexics, index, numberOfLexics)) {
                    return FALSE;
                }
            }
        return TRUE; // returns true if it follows the structure
    }
    // if token is LEFT_PARENTHESIS then increments lexeme index
    else if (someLexics[*index].token == LEFT_PARENTHESIS) {
        *index = *index +1;
        // if expression exist then returns true
        if (expression(someLexics, index, numberOfLexics)) {
            // if token is RIGHT_PARENTHESIS then increments lexeme index
            if (someLexics[*index].token == RIGHT_PARENTHESIS) {
                *index = *index +1;
                return TRUE; 
            }
        }    
    }
    // otherwise returns false
    return FALSE; 
}

// EBNF grammar rule implementation for term 			--> IDENTIFIER | NUMBER

// takes an array of lexics, an index pointer, and the total number of lexics
_Bool term(struct lexics *someLexics, int *index, int numberOfLexics) {
    // if token is IDENTIFIER then increments lexeme index
    if (someLexics[*index].token == IDENTIFIER) {
        *index = *index +1;
        return TRUE;
    }
    // if token is NUMBER then increments lexeme index
    else if (someLexics[*index].token == NUMBER) {
        *index = *index +1;
        return TRUE;
    }
    // otherwise returns false
    return FALSE;
}