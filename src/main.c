#include <at89x52.h>
#define BTN_RST_14 P3_2
#define BTN_RST_24 P3_3

unsigned char game_minutes = 10;
unsigned char game_seconds = 0;
unsigned char shotclock_seconds = 24;
const int seven_segment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                             0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delay(unsigned int i)
{

    for (; i > 0; i--)
    {
        for (int k = 0; k < 5000; k++)
        {
            __asm 
                nop
            __endasm;
        }
    }
}

void display(unsigned char i, unsigned char delay_time, unsigned char game_minutes, unsigned char game_seconds)
{
    unsigned char digit_values_shotclock[2] = {i / 10, i % 10};
    unsigned char digit_values_gameclock[4] = {game_minutes / 10, game_minutes % 10, game_seconds / 10, game_seconds % 10};

    for (int j = 0; j < 15; j++)
    {
        for (int iter = 0; iter < 4; iter++)
        {
            P2 = seven_segment[digit_values_shotclock[iter % 2 == 0 ? 0 : 1]];
            P1 = seven_segment[digit_values_gameclock[iter]];
            P0_0 = iter == 0 ? 0 : 1;
            P0_1 = iter == 1 ? 0 : 1;
            P0_2 = iter == 2 ? 0 : 1;
            P0_3 = iter == 3 ? 0 : 1;
            P3_0 = iter % 2 == 0 ? 0 : 1;
            P3_1 = iter % 2 != 0 ? 0 : 1;

            delay(delay_time);
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

            display(i, 1, game_minutes, game_seconds);

            while (!P3_4)
            {
                display(i, 1, game_minutes, game_seconds);
            }

            if (game_seconds == 0 && game_minutes == 0)
            {
                break;
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

            if (game_seconds == 0)
            {
                game_minutes--;
                game_seconds = 59;
            }else{
                game_seconds--;
            }
        }

        if (game_minutes == 0 && game_seconds == 0 && !BTN_RST_24)
        {
            game_minutes = 10;
            game_seconds = 0;
        }
        
        while (BTN_RST_14 && BTN_RST_24)
        {
            P3_5 = 1;
        }
    }
}
