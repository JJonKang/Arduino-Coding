//Name: Jonathan Kang
//UIN: 677480333
//NetID: jkang87
//Lab 6, Time on I2C LCD

// 10/24/24, 12:45~ PM
// TA Mina

//Description:
//Using an I2C LCD, take the date and time from the serial monitor
//Displays mm/dd/yyyy on first row, hh:mm:ss on second row.

//Assumption:
//Only I2C LCD is necessary, just wire it to the arduino uno.
//Most of the work is on the coding, but it's just taking stuff
//from the time library and using millis correctly

//References used:
//https://www.mathsisfun.com/leap-years.html leap year
//https://www.pjrc.com/teensy/td_libs_Time.html time library details
//https://playground.arduino.cc/Code/Time/ more time details
//https://github.com/PaulStoffregen/Time how to use time
//https://forum.arduino.cc/t/how-use-sscanf-with-a-string/1053395 sscanf
//https://docs.arduino.cc/built-in-examples/communication/SerialCallResponse/ available
//https://www.arduino.cc/reference/tr/language/functions/communication/serial/ serial commands
//https://wiki-content.arduino.cc/en/Tutorial/SetTime set time

#include <LiquidCrystal_I2C.h> //use the library
#include <TimeLib.h> //time

LiquidCrystal_I2C lcd(0x27, 16, 2); //sets up the lcd

//for millis
unsigned long startTime;
unsigned long currentTime;
const unsigned long delayTime = 1000;

char dateBuffer[16]; //day month year
char timeBuffer[16]; // hour minute second

//checks if the numbers are correcty inputted
bool validateInput(String input) {
  int day, month, year, hour, minute, second;
  //checks if there are five numbers
  if(sscanf(input.c_str(), "%d/%d/%d %d:%d:%d", &month, &day, &year, &hour, &minute, &second) != 6) {
    Serial.println("Wrong input. Do it in MM/DD/YYYY HH:MM:SS");
    return false;
  }

  //makes sure the numbers are within the limits
  if(hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59 || month < 1 || month > 12 || day < 1) {
    Serial.println("Wrong values.");
    return false;
  }

  //days in the month
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  //leap year check for Feb
  if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
    daysInMonth[1] = 29;
  }

  //check if day is within the upper limits for a month
  //checked here because february changes sometimes
  if (day > daysInMonth[month - 1]) {
    Serial.println("Invalid day for the given month.");
    return false;
  }

  return true; // If all checks pass
}

// Function to display date and time on the LCD
void displayDateTime() {
  lcd.clear();
  lcd.setCursor(0, 0); //first row
  sprintf(dateBuffer, "%02d/%02d/%04d", month(), day(), year()); 
  lcd.print(dateBuffer);//prints out day/month/year

  lcd.setCursor(0, 1); //second row
  sprintf(timeBuffer, "%02d:%02d:%02d", hour(), minute(), second());
  lcd.print(timeBuffer);//prints out hour/minute/second
}

void setup() {
  Serial.begin(9600); //start up the serial monitor
  lcd.init(); //initialize the display
  lcd.clear();
  lcd.backlight();
  setTime(0, 0, 0, 1, 1, 2000); // default to 00:00:00, 1/1/2000
  
  Serial.println("Enter the date and time in: MM/DD/YYYY HH:MM:SS");
  startTime = millis();
}

void loop() {
  currentTime = millis();
  if(currentTime - startTime >= delayTime){ //one second wait timer
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n'); //get input from serial monitor
      
      //checks input if it works
      if (validateInput(input)) {
        int day, month, year, hour, minute, second;
        sscanf(input.c_str(), "%d/%d/%d %d:%d:%d", &month, &day, &year, &hour, &minute, &second);
        setTime(hour, minute, second, day, month, year); //set the new time
        
        //changes to new date/time
        displayDateTime();
        
        //continues asking for a new date/time
        Serial.println("Enter another date and time in: MM/DD/YYYY HH:MM:SS");
      }
    }
    
    //changes date/time every second
    displayDateTime();
    startTime = millis();
  }
}