#include <dht.h>
dht DHT;

#define DHT11_PIN 2

#define Living_Room_Light 12
#define Living_Room_Fan   11
#define Bed_Room_Light    10
#define Bed_Room_Fan      9
#define Kitchen_Light     8

const int analogInPin = A0;  
const int analogOutPin = 9; 
int analog[5] = {A0,A1,A2,A3,A4};
int sensorValue = 0;      
int value = 0;
void setup()
{
    
  Serial.begin(9600);
  pinMode(Living_Room_Light,OUTPUT);
  pinMode(Living_Room_Fan,OUTPUT);
  pinMode(Bed_Room_Light,OUTPUT);
  pinMode(Bed_Room_Fan,OUTPUT);
  pinMode(Kitchen_Light,OUTPUT);
  Serial.println("Welcome"); 
}
String msg = "";
int count = 0;
void loop()
{
  // READ DATA
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    //Serial.print("OK1"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    //Serial.print("ER1"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    //Serial.print("ER2"); 
    break;
    case DHTLIB_ERROR_CONNECT:
      //  Serial.print("ER3");
        break;
    case DHTLIB_ERROR_ACK_L:
        //Serial.print("ER4");
        break;
    case DHTLIB_ERROR_ACK_H:
        //Serial.print("ER5");
        break;
    default: 
    //Serial.print("ER0"); 
    break;
  }
  
  if(Serial.available())
  {
    msg = Serial.readString();
  }
    if(msg!=""){
      //Serial.println(msg);
    
    if(msg == "L11"){
      //Serial.println("Living_Room_Light: On");
      digitalWrite(Living_Room_Light, HIGH);
    }
    if(msg == "L10"){
      //Serial.println("Living_Room_Light: Off");
      digitalWrite(Living_Room_Light, LOW);
    }
    if(msg == "L21"){
      //Serial.println("Living_Room_Fan: On");
      digitalWrite(Living_Room_Fan, HIGH);
    }
    if(msg == "L20"){
      //Serial.println("Living_Room_Fan: Off");
      digitalWrite(Living_Room_Fan, LOW);
    }
    if(msg == "L31"){
      //Serial.println("Bed_Room_Light: On");
      digitalWrite(Bed_Room_Light, HIGH);
    }
    if(msg == "L30"){
      //Serial.println("Living_Room_Fan: Off");
      digitalWrite(Bed_Room_Light, LOW);
    }
    if(msg == "L41"){
      //Serial.println("Bed_Room_Fan: On");
      digitalWrite(Bed_Room_Fan, HIGH);
    }
    if(msg == "L40"){
      //Serial.println("Bed_Room_Fan: Off");
      digitalWrite(Bed_Room_Fan, LOW);
    }
    if(msg == "L51"){
      //Serial.println("Kitchen_Light: On");
      digitalWrite(Kitchen_Light, HIGH);
    }    
    if(msg == "L50"){
      //Serial.println("Kitchen_Light: Off");
      digitalWrite(Kitchen_Light, LOW);
    }
    if(msg == "ALL1"){
      //Serial.println("All: On");
      digitalWrite(Living_Room_Light, HIGH);
      digitalWrite(Living_Room_Fan, HIGH);
      digitalWrite(Bed_Room_Light, HIGH);
      digitalWrite(Bed_Room_Fan, HIGH);
      digitalWrite(Kitchen_Light, HIGH);
    }
    if(msg == "ALL0"){
      //Serial.println("All: Off");
      digitalWrite(Living_Room_Light, LOW);
      digitalWrite(Living_Room_Fan, LOW);
      digitalWrite(Bed_Room_Light, LOW);
      digitalWrite(Bed_Room_Fan, LOW);
      digitalWrite(Kitchen_Light, LOW);
    }
    if(msg == "VAL")
      send_values();
    }
     if( count > 500){
      send_values();
      count=0;
     }
    count++;
      msg = "";
}

void send_values()
{
  Serial.print(DHT.temperature, 0);
  Serial.print(",");
  Serial.print(DHT.humidity, 0);
  Serial.print(",");
  check_water();
  Serial.print(",");
  Serial.print("70");  
  Serial.print("$");
}
void check_water()
{
  // read the analog in value:
  value = 50;
  for(int i=0 ;i< 5; i++)
  {
    sensorValue = analogRead(analog[i]);
    if(sensorValue <1010)
      value = i;
//      delay(2);
  }
switch (value)
{
   case 0:
    Serial.print("10");
    break;

  case 1:
    Serial.print("20");
    break;

  case 2:
    Serial.print("30");
    break;
  case 3:
    Serial.print("40");
    break;    
  case 4:
    Serial.print("90");
    break;
  default:
    Serial.print("80");
    break;
}
value = 50;
}


