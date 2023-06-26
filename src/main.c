#include <at89x52.h>
#define GameTime 600

unsigned char game_minutes = 10;
unsigned char game_seconds = 0;
const int sevenSegment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                            0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delay(unsigned int i)
{
    
    for (int j = i; j < 48; j++)
    {
        for (int k = 0; k < 50; k++)
        {
            __asm
                nop
            __endasm;
        }
    }
    
}

void buzzer(void)
{
    __asm
        clr P3.5
    __endasm;
}

void main(void)
{
    while (1)
    {
        while (GameTime)
        {
            int count = 24;
            for (int i = count; i >= 0; i--)
            {
                P3_5 = 1;
                for (int j = 0; j < 8; j++)
                {
                    // First Iter
                    P2 = sevenSegment[i / 10];
                    P1 = sevenSegment[game_minutes / 10];
                    P0_0 = 0;
                    P0_1 = 1;
                    P0_2 = 1;
                    P0_3 = 1;

                    P3_0 = 0;
                    P3_1 = 1;
                    delay(1.8);

                    // Second Iter
                    P2 = sevenSegment[i % 10];
                    P1 = sevenSegment[game_minutes % 10];
                    P0_0 = 1;
                    P0_1 = 0;
                    P0_2 = 1;
                    P0_3 = 1;

                    P3_0 = 1;
                    P3_1 = 0;
                    delay(1.8);

                    // Third Iter
                    P2 = sevenSegment[i / 10];
                    P1 = sevenSegment[game_seconds / 10];
                    P0_0 = 1;
                    P0_1 = 1;
                    P0_2 = 0;
                    P0_3 = 1;

                    P3_0 = 0;
                    P3_1 = 1;
                    delay(1.8);

                    // Fourth Iter
                    P2 = sevenSegment[i % 10];
                    P1 = sevenSegment[game_seconds % 10];
                    P0_0 = 1;
                    P0_1 = 1;
                    P0_2 = 1;
                    P0_3 = 0;

                    P3_0 = 1;
                    P3_1 = 0;
                    delay(1.8);
                }

                if (!P3_2)
                {
                    count = 24;
                    break;
                }
                if (!P3_3)
                {
                    count = 14;
                    break;
                }

                if (game_seconds == 0)
                {
                    game_minutes--;
                    game_seconds = 59;
                }else{
                    game_seconds--;
                }
                
            }

            while (P3_3 && P3_4)
            {
                buzzer();
            }
        }
    }
}
