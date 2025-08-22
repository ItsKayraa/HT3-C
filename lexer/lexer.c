//!std=c23

#include "lexer.h"

bool iskeyword(char text[]) {
    constexpr int keyword_len = sizeof(keywords) / sizeof(char*);
    return strExists(text, keywords, keyword_len);
}

int lex(Token *result, char *content) {
    int i = 0;
    int cpos = 0;
    int len = strlen(content);

    while (i < len) {
        char curchar = content[i];

        if (iswhitespace(curchar)) {
            i++;
            continue;
        
        // ident | keyword
        } else if (isalpha(curchar) || curchar == '_') {
            char tempstr[256];
            int j = 0;

            while (isalpha(content[i]) || isdigit(content[i]) || content[i] == '_') {
                tempstr[j++] = content[i++];
            }
            tempstr[j] = '\0';

            if (iskeyword(tempstr)) {
                result[cpos].type = T_KEYWORD;
            } else {
                result[cpos].type = T_IDENT;
            }

            strcpy(result[cpos].text, tempstr);
            cpos++;
        } else if (isdigit(curchar)) {
            char tempstr[256];
            int j = 0;
            int dota = 0;

            int typ = 0;

            while (isdigit(content[i]) || content[i] == '.') {
                if (content[i] == '.') {
                    if (i = len || dota == 1) {
                        printf("fuck you\n"); /// holy moly
                        // better error handling than c; /// skill issue
                        return 1;
                    } else {
                        dota++;
                        typ = 1;
                    }
                    tempstr[j++] = content[i++];
                }
            }
            tempstr[j] = '\0';

            if (typ == 1) {
                result[cpos].type = T_FLOAT;
            } else {
                result[cpos].type = T_INT;
            }

            strcpy(result[cpos].text, tempstr);
            cpos++;
        } else if (content[i] == '"') {
            i++;
            char tempstr[256];
            int j = 0;

            while (i < len || content[i] != '"') {
                tempstr[j++] = content[i++];
            }
            tempstr[j] = '\0';

            i++;

            result[cpos].type = T_STRING;
            strcpy(result[cpos].text, tempstr);
            cpos++;
        } else {
            switch (curchar)
            {
            case '*':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_MUL;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case '+':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_PLUS;
                strcpy(result[cpos].text, tempstr);
                break;

            case '-':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_MINUS;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case '/':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_DIV;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case '{':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_LBRC;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case '}':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_RBRC;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case '[':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_LBRK;
                strcpy(result[cpos].text, tempstr);
                break;

            case ']':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_RBRK;
                strcpy(result[cpos].text, tempstr);
                break;

            case '(':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_LPRM;
                strcpy(result[cpos].text, tempstr);
                break;

            case ')':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_RPRM;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case '.':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_DOT;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case ',':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_COMA;
                strcpy(result[cpos].text, tempstr);
                break;
            
            case ';':
                char tempstr[2] = {curchar, '\0'};
                result[cpos].type = T_SEMI;
                strcpy(result[cpos].text, tempstr);
                break;

            default:
                break;
            }
            i++;
        }
    }

    result[cpos].type = T_EOF;
    strcpy(result[cpos].text, "EOF");
    return 0;
}

#if 0

int main() {
    Token tokens[1048];

    int status = lex(tokens, "func main");
    if(status) { return 1; }

    for(unsigned int i=0; tokens[i].type!=T_EOF; i++) {
        printf("TokenType: %s | TokenText: %s\n",
               TokenType_names[tokens[i].type], tokens[i].text);
    }
    
    return 0;
}

#endif
