# motorForceMeasurement

Code for conducting BLDC motor measurements with Teensy 4.0 board.
User installed HX711.h and board specific Servo.h library required.
The code handles 6 strain gauges, a master switch, PWM signal, and USB serial.
Strain gauges need to be calibrated (hx*Calib parameters).
Low state of master switch keeps PWM signal at 0.
Teensy board gets PWM signal on USB serial (potout) from a WinForm application.
