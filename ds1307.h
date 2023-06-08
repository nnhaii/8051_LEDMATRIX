
#include <regx52.h>
#include <delay.h>

#define DS1307_SEC 0x00 //Giay
#define DS1307_MIN 0x01 //Phut
#define DS1307_HOUR 0x02 //Gio
#define DS1307_DAY 0x03 //Thu
#define DS1307_DATE 0x04 //Ngay
#define DS1307_MONTH 0x05 //Thang
#define DS1307_YEAR 0x06 //Nam

void DS1307_Write(unsigned char addr,unsigned char dat);
unsigned char DS1307_Read(unsigned char addr);
void DS1307_Set();
void DS1307_GetTime();
void DS1307_GetDate();
