//Name: Jonathan Kang
//UIN: 677470333
//NetID: jkang87
//Lab 1, Three Blinking Lights
//TA Ary 1:22 PM

//Description:
//The code first lights up one led. After it stops lighting up, the second led starts lighting up.
//After the 2nd led stops lighting up, the third led starts lighting up.
//After the third stops, the first starts again, and the cycle repeats.

//Assumption:
//Replace the pinmode's ledbuiltin with the pins on the arduino.
//Series 

//References used:
//Took inspiration from the blink example in the IDE.
//https://www.arduino.cc/reference/en/language/functions/time/millis/ to learn about millis
//https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573 to learn about the usage of millis (and digitalRead)
const unsigned long alternate = 1000; //1000 milliseconds to alternate pins in a later use
const unsigned long alternate2 = 2000;
const unsigned long alternate3 = 3000;
int ledAlt = 0; //brings order to which led lights up or not
unsigned long startTime; //inital time of the running arduino
unsigned long currentTime; //current time of the system
void setup() {
  Serial.begin(1000); //just as a check 
  pinMode(13, OUTPUT); //first (blue)
  pinMode(12, OUTPUT); //second (red)
  pinMode(11, OUTPUT); //third (green)
  startTime = millis(); //start time
}

void loop() {
  currentTime = millis();//current point continues
  //this if statement is only used once, as it sets up the first led to light up
  //if alternate's time has been reached, the if statement runs. The other if statements in the future are the same
  if(currentTime - startTime >= alternate && ledAlt == 0){
    digitalWrite(13, !digitalRead(13));
    startTime = currentTime;
    ledAlt++;
  }
  else if(currentTime - startTime >= alternate && ledAlt == 1){
    digitalWrite(13, !digitalRead(13));//shuts the first led down
    digitalWrite(12, !digitalRead(12));//second one turns on
    startTime = currentTime;
    ledAlt++;
  }
  else if(currentTime - startTime >= alternate && ledAlt == 2){
    digitalWrite(12, !digitalRead(12));//2nd is down
    digitalWrite(11, !digitalRead(11));//3rd is up
    startTime = currentTime;
    ledAlt++;
  }
  //if ledAlt >= 2, 3rd is down, 1st is up, function loops without touching the first if statement anymore
  else if(currentTime - startTime >= alternate && ledAlt == 3){
    ledAlt = 1;
    digitalWrite(13, !digitalRead(13));
    digitalWrite(11, !digitalRead(11));
    startTime = currentTime;
  }

}