#include <dht.h>

dht DHT;

#define DHT11_PIN 5
const int analogInPin = A0;  
const int analogOutPin = 9; 
int analog[5] = {A0,A1,A2,A3,A4};
int sensorValue = 0;      
int value = 0;
void setup()
{
  
Serial.begin(9600);
}
String msg = "";
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
    
    if(msg == "L11")
      Serial.println("Light 1: On");
      
    if(msg == "L10")
      Serial.println("Light 1: Off");
      
    if(msg == "L21")
      Serial.println("Light 2: On");
      
    if(msg == "L20")
      Serial.println("Light 2: Off");
      
    if(msg == "L31")
      Serial.println("Light 3: On");
      
    if(msg == "L30")
      Serial.println("Light 3: Off");
    if(msg == "VAL")
      send_values();
    }
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

