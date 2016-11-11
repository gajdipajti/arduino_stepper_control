/*
  Stepper motor driver. Raw L293D edition.
  A trimmed down version which works with the gui.
  For a Leonardo.
  dev: Gajdos Tamás
  ver: 0.2.1-raw
  
  Main Functions:
    * Turn to N position: spsN || spiN
    * Turn N steps:       stsN || stiN
    * Step one forward:   stof
    * Step one backward:  stob
    * Send home:          sh
    * Get position:       gp?
    * Set speed?
*/
#include <Stepper.h>

const int stepsPerRevolution = 200;
Stepper byj(stepsPerRevolution, 8,10,11,12);

long CurrentPos = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
        
void setup() {
  Serial.begin(115200);       // set up Serial library at 9600 bps
    
  byj.setSpeed(60);
     
  delay(1000);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  digitalWrite(13, HIGH);
  Serial.println("Stepper test!");
}

void setPos(long Pos) {
  long deltaPos = Pos - CurrentPos;
  movePos(deltaPos);
}

void movePos(long dPos) {
  byj.step(dPos);
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
      Serial.println(CurrentPos);
    } else if (inputString.startsWith("sp")) {
        setPos(toFloat(inputString.substring(3)));
    } else if (inputString.startsWith("st")) {
        movePos(toFloat(inputString.substring(3)));
    } else if (inputString.startsWith("stof")) {
        byj.step(1);
        CurrentPos++;
    } else if (inputString.startsWith("stob")) {
        byj.step(-1);
        CurrentPos--;
    } else if (inputString.startsWith("sh")) {
        if (CurrentPos > 0 ) {
          byj.step(CurrentPos);
        } else {
          byj.step(-CurrentPos);
        }
        CurrentPos = 0;
        Serial.println("OK\r");
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  serialEvent();
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

