//!std=c23

#include "parser.h"

int parser(ASM assembly, Token tokens[]) {
    int i = 0;
    int curf = 0;
    int isf = 0;
    while (tokens[i].type != T_EOF) {
        Token curtoken = tokens[i];
        switch (curtoken.type) {
            case T_KEYWORD:
                if (strcmp(curtoken.text, "func")) {
                    Token nametoken = tokens[i+1];
                    if (nametoken.type != T_IDENT) {
                        return 1;
                    }
                    int lenf = sizeof(types) / sizeof(types[0]);

                    char* typ = "";
                    char* name = "";
                    int loc = i+2;

                    if (in(types, lenf, nametoken.text)) {
                        strcpy(typ, nametoken.text);
                        Token namet = tokens[i+2];
                        if (namet.type != T_IDENT) {
                            return 1;
                        }
                        strcpy(name, namet.text);
                        loc++;
                    } else {
                        strcpy(typ, "any");
                        strcpy(name, nametoken.text);
                    }
                    if (tokens[loc].type != T_LPRM) {
                        return 1;
                    }

                    Function func;

                    loc++;
                    int jur = 0;
                    char* typ = "";
                    char* nam = "";
                    int cur;

                    for (cur = 1; tokens[loc+cur].type != T_RPRM; cur++) {
                        if (tokens[loc+cur].type == T_COMA) {
                            jur++;
                            loc++;
                            continue;
                        }
                        if (cur % 2 == 0) {
                            typ = tokens[loc+cur].text; 
                            func.params[jur][0] = typ;
                            func.params[jur][1] = nam;
                        } else {
                            nam = tokens[loc+cur].text;
                        }
                    }

                    loc += cur+1;
                    if (tokens[loc].type == T_SEMI) {
                        assembly.funcs[curf].content = malloc(strlen(name) + 3);
                        sprintf(assembly.funcs[curf].content, "%s:\n", name);
                        assembly.funcs[curf];
                        assembly.funcs[curf];
                    }
                }
                break;
            
            default:
                break;
        }
    }
}

int main() {
    Token *tokens = malloc(10 * sizeof(Token));

    int ecode = parser((ASM){}, tokens);
    if(!ecode) {
        printf("The parser has exited with error. Error code is [%d]", ecode);
        return(ecode);
    }

    free(tokens); return(0);
}