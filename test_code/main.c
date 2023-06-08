/*==========================//=================================================
  * Ten Tep      :        main.c
  * Tac Gia      :        Nguyen Nam Hai
  * Ngay         :        01-04-2023
  * Tom Tat      :        Chuong trinh dieu khien Led matrix.
==========================//=================================================*/
//===========================khai bao cac thu vien can su dung==============//
#include<main.h>
//===========================khia bao cac ham can su dung=================//
void Send_data_cot(unsigned int _data);
//===========================dinh nghia cac chan vao ra======================//
sbit SH_CP=P0^0;	//dinh nghia chan SH_CP o P0^0
sbit DS=P0^1;			//dinh nghia chan DS o P0^1
sbit ST_CP=P0^2;	//dinh nghia chan ST_CP o P0^2
//============================khai bao bien va hang==========================//
unsigned char a[16]= { 0xFF,0x01,0x00,0xEE,0xEE,0x00,0x01,0xFF,//ma chu A voi LED sang muc 0(hang muc 0, cot muc 1)
                     0xFF,0x00,0x76,0x76,0x76,0x76,0x76,0xFF   //ma chu E voi LED sang muc 0(hang muc 0, cot muc 1)
                     };
unsigned int b[16]= {0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
                      0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000
                      };//ma qu�t COT : C1 den C16, COT nao o gia tri =1 th� COT do duoc s�ng.
unsigned char i=0,k=0,j=0;
//============================HAM MAIN=======================================//
int main()
	{
			while(1)
				{
             for(i=0;i<16;i++)//quet COT thu 1 den thu 16, cho COT=0 roi goi du lieu ra cot do
                 {
                    P2=a[i];      // goi du kieu ra hang 1->8
                    Send_data_cot(b[i]); //quet cot
										delay_ms(1);       //thoi gian quet
                    Send_data_cot(0x0000);//tat het led chong lem
                 }
				}
	}
/*===========================================================================
	*Chuc nang: ham qu�t COT: goi du lieu ra COT tat/mo LED
							Khi goi du lieu 8 bit ra 1 h�ng th� goi du ieu ra cot de quet LED
	*Tham bien: _data: du lieu goi ra 74HC595
==============================================================================*/
void Send_data_cot(unsigned int _data)
{
unsigned char n;
unsigned int tam;
 
         ST_CP=0;//cho chan ST cua 74HC595 xuong muc 0
         SH_CP=0;//cho chan SH cua 74HC595 xuong muc 0
         DS=0;	//cho chan DS cua 74HC595 xuong muc 0
  for(n=0;n<16;n++)//goi 16 bit lan luoc ra 16 cot
   {
				tam=_data&0x8000;
       _data = _data<<1;//dich trai 1 bit de goi bit can goi ra  cot      
      
      if(tam==0x8000)//goi bit cao ra truoc(bit o cot thu 8 truoc)
      {
        DS=1;// cho LED sang COT =1
      }
      else                                 
     {
        DS=0;//cho LED tat COT =0
     }
      //tao xung dich du lieu   
      SH_CP=1;
      SH_CP=0;  
   }
    //tao xung chot du lieu
      ST_CP=1;
      ST_CP=0;  
}