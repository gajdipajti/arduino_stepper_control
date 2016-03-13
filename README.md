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
 * gp?  -> GET laser status (0: disabled, 1: enabled)
 * spsN -> Step to N position using SINGLE
 * spiN -> Step to N position using INTERLEAVE
 * stsN -> Step N positions using SINGLE
 * stiN -> Step N positions using INTERLEAVE
 * stof -> Step one forward INTERLEAVE
 * stob -> Step one backward INTERLEAVE
 * sh   -> Step home SINGLE (send home)
 
## LabView
  * Created an initial demo LabView GUI for the Arduino code.
  * Needs some documentation, and smoke testing.
