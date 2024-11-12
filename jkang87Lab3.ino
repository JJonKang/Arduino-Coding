//Name: Jonathan Kang
//UIN: 677480333
//NetID: jkang87
//Lab 3, Liquid Crystal Display

// 9/26/24 ~1:27PM
// TA Mina

//Description:
//This lab is to learn how to wire and use a Liquid Crystal Display.
//For me specifically, I have the I2C LCD, so I installed
//The LiquidCrystal I2C library for it to work.
//First row of screen shows my quote, moves left
//Second row of screen shows my name, doesn't move, uses sprintf

//Assumption:
//wiring would be easy, as only an i2d lcd and a 220 resistor would be needed
//coding would be trivial, only sprintf is the thing that must be learnt

//References used:
//https://lastminuteengineers.com/i2c-lcd-arduino-tutorial/ used for the LiquidCrystal I2C version
//https://www.programmingelectronics.com/sprintf-arduino/ sprintf
//https://docs.arduino.cc/learn/electronics/lcd-displays/ hello world example and scrolling
//https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/components_basic/21-component_i2c_lcd1602.html found out LCD address (0x27)
//https://www.arduino.cc/reference/en/libraries/liquidcrystal/ functions and library
#include <LiquidCrystal_I2C.h> //use the library

LiquidCrystal_I2C lcd(0x27,16,2); //sets up the lcd

//prints part of the quote string for the lcd as it moves in void loop
int first = 0;
int last = 16;

//This whole char process is just so that sprintf is used.
//buffer goes to the second row, unmoving.
char buffer[9];
char name[] = "Jona";
char name2[] = "than";

//for millis
unsigned long startTime;
unsigned long currentTime;
const unsigned long delayTime = 500;

//the quote, along with a lot of space so it's not as crowded and doesn't cut
String quote = "               Carpe diem, Seize the day.              ";

//sets up the lcd screen, makes sure that it correctly starts up
void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  startTime = millis();
}

void loop() {
  currentTime = millis();
  //wait 500 milliseconds to loop all over again
  if(currentTime - startTime >= delayTime){
    //prints second row using sprintf
    lcd.setCursor(4, 1); //2nd row, around the middle
    sprintf(buffer, "%s%s", name, name2); //for the assignment, sprintf is used, combines name and name2
    lcd.print(buffer);

    //brings cursor to first row, beginning
    lcd.setCursor(0,0);
    //when first++ and last++, it prints out quote as if it's moving to the left
    first++;
    last++;
    //if last goes beyond quote, revert both first and last to original position
    //this imitates an infinite cycle with the same string
    if(last > quote.length()){
      first = 0;
      last = 16;
    }
    //print the part of quote from first to last
    lcd.print(quote.substring(first, last));

    startTime = millis();
  }
}