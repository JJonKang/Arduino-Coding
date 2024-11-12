//Name: Jonathan Kang
//UIN: 677480333
//NetID: jkang87
//Lab 4, Analog Input: Photoresistor (LDR - Light Dependent Resistor)

// 10/3/24 1:10~ PM
// TA Mina

//Description:
//Using a 220 ohm resistor, a photoresistor is used
//to present the brightness of the area around it
//it presents the brightness text on the first row of the lcd screen
//the second row of the lcd screen tells the # of milliseconds
//since the start or reset of the Arduino.

//Assumption:
//keep the wiring from lab3
//only add new wiring for photoresistor
//keep parts of lab3 code, delete the old text, rewrite for new ones based on photoresistor

//References used:
//https://www.circuitbasics.com/how-to-use-photoresistors-to-detect-light-on-an-arduino/ how to use photoresistor

#include <LiquidCrystal_I2C.h> //use the library

LiquidCrystal_I2C lcd(0x27,16,2); //sets up the lcd

//photoresistor pin
//uses 220 ohm resistor
int photoPin = A0;

//for millis
unsigned long startTime;
unsigned long currentTime; //also used for the second row of lcd screen
const unsigned long delayTime = 500;

//all strings of light
String dark = "dark";
String semiDark = "partially dark";
String medium = "medium";
String light = "fully lit";
String bright = "brightly lit";

//sets up the lcd screen and serial monitor, makes sure that it correctly starts up
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  startTime = millis();
}

void loop() {
  currentTime = millis();
  //wait 500 milliseconds to loop all over again
  if(currentTime - startTime >= delayTime){
    lcd.clear();//clears up text from previous loop

    //for the photoresistor, reads the light amount
    int photoLight = analogRead(photoPin);
    Serial.println(photoLight);

    //prints second row, display milliseconds since Arduino's start/reset
    lcd.setCursor(0, 1);
    lcd.print(currentTime);

    //brings cursor to first row, telling brightness of area
    //those 5 if/else if statements determine the brightness text
    //based on the photoresistor's number
    //example of testing them, just put finger on photoresistor for dark, use lcd backlight for bright ones
    lcd.setCursor(0,0);
    if(photoLight < 50){
      lcd.print(dark);
    }
    else if(photoLight < 70){
      lcd.print(semiDark);
    }
    else if(photoLight < 125){
      lcd.print(medium);
    }
    else if(photoLight < 170){
      lcd.print(light);
    }
    else{
      lcd.print(bright);
    }

    startTime = millis();
  }
}