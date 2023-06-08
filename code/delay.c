  /******************************************************************************
  * Ten tep:		delay.c
  * Tac gia:	 	Nguyen Nam Hai
  * Ngay:				01-04-2023
  ******************************************************************************/
#include <delay.h>
/*
 Tan so hoat dong cua vi dieu khien=Fosc(tan so dao song thach anh)/12=>chu ky Tosc=12/Fosc
 Chon tan so thach anh=12MHz=12*10^6 Hz
  =>chu ky may (chu ky hoat dong cua vi dieu khien) la  12/(12*10^6 Hz)=1/(10^6)s = 1us
	mot vong for khoang 8 chu ky may nen = 8*1 = 8us
	=> delay_ms(1) = 125*8 = 1000uS 
*/
/*================================================
*Chuc nang: tao tre ms
*Tham so: Time la gia tri can tan tre, gia tri 16 bit
*Gia tri tra ve: Khong co
=================================================*/
void delay_ms(unsigned int Time)
{
	unsigned int i,j;
	for(i=0;i<Time;i++)
	{
		for(j=0;j<125;j++);
	}
}
/*================================================
*Chuc nang: tao tre us
*Tham so: Time la gia tri can tan tre, gia tri 16 bit
*Gia tri tra ve: Khong co
=================================================*/
/*
void delay_us(unsigned int Time)
{
	while((--Time)!=0);
} 
*/
