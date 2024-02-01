#include <SPI.h>
//EPD
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"  

#define SCK   12          //uSUP SPI connector LaskaKit  ESP32-S3-DEVKit
#define MOSI  11          //uSUP SPI connector LaskaKit  ESP32-S3-DEVKit
#define BUSY  13          //uSUP SPI connector LaskaKit  ESP32-S3-DEVKit
#define CS    10          //uSUP SPI connector LaskaKit  ESP32-S3-DEVKit
#define RES   18
#define DC    17
#define USUP_POWER  47 //uSUP connector power output pin

void setup() {
  Serial.begin(115200);
  pinMode(USUP_POWER, OUTPUT);
  digitalWrite(USUP_POWER, HIGH);   // turn the uSUP connector on (HIGH is the voltage level)
  Serial.println("Display power ON");
  delay(1000);

   pinMode(BUSY, INPUT);  //BUSY
   pinMode(RES, OUTPUT); //RES 
   pinMode(DC, OUTPUT); //DC   
   pinMode(CS, OUTPUT); //CS   
   //SPI
   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0)); 
   SPI.begin(SCK, -1, MOSI, CS);   // Setting up uSUP SPI on LaskaKit ESP32-S3-DEVKit
}

//Tips//
/*
1.Flickering is normal when EPD is performing a full screen update to clear ghosting from the previous image so to ensure better clarity and legibility for the new image.
2.There will be no flicker when EPD performs a partial refresh.
3.Please make sue that EPD enters sleep mode when refresh is completed and always leave the sleep mode command. Otherwise, this may result in a reduced lifespan of EPD.
4.Please refrain from inserting EPD to the FPC socket or unplugging it when the MCU is being powered to prevent potential damage.)
5.Re-initialization is required for every full screen update.
6.When porting the program, set the BUSY pin to input mode and other pins to output mode.
*/
void loop() {
  
#if 1//Full screen refresh demostration.

   /************Full display*******************/
    EPD_init(); //Full screen refresh initialization.
    PIC_display(gImage_256);//To Display one image using full screen refresh.
    EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
    delay(5000); //Delay for 5s.
    
  #if 0//Demonstration of Dispaly colored stripes, to enable this feature, please change 0 to 1.
   /************Full display*******************/
    EPD_init(); //Full screen refresh initialization.
    EPD_horizontal();//To Display one image using full screen refresh.
    EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
     delay(5000); //Delay for 5s.
    
    EPD_init(); //Full screen refresh initialization.
    EPD_vertical();//To Display one image using full screen refresh.
    EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
     delay(5000); //Delay for 5s.
    
  #endif    
    EPD_init(); //Full screen refresh initialization.
    PIC_display_Clear(); //Clear screen function.
    EPD_sleep();//Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.. 
        
#endif        
    while(1); // The program stops here            
   
}




//////////////////////////////////END//////////////////////////////////////////////////
