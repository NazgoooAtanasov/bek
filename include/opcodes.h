#ifndef BEK_OPCODES_
#define BEK_OPCODES_

#define OP_CODES_COUNT 4

enum _OpCodes {
    PUSH_OP = 0x01,
    PLUS_OP = 0x02,
    MINUS_OP = 0x03,
    RET_OP = 0xFF
};

#endif // BEK_OPCODES_
