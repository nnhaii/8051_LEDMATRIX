#ifndef _I2C_H_
#define _I2C_H_

void I2C_time_start();
void I2C_time_stop();
unsigned char I2C_write(unsigned char dat);
unsigned char I2C_read(void);

#endif /* _I2C_H_ */
