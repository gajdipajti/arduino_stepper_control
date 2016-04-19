# arduino-stepper-control
Control an arduino with motor shield over serial.

 * The String->float conversion: http://forum.arduino.cc/index.php?topic=179666.msg1331654#msg1331654
 * AFMotor: https://github.com/adafruit/Adafruit-Motor-Shield-library
 * Tutorial: https://learn.adafruit.com/adafruit-motor-shield/af-stepper-class

# Start Here:
 1. Clone the repository to your sketchbook folder.
 2. Connect a Motor Shield v1 with a Stepper Motor.
 3. Burn it to your Arduino.
 
# Communication with the Controller:
## Serial: 115200 8N1
### Send Command: Carridge Return (\r)
 * gp?  -> GET position
 * spsN -> Step to N position using SINGLE
 * spiN -> Step to N position using INTERLEAVE
 * stsN -> Step N positions using SINGLE
 * stiN -> Step N positions using INTERLEAVE
 * stof -> Step one forward INTERLEAVE
 * stob -> Step one backward INTERLEAVE
 * sh   -> Step home SINGLE (send home)
 
## LabView GUI
 * Created with LabView v14.
 * Created an initial demo LabView GUI for the Arduino code.
 * Covers all arduino functions. No extra functionality/calculation.
 * With tooltips on the GUI.
 * Creates a settings file and command log (if enabled) to the default LabView Data folder.

# Help, contact, and a request.
 * If you need help, open an issue, so I can track them.
 * If you have any suggestions, open an issue.
 * If you use the repository give a star. It is good to know, that someone uses the code you have written.
