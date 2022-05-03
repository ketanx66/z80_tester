#ifndef Z80_H
#define Z80_H

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "commands.h"

int arduinoFD; //File descriptor

#define MREQ   0
#define IORQ   1
#define RD     2
#define WR     3
#define BUSACK 4
#define BUSREQ 5 // change to HALT on board and then here
#define M1     6
#define RFSH   7

#define HALT   8
#define NMI    9
#define INT    10
#define WAIT   11
#define RESET  12

typedef struct z80_PinState
{
    uint8_t AddresH;
    uint8_t AddresL;
    uint8_t Data;
    uint8_t Control;
} z80_PinState;
typedef struct z80_RegisterState
{
    uint8_t IXH,IXL;
    uint8_t IYH,IYL;
    uint8_t SPH,SPL;
    uint8_t PCH,PCL;
    uint8_t A,F;
    uint8_t B,C;
    uint8_t D,E;
    uint8_t H,L;
    uint8_t A_,F_;
    uint8_t B_,C_;
    uint8_t D_,E_;
    uint8_t H_,L_;
    uint8_t I;
    uint8_t R;
} z80_RegisterState;

z80_PinState      z80_Pins;
z80_RegisterState z80_Registers;

void get_PinState(){
    char instr = (char)GET_PIN_STATE; 
    if (write(arduinoFD,&instr,1) < 0)
    {
        perror("Write failed");
        exit(1);
    }
    usleep(50000);
    read(arduinoFD,&z80_Pins.AddresH,1);
    usleep(10000);
    read(arduinoFD,&z80_Pins.AddresL,1);
    usleep(10000);
    read(arduinoFD,&z80_Pins.Data,1);
    usleep(10000);
    read(arduinoFD,&z80_Pins.Control,1);
    usleep(50000);
}

void reset(){
    char instr = (char)RESET_CPU; 
    if (write(arduinoFD,&instr,1) < 0)
    {
        perror("Write failed");
        exit(1);
    }
}

#endif