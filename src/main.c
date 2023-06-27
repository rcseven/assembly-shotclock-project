#include <at89x52.h>
#define BTN_RST_14 P3_2
#define BTN_RST_24 P3_3

unsigned int game_time = 600;
unsigned char game_minutes = 10;
unsigned char game_seconds = 0;
unsigned char shotclock_seconds = 24;
const int seven_segment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                             0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delay(unsigned int i)
{

    for (int j = i; j < 50; j++)
    {
        for (int k = 0; k < 48; k++)
        {
            __asm 
                nop
            __endasm;
        }
    }
}

void main(void)
{
    while (1)
    {
        for (int i = shotclock_seconds; i >= 0; i--)
        {
            P3_5 = 0;
            for (int j = 0; j < 8; j++)
            {
                // First Iter
                P2 = seven_segment[i / 10];
                P1 = seven_segment[game_minutes / 10];
                P0_0 = 0;
                P0_1 = 1;
                P0_2 = 1;
                P0_3 = 1;

                P3_0 = 0;
                P3_1 = 1;
                delay(1.8);

                // Second Iter
                P2 = seven_segment[i % 10];
                P1 = seven_segment[game_minutes % 10];
                P0_0 = 1;
                P0_1 = 0;
                P0_2 = 1;
                P0_3 = 1;

                P3_0 = 1;
                P3_1 = 0;
                delay(1.8);

                // Third Iter
                P2 = seven_segment[i / 10];
                P1 = seven_segment[game_seconds / 10];
                P0_0 = 1;
                P0_1 = 1;
                P0_2 = 0;
                P0_3 = 1;

                P3_0 = 0;
                P3_1 = 1;
                delay(1.8);

                // Fourth Iter
                P2 = seven_segment[i % 10];
                P1 = seven_segment[game_seconds % 10];
                P0_0 = 1;
                P0_1 = 1;
                P0_2 = 1;
                P0_3 = 0;

                P3_0 = 1;
                P3_1 = 0;
                delay(1.8);
            }

            if (!BTN_RST_24)
            {
                shotclock_seconds = 24;
                break;
            }
            if (!BTN_RST_14)
            {
                shotclock_seconds = 14;
                break;
            }
            if (game_time == 0)
            {
                break;
            }
            

            if (game_seconds == 0)
            {
                game_minutes--;
                game_seconds = 59;
            }
            else
            {
                game_seconds--;
            }
            game_time--;
        }

        while (BTN_RST_14 && BTN_RST_24)
        {
            P3_5 = 1;
        }
    }
}
