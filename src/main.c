#include <at89x52.h>
const int sevenSegment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                            0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// create a delay function
void delay(int ms)
{
    for (int i = 0; i < ms; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
        }
    }
}

void main(void)
{
    while (1)
    {
        for (int i = 24; i >= 0; i--)
        {
            P2 = sevenSegment[i / 10];
            P3_0 = 0;
            P3_1 = 1;
            delay(12);
            P2 = sevenSegment[i % 10];
            P3_0 = 1;
            P3_1 = 0;
            delay(12);
        }
    }
}
