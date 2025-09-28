//!-I. -std=c23 -Wall

/// ================================ [ DECLARATIONS ] ================================ ///

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/// #define TOKENNAME_DEBUG /// uncomment for token names

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
	/// === file checks ===================

    if(argc<2) { /// if there are at least 2 arguments
		ERR("Expected a source file.");
        return 1;
    }
    
    // source file: argv[1]
    if(access(argv[1], F_OK) != 0) {
		ERR("Source file doesn't exist.");
        return 1;
    }

	/// === main ==========================
    
    char* content = readFile(argv[1]);
    Token* tokenStream = lexer(content);
	free(content); /// content is presumably never used after this, so i recommend freeing

	for(; tokenStream->type != TOKEN_EOF; tokenStream++) {
		printf("TOKENNAME: " TOKENNAMEFMT "; TOKENVAL: %s;\n", 
				TOKENNAME(tokenStream->type), tokenStream->value
		); free(tokenStream->value);
	} printf("REACHED EOF\n");

    parser(tokenStream);

	/// === exfiltration ==================

    free(tokenStream);
    return(0);

	/// ===================================
}

/// ==================================== [ NOTE ] ==================================== ///
#if 0

I might wanna talk about not doing the args at the top

#endif
/// ================================================================================== ///
