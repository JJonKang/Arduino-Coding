//Name: Jonathan Kang
//UIN: 677480333
//NetID: jkang87
//Lab 5 – Multiple Inputs and Outputs

// 12:24 PM 10/10/24
// TA Mina

//Description:
//Two parts will be happening through the Arduino.
//Part 1:
//if photoresistor sees bright light, increase # of LEDs
//otherwise decrease the # of LEDs if it gets darker
//basically lab 4 but instead of LCD screen use LEDs
//Part 2:
//Potentiometer = analog input for the buzzer
//if potentiometer is at lowest range, buzzer is off
//if low range, buzzer waits a long time before making a noise
//if high range, buzzer takes smaller breaks, until it's permanently on
//buzzer makes a noise for 1 second, noise is associated with a music note

//Assumption:
//4 parallel circuits, one has 4 leds, 1 has a photoresistor
//another has the potentiometer, and one has a passive buzzer
//coding wouldn't take too long as it seems to all join together without
//too much difficulty.
//I can use the 220 ohm resistor instead of 10k for the photoresistor.

//References used:
//https://docs.arduino.cc/learn/electronics/potentiometer-basics/ how to use a potentiometer
//https://www.circuitbasics.com/how-to-use-active-and-passive-buzzers-on-the-arduino/ how to use a passive buzzer
//https://docs.arduino.cc/built-in-examples/digital/toneMelody/ music notes
//https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/ tone function

//photoresistor pin
//uses 220 ohm resistor
int photoPin = A0;

//buzzer pin
const int buzzer = 7;

//potentiometer pin
int potent = A3;

//for millis: 1 is for LEDs, 2 is for buzzers
unsigned long startTime1;
unsigned long currentTime1;
const unsigned long delayTime1 = 500; //for LEDs
unsigned long startTime2;
unsigned long currentTime2;
unsigned long delayTime2 = 0; //for the buzzer

//LED pins
const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int led4 = 10;

//sets up the LEDs, potentiometer, photoresistor, and the passive buzzer
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  startTime1 = millis();
  startTime2 = millis();
}

void loop() {
  currentTime1 = millis();
  currentTime2 = millis();
  //wait 500 milliseconds to loop all over again
  //this if statement is for the LEDs
  if(currentTime1 - startTime1 >= delayTime1){

    //for the photoresistor, reads the light amount
    int photoLight = analogRead(photoPin);
    Serial.println(photoLight);

    //those 5 if/else if statements determine the brightness text
    //based on the photoresistor's number
    //example of testing them, just put finger on photoresistor for dark, use lcd backlight for bright ones
    if(photoLight < 50){//very dark
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }
    else if(photoLight < 70){//dim
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }
    else if(photoLight < 125){//normal
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }
    else if(photoLight < 170){//somewhat bright
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
    }
    else{
      digitalWrite(led1, HIGH);//very bright
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
    }
    startTime1 = millis();
  }

  //this if statement determines whether to make the buzzer make a noise
  //the tone uses 262 Hz, which is C4's note.
  //delayTime2 is based on the position of the potentiometer
  //buzzer always makes a sound for 1 second, unless it's off
  if(currentTime2 - startTime2 >= delayTime2){
    int potentVal = analogRead(potent);
    if(potentVal < 35){ //turned off, range is 0-35 for safe measure
      digitalWrite(buzzer, LOW);
    }
    else if(potentVal < 200){ //8 second timer
      tone(7, 262, 1000);
      delayTime2 = 9000;
    }
    else if(potentVal < 400){ //4 second timer
      tone(7, 262, 1000);
      delayTime2 = 5000;
    }
    else if(potentVal < 600){ //2 second timer
      tone(7, 262, 1000);
      delayTime2 = 3000;
    }
    else if(potentVal < 800){ //1 second timer
      tone(7, 262, 1000);
      delayTime2 = 2000;
    }
    else if(potentVal < 1000){ //.5 second timer
      tone(7, 262, 1000);
      delayTime2 = 1500;
    }
    else{ //constant loop
      tone(7, 262, 1000);
      delayTime2 = 1000;
    }
    startTime2 = millis();
  }
}