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

#include <HX711.h>
#include <Servo.h>




Servo motor;

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

HX711 hx1;
HX711 hx2;
HX711 hx3;
HX711 hx4;
HX711 hx5;
HX711 hx6;


const int pwmout = 12;
const int pwmmin = 1000;
const int pwmmax = 2000;

char potout = 0;

int pwm;

const int master = 13;

const int currentMeas = A5;

float current;

int pwmtomotor;

const float hx1Calib = 93870.43;
const float hx2Calib = -103950.70;
const float hx3Calib = 92177.35;
const float hx4Calib = 102815.72;
const float hx5Calib = -99859.09;
const float hx6Calib = 95043.76;

float read1;
float read2;
float read3;
float read4;
float read5;
float read6;

long previousMillis = 0;
long currentMillis = 0;

int interval = 300;

void setup()
{

    Serial.begin(115200);

    pinMode(pwmout, OUTPUT);
    pinMode(master, INPUT);
    pinMode(currentMeas, INPUT);

    hx1.begin(hx1_d, hx1_s);
    hx2.begin(hx2_d, hx2_s);
    hx3.begin(hx3_d, hx3_s);
    hx4.begin(hx4_d, hx4_s);
    hx5.begin(hx5_d, hx5_s);
    hx6.begin(hx6_d, hx6_s);

    hx1.tare();
    hx2.tare();
    hx3.tare();
    hx4.tare();
    hx5.tare();
    hx6.tare();

    hx1.set_scale(hx1Calib);
    hx2.set_scale(hx2Calib);
    hx3.set_scale(hx3Calib);
    hx4.set_scale(hx4Calib);
    hx5.set_scale(hx5Calib);
    hx6.set_scale(hx6Calib);

    motor.attach(pwmout);
}

// Add the main program code into the continuous loop() function
void loop()
{

    if (digitalRead(master) == 1)
    {
        
        if (Serial.available() > 0)
        {
            potout = Serial.read();
        }
        
        if (potout == 101)
        {
            hx1.tare();
            hx2.tare();
            hx3.tare();
            hx4.tare();
            hx5.tare();
            hx6.tare();
        }
        else if (potout == 102)
        {
            potout = 0;
            pwm = 0;
            motor.writeMicroseconds(pwm);
        }
        else
        {
            pwm =(int)potout;

            pwm = map(pwm, 0, 100, 1000, 2000);

            motor.writeMicroseconds(pwm);

            read1 = hx1.get_units();

            read2 = hx2.get_units();

            read3 = hx3.get_units();

            read4 = hx4.get_units();

            read5 = hx5.get_units();

            read6 = hx6.get_units();

            current = analogRead(currentMeas);

        }
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval == true)
        {
            String writeString = String(millis() * 0.001) + "," + String(pwm) + "," + String(read1) + "," + String(read2) + "," + String(read3) + "," + String(read4) + "," + String(read5) + "," + String(read6) + "," + String(current);

            for (size_t i = 0; i < writeString.length(); i++)
            {
                char c = writeString.charAt(i);
                Serial.write(c);
            }
            Serial.write('\n');

            previousMillis = currentMillis;
        }
    }
    else if (digitalRead(master) == 0)
    {
        potout = 0;
        pwm = 0;
        motor.write(pwm);
    }

}
