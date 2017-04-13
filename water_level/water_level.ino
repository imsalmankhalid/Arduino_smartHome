/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
int analog[5] = {A0,A1,A2,A3,A4};
int sensorValue[5] ={0,0,0,0,0};       // value read from the pot
int value = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("0\t1\t2\t3\t4");
}

void loop() {
  // read the analog in value:
  value = 0;
  for(int i=0 ;i< 5; i++)
  {
    sensorValue[i] = analogRead(analog[i]);
    delay(10);
  }
    // print the results to the serial monitor:
//    Serial.print("sensor = ");
//    Serial.print(i);
    //Serial.print("\t output = ");
    for(int i=0; i<5; i++)
    {
      Serial.print(sensorValue[i]);
      Serial.print("\t");
      sensorValue[i] = 0;
    }
      Serial.println();

    delay(1000);
}
