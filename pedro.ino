#include "DualVNH5019MotorShield.h" //drive motor
#include "Wire.h"
#include "mavlink.h"
#include <SoftwareSerial.h>


void setup()
{
    md.init();
    // ss.begin(115200);
    _starttime_r = millis();
    _starttime_s = millis();
    _starttime_m = millis();
    Serial.begin(9600);
    Serial3.begin(115200);
    pinMode(28, INPUT); // leme
    pinMode(26, INPUT); // vela
}

