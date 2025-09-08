//!-Isrc -std=c23 -Wall

#include "lexer.h"

bool iswhitespace(char c) {
    return (c==' ' || c=='\n' || c=='\t' || c=='\r');
}
bool isdym(char c) {
    return(c == '&' || c == '*' || c == '+' || c == '/' || c == '-' || c == '?' || c == '|' || c == '%' || c == '=' || c == '^' || c == '!');
} bool isym(char c) {
    return(c == '(' || c == ')' || c == '{' || c == '}' || c == '&' || c == '*' || c == '+' || c == '/' || c == '-' || c == '?' || c == '|' || c == '%' || c == '=' || c == '^' || c == '!' || c == '[' || c == ']');
}

bool iskeyw(char* s) {
    for (int i = 0; i <= sizeof(keywords); i++) {
        if (strcmp(s, keywords[i])) return true;
    }
}

Token* lexer(char* code) {
    size_t len = strlen(code);
    Token* result = malloc(sizeof(Token));
    if (!result) {
        perror("malloc failed");
        exit(1);
    }

    size_t token_index = 0;

    for (size_t i = 0; i < len; i++) {
        char curchar = code[i];
        /*
        result[i].type = TOKEN_IDENT;

        result[i].value = malloc(2);
        result[i].value[0] = curchar;
        result[i].value[1] = '\0';
        */

        if (iswhitespace(curchar)) continue;

        if (isalpha(curchar) || curchar == '_') {
            // create dyn string
            char* tempstr = malloc(1);
            if (!tempstr) {
                perror("malloc failed");
                exit(1);
            }
            size_t idx = 0;

            while (i < len && (code[i] == '_' || isalpha(code[i]) || isdigit(code[i]))) {
                char* newptr = realloc(tempstr, idx + 2);
                if (!newptr) {
                    perror("realloc failed");
                    free(tempstr);
                    exit(1);
                }
                tempstr = newptr;

                tempstr[idx++] = code[i];
                i++;
            }

            tempstr[idx] = '\0';  // end it
            i--;                  // dec the index

            // create the token
            result[token_index].type = TOKEN_IDENT;
            result[token_index].value = tempstr;
            token_index++;
        }
        else if (isdigit(curchar)) {
            // create dyn string
            char* tempstr = malloc(1);
            if (!tempstr) {
                perror("malloc failed");
                exit(1);
            }
            size_t idx = 0;

            while (i < len && (code[i] == '.' || isdigit(code[i]))) {
                char* newptr = realloc(tempstr, idx + 2);
                if (!newptr) {
                    perror("realloc failed");
                    free(tempstr);
                    exit(1);
                }
                tempstr = newptr;

                tempstr[idx++] = code[i];
                i++;
            }
            tempstr[idx] = '\0';  // end it
            i--;                  // dec the index

            // create the token
            // only have one type for both float and number.
            result[token_index].type = TOKEN_NUMBER;
            result[token_index].value = tempstr;
            token_index++;
        } else if (curchar == '.') {
            if (code[i+1] <= len && code[i+1] == '.') {
                result[token_index].type = TOKEN_DOUBLE + TOKEN_DOT;
                result[token_index].value = malloc(3);
                result[token_index].value[0] = '.';
                result[token_index].value[1] = '.';
                result[token_index].value[2] = '\0';
            } else {
                result[token_index].type = TOKEN_DOT;
                result[token_index].value = malloc(2);
                result[token_index].value[0] = '.';
                result[token_index].value[1] = '\0';
            }
            token_index++;
        } else if (curchar == ':') {
            if (code[i+1] <= len && code[i+1] == ':') {
                result[token_index].type = TOKEN_DOUBLE + TOKEN_DOT;
                result[token_index].value = malloc(3);
                result[token_index].value[0] = ':';
                result[token_index].value[1] = ':';
                result[token_index].value[2] = '\0';
            } else {
                result[token_index].type = TOKEN_DOT;
                result[token_index].value = malloc(2);
                result[token_index].value[0] = ':';
                result[token_index].value[1] = '\0';
            }
            token_index++;
        } else if (curchar == ',') {
            result[token_index].type     = TOKEN_DOT;
            result[token_index].value    = malloc(2);
            result[token_index].value[0] = ',';
            result[token_index].value[1] = '\0';
            token_index++;
        } else if (isym(curchar)) {
            if (code[i+1] <= len && isdym(code[i+1])) {
                result[token_index].type  = TOKEN_DOUBLE + TOKEN_SYMBOL;
                result[token_index].value = malloc(3);
                result[token_index].value[0] = curchar;
                result[token_index].value[1] = code[i+1];
                result[token_index].value[2] = '\0';
                i++;
            } else {
                result[token_index].type = TOKEN_SYMBOL;
                result[token_index].value = malloc(2);
                result[token_index].value[0] = curchar;
                result[token_index].value[1] = '\0';
            }
            token_index++;
        } else if (curchar == ';') {
            result[token_index].type = TOKEN_SEMICOL;
            result[token_index].value = malloc(2);
            result[token_index].value[0] = ';';
            result[token_index].value[1] = '\0';
            token_index++;
        } else {
            fprintf(stderr, "unknown token: %c\n", curchar);
            free(result);
            exit(1);
        }
        Token* newptr = realloc(result, (token_index + 1) * sizeof(Token));
        if (!newptr) {
            perror("realloc failed");
            free(result);
            exit(1);
        }
        result = newptr;
    }

    result[token_index].type = TOKEN_EOF;
    result[token_index].value = "EOF";

    return result;
}