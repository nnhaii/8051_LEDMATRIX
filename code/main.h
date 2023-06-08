	/******************************************************************************
	* Ten tep:		delay.h
	* Tac gia:	 	Nguyen Nam Hai
	* Ngay:				01-04-2023
	******************************************************************************/
#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <math.h>
#include <regx52.h>
#include <delay.h>

unsigned char code so[10][8] = {
{0xFF,0x83,0x01,0x6D,0x75,0x01,0x83,0xFF},//0
{0xFF,0x7F,0x77,0x01,0x01,0x7F,0x7F,0xFF},//1
{0xFF,0x3B,0x19,0x5D,0x6D,0x61,0x73,0xFF},//2
{0xFF,0xBB,0x39,0x6D,0x6D,0x01,0x93,0xFF},//3
{0xFF,0xCF,0xD7,0xDB,0x01,0x01,0xDF,0xFF},//4
{0xFF,0xB1,0x31,0x75,0x75,0x05,0x8D,0xFF},//5
{0xFF,0x83,0x01,0x6D,0x6D,0x09,0x9B,0xFF},//6
{0xFF,0xF9,0xF9,0x1D,0x05,0xE1,0xF9,0xFF},//7
{0xFF,0x93,0x01,0x6D,0x6D,0x01,0x93,0xFF},//8
{0xFF,0xB3,0x21,0x6D,0x6D,0x01,0x83,0xFF},//9
  };
#endif
