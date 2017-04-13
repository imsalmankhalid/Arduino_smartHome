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
  // DISPLAY DATA
  Serial.print("Humidity Level = ");
  Serial.print(DHT.humidity, 1);
  Serial.print("  Temperature = ");
  Serial.print(DHT.temperature, 1);
  Serial.print("  Water Level = ");
  check_water();
  Serial.println("");
  delay(2000);
}

void check_water()
{
  // read the analog in value:
  value = 50;
  for(int i=0 ;i< 5; i++)
  {
    sensorValue = analogRead(analog[i]);
    // map it to the range of the analog out:
    if(sensorValue <1010)
      value = i;
      delay(500);
  }
switch (value)
{
   case 0:
    Serial.print("LOW");
    break;

  case 1:
    Serial.print("LEVEL 2");
    break;

  case 2:
    Serial.print("LEVEL 3");
    break;
  case 3:
    Serial.print("LEVEL 4");
    break;    
  case 4:
    Serial.print("FULL");
    break;
  default:
    Serial.print("NO WATER");
    break;
}
value = 50;
}

