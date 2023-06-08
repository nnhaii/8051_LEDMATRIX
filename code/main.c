	/******************************************************************************
	* Ten tep:		delay.h
	* Tac gia:	 	Nguyen Nam Hai
	* Ngay:				01-04-2023
	******************************************************************************/
#include <main.h>

#include "i2c.h"


void Send_data_cot(unsigned int _data);
void Send_data_cot_1(unsigned int _data);
void DISPLAY_1(unsigned char d[8], unsigned char r[16]);
void DISPLAY_2(unsigned char d[8], unsigned char r[16]);
//===========================dinh nghia cac chan vao ra======================//
sbit SH_CP = P0^0; //dinh nghia chan SH_CP o P0^0
sbit DS = P0^1; //dinh nghia chan DS o P0^1
sbit ST_CP = P0^2; //dinh nghia chan ST_CP o P0^2

sbit SH_CP_1 = P0^4; //dinh nghia chan SH_CP o P0^0
sbit DS_1 = P0^6; //dinh nghia chan DS o P0^1
sbit ST_CP_1 = P0^5; //dinh nghia chan ST_CP o P0^2
//============================khai bao bien va hang==========================//
unsigned char t_h[16], t_m[16];
unsigned int b[16] = {
  0x0001, 0x0002, 0x0004, 0x0008, 
	0x0010, 0x0020, 0x0040, 0x0080, 
	0x0100, 0x0200, 0x0400, 0x0800, 
	0x1000, 0x2000, 0x4000, 0x8000
};
unsigned char i = 0, k = 0, j = 0;
unsigned char sec, min, hour, day, month, year;
//============================DS1307==========================//
#define DS1307_SEC 0x00 //Giay
#define DS1307_MIN 0x01 //Phut
#define DS1307_HOUR 0x02 //Gio
#define DS1307_DAY 0x03 //Thu
#define DS1307_DATE 0x04 //Ngay
#define DS1307_MONTH 0x05 //Thang
#define DS1307_YEAR 0x06 //Nam


//void DS1307_Write(unsigned char addr, unsigned char dat) {
//  unsigned int temp;
//  temp = dat; /*HEX to BCD*/
//  dat = (((dat / 10) * 16) | (temp % 10)); /*for Led 7seg*/
//  I2C_time_start(); /* time_start i2c bus */
//  I2C_write(0XD0); /* Connect to DS1307 */
//  I2C_write(addr); /* Requetime_5 RAM address on DS1307 */
//   I2C_write(dat);
//  I2C_time_stop();
//}
unsigned char DS1307_Read(unsigned char addr) {
  unsigned int tm, ret;
  I2C_time_start(); /* time_start i2c bus */
  I2C_write(0xD0); /* Connect to DS1307 */
  I2C_write(addr); /* Requetime_5 RAM address on DS1307 */
  I2C_time_start(); /* time_start i2c bus */
  I2C_write(0XD1); /* Connect to DS1307 for Read */
  ret = I2C_read(); /* Receive data */
  I2C_time_stop();
  tm = ret; /*BCD to HEX*/
  ret = (((ret / 16) * 10) + (tm & 0x0f)); /*for Led 7seg*/
  return ret;
}
/*
void DS1307_Set() {
  //Ghi du lieu ngay gio vao DS1307
  DS1307_Write(DS1307_SEC, sec);
  DS1307_Write(DS1307_MIN, min);
  DS1307_Write(DS1307_HOUR, hour);
  DS1307_Write(DS1307_DATE, day);
  DS1307_Write(DS1307_MONTH, month);
  DS1307_Write(DS1307_YEAR, year);
}
*/
void DS1307_GetTime() {
  //Doc du lieu gio tu DS1307
  hour = DS1307_Read(DS1307_HOUR);
  min = DS1307_Read(DS1307_MIN);
  sec = DS1307_Read(DS1307_SEC);
}
/*
void DS1307_GetDate() {
  //Doc du lieu ngay tu DS1307
  day = DS1307_Read(DS1307_DATE);
  month = DS1307_Read(DS1307_MONTH);
  year = DS1307_Read(DS1307_YEAR);
}
*/
//End code DS1307

//============================HAM MAIN=======================================//
int main() {

  // Initialize I2C communication
	DS1307_GetTime();
  while (1) {
    hour = DS1307_Read(DS1307_HOUR);
    min = DS1307_Read(DS1307_MIN);

    DISPLAY_1(so[hour / 10], t_h);
    DISPLAY_2(so[hour % 10], t_h);
    DISPLAY_1(so[min / 10], t_m);
    DISPLAY_2(so[min % 10], t_m);

    for (i = 0; i < 16; i++) //quet COT thu 1 den thu 16, cho COT=0 roi goi du lieu ra cot do
    {
      P2 = t_h[i]; // goi du kieu ra hang 1->8
      P1 = t_m[i];
      Send_data_cot(b[i]); //quet cot
      Send_data_cot_1(b[i]);
      delay_ms(1); //thoi gian quet
      Send_data_cot(0x0000); //tat het led chong lem
      Send_data_cot_1(0x0000);
    }
  }
}

void Send_data_cot(unsigned int _data) {
  unsigned char n;
  unsigned int tam;

  ST_CP = 0; //cho chan ST cua 74HC595 xuong muc 0
  SH_CP = 0; //cho chan SH cua 74HC595 xuong muc 0
  DS = 0; //cho chan DS cua 74HC595 xuong muc 0
  for (n = 0; n < 16; n++) //goi 16 bit lan luoc ra 16 cot
  {
    tam = _data & 0x8000;
    _data = _data << 1; //dich trai 1 bit de goi bit can goi ra  cot      

    if (tam == 0x8000) //goi bit cao ra truoc(bit o cot thu 8 truoc)
    {
      DS = 1; // cho LED sang COT =1
    } else {
      DS = 0; //cho LED tat COT =0
    }
    //tao xung dich du lieu   
    SH_CP = 1;
    SH_CP = 0;
  }
  //tao xung chot du lieu
  ST_CP = 1;
  ST_CP = 0;
}

void Send_data_cot_1(unsigned int _data) {
  unsigned char n;
  unsigned int tam;

  ST_CP_1 = 0; //cho chan ST cua 74HC595 xuong muc 0
  SH_CP_1 = 0; //cho chan SH cua 74HC595 xuong muc 0
  DS_1 = 0; //cho chan DS cua 74HC595 xuong muc 0
  for (n = 0; n < 16; n++) //goi 16 bit lan luoc ra 16 cot
  {
    tam = _data & 0x8000;
    _data = _data << 1; //dich trai 1 bit de goi bit can goi ra  cot      

    if (tam == 0x8000) //goi bit cao ra truoc(bit o cot thu 8 truoc)
    {
      DS_1 = 1; // cho LED sang COT =1
    } else {
      DS_1 = 0; //cho LED tat COT =0
    }
    //tao xung dich du lieu   
    SH_CP_1 = 1;
    SH_CP_1 = 0;
  }
  //tao xung chot du lieu
  ST_CP_1 = 1;
  ST_CP_1 = 0;
}

void DISPLAY_1(unsigned char d[8], unsigned char r[16]) {
  unsigned char j;
  for (j = 0; j < 8; j++) {
    r[j] = d[j];
  }
}

void DISPLAY_2(unsigned char d[8], unsigned char r[16]) {
  unsigned char j;
  for (j = 0; j < 8; j++) {
    r[j + 8] = d[j];
  }
}