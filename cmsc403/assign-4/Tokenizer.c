/*
Name: Javeria Hanif
Date: Mar 1, 2024 
Course: CMSC 403 Spring 2024
Description: The Tokenizer.c file reads characters from a given file and tokenizes the characters 
based on a set of rules. The rules help the tokenizer to identify tokens and associate them with lexemes. 
*/

#include "Tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// aLex is an array of type struct lexics
// numLex is number of tokens/lexemes we found
// inf is file pointer to read characters from 

// tokenizer function tokenizes characters from a given file and stores 
// resulting lexemes and tokens in an array 
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf) {
    char chara; // current character being read
    char lexeme[LEXEME_MAX] = ""; // stores the current lexeme
    enum token tokenExist; // stores the current token
    int lengthLexeme = 0; // length of current lexeme
    int readNext = 1; // flag for reading the next character
    _Bool token_found = FALSE; // flag if token has been found

    // iterates through characters in the file
    do {
        if (readNext) {
            chara = fgetc(inf); // reads first character 
        }
        // if character is not EOF then appends current character to the lexeme
        if (chara != EOF) {
            lengthLexeme++;
            strncat(lexeme, &chara, 1);

            // gets tokens associated with the current lexeme
            enum token match = get_token(lexeme);
            
            // if a valid token is found then, get the actual token for current lexeme
            if (match != -1) {
                tokenExist = get_token(lexeme);
                readNext = 1;
                token_found = TRUE;
            }
            else {
                // checks for whitespaces
                if (strcmp(lexeme, " ") != 0 && strcmp(lexeme, "\n") && strcmp(lexeme, "\t")) {
                    // reads next character if no token is found
                    if (!token_found) {
                        readNext = 1;
                        continue;
                    }
                    // resets the token_found
                    token_found = FALSE;
                    // copies current lexeme to the lexics array excluding last character
                    strncpy(aLex[*numLex].lexeme, lexeme, lengthLexeme-1);
                    aLex[*numLex].token = tokenExist; // assigns the corresponding token
                    *numLex += 1; // increments numLex that are found
                    // if current character is not a whitespace then dont read
                    if (chara != ' ' && chara != '\n' && chara != '\t') {
                        readNext = 0; 
                    }
                }
                lexeme[0] = '\0'; // resets the lexeme
                lengthLexeme = 0; // resets the length of lexeme
            }
        }
        else {
            // copies entire lexeme to the lexics array 
            strncpy(aLex[*numLex].lexeme, lexeme, lengthLexeme);
            // assigns the corresponding token
            aLex[*numLex].token = tokenExist;
            *numLex += 1; // increments numLex that are found
        }
    } while (chara != EOF);

    return 1;
}

// checks if the string matches 
// specific tokens and returns the corresponding enum
enum token get_token(char *str) {
    if (strcmp(str, "(") == 0) {
        return LEFT_PARENTHESIS;
    }
    if (strcmp(str, ")") == 0) {
        return RIGHT_PARENTHESIS;
    }
    if (strcmp(str, "{") == 0) {
        return LEFT_BRACKET;
    }
    if (strcmp(str, "}") == 0) {
        return RIGHT_BRACKET;
    }
    if (strcmp(str, "while") == 0) {
        return WHILE_KEYWORD;
    }
    if (strcmp(str, "return") == 0) {
        return RETURN_KEYWORD;
    }
    if (strcmp(str, "=") == 0) {
        return EQUAL;
    }
    if (strcmp(str, ",") == 0) {
        return COMMA;
    }
    if (strcmp(str, ";") == 0) {
        return EOL;
    }
    if (strcmp(str, "int") == 0 || strcmp(str, "void") == 0) {
        return VARTYPE;
    }
    // checks for valid identifier and returns IDENTIFIER token 
    if (validIdentifier(str)) {
        return IDENTIFIER;
    }
    // checks for specific operators and returns BINOP token
    if (strcmp(str, "=") == 0 || strcmp(str, "+") == 0 || strcmp(str, "*") == 0 ||
        strcmp(str, "!=") == 0 || strcmp(str, "==") == 0 || strcmp(str, "%") == 0) {
        return BINOP;
    }
    // checks for valid nunber and returns NUMBER token 
    if (validNumber(str)) {
        return NUMBER;
    }
    // invalid
    return -1;  
}

