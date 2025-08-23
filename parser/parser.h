#ifndef PARSER_H
#define PARSER_H

#include "../utilities/utils.h"
#include "../lexer/lexer.h"

const char* registers[] = {
    "rdi",
    "rsi",
    "rdx",
    "rcx",
    "r8",
    "r9"
};

typedef struct {
    char* content;
    char* typ;
    char params[256][2];
    /*
    params = [
        [typ, nm]   
    ]
    */
} Function;

typedef struct {
    char* sbefore;
    char* sectdata;
    char* secttext;
    char* sectafter;
    Function* funcs;
} ASM;

int parser(ASM assembly, Token* tokens);

#endif
