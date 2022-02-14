#ifndef BEK_COMPILER_
#define BEK_COMPILER_

#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "token.h"
#include "bytebuff.h"
#include "opcodes.h"

enum _CompStatus {
    C_NOT_STARTED,
    C_FINISHED,
    C_ERROR
};

struct _Compiler {
    int running;
    int status;
    const char* output_file;
};
typedef struct _Compiler Compiler;

void compiler_create(Compiler* comp, const char* output_file);
int compiler_compile(Compiler* comp, Token* tokens, int tokens_count);

#endif // BEK_COMPILER_
