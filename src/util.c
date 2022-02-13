#include "../include/util.h"

char* read_file(const char* fp) {
    FILE* file = fopen(fp, "r");

    fseek(file, 0, SEEK_END);
    int file_buff_sz = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* file_buff = (char*) malloc(sizeof(char) * file_buff_sz + 1);

    fread(file_buff, 1, file_buff_sz, file);
    file_buff[file_buff_sz] = '\0';
    fclose(file);

    return file_buff;
}

uint8_t* read_file_binary(const char* fp) {
    FILE* file = fopen(fp, "rb");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t* buffer = (uint8_t*) malloc(sizeof(uint8_t) * size);
    fread(buffer, 1, size, file);
    fclose(file);

    return buffer;
}

void write_binary(ByteBuff* bf, const char* output) {
    FILE* f = fopen(output, "wb");
    fwrite(bf->buffer, 1, bf->ptr, f);
    fclose(f);
}
