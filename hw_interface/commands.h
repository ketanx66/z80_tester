#ifndef COMMANDS_H
#define COMMANDS_H

#define MAGIC 33
enum commands {
    GET_PIN_STATE = MAGIC,
    GET_REGISTERS,
    TICK,
    RESET_CPU,
    DUMMY
};

#endif