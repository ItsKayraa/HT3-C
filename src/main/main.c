//!-I. -std=c23 -Wall

/// ================================ [ DECLARATIONS ] ================================ ///

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "../parser/parser.h"

/// =================================== [ MACROS ] =================================== ///

/// === colour console ================

#define RED     "\033[1;31m"
#define RESET   "\033[0m"

/// === print error ===================

/// perrors the given message in this template: "error: <urmsg> \n", colouring "error:"
#define ERR(msg) perror(RED "error: " RESET msg "\n")

/// ==================================== [ FUNC ] ==================================== ///

/// returns a pointer
char* readFile(const char *path) {
    FILE *fp = fopen(path, "r");
    if(!fp) {
		ERR("File opening failed.");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buffer = malloc(size + 1);
    if(!buffer) {
		ERR("Memory allocation failed.");
        fclose(fp);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, size, fp);
    buffer[read_size] = '\0';

    fclose(fp);
    return buffer;
}

/// ==================================== [ MAIN ] ==================================== ///

int main(int argc, char* argv[]) {
    if(argc<2) { /// if there is at least 2 arguments
		ERR("Expected a source file.");
        return 1;
    }
    
    // source file: argv[1]
    if(access(argv[1], F_OK) != 0) {
		ERR("Source file doesn't exist.");
        return 1;
    }
    
    char* content = readFile(argv[1]);
    Token* result = lexer(content);

    for (size_t i = 0; result[i].type != TOKEN_EOF; i++) {
        printf("TOKEN_TYPE: %d, TOKEN_VALUE: %s\n", result[i].type, result[i].value);
        free(result[i].value);
    }

    parser(result);

    free(result);

    return(0);
}

#if 0
/// ==================================== [ NOTE ] ==================================== ///



#endif
