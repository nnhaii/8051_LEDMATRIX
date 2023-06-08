
#include "ds1307.h"
#include "i2c.h"

unsigned char sec, min, hour, day, month, year;

void DS1307_Write(unsigned char addr, unsigned char dat) {
  unsigned int temp;
  temp = dat; /*HEX to BCD*/
  dat = (((dat / 10) * 16) | (temp % 10)); /*for Led 7seg*/
  I2C_time_start(); /* time_start i2c bus */
  I2C_write(0XD0); /* Connect to DS1307 */
  I2C_write(addr); /* Requetime_5 RAM address on DS1307 */
  I2C_write(dat);
  I2C_time_stop();
}
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
void DS1307_Set() {
  //Ghi du lieu ngay gio vao DS1307
  DS1307_Write(DS1307_SEC, sec);
  DS1307_Write(DS1307_MIN, min);
  DS1307_Write(DS1307_HOUR, hour);
  DS1307_Write(DS1307_DATE, day);
  DS1307_Write(DS1307_MONTH, month);
  DS1307_Write(DS1307_YEAR, year);
}
void DS1307_GetTime() {
  //Doc du lieu gio tu DS1307
  hour = DS1307_Read(DS1307_HOUR);
  min = DS1307_Read(DS1307_MIN);
  sec = DS1307_Read(DS1307_SEC);
}

void DS1307_GetDate() {
  //Doc du lieu ngay tu DS1307
  day = DS1307_Read(DS1307_DATE);
  month = DS1307_Read(DS1307_MONTH);
  year = DS1307_Read(DS1307_YEAR);
} //End code DS1307