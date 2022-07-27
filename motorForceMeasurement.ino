// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       motorForceMeasurement.ino
    Created:	2022. 07. 26. 14:56:56
    Author:     RAC\peter.gal
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#include <PWMServo.h>
#include <HX711.h>

HX711 hx1;
HX711 hx2;
HX711 hx3;
HX711 hx4;
HX711 hx5;
HX711 hx6;

PWMServo motor;

const int hx1_d = 0;
const int hx1_s = 1;

const int hx2_d = 2;
const int hx2_s = 3;

const int hx3_d = 4;
const int hx3_s = 5;

const int hx4_d = 6;
const int hx4_s = 7;

const int hx5_d = 8;
const int hx5_s = 9;

const int hx6_d = 10;
const int hx6_s = 11;

const int pwmout = 12;

const int pwmmin = 1000;
const int pwmmax = 2000;

const int pot = A0;
int potout;

const int master = 13;

const float hx1Calib = 1;
const float hx2Calib = 1;
const float hx3Calib = 1;
const float hx4Calib = 1;
const float hx5Calib = 1;
const float hx6Calib = 1;


void setup()
{

    Serial.begin(9600);
    Serial.println("Motor testbench program started.");

    pinMode(pwmout, OUTPUT);
    pinMode(pot, INPUT);
    pinMode(master, INPUT);

    hx1.begin(hx1_d, hx1_s);
    hx2.begin(hx2_d, hx2_s);
    hx3.begin(hx3_d, hx3_s);
    hx4.begin(hx4_d, hx4_s);
    hx5.begin(hx5_d, hx5_s);
    hx6.begin(hx6_d, hx6_s);

    hx1.set_scale(hx1Calib);
    hx2.set_scale(hx2Calib);
    hx3.set_scale(hx3Calib);
    hx4.set_scale(hx4Calib);
    hx5.set_scale(hx5Calib);
    hx6.set_scale(hx6Calib);

    hx1.tare();
    hx2.tare();
    hx3.tare();
    hx4.tare();
    hx5.tare();
    hx6.tare();

    motor.attach(pwmout, pwmmin, pwmmax);

}

// Add the main program code into the continuous loop() function
void loop()
{
    if (digitalRead(master) == 1)
    {
        potout = analogRead(pot);
        potout = map(potout, 0, 1023, 0, 180);

        motor.write(potout);
        
        Serial.print("Timestamp: ");
        Serial.println(millis());

        Serial.print("PWM: ");
        Serial.println(potout);

        int read1 = (hx1.get_units(10) * (1 / 9.81) / 1000);
        int read2 = (hx2.get_units(10) * (1 / 9.81) / 1000);
        int read3 = (hx3.get_units(10) * (1 / 9.81) / 1000);
        int read4 = (hx4.get_units(10) * (1 / 9.81) / 1000);
        int read5 = (hx5.get_units(10) * (1 / 9.81) / 1000);
        int read6 = (hx6.get_units(10) * (1 / 9.81) / 1000);

        Serial.print("result of force sensor 1: ");
        Serial.println(read1);
        Serial.print("result of force sensor 2: ");
        Serial.println(read2);
        Serial.print("result of force sensor 3: ");
        Serial.println(read3);
        Serial.print("result of force sensor 4: ");
        Serial.println(read4);
        Serial.print("result of torque sensor 5: ");
        Serial.println(read5);
        Serial.print("result of torque sensor 6: ");
        Serial.println(read6);
    }
    else
    {
        potout = 0;
        motor.write(potout);
        Serial.print("Please write current date and time of termination: ");
        String date = Serial.readString();
        Serial.print(date);
        Serial.println(" End of test.");

    }

    delay(3000);
}
