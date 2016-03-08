/*
  Stepper motor driver.
  dev: Gajdos Tamás
  ver: 0.1
  
  Main Functions:
    * Turn to N position: spsN || spiN
    * Turn N steps:       stsN || stiN
    * Step one forward:   stof
    * Step one backward:  stob
    * Send home:          sh
    * Get position:       gp?
    * Set speed?
  
*/
#include <AFMotor.h>

AF_Stepper motor(200, 2);
long CurrentPos = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
        
void setup() {
  Serial.begin(115200);       // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
     
  motor.setSpeed(20);  // 10 rpm   
     
  motor.release();
  delay(1000);
}

void setHome(long Pos) {
  CurrentPos = Pos;
}

void gotoHome() {
  Serial.println("sh");
//  long stepsToHome = CurrentPos/2;
//  if (CurrentPos > 0 ) {
//    motor.step(stepsToHome, BACKWARD, SINGLE);
//  } else {
//    motor.step(-stepsToHome, FORWARD, SINGLE);
//  }
  Serial.println("OK\r");
}

void setPos(long Pos, int mode) {
  long deltaPos = Pos - CurrentPos;
  movePos(deltaPos, mode);
//  if ( mode < 2 ){
//    deltaPos = deltaPos/2;  
//  }
//  if (deltaPos > 0) {
//    motor.step(deltaPos, FORWARD, mode);
//  } else {
//    motor.step(-deltaPos, BACKWARD, mode);
//  }
//  CurrentPos = Pos;
//  Serial.println("OK\r");
}

void movePos(long dPos, int mode) {
  if ( mode < 2 ){
    dPos /= 2;  
  }
  if (dPos > 0) {
    motor.step(dPos, FORWARD, mode);
  } else {
    motor.step(-dPos, BACKWARD, mode);
  }
  if ( mode < 2 ){
    dPos *= 2;  
  }
  CurrentPos += dPos;
  Serial.println("OK\r");
}

float toFloat(String s) {
  char carray[s.length() + 1];            //determine size of the array
  s.toCharArray(carray, sizeof(carray));  //put readStringinto an array
  float floatNumber = atof(carray);       //convert the array into a float
  return floatNumber;
}
     
void loop() {
  
  if (stringComplete) {
    if (inputString.startsWith("gp?")) {
    // These are the get* functions
      Serial.println(CurrentPos);
   
    } else if (inputString.startsWith("s")) {
    // These are the set* functions
      if (inputString.startsWith("sps")) {
        // Set position SINGLE
        setPos(toFloat(inputString.substring(3)), SINGLE);
      } else if (inputString.startsWith("spi")) {
        // Set position INTERLEAVE
        setPos(toFloat(inputString.substring(3)), INTERLEAVE);
        float pos = toFloat(inputString.substring(3));
      } else if (inputString.startsWith("sts")) {
        // Step multiple SINGLE
        movePos(toFloat(inputString.substring(3)), SINGLE);
      } else if (inputString.startsWith("sti")) {
        // Step multiple INTERLEAVE
        movePos(toFloat(inputString.substring(3)), INTERLEAVE);
      } else if (inputString.startsWith("stof")) {
        // Step one forward INTERLEAVE
        motor.onestep(FORWARD, INTERLEAVE);
        CurrentPos++;
      } else if (inputString.startsWith("stob")) {
        motor.onestep(BACKWARD, INTERLEAVE);
        CurrentPos--;
        // Step one backward INTERLEAVE
      } else if (inputString.startsWith("sh")) {
        // Go home SINGLE
        if (CurrentPos > 0 ) {
          motor.step(CurrentPos/2, BACKWARD, SINGLE);
        } else {
          motor.step(-CurrentPos/2, FORWARD, SINGLE);
        }
        setHome(0);
        Serial.println("OK\r");
      }
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX. This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response. Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a carriage return (ASCII 13),
    // set a flag so the main loop can do something about it:
    if (inChar == '\r') {
      stringComplete = true;
    } 
  }
}
