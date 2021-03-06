#ifndef BEK_UTIL_
#define BEK_UTIL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bytebuff.h"

char* read_file(const char* fp); 

uint8_t* read_file_binary(const char* fp);

void write_binary(ByteBuff* bf, const char* output);

char *strrev(char *str);

#endif // BEK_UTIL_
