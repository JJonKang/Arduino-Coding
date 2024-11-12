//Name: Jonathan Kang
//UIN: 677480333
//NetID: jkang87
//Lab 2, Three Bit Counter

//~1 PM, 9/13/24
//TA Ethan Ky

//Description:
//Two buttons are used to control the three leds used as binary digits.
//One button increases "presses" by 1, the other button decreases it by 1.
//Debouncing has been implemented on the buttons to make sure it accurately 
//Blue led = first digit, Red led = second digit, white led = third digit
//The number created by "presses" is converted into binary
//for the leds to use.

//Assumption:
//One button increases number by 1 (until 7), another button decreases number by 0 (until 0)
//Assuming that that's how the button works above.
//Putting buttons before the leds as the correct call

//References used:
//https://docs.arduino.cc/built-in-examples/digital/Button/ to learn about wiring for buttons
//https://www.ladyada.net/learn/arduino/lesson5.html for learning about leds and buttons together
//https://docs.arduino.cc/built-in-examples/digital/Debounce/ debouncing
//https://instructables.com/Understanding-the-Pull-up-Resistor-With-Arduino/ pull down resistor
//https://www.ladyada.net/learn/arduino/lesson5.html button press memory
//https://www.scaler.com/topics/decimal-to-binary-in-cpp/ number to binary conversion
const int button1 = 2; //pin 2, INCREASE
const int button2 = 3; //pin 3, DECREASE
const int white = 12; //pin 12, white led
const int red = 11; //pin 11, red led
const int blue = 10; //pin 10, blue led
unsigned long lastDebounce1Time = 0; //debounce button1
unsigned long lastDebounce2Time = 0; //debounce button2
unsigned long debounceDelay = 80; //delay 80 ms
int val1; //button1 pressed or not?
int val2; //button2 pressed or not?
int button1State; //records val1 values for loop
int button2State; //records val2 values for loop

int presses = 0; //0-7

void setup() {

  Serial.begin(9600); //as a check
  pinMode(white, OUTPUT); //third (white)
  pinMode(red, OUTPUT); //second (red)
  pinMode(blue, OUTPUT); //first (blue)
  pinMode(button1, INPUT); //INCREASE
  pinMode(button2, INPUT); //DECREASE
  button1State = digitalRead(button1); //starts status for button1
  button2State = digitalRead(button2); //starts status for button2

}
//NOTE: if statements are mostly doubled to take account of two different buttons
void loop() {
  //edge case for when 0 presses
  if(presses == 0){
    digitalWrite(blue, LOW);
  }

  val1 = digitalRead(button1); //get button1 val
  val2 = digitalRead(button2); //get button2 val

  //check if current val is same as the previous state for both buttons
  //if not the same, record time value to the debounce for either one
  if(val1 != button1State){
    lastDebounce1Time = millis();
  }
  if(val2 != button2State){
    lastDebounce2Time = millis();
  }
  
  //if the time minus the previous debounce time is greater than the delay (80)...
  //and if the value isn't the same as the previous value (again)
  //the previous value variable becomes the current one
  //checks both buttons
  if((millis() - lastDebounce1Time) > debounceDelay){
    if(val1 != button1State){
      button1State = val1;
    }
  }
  if((millis() - lastDebounce2Time) > debounceDelay){
    if(val2 != button2State){
      button2State = val2;
    }
  }

  //button1 pressed and different?
  //increase press count if it's less than 6
  if(val1 == HIGH && val1 != button1State && presses <= 6){
    presses++;
  }

  //button2 pressed and differnt?
  //decrease press count if it's more than 1
  if(val2 == HIGH && val2 != button2State && presses >= 1){
    presses--;
  }

  //create a copy of press count as binary (as it'll be altered)
  int binary = presses;
  //press to binary string conversion, technically in reverse binary
  String conversion = "";

  //line 58 covers press count 0, 1-7 is covered here
  while(binary != 0){
    conversion += (binary % 2 ? "1" : "0"); //if remainder of binary is 1, +1 to string, vice versa
    binary /= 2; //divide binary by 2 for next while loop check
    
    //leftmost conversion number determines blue
    if(conversion[0] == '1'){
      digitalWrite(blue, HIGH); 
    }
    else digitalWrite(blue, LOW);

    //middle conversion number determines red
    if(conversion[1] == '1'){
      digitalWrite(red, HIGH);
    }
    else digitalWrite(red, LOW);

    //rightmost number determines white
    if(conversion[2] == '1'){
      digitalWrite(white, HIGH);
    }
    else digitalWrite(white, LOW);
  }

  Serial.println(presses); //press check

  //new "previous" states are the vals, used for the next loop
  button1State = val1;
  button2State = val2;
}
