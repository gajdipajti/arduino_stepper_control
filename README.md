# arduino-stepper-control
Control an arduino uno with motor shield over serial.

 * The String->float conversion: http://forum.arduino.cc/index.php?topic=179666.msg1331654#msg1331654
 * AFMotor: https://github.com/adafruit/Adafruit-Motor-Shield-library
 * Tutorial: https://learn.adafruit.com/adafruit-motor-shield/af-stepper-class

# Start Here:
 1. Clone the repository to your sketchbook folder.
 2. Connect a Motor Shield v1 with a Stepper Motor.
 3. Burn it to your Arduino UNO.
 
# Communication with the Controller:
## Serial: 115200 8N1
### Send Command: Carridge Return (\r)

NEMA:
 * gp?  -> GET position
 * spsN -> Step to N position using SINGLE
 * spiN -> Step to N position using INTERLEAVE
 * stsN -> Step N positions using SINGLE
 * stiN -> Step N positions using INTERLEAVE
 * stof -> Step one forward INTERLEAVE
 * stob -> Step one backward INTERLEAVE
 * sh   -> Step home SINGLE (send home)

28BYJ-48:
 * gbp?  -> GET position
 * bpsN -> Step to N position using SINGLE
 * bpiN -> Step to N position using INTERLEAVE
 * btsN -> Step N positions using SINGLE
 * btiN -> Step N positions using INTERLEAVE
 * btof -> Step one forward INTERLEAVE
 * btob -> Step one backward INTERLEAVE
 * bh   -> Step home SINGLE (send home)

## Changelog:
 * v0.2: I added a secondary stepper (28BYJ-48) to my setup, and I duplicated the code (Very, very lazy programming) to include commands for the new stepper.
 * v0.2.1: I changed the second stepper to another nema, so I changed the setup value and the name.
 * v0.2.1: Added a button to the labview code, to switch between steppers.

## LabView GUI
 * Created with LabView v14.
 * Created an initial demo LabView GUI for the Arduino code (NEMA only).
 * Covers all arduino functions. No extra functionality/calculation.
 * With tooltips on the GUI.
 * Creates a settings file and command log (if enabled) to the default LabView Data folder.

# Help, contact, and a request.
 * If you need help, open an issue, so I can track them.
 * If you have any suggestions, open an issue.
 * If you use the repository give a star. It is good to know, that someone uses the code you have written.
 * ISSUES with Arduino Leonardo:
   * The Leonardo board does not support the Motor Shield v1.
   * The Leonardo board does not handle SerialEvents. [FIX](http://forum.arduino.cc/index.php?topic=150558.msg1131262#msg1131262)
