#include <stdio.h>
#include <z80.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

enum commands {
    GET_PIN_STATE
};

void show_pinState(){
    printf("------PIN STATE------\n");
    printf("Addres:  %#03x "
            BYTE_TO_BINARY_PATTERN
            BYTE_TO_BINARY_PATTERN"b\n",
            z80_Pins.AddresH,
            z80_Pins.AddresL,
            BYTE_TO_BINARY(z80_Pins.AddresH),
            BYTE_TO_BINARY(z80_Pins.AddresL));
    printf("Data:    %#02x "
            BYTE_TO_BINARY_PATTERN"b\n",
            z80_Pins.Data,
            BYTE_TO_BINARY(z80_Pins.Data));
    printf("Control: %#02x "
            BYTE_TO_BINARY_PATTERN"b\n",
            z80_Pins.Control,
            BYTE_TO_BINARY(z80_Pins.Control));
    printf("---------------------\n");
}