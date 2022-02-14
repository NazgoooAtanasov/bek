#ifndef BEK_BYTEBUFF_
#define BEK_BYTEBUFF_

#include <stdint.h>
#include <stdlib.h>

struct _ByteBuff {
    uint8_t* buffer;
    int ptr;
    size_t buff_sz;
};
typedef struct _ByteBuff ByteBuff;

void bytebuff_create(ByteBuff* bf);

void bytebuff_destroy(ByteBuff* bf);

void add_byte8(ByteBuff* bf, uint8_t data);

void add_byte16(ByteBuff* bf, uint16_t data);

void add_byte32(ByteBuff* bf, uint32_t data);

#endif // BEK_BYTEBUFF_
