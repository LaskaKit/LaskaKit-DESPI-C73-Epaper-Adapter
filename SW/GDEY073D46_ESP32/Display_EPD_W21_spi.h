#ifndef _DISPLAY_EPD_W21_SPI_
#define _DISPLAY_EPD_W21_SPI_
#include "Arduino.h"

#define BUSY  13          //uSUP SPI connector LaskaKit  ESP32-S3-DEVKit
#define CS    10          //uSUP SPI connector LaskaKit  ESP32-S3-DEVKit
#define RES   18
#define DC    17

#define isEPD_W21_BUSY digitalRead(BUSY)  //BUSY
#define EPD_W21_RST_0 digitalWrite(RES,LOW)  //RES
#define EPD_W21_RST_1 digitalWrite(RES,HIGH)
#define EPD_W21_DC_0  digitalWrite(DC,LOW) //DC
#define EPD_W21_DC_1  digitalWrite(DC,HIGH)
#define EPD_W21_CS_0 digitalWrite(CS,LOW) //CS
#define EPD_W21_CS_1 digitalWrite(CS,HIGH)


void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char datas);
void EPD_W21_WriteCMD(unsigned char command);


#endif 
