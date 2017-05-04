#include <dht.h>
#include <Servo.h>
 
int servoPin = 3;
 
Servo servo;  
String temp;
 
int servoAngle = 0;   // servo position in degrees
int count =0;

dht DHT;

#define DHT11_PIN 2

#define LRL 12
#define LRF 11
#define BRL 10
#define BRF 9
#define KTL 8

const int analogInPin = A0;  
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LRL,OUTPUT);
pinMode(LRF,OUTPUT);
pinMode(BRL,OUTPUT);
pinMode(BRF,OUTPUT);
pinMode(KTL,OUTPUT);
servo.attach(servoPin);

}
String msg = "";

void loop() {

  sensorValue = analogRead(analogInPin);  
//  sensorValue = map(sensorValue, 800, 1000, 100, 0); 
  msg = Serial.readString();
    if(msg != "")
    {
      Serial.println(msg);
    
        if(msg[0] == 'L' && msg[1] == 'L' && msg[2]=='1'){
          digitalWrite(LRL, HIGH);
        }
        if(msg[0] == 'L' && msg[1] == 'L' && msg[2]=='0'){
            digitalWrite(LRL, LOW);
        }
        if(msg[0] == 'L' && msg[1] == 'F' && msg[2]=='1'){
          digitalWrite(LRF, HIGH);
        }
         if(msg[0] == 'L' && msg[1] == 'F' && msg[2]=='0'){
          digitalWrite(LRF, LOW);
        }
         if(msg[0] == 'B' && msg[1] == 'L' && msg[2]=='1'){
          digitalWrite(BRL, HIGH);
        }
         if(msg[0] == 'B' && msg[1] == 'L' && msg[2]=='0'){
          digitalWrite(BRL, LOW);
        }
         if(msg[0] == 'B' && msg[1] == 'F' && msg[2]=='1'){
          digitalWrite(BRF, HIGH);
        }
         if(msg[0] == 'B' && msg[1] == 'F' && msg[2]=='0'){
          digitalWrite(BRF, LOW);
        }
         if(msg[0] == 'K' && msg[1] == 'L' && msg[2]=='1'){
          digitalWrite(KTL, HIGH);
        }
         if(msg[0] == 'K' && msg[1] == 'L' && msg[2]=='0'){
          digitalWrite(KTL, LOW);
        }
         if(msg[0] == 'G' && msg[1] == 'T' && msg[2]=='1'){
         for(servoAngle = 10; servoAngle < 121; servoAngle++)  //now move back the micro servo from 0 degrees to 180 degrees
          {                                
            servo.write(servoAngle);          
            delay(10);      
          }
        }
         if(msg[0] == 'G' && msg[1] == 'T' && msg[2]=='0'){
           servo.write(10);
        }        
    }
/*================Temperature and Humidity===================*/
  int chk = DHT.read11(DHT11_PIN);
  delay(10);
 if(count > 5 || count ==0)
 { 
   // temp = temp + DHT.temperature + "," + DHT.humidity + "," + sensorValue+"ppp";
    int a = DHT.temperature;
    int b = DHT.humidity;
    Serial.print(a);
    Serial.print(b);
    Serial.println(sensorValue);
    count =0;
  }
  temp = "";
  count++;
  
/*===========================================================*/
            
    msg="";
   
}
