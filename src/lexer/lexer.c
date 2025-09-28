//!-Isrc -std=c23 -Wall

#include "lexer.h"

const char* keywords[] = {
    "func", "printl", "eret", "ret", "int", "str", "char"
};

#define iswhitespace(c) (c==' ' || c=='\n' || c=='\t' || c=='\r')

#define isdym(c) ( \
        c == '&' || c == '*' || c == '+' || c == '/'  \
        || c == '-' || c == '?' || c == '|' || c == '%' \
        || c == '=' || c == '^' || c == '!')

#define isym(c) (c == '(' || c == ')' || c == '{' || c == '}' \
        || c == '&' || c == '*' || c == '+' || c == '/' \
        || c == '-' || c == '?' || c == '|' || c == '%' \
        || c == '=' || c == '^' || c == '!' \
        || c == '[' || c == ']' )

bool in(const char **keywords, int len, char *target) {
    int i;
    for(i = 0; i < len; i++) {
        const char* cur = keywords[i];
        if (strcmp(cur, target) == 0) {
            return 1;
        } else {
            continue;
        }
    }
    return 0;
}

bool iskeyw(char text[]) {
    int keyword_len = sizeof(keywords) / sizeof(keywords[0]);
    return in(keywords, keyword_len, text);
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

            printf("%s\n", tempstr);

            // create the token
            if (iskeyw(tempstr)) {
                result[token_index].type = TOKEN_KEYWORD;
            } else {
                result[token_index].type = TOKEN_IDENT;
            }
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
                result[token_index].type = TOKEN_DOUBLE + TOKEN_COL;
                result[token_index].value = malloc(3);
                result[token_index].value[0] = ':';
                result[token_index].value[1] = ':';
                result[token_index].value[2] = '\0';
            } else {
                result[token_index].type = TOKEN_COL;
                result[token_index].value = malloc(2);
                result[token_index].value[0] = ':';
                result[token_index].value[1] = '\0';
            }
            token_index++;
        } else if (curchar == ',') {
            result[token_index].type     = TOKEN_COMMA;
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
