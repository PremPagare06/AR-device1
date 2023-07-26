#include "U8glib.h"                           //library for interfacing OLED

U8GLIB_SSD1306_128X64 OLED(U8G_I2C_OPT_NONE); //create instance of U8glib. For different OLED types/resolutions, check U8glib documentation. I used 128x64 monochromatic OLED display with I2C interface

long int rewrite = 0;                         //this will hold our last rewritten time from millis() function
const short firstRow = 12;                    //some constants that define where the rows will be
const short secondRow = 27;
const short thirdRow = 42;
const short fourthRow = 57;
const short width = 128;   
 
void setup(void) {
  Serial.begin(9600);                         //open serial interface with baud of 9600 (have to be the same as in python script)
}

String serialReceive;                         //some Strings, that will contain values got from Serial buffer. First one will contain the entire data string, others will contain only substrings that belongs to them


void loop(void) {
  if(Serial.available() > 0) {                //if any data is available in serial buffer
    serialReceive = Serial.readString();      //read it as string and put into serialReceive variable
  }

    
  if (millis()-rewrite > 100) {               //OLED handler statement.. 
    OLED.firstPage();                         //go to the first page of OLED
    do {
      drawOLED();                             //our function that draws OLED display
    } while( OLED.nextPage() );
    rewrite = millis();                       //this piece of code can be found on different sites as recommended way to display stuff on OLED, if you are interested in how it works, just google it
  }
  
  delay(10);                                  //wait for 10ms, as OLED needs some time to get refreshed
}

void drawOLED(void) {
  OLED.setFont(u8g_font_unifontr);            //set font to monospace type (15x15 px). "r" on the end means REDUCED, this fontset uses only 1.1kb while full version (without "r") is some 5.5kb large... 
  OLED.setPrintPos(0, firstRow);              //set printing position to edge of screen, first row
  // OLED.print("Translating");                         //print legend text
  // OLED.setPrintPos(0);             //set printing position to a bit further
  OLED.print(serialReceive);                        //print the value received and split from the Serial
}