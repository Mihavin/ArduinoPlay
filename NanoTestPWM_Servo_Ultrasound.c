#include <HCSR04.h>
#include <Arduino.h>
#include <Servo.h>
#define LED 11

float distance = 0;
int idist = 0;
Servo myservo;
UltraSonicDistanceSensor distanceSensor(18, 19);  // Initialize sensor that uses digital pins 13 and 12.
unsigned long previousMeasurementMillis = 0;
const unsigned long measurementInterval = 50;

void setup () {
    pinMode(LED, OUTPUT);

    myservo.attach(17);
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    const unsigned long currentMillis = millis();

    if (currentMillis - previousMeasurementMillis >= measurementInterval) {
        previousMeasurementMillis = currentMillis;

        // Every 50 milliseconds, do a measurement using the sensor and print the distance in centimeters.
        distance = distanceSensor.measureDistanceCm();
        if (distance > 0) {
            // Serial.println(distance);
            idist = int(distance);
            Serial.println(idist);
            analogWrite(LED, idist);
            myservo.write(int(distance) * 2);
        }
    }
}
