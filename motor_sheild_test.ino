#include <AFMotor.h>
#include "IRremote.h"

int receiver = A0;           // IR pin
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
AF_DCMotor motor3(3);        // Sets up motor 3
AF_DCMotor motor4(4);        // Sets up motor 4

// Global Variables
char input = '-';
bool forwardBool = false;
bool backwardBool = false;
bool leftBool = false;
bool rightBool = false;
void setup() {
  // Sets motor Speed
  int motorSpeed = 2000;
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);
  Serial.begin(9600);  // Begins Serial
  irrecv.enableIRIn(); // Start the receiver
}

void translateIR()
{
  switch(results.value)
  {
  case 0xFFA25D: input = 'p'; break;
  case 0xFF629D: input = 'f'; break;
  case 0xFF22DD: input = 'l';   break;
  case 0xFFC23D: input = 'r'; break;
  case 0xFFA857: input = 'b';   break;
  default: 
    Serial.println(" other button : ");
    Serial.println(results.value);
  }
  delay(500);
}
/**
 * Motor Functions
 * forward backward left right and release
 */
void forward() {
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}
void backward() {
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}
void left(){
  motor4.run(FORWARD);
  motor3.run(FORWARD);
}
void right(){
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void release(){
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
  // Get ir input
  if (irrecv.decode(&results)) 
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }
  
  // Control motor depending on inputs
  switch (input){
    case 'f':{
      if (forwardBool == false){release();forward();forwardBool = true;input = '1';}
      else {release();forwardBool = false;input = '1';}
    }
    case 'b':{
      if (backwardBool == false){release();backward();backwardBool = true;input = '1';}
      else {release();backwardBool = false;input = '1';}
    }
    case 'l':{
      if (leftBool == false){release();left();leftBool = true;input = '1';}
      else {release();leftBool = false;input = '1';}
    }
    if (rightBool == false){release();right();rightBool = true;input = '1';}
      else {release();rightBool = false;input = '1';}
    }
  }
