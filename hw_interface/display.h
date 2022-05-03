#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <termios.h>
#include "z80.h"
#include "commands.h"

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

#define SERIAL "/dev/ttyACM0"
#define BAUD_RATE 96000


int serial_init()
{
    int fd,retval;
    struct termios serial_settings;
    fd = open(SERIAL, O_RDWR | O_NOCTTY);
    sleep(3);
    if (fd < 0)
    {
        perror("Couldn't open SERIAL");
        exit(EXIT_FAILURE);
    }
    if (tcgetattr(fd, &serial_settings) < 0)
    {
        perror("Couldn't get termios struct");
        exit(EXIT_FAILURE);
    }
    if (cfsetospeed(&serial_settings, B9600) < 0)
    {
        perror("Couldn't set out baud rate");
        exit(EXIT_FAILURE);
    }
    if (cfsetispeed(&serial_settings, B9600) < 0)
    {
        perror("Couldnt't set in baud rate");
        exit(EXIT_FAILURE);
    }
    serial_settings.c_cflag &= ~(PARENB | CSTOPB | CSIZE);
    serial_settings.c_cflag |= (CS8 | CREAD | CLOCAL);
    serial_settings.c_iflag &= ~(IXON |IXOFF | IXANY);
    serial_settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    serial_settings.c_oflag &= ~OPOST;

    serial_settings.c_cc[VMIN]=0;
    serial_settings.c_cc[VTIME]=0;

    if (tcsetattr(fd,TCSANOW,&serial_settings) < 0)
    {
        perror("Couldn't set serial");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    return fd;
}

void show_pinState(){
    printf("------PIN STATE------\n");
    printf("Addres:  0x%02x%02x 0b"
            BYTE_TO_BINARY_PATTERN
            BYTE_TO_BINARY_PATTERN"\n",
            z80_Pins.AddresH,
            z80_Pins.AddresL,
            BYTE_TO_BINARY(z80_Pins.AddresH),
            BYTE_TO_BINARY(z80_Pins.AddresL));
    printf("Data:    0x%02x   0b"
            BYTE_TO_BINARY_PATTERN"\n",
            z80_Pins.Data,
            BYTE_TO_BINARY(z80_Pins.Data));
    printf("Control: 0x%02x   0b"
            BYTE_TO_BINARY_PATTERN"\n",
            z80_Pins.Control,
            BYTE_TO_BINARY(z80_Pins.Control));
    printf("---------------------\n");
}

void show_pinControlState(){
    printf("-------CONTROL-------\n"
           "RFSH   %c\n"
           "M1     %c\n"
           "HALT   %c\n"
           "BUSACK %c\n"
           "WR     %c\n"
           "RD     %c\n"
           "IORQ   %c\n"
           "MREQ   %c\n"
           "---------------------\n",
           BYTE_TO_BINARY(z80_Pins.Control));
}

#endif