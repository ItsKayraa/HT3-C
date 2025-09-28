#include "parser.h"
#include <stdio.h>
/// it'll be compiling later on.


int parser(Token* tokens) {
    for (int i = 0; i <= sizeof(tokens); i++) {
        Token curt = tokens[i];

        if (curt.type == TOKEN_KEYWORD) {
            printf("keyword %s\n", curt.value);
            if (strcmp(curt.value, "func") == 0) {
                printf("function\n");
                if (i+1 > sizeof(tokens)) return 1;

                Token namet = tokens[i+1];

                if (namet.type != TOKEN_IDENT) return 1;

                printf("function %s\n", namet.value);
                i++;
            }
        }
    }
}
