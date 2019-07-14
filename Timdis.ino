#include "lcdDisplay.h"

// definition of buttons;
#define btnUP     1
#define btnDOWN   2
#define btnSELECT 4
#define btnNONE   5

Screen screen; // create an object

//***Global variables***
int flag = 0;
int lcd_key     = 0;
int adc_key_in  = 0;
bool welcome = true;


//read the button value
int read_LCD_buttons()
{
   adc_key_in = analogRead(0);  // read analog A0 value 
   if (adc_key_in > 1000) return btnNONE; 
   if (adc_key_in < 250)  return btnUP; 
   if (adc_key_in < 450)  return btnDOWN; 
   if (adc_key_in < 850)  return btnSELECT;  
   
   return btnNONE; 
}

void setup() {
  Serial.begin(9600);
  analogWrite(10, LOW);
  }

void loop() {
lcd_key = read_LCD_buttons();

//********Buttons********
//**Button "+" **
switch (lcd_key)    
{
   case btnUP:
    {
    if(flag == 0)
    {
      break;
    }
    else
    {
    int interception = 0;
    screen.resetScreen();
    interception = screen.returnPlusSeconds();
    if(interception<10)
    {
       screen.showTimeWithSecondsReplacement();
    }   
    else
    {  
       screen.showTimeScreen();
    } 
    delay(100); 
    }
     break;
   }
 
//**Button "-" **
case btnDOWN:
  {
    if(flag == 0)
    {
      break;
    }
    else
    {
      int interception = 0;
      screen.resetScreen();
      interception = screen.returnMinusSeconds();
      if(interception<10)
      {
        screen.showTimeWithSecondsReplacement();
      }    
      else
      {
        screen.showTimeScreen();
      }
      delay(100);
    }
  break;
  }

//**button main**
case btnSELECT:
  {
    analogWrite(10, 150);
    flag = 1;
    if (welcome==false)
    {
      delay(1000);
      if(analogRead(0)<850)
      {
        analogWrite(10,0);
        delay(1000);
        analogWrite(10,150);
        
        screen.resetScreen();
        screen.welcomeScreen();
        welcome=true;
        break;
      }
      screen.mainFunctionCoutingDownScreen();
    }
    else
    {
      screen.resetScreen();
      screen.welcomeScreen();
      welcome=false;
      screen.resetScreen();
      screen.showTimeWithSecondsReplacement();
    }
    break;
  }
 }
}
