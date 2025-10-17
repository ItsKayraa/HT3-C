#ifndef LEXER_H
#define LEXER_H

/// ================================ [ DECLARATIONS ] ================================ ///

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// ================================= [ TOKENNAMES ] ================================= ///

/// === token main =======================

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

/// === token name dbg ===================

    #ifdef TOKENNAME_DEBUG

/// token names

/// !! KEEP THESE IN SYNC WITH TK MAIN !! ///

#define ___INS(macro) \
    [macro] = #macro
const char *const tokenname[TOKEN_DOUBLE+1] = { 
	___INS(TOKEN_IDENT),
	___INS(TOKEN_KEYWORD),
	___INS(TOKEN_NUMBER),
	___INS(TOKEN_OP),
	___INS(TOKEN_SYMBOL),
	___INS(TOKEN_EOF),
	___INS(TOKEN_DOT),
	___INS(TOKEN_SEMICOL),
	___INS(TOKEN_COMMA),
	___INS(TOKEN_COL),
	___INS(TOKEN_DOUBLE),
};

/// varying macros

#define INIT_TOKENNAME() \
    for(uint8_t i=0; i<TOKEN_DOUBLE+1; i++) { \
        if(!tokenname[i]) { tokenname[i]="TOKEN_INVALID"; } \
    }

#define TOKENNAMEFMT "%s"
#define TOKENNAME(tk) tokenname[tk]

    #else

#define INIT_TOKENNAME()

#define TOKENNAMEFMT "%hhu"
#define TOKENNAME(tk) tk

    #endif

/// =====================================

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

	!!! REMEMBER TO KEEP THE TOKENS SYNCHRONISED !!!

imma make this commit purely for main and then we can decide what to do with the lexer
	and parser

#endif
/// ================================================================================== ///

#endif
