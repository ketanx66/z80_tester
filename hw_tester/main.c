#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include "../hw_interface/commands.h"
#include "pins.h"

#define F_CPU 16000000
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define CLOCK_HIGH 1
#define CLOCK_LOW  0
#define HIGH 0
#define LOW 1

uint8_t mem[] = {
 0x21, 0x0a, 0x00, //ld hl, ??
 0x0e, 0x00, //ld c, 0
 0x06, 0x0c, //ld b, 12
 0xed, 0xb3, //otir
 0x76, //halt
 'H','e','l','l','o', ' ','W','o','r','l','d','\n'
};

uint8_t memory[1024];

void post_pin_state(){
  putchar(PIN_ADDRES_H);
  putchar(PIN_ADDRES_L);
  putchar(PIN_DATA);
  putchar(PIN_CONTROL);
}

void uart_init()
{
  UBRR0 = UBRR_VALUE;
  UCSR0A = 0;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

int uart_transmit(char data, FILE *stream)
{
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

int uart_receive(FILE *stream)
{
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

#define CLOCK(state) (state == CLOCK_HIGH) ? (PORT_CLOCK |= _BV(P_CLOCK)) \
                                           : (PORT_CLOCK &= ~_BV(P_CLOCK))

#define RESET(state) (state == HIGH) ? (PORT_RESET |= _BV(P_RESET)) \
                                     : (PORT_RESET &= ~_BV(P_RESET))

FILE uart_file;

unsigned int prog[4] = {0xdb, 0x45, 0xd3, 0x01}; 

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  
  DDR_ADDRES_L = 0x00;
  DDR_ADDRES_H = 0x00;
  DDR_DATA     = 0x00;
  DDR_INPUT    = 0x00;

  
  DDR_INPUT  |= _BV(P_INT) | _BV(P_NMI) | _BV(P_BUSREQ) | _BV(P_WAIT);
  PORT_INPUT |= _BV(P_INT) | _BV(P_NMI) | _BV(P_BUSREQ) | _BV(P_WAIT);

  DDR_CLOCK |= _BV(P_CLOCK);

  DDR_RESET |= _BV(P_RESET);
  PORT_RESET &= ~_BV(P_RESET);

  char y = 1;
  PORTH &= ~(_BV(PH6));
  _delay_ms(2500);
  PORTH |= _BV(PH6);

  memset(memory, 0, sizeof(memory));
  memcpy(memory, mem, sizeof(mem));

  while(1) {
    unsigned int command;

    command = getchar();
    switch(command)
    {
      case(GET_PIN_STATE):
      {
        post_pin_state();
        break;
      }
      case(DUMMY):
      {
        start();
        putchar('!');
        break;
      }
      case(TICK):
      {
        CLOCK(CLOCK_HIGH);
        _delay_ms(10);
        CLOCK(CLOCK_LOW);
        break;
      }
      case(RESET_CPU):
      {
        PORTH |= _BV(PH6);
        _delay_ms(10);
        PORTG |= _BV(PG5);
        _delay_ms(10);
        PORTG &= ~(_BV(PG5));
        _delay_ms(10);
        PORTG |= _BV(PG5);
        _delay_ms(10);
        PORTG &= ~(_BV(PG5));
        _delay_ms(10);
        PORTG |= _BV(PG5);
        _delay_ms(10);
        PORTG &= ~(_BV(PG5));
        _delay_ms(10);
        PORTG |= _BV(PG5);
        _delay_ms(10);
        PORTG &= ~(_BV(PG5));
        _delay_ms(10);
        PORTH &= ~(_BV(PH6));
        break;
      }
    } //switch
  } //while
}
