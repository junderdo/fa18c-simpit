/* 
 * @description ssd1305 controller 
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 */

#include <SPI.h>
#include <Wire.h>

#include <stdio.h>
#include "ssd1305.h"

// images
#include "images/boot-f-18-c/boot-seq-1.c"
#include "images/boot-f-18-c/boot-seq-2.c"
#include "images/boot-f-18-c/boot-seq-3.c"
#include "images/boot-f-18-c/boot-seq-4.c"
#include "images/boot-f-18-c/boot-seq-5.c"
#include "images/boot-f-18-c/boot-seq-6.c"
#include "images/boot-f-18-c/boot-seq-7.c"
#include "images/boot-f-18-c/boot-seq-8.c"
#include "images/boot-f-18-c/boot-seq-9.c"
#include "images/boot-f-18-c/boot-seq-10.c"
#include "images/boot-f-18-c/boot-seq-11.c"
#include "images/boot-f-18-c/boot-seq-12.c"
#include "images/boot-f-18-c/boot-seq-13.c"
#include "images/boot-f-18-c/boot-seq-14.c"
#include "images/boot-f-18-c/boot-seq-15.c"
#include "images/boot-f-18-c/boot-seq-16.c"
#include "images/boot-f-18-c/boot-seq-17.c"
#include "images/boot-f-18-c/boot-seq-18.c"
#include "images/boot-f-18-c/boot-seq-19.c"
#include "images/boot-f-18-c/boot-seq-20.c"
#include "images/boot-f-18-c/boot-seq-21.c"

const uint8_t Font1612[11][32] PROGMEM =
{
  { 0x00, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C,
    0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00
  },/*"0",0*/
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x30, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },/*"1",1*/
  { 0x00, 0x00, 0x39, 0xFC, 0x39, 0xFC, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C,
    0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x3F, 0x8C, 0x3F, 0x8C, 0x00, 0x00
  },/*"2",2*/
  { 0x00, 0x00, 0x38, 0x1C, 0x38, 0x1C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C,
    0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00
  },/*"3",3*/
  { 0x00, 0x00, 0x3F, 0x80, 0x3F, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80,
    0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00
  },/*"4",4*/
  { 0x00, 0x00, 0x3F, 0x8C, 0x3F, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C,
    0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0xFC, 0x31, 0xFC, 0x00, 0x00
  },/*"5",5*/
  { 0x00, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C,
    0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0xFC, 0x31, 0xFC, 0x00, 0x00
  },/*"6",6*/
  { 0x00, 0x00, 0x38, 0x00, 0x38, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00,
    0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00
  },/*"7",7*/
  { 0x00, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C,
    0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00
  },/*"8",8*/
  { 0x00, 0x00, 0x3F, 0x9C, 0x3F, 0x9C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C,
    0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x31, 0x8C, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00
  },/*"9",9*/
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x30,
    0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },/*":",10*/
};

const uint8_t Font1206[95][12] PROGMEM = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*" ",0*/
  {0x00, 0x00, 0x00, 0x00, 0x3F, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"!",1*/
  {0x00, 0x00, 0x30, 0x00, 0x40, 0x00, 0x30, 0x00, 0x40, 0x00, 0x00, 0x00}, /*""",2*/
  {0x09, 0x00, 0x0B, 0xC0, 0x3D, 0x00, 0x0B, 0xC0, 0x3D, 0x00, 0x09, 0x00}, /*"#",3*/
  {0x18, 0xC0, 0x24, 0x40, 0x7F, 0xE0, 0x22, 0x40, 0x31, 0x80, 0x00, 0x00}, /*"$",4*/
  {0x18, 0x00, 0x24, 0xC0, 0x1B, 0x00, 0x0D, 0x80, 0x32, 0x40, 0x01, 0x80}, /*"%",5*/
  {0x03, 0x80, 0x1C, 0x40, 0x27, 0x40, 0x1C, 0x80, 0x07, 0x40, 0x00, 0x40}, /*"&",6*/
  {0x10, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"'",7*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x20, 0x40, 0x40, 0x20}, /*"(",8*/
  {0x00, 0x00, 0x40, 0x20, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00}, /*")",9*/
  {0x09, 0x00, 0x06, 0x00, 0x1F, 0x80, 0x06, 0x00, 0x09, 0x00, 0x00, 0x00}, /*"*",10*/
  {0x04, 0x00, 0x04, 0x00, 0x3F, 0x80, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00}, /*"+",11*/
  {0x00, 0x10, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*",",12*/
  {0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00}, /*"-",13*/
  {0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*".",14*/
  {0x00, 0x20, 0x01, 0xC0, 0x06, 0x00, 0x38, 0x00, 0x40, 0x00, 0x00, 0x00}, /*"/",15*/
  {0x1F, 0x80, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"0",16*/
  {0x00, 0x00, 0x10, 0x40, 0x3F, 0xC0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00}, /*"1",17*/
  {0x18, 0xC0, 0x21, 0x40, 0x22, 0x40, 0x24, 0x40, 0x18, 0x40, 0x00, 0x00}, /*"2",18*/
  {0x10, 0x80, 0x20, 0x40, 0x24, 0x40, 0x24, 0x40, 0x1B, 0x80, 0x00, 0x00}, /*"3",19*/
  {0x02, 0x00, 0x0D, 0x00, 0x11, 0x00, 0x3F, 0xC0, 0x01, 0x40, 0x00, 0x00}, /*"4",20*/
  {0x3C, 0x80, 0x24, 0x40, 0x24, 0x40, 0x24, 0x40, 0x23, 0x80, 0x00, 0x00}, /*"5",21*/
  {0x1F, 0x80, 0x24, 0x40, 0x24, 0x40, 0x34, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"6",22*/
  {0x30, 0x00, 0x20, 0x00, 0x27, 0xC0, 0x38, 0x00, 0x20, 0x00, 0x00, 0x00}, /*"7",23*/
  {0x1B, 0x80, 0x24, 0x40, 0x24, 0x40, 0x24, 0x40, 0x1B, 0x80, 0x00, 0x00}, /*"8",24*/
  {0x1C, 0x00, 0x22, 0xC0, 0x22, 0x40, 0x22, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"9",25*/
  {0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*":",26*/
  {0x00, 0x00, 0x00, 0x00, 0x04, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*";",27*/
  {0x00, 0x00, 0x04, 0x00, 0x0A, 0x00, 0x11, 0x00, 0x20, 0x80, 0x40, 0x40}, /*"<",28*/
  {0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x00, 0x00, 0x00}, /*"=",29*/
  {0x00, 0x00, 0x40, 0x40, 0x20, 0x80, 0x11, 0x00, 0x0A, 0x00, 0x04, 0x00}, /*">",30*/
  {0x18, 0x00, 0x20, 0x00, 0x23, 0x40, 0x24, 0x00, 0x18, 0x00, 0x00, 0x00}, /*"?",31*/
  {0x1F, 0x80, 0x20, 0x40, 0x27, 0x40, 0x29, 0x40, 0x1F, 0x40, 0x00, 0x00}, /*"@",32*/
  {0x00, 0x40, 0x07, 0xC0, 0x39, 0x00, 0x0F, 0x00, 0x01, 0xC0, 0x00, 0x40}, /*"A",33*/
  {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x24, 0x40, 0x1B, 0x80, 0x00, 0x00}, /*"B",34*/
  {0x1F, 0x80, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x30, 0x80, 0x00, 0x00}, /*"C",35*/
  {0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"D",36*/
  {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x2E, 0x40, 0x30, 0xC0, 0x00, 0x00}, /*"E",37*/
  {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x2E, 0x00, 0x30, 0x00, 0x00, 0x00}, /*"F",38*/
  {0x0F, 0x00, 0x10, 0x80, 0x20, 0x40, 0x22, 0x40, 0x33, 0x80, 0x02, 0x00}, /*"G",39*/
  {0x20, 0x40, 0x3F, 0xC0, 0x04, 0x00, 0x04, 0x00, 0x3F, 0xC0, 0x20, 0x40}, /*"H",40*/
  {0x20, 0x40, 0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x20, 0x40, 0x00, 0x00}, /*"I",41*/
  {0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x3F, 0xC0, 0x20, 0x00, 0x20, 0x00}, /*"J",42*/
  {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x0B, 0x00, 0x30, 0xC0, 0x20, 0x40}, /*"K",43*/
  {0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0xC0}, /*"L",44*/
  {0x3F, 0xC0, 0x3C, 0x00, 0x03, 0xC0, 0x3C, 0x00, 0x3F, 0xC0, 0x00, 0x00}, /*"M",45*/
  {0x20, 0x40, 0x3F, 0xC0, 0x0C, 0x40, 0x23, 0x00, 0x3F, 0xC0, 0x20, 0x00}, /*"N",46*/
  {0x1F, 0x80, 0x20, 0x40, 0x20, 0x40, 0x20, 0x40, 0x1F, 0x80, 0x00, 0x00}, /*"O",47*/
  {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x24, 0x00, 0x18, 0x00, 0x00, 0x00}, /*"P",48*/
  {0x1F, 0x80, 0x21, 0x40, 0x21, 0x40, 0x20, 0xE0, 0x1F, 0xA0, 0x00, 0x00}, /*"Q",49*/
  {0x20, 0x40, 0x3F, 0xC0, 0x24, 0x40, 0x26, 0x00, 0x19, 0xC0, 0x00, 0x40}, /*"R",50*/
  {0x18, 0xC0, 0x24, 0x40, 0x24, 0x40, 0x22, 0x40, 0x31, 0x80, 0x00, 0x00}, /*"S",51*/
  {0x30, 0x00, 0x20, 0x40, 0x3F, 0xC0, 0x20, 0x40, 0x30, 0x00, 0x00, 0x00}, /*"T",52*/
  {0x20, 0x00, 0x3F, 0x80, 0x00, 0x40, 0x00, 0x40, 0x3F, 0x80, 0x20, 0x00}, /*"U",53*/
  {0x20, 0x00, 0x3E, 0x00, 0x01, 0xC0, 0x07, 0x00, 0x38, 0x00, 0x20, 0x00}, /*"V",54*/
  {0x38, 0x00, 0x07, 0xC0, 0x3C, 0x00, 0x07, 0xC0, 0x38, 0x00, 0x00, 0x00}, /*"W",55*/
  {0x20, 0x40, 0x39, 0xC0, 0x06, 0x00, 0x39, 0xC0, 0x20, 0x40, 0x00, 0x00}, /*"X",56*/
  {0x20, 0x00, 0x38, 0x40, 0x07, 0xC0, 0x38, 0x40, 0x20, 0x00, 0x00, 0x00}, /*"Y",57*/
  {0x30, 0x40, 0x21, 0xC0, 0x26, 0x40, 0x38, 0x40, 0x20, 0xC0, 0x00, 0x00}, /*"Z",58*/
  {0x00, 0x00, 0x00, 0x00, 0x7F, 0xE0, 0x40, 0x20, 0x40, 0x20, 0x00, 0x00}, /*"[",59*/
  {0x00, 0x00, 0x70, 0x00, 0x0C, 0x00, 0x03, 0x80, 0x00, 0x40, 0x00, 0x00}, /*"\",60*/
  {0x00, 0x00, 0x40, 0x20, 0x40, 0x20, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00}, /*"]",61*/
  {0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"^",62*/
  {0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10}, /*"_",63*/
  {0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"`",64*/
  {0x00, 0x00, 0x02, 0x80, 0x05, 0x40, 0x05, 0x40, 0x03, 0xC0, 0x00, 0x40}, /*"a",65*/
  {0x20, 0x00, 0x3F, 0xC0, 0x04, 0x40, 0x04, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"b",66*/
  {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x04, 0x40, 0x06, 0x40, 0x00, 0x00}, /*"c",67*/
  {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x24, 0x40, 0x3F, 0xC0, 0x00, 0x40}, /*"d",68*/
  {0x00, 0x00, 0x03, 0x80, 0x05, 0x40, 0x05, 0x40, 0x03, 0x40, 0x00, 0x00}, /*"e",69*/
  {0x00, 0x00, 0x04, 0x40, 0x1F, 0xC0, 0x24, 0x40, 0x24, 0x40, 0x20, 0x00}, /*"f",70*/
  {0x00, 0x00, 0x02, 0xE0, 0x05, 0x50, 0x05, 0x50, 0x06, 0x50, 0x04, 0x20}, /*"g",71*/
  {0x20, 0x40, 0x3F, 0xC0, 0x04, 0x40, 0x04, 0x00, 0x03, 0xC0, 0x00, 0x40}, /*"h",72*/
  {0x00, 0x00, 0x04, 0x40, 0x27, 0xC0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00}, /*"i",73*/
  {0x00, 0x10, 0x00, 0x10, 0x04, 0x10, 0x27, 0xE0, 0x00, 0x00, 0x00, 0x00}, /*"j",74*/
  {0x20, 0x40, 0x3F, 0xC0, 0x01, 0x40, 0x07, 0x00, 0x04, 0xC0, 0x04, 0x40}, /*"k",75*/
  {0x20, 0x40, 0x20, 0x40, 0x3F, 0xC0, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00}, /*"l",76*/
  {0x07, 0xC0, 0x04, 0x00, 0x07, 0xC0, 0x04, 0x00, 0x03, 0xC0, 0x00, 0x00}, /*"m",77*/
  {0x04, 0x40, 0x07, 0xC0, 0x04, 0x40, 0x04, 0x00, 0x03, 0xC0, 0x00, 0x40}, /*"n",78*/
  {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x04, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"o",79*/
  {0x04, 0x10, 0x07, 0xF0, 0x04, 0x50, 0x04, 0x40, 0x03, 0x80, 0x00, 0x00}, /*"p",80*/
  {0x00, 0x00, 0x03, 0x80, 0x04, 0x40, 0x04, 0x50, 0x07, 0xF0, 0x00, 0x10}, /*"q",81*/
  {0x04, 0x40, 0x07, 0xC0, 0x02, 0x40, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00}, /*"r",82*/
  {0x00, 0x00, 0x06, 0x40, 0x05, 0x40, 0x05, 0x40, 0x04, 0xC0, 0x00, 0x00}, /*"s",83*/
  {0x00, 0x00, 0x04, 0x00, 0x1F, 0x80, 0x04, 0x40, 0x00, 0x40, 0x00, 0x00}, /*"t",84*/
  {0x04, 0x00, 0x07, 0x80, 0x00, 0x40, 0x04, 0x40, 0x07, 0xC0, 0x00, 0x40}, /*"u",85*/
  {0x04, 0x00, 0x07, 0x00, 0x04, 0xC0, 0x01, 0x80, 0x06, 0x00, 0x04, 0x00}, /*"v",86*/
  {0x06, 0x00, 0x01, 0xC0, 0x07, 0x00, 0x01, 0xC0, 0x06, 0x00, 0x00, 0x00}, /*"w",87*/
  {0x04, 0x40, 0x06, 0xC0, 0x01, 0x00, 0x06, 0xC0, 0x04, 0x40, 0x00, 0x00}, /*"x",88*/
  {0x04, 0x10, 0x07, 0x10, 0x04, 0xE0, 0x01, 0x80, 0x06, 0x00, 0x04, 0x00}, /*"y",89*/
  {0x00, 0x00, 0x04, 0x40, 0x05, 0xC0, 0x06, 0x40, 0x04, 0x40, 0x00, 0x00}, /*"z",90*/
  {0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x7B, 0xE0, 0x40, 0x20, 0x00, 0x00}, /*"{",91*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00}, /*"|",92*/
  {0x00, 0x00, 0x40, 0x20, 0x7B, 0xE0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"}",93*/
  {0x40, 0x00, 0x80, 0x00, 0x40, 0x00, 0x20, 0x00, 0x20, 0x00, 0x40, 0x00}, /*"~",94*/
};

const uint8_t Font1608[95][16] PROGMEM = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*" ",0*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xCC, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"!",1*/
  {0x00, 0x00, 0x08, 0x00, 0x30, 0x00, 0x60, 0x00, 0x08, 0x00, 0x30, 0x00, 0x60, 0x00, 0x00, 0x00}, /*""",2*/
  {0x02, 0x20, 0x03, 0xFC, 0x1E, 0x20, 0x02, 0x20, 0x03, 0xFC, 0x1E, 0x20, 0x02, 0x20, 0x00, 0x00}, /*"#",3*/
  {0x00, 0x00, 0x0E, 0x18, 0x11, 0x04, 0x3F, 0xFF, 0x10, 0x84, 0x0C, 0x78, 0x00, 0x00, 0x00, 0x00}, /*"$",4*/
  {0x0F, 0x00, 0x10, 0x84, 0x0F, 0x38, 0x00, 0xC0, 0x07, 0x78, 0x18, 0x84, 0x00, 0x78, 0x00, 0x00}, /*"%",5*/
  {0x00, 0x78, 0x0F, 0x84, 0x10, 0xC4, 0x11, 0x24, 0x0E, 0x98, 0x00, 0xE4, 0x00, 0x84, 0x00, 0x08}, /*"&",6*/
  {0x08, 0x00, 0x68, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"'",7*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x18, 0x18, 0x20, 0x04, 0x40, 0x02, 0x00, 0x00}, /*"(",8*/
  {0x00, 0x00, 0x40, 0x02, 0x20, 0x04, 0x18, 0x18, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*")",9*/
  {0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x0F, 0xF0, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x00, 0x00}, /*"*",10*/
  {0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x0F, 0xF8, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00}, /*"+",11*/
  {0x00, 0x01, 0x00, 0x0D, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*",",12*/
  {0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80}, /*"-",13*/
  {0x00, 0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*".",14*/
  {0x00, 0x00, 0x00, 0x06, 0x00, 0x18, 0x00, 0x60, 0x01, 0x80, 0x06, 0x00, 0x18, 0x00, 0x20, 0x00}, /*"/",15*/
  {0x00, 0x00, 0x07, 0xF0, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x08, 0x08, 0x07, 0xF0, 0x00, 0x00}, /*"0",16*/
  {0x00, 0x00, 0x08, 0x04, 0x08, 0x04, 0x1F, 0xFC, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"1",17*/
  {0x00, 0x00, 0x0E, 0x0C, 0x10, 0x14, 0x10, 0x24, 0x10, 0x44, 0x11, 0x84, 0x0E, 0x0C, 0x00, 0x00}, /*"2",18*/
  {0x00, 0x00, 0x0C, 0x18, 0x10, 0x04, 0x11, 0x04, 0x11, 0x04, 0x12, 0x88, 0x0C, 0x70, 0x00, 0x00}, /*"3",19*/
  {0x00, 0x00, 0x00, 0xE0, 0x03, 0x20, 0x04, 0x24, 0x08, 0x24, 0x1F, 0xFC, 0x00, 0x24, 0x00, 0x00}, /*"4",20*/
  {0x00, 0x00, 0x1F, 0x98, 0x10, 0x84, 0x11, 0x04, 0x11, 0x04, 0x10, 0x88, 0x10, 0x70, 0x00, 0x00}, /*"5",21*/
  {0x00, 0x00, 0x07, 0xF0, 0x08, 0x88, 0x11, 0x04, 0x11, 0x04, 0x18, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"6",22*/
  {0x00, 0x00, 0x1C, 0x00, 0x10, 0x00, 0x10, 0xFC, 0x13, 0x00, 0x1C, 0x00, 0x10, 0x00, 0x00, 0x00}, /*"7",23*/
  {0x00, 0x00, 0x0E, 0x38, 0x11, 0x44, 0x10, 0x84, 0x10, 0x84, 0x11, 0x44, 0x0E, 0x38, 0x00, 0x00}, /*"8",24*/
  {0x00, 0x00, 0x07, 0x00, 0x08, 0x8C, 0x10, 0x44, 0x10, 0x44, 0x08, 0x88, 0x07, 0xF0, 0x00, 0x00}, /*"9",25*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*":",26*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*";",27*/
  {0x00, 0x00, 0x00, 0x80, 0x01, 0x40, 0x02, 0x20, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 0x00, 0x00}, /*"<",28*/
  {0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x00, 0x00}, /*"=",29*/
  {0x00, 0x00, 0x10, 0x04, 0x08, 0x08, 0x04, 0x10, 0x02, 0x20, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00}, /*">",30*/
  {0x00, 0x00, 0x0E, 0x00, 0x12, 0x00, 0x10, 0x0C, 0x10, 0x6C, 0x10, 0x80, 0x0F, 0x00, 0x00, 0x00}, /*"?",31*/
  {0x03, 0xE0, 0x0C, 0x18, 0x13, 0xE4, 0x14, 0x24, 0x17, 0xC4, 0x08, 0x28, 0x07, 0xD0, 0x00, 0x00}, /*"@",32*/
  {0x00, 0x04, 0x00, 0x3C, 0x03, 0xC4, 0x1C, 0x40, 0x07, 0x40, 0x00, 0xE4, 0x00, 0x1C, 0x00, 0x04}, /*"A",33*/
  {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x04, 0x11, 0x04, 0x0E, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"B",34*/
  {0x03, 0xE0, 0x0C, 0x18, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x10, 0x08, 0x1C, 0x10, 0x00, 0x00}, /*"C",35*/
  {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x08, 0x08, 0x07, 0xF0, 0x00, 0x00}, /*"D",36*/
  {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x04, 0x17, 0xC4, 0x10, 0x04, 0x08, 0x18, 0x00, 0x00}, /*"E",37*/
  {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x00, 0x17, 0xC0, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00}, /*"F",38*/
  {0x03, 0xE0, 0x0C, 0x18, 0x10, 0x04, 0x10, 0x04, 0x10, 0x44, 0x1C, 0x78, 0x00, 0x40, 0x00, 0x00}, /*"G",39*/
  {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x84, 0x00, 0x80, 0x00, 0x80, 0x10, 0x84, 0x1F, 0xFC, 0x10, 0x04}, /*"H",40*/
  {0x00, 0x00, 0x10, 0x04, 0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x10, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"I",41*/
  {0x00, 0x03, 0x00, 0x01, 0x10, 0x01, 0x10, 0x01, 0x1F, 0xFE, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00}, /*"J",42*/
  {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x03, 0x80, 0x14, 0x64, 0x18, 0x1C, 0x10, 0x04, 0x00, 0x00}, /*"K",43*/
  {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x0C, 0x00, 0x00}, /*"L",44*/
  {0x10, 0x04, 0x1F, 0xFC, 0x1F, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x1F, 0xFC, 0x10, 0x04, 0x00, 0x00}, /*"M",45*/
  {0x10, 0x04, 0x1F, 0xFC, 0x0C, 0x04, 0x03, 0x00, 0x00, 0xE0, 0x10, 0x18, 0x1F, 0xFC, 0x10, 0x00}, /*"N",46*/
  {0x07, 0xF0, 0x08, 0x08, 0x10, 0x04, 0x10, 0x04, 0x10, 0x04, 0x08, 0x08, 0x07, 0xF0, 0x00, 0x00}, /*"O",47*/
  {0x10, 0x04, 0x1F, 0xFC, 0x10, 0x84, 0x10, 0x80, 0x10, 0x80, 0x10, 0x80, 0x0F, 0x00, 0x00, 0x00}, /*"P",48*/
  {0x07, 0xF0, 0x08, 0x18, 0x10, 0x24, 0x10, 0x24, 0x10, 0x1C, 0x08, 0x0A, 0x07, 0xF2, 0x00, 0x00}, /*"Q",49*/
  {0x10, 0x04, 0x1F, 0xFC, 0x11, 0x04, 0x11, 0x00, 0x11, 0xC0, 0x11, 0x30, 0x0E, 0x0C, 0x00, 0x04}, /*"R",50*/
  {0x00, 0x00, 0x0E, 0x1C, 0x11, 0x04, 0x10, 0x84, 0x10, 0x84, 0x10, 0x44, 0x1C, 0x38, 0x00, 0x00}, /*"S",51*/
  {0x18, 0x00, 0x10, 0x00, 0x10, 0x04, 0x1F, 0xFC, 0x10, 0x04, 0x10, 0x00, 0x18, 0x00, 0x00, 0x00}, /*"T",52*/
  {0x10, 0x00, 0x1F, 0xF8, 0x10, 0x04, 0x00, 0x04, 0x00, 0x04, 0x10, 0x04, 0x1F, 0xF8, 0x10, 0x00}, /*"U",53*/
  {0x10, 0x00, 0x1E, 0x00, 0x11, 0xE0, 0x00, 0x1C, 0x00, 0x70, 0x13, 0x80, 0x1C, 0x00, 0x10, 0x00}, /*"V",54*/
  {0x1F, 0xC0, 0x10, 0x3C, 0x00, 0xE0, 0x1F, 0x00, 0x00, 0xE0, 0x10, 0x3C, 0x1F, 0xC0, 0x00, 0x00}, /*"W",55*/
  {0x10, 0x04, 0x18, 0x0C, 0x16, 0x34, 0x01, 0xC0, 0x01, 0xC0, 0x16, 0x34, 0x18, 0x0C, 0x10, 0x04}, /*"X",56*/
  {0x10, 0x00, 0x1C, 0x00, 0x13, 0x04, 0x00, 0xFC, 0x13, 0x04, 0x1C, 0x00, 0x10, 0x00, 0x00, 0x00}, /*"Y",57*/
  {0x08, 0x04, 0x10, 0x1C, 0x10, 0x64, 0x10, 0x84, 0x13, 0x04, 0x1C, 0x04, 0x10, 0x18, 0x00, 0x00}, /*"Z",58*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x00, 0x00}, /*"[",59*/
  {0x00, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x03, 0x80, 0x00, 0x60, 0x00, 0x1C, 0x00, 0x03, 0x00, 0x00}, /*"\",60*/
  {0x00, 0x00, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"]",61*/
  {0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00}, /*"^",62*/
  {0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01}, /*"_",63*/
  {0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"`",64*/
  {0x00, 0x00, 0x00, 0x98, 0x01, 0x24, 0x01, 0x44, 0x01, 0x44, 0x01, 0x44, 0x00, 0xFC, 0x00, 0x04}, /*"a",65*/
  {0x10, 0x00, 0x1F, 0xFC, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x00, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"b",66*/
  {0x00, 0x00, 0x00, 0x70, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x00, 0x88, 0x00, 0x00}, /*"c",67*/
  {0x00, 0x00, 0x00, 0x70, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x11, 0x08, 0x1F, 0xFC, 0x00, 0x04}, /*"d",68*/
  {0x00, 0x00, 0x00, 0xF8, 0x01, 0x44, 0x01, 0x44, 0x01, 0x44, 0x01, 0x44, 0x00, 0xC8, 0x00, 0x00}, /*"e",69*/
  {0x00, 0x00, 0x01, 0x04, 0x01, 0x04, 0x0F, 0xFC, 0x11, 0x04, 0x11, 0x04, 0x11, 0x00, 0x18, 0x00}, /*"f",70*/
  {0x00, 0x00, 0x00, 0xD6, 0x01, 0x29, 0x01, 0x29, 0x01, 0x29, 0x01, 0xC9, 0x01, 0x06, 0x00, 0x00}, /*"g",71*/
  {0x10, 0x04, 0x1F, 0xFC, 0x00, 0x84, 0x01, 0x00, 0x01, 0x00, 0x01, 0x04, 0x00, 0xFC, 0x00, 0x04}, /*"h",72*/
  {0x00, 0x00, 0x01, 0x04, 0x19, 0x04, 0x19, 0xFC, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"i",73*/
  {0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x01, 0x01, 0x19, 0x01, 0x19, 0xFE, 0x00, 0x00, 0x00, 0x00}, /*"j",74*/
  {0x10, 0x04, 0x1F, 0xFC, 0x00, 0x24, 0x00, 0x40, 0x01, 0xB4, 0x01, 0x0C, 0x01, 0x04, 0x00, 0x00}, /*"k",75*/
  {0x00, 0x00, 0x10, 0x04, 0x10, 0x04, 0x1F, 0xFC, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"l",76*/
  {0x01, 0x04, 0x01, 0xFC, 0x01, 0x04, 0x01, 0x00, 0x01, 0xFC, 0x01, 0x04, 0x01, 0x00, 0x00, 0xFC}, /*"m",77*/
  {0x01, 0x04, 0x01, 0xFC, 0x00, 0x84, 0x01, 0x00, 0x01, 0x00, 0x01, 0x04, 0x00, 0xFC, 0x00, 0x04}, /*"n",78*/
  {0x00, 0x00, 0x00, 0xF8, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x00, 0xF8, 0x00, 0x00}, /*"o",79*/
  {0x01, 0x01, 0x01, 0xFF, 0x00, 0x85, 0x01, 0x04, 0x01, 0x04, 0x00, 0x88, 0x00, 0x70, 0x00, 0x00}, /*"p",80*/
  {0x00, 0x00, 0x00, 0x70, 0x00, 0x88, 0x01, 0x04, 0x01, 0x04, 0x01, 0x05, 0x01, 0xFF, 0x00, 0x01}, /*"q",81*/
  {0x01, 0x04, 0x01, 0x04, 0x01, 0xFC, 0x00, 0x84, 0x01, 0x04, 0x01, 0x00, 0x01, 0x80, 0x00, 0x00}, /*"r",82*/
  {0x00, 0x00, 0x00, 0xCC, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x24, 0x01, 0x98, 0x00, 0x00}, /*"s",83*/
  {0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x07, 0xF8, 0x01, 0x04, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00}, /*"t",84*/
  {0x01, 0x00, 0x01, 0xF8, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x01, 0x08, 0x01, 0xFC, 0x00, 0x04}, /*"u",85*/
  {0x01, 0x00, 0x01, 0x80, 0x01, 0x70, 0x00, 0x0C, 0x00, 0x10, 0x01, 0x60, 0x01, 0x80, 0x01, 0x00}, /*"v",86*/
  {0x01, 0xF0, 0x01, 0x0C, 0x00, 0x30, 0x01, 0xC0, 0x00, 0x30, 0x01, 0x0C, 0x01, 0xF0, 0x01, 0x00}, /*"w",87*/
  {0x00, 0x00, 0x01, 0x04, 0x01, 0x8C, 0x00, 0x74, 0x01, 0x70, 0x01, 0x8C, 0x01, 0x04, 0x00, 0x00}, /*"x",88*/
  {0x01, 0x01, 0x01, 0x81, 0x01, 0x71, 0x00, 0x0E, 0x00, 0x18, 0x01, 0x60, 0x01, 0x80, 0x01, 0x00}, /*"y",89*/
  {0x00, 0x00, 0x01, 0x84, 0x01, 0x0C, 0x01, 0x34, 0x01, 0x44, 0x01, 0x84, 0x01, 0x0C, 0x00, 0x00}, /*"z",90*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x3E, 0xFC, 0x40, 0x02, 0x40, 0x02}, /*"{",91*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"|",92*/
  {0x00, 0x00, 0x40, 0x02, 0x40, 0x02, 0x3E, 0xFC, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, /*"}",93*/
  {0x00, 0x00, 0x60, 0x00, 0x80, 0x00, 0x80, 0x00, 0x40, 0x00, 0x40, 0x00, 0x20, 0x00, 0x20, 0x00}, /*"~",94*/
};

const uint8_t Font3216[11][64] PROGMEM =
{
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, /*"0",0*/
    0x30, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x0C,
    0x30, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x0C,
    0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*"1",1*/
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x01, 0xFF, 0xFC, 0x3C, 0x01, 0xFF, 0xFC, /*"2",2*/
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x3F, 0xFF, 0x80, 0x0C, 0x3F, 0xFF, 0x80, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x3C, 0x38, 0x00, 0x00, 0x3C, /*"3",3*/
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x80, 0x00, 0x3F, 0xFF, 0x80, 0x00, /*"4",4*/
    0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00,
    0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00,
    0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x80, 0x3C, 0x3F, 0xFF, 0x80, 0x3C, /*"5",5*/
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x30, 0x01, 0xFF, 0xFC, 0x30, 0x01, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, /*"6",6*/
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x3C, 0x01, 0xFF, 0xFC, 0x3C, 0x01, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, /*"7",7*/
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, /*"8",8*/
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x80, 0x3C, 0x3F, 0xFF, 0x80, 0x3C, /*"9",9*/
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C, 0x30, 0x01, 0x80, 0x0C,
    0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*":",10*/
    0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x0C, 0x00, 0x00, 0x30,
    0x0C, 0x00, 0x00, 0x30, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
};
const uint8_t waveshare_ch[448] PROGMEM =
{
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XFF,0XF0,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XFF,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X1F,0XFF,0XFF,0X01,0XC6,0X1C,0X00,0X00,0X00,0X01,0XC0,0X00,
    0X00,0X00,0X1F,0XFF,0XDF,0X81,0XB6,0XDC,0X3F,0XFF,0XF8,0XFF,0XFF,0XC3,0XFF,0XFF,
    0X1F,0XFF,0X9F,0X83,0XB6,0XDF,0X3F,0XFF,0XF8,0XFF,0XFF,0XC3,0XFF,0XFF,0X1F,0XFF,
    0X1F,0XC7,0XB6,0XFF,0X00,0X38,0X00,0XFF,0XFF,0XC3,0XFF,0XFF,0X1F,0XFF,0X1F,0XE7,
    0X36,0XFF,0X3F,0XFF,0XF8,0XC1,0XC0,0XC0,0X00,0X1E,0X10,0XC7,0X19,0XE7,0X37,0XE0,
    0X3F,0XFF,0XF8,0XC1,0XC0,0XC0,0X00,0X3C,0X18,0XC6,0X38,0XF1,0XFF,0XC7,0X38,0X38,
    0X38,0XC1,0XC0,0XC0,0X00,0X78,0X18,0XC6,0X30,0XF1,0XBF,0XF6,0X3B,0X39,0XF8,0XC1,
    0XC0,0XC0,0X7F,0XF8,0X18,0X02,0X70,0X73,0X80,0X3E,0X3B,0XFB,0XB8,0XFF,0XFF,0XC0,
    0X7F,0XF0,0X1C,0X00,0X20,0X77,0XBF,0X9E,0X38,0X38,0X38,0XFF,0XFF,0XC0,0X7F,0XE0,
    0X1C,0X10,0X22,0X37,0XBF,0X9E,0X38,0XFB,0X38,0XFF,0XFF,0XC0,0X00,0XE0,0X1C,0X10,
    0X42,0X33,0X80,0X1E,0X3B,0XFB,0XF8,0XC1,0XC0,0XC0,0X00,0XE0,0X1E,0X30,0XC6,0X33,
    0XBF,0X9C,0X00,0X00,0X00,0XC1,0XC0,0XC7,0XFF,0XFF,0X1E,0X39,0X86,0X33,0XBF,0X9C,
    0X1F,0XFF,0XF8,0XC1,0XC0,0XC7,0XFF,0XFF,0X1E,0X39,0XCE,0X73,0XBF,0X8C,0X1F,0XFF,
    0XF8,0XC1,0XC1,0XC7,0XFF,0XFF,0X0F,0XFF,0XF8,0X73,0XB9,0X9C,0X00,0X00,0X38,0XFF,
    0XFF,0XC0,0X00,0XE0,0X0F,0XFF,0XF8,0X73,0XB9,0X9E,0X00,0X00,0X38,0XFF,0XFF,0XC0,
    0X00,0XE0,0X07,0XFF,0XF8,0XF3,0XB9,0X9E,0X1F,0XFF,0XF8,0XFF,0XFF,0X80,0X00,0XE0,
    0X03,0XFF,0XF9,0XF3,0XB9,0X9E,0X1F,0XFF,0XF8,0X01,0XC0,0X00,0X00,0XE0,0X03,0XFF,
    0XFB,0XF3,0XB9,0XBE,0X00,0X00,0X38,0X01,0XC0,0X03,0XFF,0XE0,0X01,0XFF,0XFF,0XF3,
    0XF9,0XFF,0X1F,0XFF,0XF8,0X01,0XFF,0XC3,0XFF,0XE0,0X00,0X7F,0XFF,0XF3,0XF9,0XF7,
    0X1F,0XFF,0XF8,0X00,0XFF,0XC3,0XFF,0XE0,0X00,0X1F,0XFF,0XF3,0X80,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const uint8_t Signal816[16] PROGMEM = //mobie signal
{
  0xFE, 0x02, 0x92, 0x0A, 0x54, 0x2A, 0x38, 0xAA, 0x12, 0xAA, 0x12, 0xAA, 0x12, 0xAA, 0x12, 0xAA
};

const uint8_t Msg816[16] PROGMEM =  //message
{
  0x1F, 0xF8, 0x10, 0x08, 0x18, 0x18, 0x14, 0x28, 0x13, 0xC8, 0x10, 0x08, 0x10, 0x08, 0x1F, 0xF8
};

const uint8_t Bat816[16] PROGMEM = //batery
{
  0x0F, 0xFE, 0x30, 0x02, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x30, 0x02, 0x0F, 0xFE
};

const uint8_t Bluetooth88[8] PROGMEM = // bluetooth
{
  0x18, 0x54, 0x32, 0x1C, 0x1C, 0x32, 0x54, 0x18
};

const uint8_t GPRS88[8] PROGMEM = //GPRS
{
  0xC3, 0x99, 0x24, 0x20, 0x2C, 0x24, 0x99, 0xC3
};

const uint8_t Alarm88[8] PROGMEM = //alram
{
  0xC3, 0xBD, 0x42, 0x52, 0x4E, 0x42, 0x3C, 0xC3
};

void command(uint8_t cmd) {
  digitalWrite(OLED_DC, LOW);
  SPIWrite(&cmd, 1);
}

void SPIWrite(uint8_t *buffer, int bufferLength) {
  int i;
  digitalWrite(OLED_CS, LOW);
  for (i = 0; i < bufferLength; i++) {
    SPI.transfer(buffer[i]);
  }
  digitalWrite(OLED_CS, HIGH);
}

void SSD1305_begin()
{

  pinMode(OLED_RST, OUTPUT);
  pinMode(OLED_DC, OUTPUT);
  pinMode(OLED_CS, OUTPUT);
  SPI.begin();

  SPI.setClockDivider(SPI_CLOCK_DIV128);

  digitalWrite(OLED_CS, LOW);
  digitalWrite(OLED_RST, HIGH);
  delay(10);
  digitalWrite(OLED_RST, LOW);
  delay(10);
  digitalWrite(OLED_RST, HIGH);
  
  command(0xAE);//--turn off oled panel
  command(0x04);//--turn off oled panel
  command(0x10);//--turn off oled panel
  command(0x40);//---set low column address
  command(0x81);//---set high column address
  command(0x80);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  command(0xA1);//--set contrast control register
  command(0xA6); // Set SEG Output Current Brightness
  command(0xA8);//--Set SEG/Column Mapping     0xa0×óÓÒ·´ÖÃ 0xa1Õý³£
  command(0x1F);//Set COM/Row Scan Direction   0xc0ÉÏÏÂ·´ÖÃ 0xc8Õý³£
  command(0xC8);//--set normal display
  command(0xD3);//--set multiplex ratio(1 to 64)
  command(0x00);//--1/64 duty
  command(0xD5);//-set display offset Shift Mapping RAM Counter (0x00~0x3F)
  command(0xF0);//-not offset
  command(0xd8);//--set display clock divide ratio/oscillator frequency
  command(0x05);//--set divide ratio, Set Clock as 100 Frames/Sec
  command(0xD9);//--set pre-charge period
  command(0xC2);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  command(0xDA);//--set com pins hardware configuration
  command(0x12);
  command(0xDB);//--set vcomh
  command(0x08);//Set VCOM Deselect Level
  command(0xAF);//-Set Page Addressing Mode (0x00/0x01/0x02)
}

uint8_t oled_buf[WIDTH * HEIGHT / 8];

void SSD1305_boot()
{
    /* display boot sequence image slideshow/video */
    SSD1305_begin();
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq1, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq2, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq3, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq4, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq5, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq6, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq7, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq8, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq9, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq10, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(500);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq11, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq12, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq13, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq14, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq15, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq16, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq17, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq18, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq19, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq20, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
    delay(100);
    SSD1305_clear(oled_buf);
    SSD1305_bitmap(0, 0, gImage_bootseq21, 128, 32, oled_buf);
    SSD1305_display(oled_buf);
}

void SSD1305_clear(uint8_t* buffer)
{
  int i;
  for (i = 0; i < WIDTH * HEIGHT / 8; i++)
  {
    buffer[i] = 0;
  }
}

void SSD1305_pixel(int x, int y, char color, uint8_t* buffer)
{
  if (x > WIDTH || y > HEIGHT)return ;
  if (color)
    buffer[x + (y / 8)*WIDTH] |= 1 << (y % 8);
  else
    buffer[x + (y / 8)*WIDTH] &= ~(1 << (y % 8));
}

void SSD1305_char1616(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer)
{
  uint8_t i, j;
  uint8_t chTemp = 0, y0 = y, chMode = 0;

  for (i = 0; i < 32; i++) {
    chTemp = pgm_read_byte(&Font1612[chChar - 0x30][i]);
    for (j = 0; j < 8; j++) {
      chMode = chTemp & 0x80 ? 1 : 0;
      SSD1305_pixel(x, y, chMode, buffer);
      chTemp <<= 1;
      y++;
      if ((y - y0) == 16) {
        y = y0;
        x++;
        break;
      }
    }
  }
}

void SSD1305_char(unsigned char x, unsigned char y, char acsii, char size, char mode, uint8_t* buffer)
{
  unsigned char i, j, y0 = y;
  char temp;
  unsigned char ch = acsii - ' ';
  for (i = 0; i < size; i++) {
    if (size == 12)
    {
      if (mode)temp = pgm_read_byte(&Font1206[ch][i]);
      else temp = ~pgm_read_byte(&Font1206[ch][i]);
    }
    else
    {
      if (mode)temp = pgm_read_byte(&Font1608[ch][i]);
      else temp = ~pgm_read_byte(&Font1608[ch][i]);
    }
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80) SSD1305_pixel(x, y, 1, buffer);
      else SSD1305_pixel(x, y, 0, buffer);
      temp <<= 1;
      y++;
      if ((y - y0) == size)
      {
        y = y0;
        x++;
        break;
      }
    }
  }
}

void SSD1305_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t* buffer)
{
  while (*pString != '\0') {
    if (x > (WIDTH - Size / 2)) {
      x = 0;
      y += Size;
      if (y > (HEIGHT - Size)) {
        y = x = 0;
      }
    }

    SSD1305_char(x, y, *pString, Size, Mode, buffer);
    x += Size / 2;
    pString++;
  }
}

void SSD1305_char3216(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer)
{
  uint8_t i, j;
  uint8_t chTemp = 0, y0 = y, chMode = 0;

  for (i = 0; i < 64; i++) {
    chTemp = pgm_read_byte(&Font3216[chChar - 0x30][i]);
    for (j = 0; j < 8; j++) {
      chMode = chTemp & 0x80 ? 1 : 0;
      SSD1305_pixel(x, y, chMode, buffer);
      chTemp <<= 1;
      y++;
      if ((y - y0) == 32) {
        y = y0;
        x++;
        break;
      }
    }
  }
}

void SSD1305_bitmap(uint8_t x, uint8_t y, const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer)
{
  uint8_t i, j, byteWidth = (chWidth + 7) / 8;
  for (j = 0; j < chHeight; j++) {
    for (i = 0; i < chWidth; i++) {
      if (pgm_read_byte(pBmp + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        SSD1305_pixel(x + i, y + j, 1, buffer);
      }
    }
  }
}

void SSD1305_display(uint8_t* pBuf)
{
  uint8_t page;
  for (page = 0; page < 8; page++) {
    /* set page address */
    command(0xB0 + page);
    /* set low column address */
    command(0x04);
    /* set high column address */
    command(0x10);
    /* write data */
    digitalWrite(OLED_DC, HIGH);
    SPIWrite(pBuf, WIDTH);
    pBuf += WIDTH;
  }
}
