//!-I. -std=c23 -Wall

/// ================================ [ DECLARATIONS ] ================================ ///

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../lexer/lexer.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define BLUE    "\033[1;34m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

/// ==================================== [ MAIN ] ==================================== ///

char* readFile(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror(RED "error:" RESET " File opening failed.");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        perror(RED "error:" RESET " Memory allocation failed.");
        fclose(fp);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, size, fp);
    buffer[read_size] = '\0';

    fclose(fp);
    return buffer;
}

// make it char* later
Token* compile(char* code) {
    // just lex for now
    return(lexer(code));
}

int main(int argc, char* argv[]) {
    if(argc<2) { /// if there is at least 2 arguments
        perror(RED "error:" RESET " expected a source file.\n");
        return 1;
    }
    
    // source file: argv[1]
    if (access(argv[1], F_OK) != 0) {
        perror(RED "error:" RESET " source file doesn't exists.\n");
        return 1;
    }
    
    char* content = readFile(argv[1]);
    Token* result = compile(content);

    for (size_t i = 0; result[i].type != TOKEN_EOF; i++) {
        printf("TOKEN_TYPE: %d, TOKEN_VALUE: %s\n", result[i].type, result[i].value);
        free(result[i].value);
    }

    free(result);

    return(0);
}

#if 0
/// ==================================== [ NOTE ] ==================================== ///



#endif