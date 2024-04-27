#include "arduino_secrets.h"
#include "thingProperties.h"

/* 
  Light dimmer and Fan speed controller using ESP8266
  Paras Kore    (21ECE1024)
  Shreeya Kamat (21ECE1034)

  int all;
  int speed;
  bool backward;
  bool forward;
*/

void setup() {
  pinMode(D5, OUTPUT);  // Enable Pin
  pinMode(D1, OUTPUT);  // Input 2
  pinMode(D0, OUTPUT);  // Input 1
  
  pinMode(D2, OUTPUT);  // LED 1
  pinMode(D3, OUTPUT);  // LED 2
  pinMode(D4, OUTPUT);  // LED 3

  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  if(backward == 0 && forward == 0){
    off();
  }
}

/*
  Since Forward is READ_WRITE variable, onForwardChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onForwardChange()  {
  // Add your code here to act upon Forward change
  if(forward == 1){
    digitalWrite(D1, HIGH);
    digitalWrite(D0, LOW);
    backward = 0;
  }
}
/*
  Since Backward is READ_WRITE variable, onBackwardChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBackwardChange()  {
  // Add your code here to act upon Backward change
  if(backward == 1){
    digitalWrite(D0, HIGH);
    digitalWrite(D1, LOW);
    forward = 0;
  }
}
void off()  {
  // Add your code here to act upon Backward change
    
    speed = 0;
    analogWrite(D5, 0);
  }
/*
  Since Speed is READ_WRITE variable, onSpeedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSpeedChange()  {
  // Add your code here to act upon Speed change
  switch (speed){
    case 0: analogWrite(D5, 0);
            break;
    case 1: analogWrite(D5, 130);
            break;
    case 2: analogWrite(D5, 160);
            break;
    case 3: analogWrite(D5, 190);
            break;
    case 4: analogWrite(D5, 220);
            break;
    case 5: analogWrite(D5, 253);
            break;
  }
}
/*
  Since All is READ_WRITE variable, onAllChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAllChange()  {
  // Add your code here to act upon All change
  analogWrite(D2, all);
  analogWrite(D3, all);
  analogWrite(D4, all);
}