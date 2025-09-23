#ifndef LEXER_H
#define LEXER_H

/// ================================ [ DECLARATIONS ] ================================ ///

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// ================================= [ TOKENNAMES ] ================================= ///

#define TOKEN_IDENT   0
#define TOKEN_KEYWORD 1
#define TOKEN_NUMBER  2
#define TOKEN_OP      3
#define TOKEN_SYMBOL  4
#define TOKEN_EOF     5
#define TOKEN_DOT     6
#define TOKEN_SEMICOL 7
#define TOKEN_COMMA   8
#define TOKEN_COL     9
#define TOKEN_DOUBLE  50

/// =================================== [ STRUCT ] =================================== ///

typedef struct {
    int type;
    char* value;
} Token;

/// ================================== [ TEMPLATE ] ================================== ///

bool iswhitespace(char c);
bool isdym(char c);
bool isym(char c);
bool iskeyw(char* s);

Token* lexer(char* code);

/// ==================================== [ NOTE ] ==================================== ///
#if 0



#endif
/// ================================================================================== ///

#endif
