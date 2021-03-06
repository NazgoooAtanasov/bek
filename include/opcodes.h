#ifndef BEK_OPCODES_
#define BEK_OPCODES_

#define OP_CODES_COUNT 15

enum _OpCodes {
    PUSH_OP = 0x01,
    PLUS_OP = 0x02,
    MINUS_OP = 0x03,
    MULT_OP = 0x04,
    DEV_OP = 0x05,
    PRINT_OP = 0x06,

    END_BLOCK_OP = 0x07,

    CONDITION_OP = 0x08,
    CONDITION_START_OP = 0x09,

    CONDITION_EQ_OP = 0x0A,
    CONDITION_BIGGER_EQ_OP = 0x0B,
    CONDITION_LESS_EQ_OP = 0x0C,
    CONDITION_LESS_OP = 0x0D,
    CONDITION_BIGGER_OP = 0x0E,

    RET_OP = 0xFF
};

#endif // BEK_OPCODES_
