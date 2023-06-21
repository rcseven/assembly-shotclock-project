#include <at89x52.h>

// Write a delay function
void delay(void)
{
    __asm
        MOV R2, #250

        LOOP_1:
            ; Inner loop 2 counter -> 2
            MOV R1, #247

            LOOP_2:
                ; Inner loop 3 counter -> 6
                MOV R0, #6

                LOOP_3:   
                    DJNZ R0, LOOP_3 ; Decrement R0, jump if not zero

                DJNZ R1, LOOP_2 ; Decrement R1, jump if not zero

            DJNZ R2, LOOP_1 ; Decrement R2, jump if not zero
    __endasm;
}

void main(void)
{
    while (1)
    {
        P1_0 = !P1_0;
        delay();
    }
}
