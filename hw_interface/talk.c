#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "z80.h"
#include "display.h"


int main(){
    arduinoFD = serial_init();
    
  //  usleep(20000);
    
    for(;;)
    {
        char command = getchar();
        switch(command)
        {
            case('h'):
            case('H'):
            case('?'):
            {
                printf("--------HELP---------\n"
                       "h - help\n"
                       "g - pin state\n"
                       "q - quit\n"
                       "---------------------\n");
                break;
            }
            case('g'):
            {
                get_PinState();
                show_pinState();
                break;
            }
            case('d'):
            {
                char instr = (char)DUMMY; 
                if (write(arduinoFD,&instr,1) < 0)
                {
                    perror("Write failed");
                    exit(1);
                }
                break;
            }
            case('t'):
            {
                char instr = (char)TICK; 
                if (write(arduinoFD,&instr,1) < 0)
                {
                    perror("Write failed");
                    exit(1);
                }
                break;
            }
            case('c'):
            {   
                get_PinState();
                show_pinControlState();
                break;
            }
            case('r'):
            {
                reset();
                break;
            }
            case('i'):
            {
                char buf[255];
                getline(arduinoFD,buf);
                printf("%c",buf);
            }
            case('q'):
            case('Q'):
            {
                return 0;
                break;
            }
        }
    }
}


