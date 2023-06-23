#include <at89x52.h>
const int sevenSegment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                            0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// create a delay function
void delay(void)
{
    __asm
        mov r0, #50
    L1:
        mov r1, #50
    L2:
        mov r2, #50
    L3:
        djnz r2, L3
        djnz r1, L2
        djnz r0, L1
    __endasm;
}

void buzzer(void)
{
    __asm
        clr P3.5
    __endasm;
}

void main(void)
{
    int count = 24;
    while (1)
    {   
        for (int i = count; i >= 0; i--)
        {   
            P3_5 = 1;
            P2 = sevenSegment[i / 10];
            P3_0 = 0;
            P3_1 = 1;
            delay();
            P2 = sevenSegment[i % 10];
            P3_0 = 1;
            P3_1 = 0;
            delay();

            if (!P3_3){
                count = 24;
                break;
            }
            if(!P3_4){
                count = 14;
                break;
            }
        }

        while (P3_3 && P3_4)
        {
            buzzer();
        }
    }
}
