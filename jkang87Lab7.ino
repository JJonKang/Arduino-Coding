//Name: Jonathan Kang
//UIN: 677480333
//NetID: jkang87

//Name: Ron Pham
//UIN: 677854696
//NetID: tpham67
//Lab 7, Two Ardunios in a Serial Connection

// 12/31/2024, 1:05~ PM
// TA Mina

//Description:
//Using two arduinos, serially connect them
//Each arduino has an LED and a button connected
//One arduino's button changes the LED of the other arduino, and vice versa

//Assumption:
//Same code, so just use different pins and act like the whole thing is on one arduino
//use the lab 6 serial stuff
//use two power sources

//References used:
//https://robotic-controls.com/learn/arduino/arduino-arduino-serial-communication wiring two arduinos together
//https://www.electroniclinic.com/serial-communication-between-two-arduino-boards/ examples of two arduinos
//https://www.instructables.com/Understanding-the-Pull-up-Resistor-With-Arduino/ pulldown button (again)
//https://docs.arduino.cc/learn/communication/uart/ serial1
unsigned long startTime;
unsigned long currentTime;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 80;

int led = 8; //pin
int ledState = LOW; //current led state
int b = 7; //pin
int bStateCurr = LOW; //current button state
int bStatePrev = LOW; //previous button state

void setup() {
  Serial1.begin(9600);  //start serial communication (notice it's Serial1)
  //setup pins for LED and button
  pinMode(led, OUTPUT);
  pinMode(b, INPUT);
  startTime = millis();
}

void loop() {
  currentTime = millis();
  bStateCurr = digitalRead(b); //get button state
  if(currentTime - lastDebounceTime >= debounceDelay){ //debounce check
    if(bStateCurr != bStatePrev){ //if button state has changed
      if(bStateCurr == HIGH){ //and if button is high
        ledState = !ledState; //change led state variable to low or high
        Serial1.write(ledState + '0'); //input led's state into serial1 connection
      }
      lastDebounceTime = millis(); //reset debounce time
    }
  }
  bStatePrev = bStateCurr; //prev is the curr state for this loop
  if(Serial1.available() > 0){ //does serial1 have the input?
    digitalWrite(led, Serial1.read() - '0'); //change led from other arduino
  }
}
