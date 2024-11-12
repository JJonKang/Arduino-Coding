//Name: Jonathan Kang
//UIN: 677480333
//NetID: jkang87

//Lab 9, Analog Inputs

// 11/12/2024 12:40 PM
// TA Mina

//Description:
//Using a joystick and a potentiometer
//the analog inputs from those two controls the color of the RGB LED
//x-axis joystick = red value, y-axis joystick = green value, potentiometer = blue value
//red, green, blue LEDs are also added to show intensity of RGB LED
//time in code is for PWM

//Assumption:
//learn how to use a joystick and the rgb led
//figure out how the rgb led works
//do a lot of if statements for the analogs

//References used:
//https://arduinogetstarted.com/tutorials/arduino-joystick using joystick
//https://docs.arduino.cc/built-in-examples/usb/JoystickMouseControl/ more examples on using joystick, also to get the map function
//https://www.instructables.com/How-to-use-Potentiometer-Arduino-Tutorial/ using potentiometer
//https://arduinogetstarted.com/tutorials/arduino-rgb-led rgb led
//https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/ more rgb led info
//https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino pwm info

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
//potentiometer
const int pot = A2;
//RGB LED
const int rgbRED   = 5;
const int rgbGREEN = 6;
const int rgbBLUE  = 9;
//3 LEDs
const int red = 3;
const int green = 10;
const int blue = 11;

unsigned long startTime;
unsigned long currentTime;
const int time = 40;

int led = 8; //pin

void setup() {
  //setup pins for rgb LED and LEDs
  pinMode(rgbRED, OUTPUT);
  pinMode(rgbGREEN, OUTPUT);
  pinMode(rgbBLUE, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  startTime = millis();
}

void loop() {
  currentTime = millis();
  if(currentTime - startTime > time){ //PWM
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);
    int potValue = analogRead(pot);

    //converting 0-1023 to 0-255 for the LEDs
    int redValue = map(xValue, 0, 1023, 0, 255);
    int greenValue = map(yValue, 0, 1023, 0, 255);
    int blueValue = map(potValue, 0, 1023, 0, 255);

    //put in values for LEDs
    analogWrite(rgbRED, redValue);
    analogWrite(rgbGREEN, greenValue);
    analogWrite(rgbBLUE, blueValue);
    analogWrite(red, redValue);
    analogWrite(green, greenValue);
    analogWrite(blue, blueValue);
    startTime = millis(); 
  }
}
