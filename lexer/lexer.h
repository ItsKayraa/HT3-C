#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

typedef enum {
    T_COMA,
    T_SEMI,
    T_LPRM,
    T_RPRM,
    T_LBRC,
    T_RBRC,
    T_LBRK,
    T_RBRK,
    T_DOT,
    T_MUL,
    T_PLUS,
    T_MINUS,
    T_DIV,
    T_IDENT,
    T_STRING,
    T_CHAR,
    T_FLOAT,
    T_INT,
    T_KEYWORD,
    T_EOF
} TokenType;

const char* TokenType_names[] = {
    "T_COMA",
    "T_SEMI",
    "T_LPRM",
    "T_RPRM",
    "T_LBRC",
    "T_RBRC",
    "T_LBRK",
    "T_RBRK",
    "T_DOT",
    "T_MUL",
    "T_PLUS",
    "T_MINUS",
    "T_DIV",
    "T_IDENT",
    "T_STRING",
    "T_CHAR",
    "T_FLOAT",
    "T_INT",
    "T_KEYWORD",
    "T_EOF"
};


typedef struct {
    TokenType type;
    char text[256];
} Token;

bool in(const char **keywords, int len, char *target);

bool iswhitespace(char ch);
bool isfloat(const char text[]);

int lex(Token* result, char *content);

const char* keywords[] = {"func", "eret", "ret", "char"};
const char* types[] = {"int", "str"};

#endif