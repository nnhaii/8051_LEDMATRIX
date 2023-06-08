#include <reg52.h>

sbit SCLK=P3^6; // SCLK pin of 74HC595
sbit RCLK=P3^5; // RCLK pin of 74HC595
sbit SER=P3^4; // SER pin of 74HC595

unsigned char column[8]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // column data for 8x8 LED matrix
unsigned char digit[10]={0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B}; // digit patterns for 7-segment display

void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for (i = 0; i < ms; i++)
        for (j = 0; j < 125; j++);
}

void shift_out(unsigned char value)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        SER = value & 0x80;
        SCLK = 0;
        SCLK = 1;
        value <<= 1;
    }
}

void update_column(unsigned char col)
{
    unsigned char i;

    RCLK = 0;
    shift_out(~col);
    shift_out(0xFF);
    RCLK = 1;
    delay_ms(1);
    RCLK = 0;

    for (i = 0; i < 8; i++)
    {
        SCLK = 0;
        SCLK = 1;
        column[i] <<= 1;
    }
}

void display_digit(unsigned char digit)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        if (digit & (1 << i))
            column[i] |= 0x01;
        else
            column[i] &= 0xFE;
    }
}

void display_time(unsigned char sec)
{
    unsigned char digit1, digit2;

    digit1 = sec / 10;
    digit2 = sec % 10;

    display_digit(digit[digit1]);
    update_column(column[0]);
    display_digit(digit[digit2]);
    update_column(column[1]);
}

void main()
{
    unsigned char sec = 0;

    while (1)
    {
        display_time(sec);

        sec++;
        if (sec == 60)
            sec = 0;

        delay_ms(1000);
    }
}
