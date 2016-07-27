/*
  Stepper motor driver.
  dev: Gajdos Tamás
  ver: 0.2
  
  Main Functions:
    * Turn to N position: spsN || spiN
    * Turn N steps:       stsN || stiN
    * Step one forward:   stof
    * Step one backward:  stob
    * Send home:          sh
    * Get position:       gp?
    * Set speed?
    
  Main 28BYJ-28 Functions:
    * Turn to N position: bpsN || bpiN
    * Turn N steps:       btsN || btiN
    * Step one forward:   btof
    * Step one backward:  btob
    * Send home:          bh
    * Get position:       gbp?
    * Set speed?
  
*/
#include <AFMotor.h>

AF_Stepper nema(200, 2);
AF_Stepper byj48(64, 1);

long CurrentPos = 0;
long CurrentBos = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
        
void setup() {
  Serial.begin(115200);       // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
     
  nema.setSpeed(20);
  byj48.setSpeed(320);
     
  nema.release();
  byj48.release();
  delay(1000);
}

void setHome(long Pos) {
  CurrentPos = Pos;
}

void setBHome(long Bos) {
  CurrentBos = Bos;
}

void setPos(long Pos, int mode) {
  long deltaPos = Pos - CurrentPos;
  movePos(deltaPos, mode);
}

void setBos(long Bos, int mode) {
  long deltaBos = Bos - CurrentBos;
  moveBos(deltaBos, mode);
}


void movePos(long dPos, int mode) {
  if ( mode < 2 ){
    dPos /= 2;  
  }
  if (dPos > 0) {
    nema.step(dPos, FORWARD, mode);
  } else {
    nema.step(-dPos, BACKWARD, mode);
  }
  if ( mode < 2 ){
    dPos *= 2;  
  }
  CurrentPos += dPos;
  Serial.println("OK\r");
}

void moveBos(long dBos, int mode) {
  if ( mode < 2 ){
    dBos /= 2;  
  }
  if (dBos > 0) {
    byj48.step(dBos, FORWARD, mode);
  } else {
    byj48.step(-dBos, BACKWARD, mode);
  }
  if ( mode < 2 ){
    dBos *= 2;  
  }
  CurrentBos += dBos;
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
    } else if (inputString.startsWith("gbp?")) {
    // These are the get* functions
      Serial.println(CurrentBos);
  
    } else if (inputString.startsWith("s")) {
    // These are the set* functions for NEMA
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
        nema.onestep(FORWARD, INTERLEAVE);
        CurrentPos++;
      } else if (inputString.startsWith("stob")) {
        nema.onestep(BACKWARD, INTERLEAVE);
        CurrentPos--;
        // Step one backward INTERLEAVE
      } else if (inputString.startsWith("sh")) {
        // Go home SINGLE
        if (CurrentPos > 0 ) {
          nema.step(CurrentPos/2, BACKWARD, SINGLE);
        } else {
          nema.step(-CurrentPos/2, FORWARD, SINGLE);
        }
        setHome(0);
        Serial.println("OK\r");
      }
    } else if (inputString.startsWith("b")) {
      // These are the set* functions for 28BYJ-48
      if (inputString.startsWith("bps")) {
        // Set position SINGLE
        setBos(toFloat(inputString.substring(3)), SINGLE);
      } else if (inputString.startsWith("bpi")) {
        // Set position INTERLEAVE
        setBos(toFloat(inputString.substring(3)), INTERLEAVE);
        float pos = toFloat(inputString.substring(3));
      } else if (inputString.startsWith("bts")) {
        // Step multiple SINGLE
        moveBos(toFloat(inputString.substring(3)), SINGLE);
      } else if (inputString.startsWith("bti")) {
        // Step multiple INTERLEAVE
        moveBos(toFloat(inputString.substring(3)), INTERLEAVE);
      } else if (inputString.startsWith("btof")) {
        // Step one forward INTERLEAVE
        byj48.onestep(FORWARD, INTERLEAVE);
        CurrentBos++;
      } else if (inputString.startsWith("btob")) {
        byj48.onestep(BACKWARD, INTERLEAVE);
        CurrentBos--;
        // Step one backward INTERLEAVE
      } else if (inputString.startsWith("bh")) {
        // Go home SINGLE
        if (CurrentBos > 0 ) {
          byj48.step(CurrentBos/2, BACKWARD, SINGLE);
        } else {
          byj48.step(-CurrentBos/2, FORWARD, SINGLE);
        }
        setBHome(0);
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

