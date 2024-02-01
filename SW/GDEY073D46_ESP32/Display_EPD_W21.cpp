#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

void EPD_W21_Init(void)
{
  EPD_W21_RST_0;    // Module reset
  delay(10);//At least 10ms delay 
  EPD_W21_RST_1;
  delay(10);//At least 10ms delay 
  
}

void EPD_init(void)
{ 

  EPD_W21_Init(); //Electronic paper IC reset   
  
  EPD_W21_WriteCMD(0xAA);    // CMDH
  EPD_W21_WriteDATA(0x49);
  EPD_W21_WriteDATA(0x55);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x08);
  EPD_W21_WriteDATA(0x09);
  EPD_W21_WriteDATA(0x18);

  EPD_W21_WriteCMD(PWRR);
  EPD_W21_WriteDATA(0x3F);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x32);
  EPD_W21_WriteDATA(0x2A);
  EPD_W21_WriteDATA(0x0E);
  EPD_W21_WriteDATA(0x2A);
  
  EPD_W21_WriteCMD(PSR);  
  EPD_W21_WriteDATA(0x5F);
  EPD_W21_WriteDATA(0x69);
  
  EPD_W21_WriteCMD(POFS);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x54);
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x44); 

  EPD_W21_WriteCMD(BTST1);
  EPD_W21_WriteDATA(0x40);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x2C);
  
  EPD_W21_WriteCMD(BTST2);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x16);
  EPD_W21_WriteDATA(0x25);

  EPD_W21_WriteCMD(BTST3);
  EPD_W21_WriteDATA(0x6F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x1F);
  EPD_W21_WriteDATA(0x22);
 
  EPD_W21_WriteCMD(0x13);    // IPC
  EPD_W21_WriteDATA(0x00);
  EPD_W21_WriteDATA(0x04);
  
  EPD_W21_WriteCMD(PLL);
  EPD_W21_WriteDATA(0x02);
  
  EPD_W21_WriteCMD(0x41);     // TSE
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(CDI);
  EPD_W21_WriteDATA(0x3F);
  
  EPD_W21_WriteCMD(TCON);
  EPD_W21_WriteDATA(0x02);
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(TRES);
  EPD_W21_WriteDATA(0x03);
  EPD_W21_WriteDATA(0x20);
  EPD_W21_WriteDATA(0x01); 
  EPD_W21_WriteDATA(0xE0);
  
  EPD_W21_WriteCMD(VDCS);
  EPD_W21_WriteDATA(0x1E); 

  EPD_W21_WriteCMD(T_VDCS);
  EPD_W21_WriteDATA(0x00);

  EPD_W21_WriteCMD(0x86);    // AGID
  EPD_W21_WriteDATA(0x00);
  
  EPD_W21_WriteCMD(PWS);
  EPD_W21_WriteDATA(0x2F);
 
  EPD_W21_WriteCMD(0xE0);   // CCSET
  EPD_W21_WriteDATA(0x00); 
  
  EPD_W21_WriteCMD(0xE6);   // TSSET
  EPD_W21_WriteDATA(0x00);  

  EPD_W21_WriteCMD(0x04);     //PWR on  
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}
  
void EPD_sleep(void)
{
    EPD_W21_WriteCMD(0X02);   //power off
    EPD_W21_WriteDATA(0x00);
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
    /*EPD_W21_WriteCMD(0X07);   //deep sleep
    EPD_W21_WriteDATA(0xA5);*/
}

/**********************************display picture**********************************/ 
void Acep_color(unsigned char color)
{
  unsigned int i,j;
  EPD_W21_WriteCMD(0x10);        
  for(i=0;i<480;i++)
  {
    for(j=0;j<800/2;j++)
    {
      EPD_W21_WriteDATA(color);
    }
  }
  
  //Refresh
  EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
  EPD_W21_WriteDATA(0x00);
  delay(1);              //!!!The delay here is necessary, 200uS at least!!!     
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

unsigned char Color_get(unsigned char color)
{
  unsigned datas;
  switch(color)
  {
    case 0xFF:
      datas=white;
    break;
    case 0xFC:
      datas=yellow;
    break;
    case 0xF1:
      datas=orange;
    break;        
    case 0xE5:
      datas=red;
    break;  
    case 0x4B:
      datas=blue;
    break;  
    case 0x39:
      datas=green;
    break;  
    case 0x00:
      datas=black;
    break;    
    default:
    break;      
  }
   return datas;
}
void PIC_display(const unsigned char* picData)
{
  unsigned int i,j,k;
  unsigned char temp1,temp2;
  unsigned char data_H,data_L,data;
  

   //Acep_color(White); //Each refresh must be cleaned first   
  EPD_W21_WriteCMD(0x10);        
  for(i=0;i<480;i++)
  { 
    k=0;
    for(j=0;j<800/2;j++)
    {
      
      temp1=picData[i*800+k++]; 
      temp2=picData[i*800+k++];
      data_H=Color_get(temp1)<<4;
      data_L=Color_get(temp2);
      data=data_H|data_L;
      EPD_W21_WriteDATA(data);
    }
  } 
  
   //Refresh
    EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
    EPD_W21_WriteDATA(0x00);
    delay(1);   //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}


void EPD_horizontal(void)
{
  unsigned int i,j;
  unsigned char index = 0x00;
  unsigned char const Color[8] = {Black,White,Green,Blue,Red,Yellow,Orange,White};

 //Acep_color(White); //Each refresh must be cleaned first    
  EPD_W21_WriteCMD(0x10);      //start to transport picture
  for(i=0;i<480;i++){
    if((i%60 == 0) && (i != 0))
      index ++;
    for(j =0;j<800/2;j++){
      EPD_W21_WriteDATA(Color[index]);  
    }
  }
   //Refresh
    EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
    EPD_W21_WriteDATA(0x00);
    delay(1);   //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

void EPD_vertical(void)
{
  unsigned int i,j,k;
  unsigned char const Color[8] = {Black,White,Green,Blue,Red,Yellow,Orange,White};
  
  // Acep_color(White); //Each refresh must be cleaned first   
  EPD_W21_WriteCMD(0x10);      //start to transport pictu
  for(i=0;i<480;i++)
  {
    for(k = 0 ; k < 7; k ++)  //7 color      400/8=50  
    {
      for(j = 0 ; j < 50; j ++)
      {
        EPD_W21_WriteDATA(Color[k]);
      }
    }
    for(j = 0; j <50 ; j++) 
    {
      EPD_W21_WriteDATA(White);
    }
  }
   //Refresh
    EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
    EPD_W21_WriteDATA(0x00);
    delay(1);   //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

void PIC_display_Clear(void)
{
   unsigned int i,j;
  //Acep_color(Clean); //Each refresh must be cleaned first 
  EPD_W21_WriteCMD(0x10);        
  for(i=0;i<480;i++)
  {
    for(j=0;j<800/2;j++)
    {
      EPD_W21_WriteDATA(White);
    }
  }
  
  //Refresh
  EPD_W21_WriteCMD(0x12);   //DISPLAY REFRESH   
  EPD_W21_WriteDATA(0x00);
  delay(1);              //!!!The delay here is necessary, 200uS at least!!!     
  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

void lcd_chkstatus(void)
{
  while(!isEPD_W21_BUSY);                         
}














/***********************************************************
            end file
***********************************************************/
