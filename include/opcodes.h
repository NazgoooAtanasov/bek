#ifndef BEK_OPCODES_
#define BEK_OPCODES_

#define OP_CODES_COUNT 6

enum _OpCodes {
    PUSH_OP = 0x01,
    PLUS_OP = 0x02,
    MINUS_OP = 0x03,
    MULT_OP = 0x04,
    DEV_OP = 0x05,
    RET_OP = 0xFF
};

#endif // BEK_OPCODES_
