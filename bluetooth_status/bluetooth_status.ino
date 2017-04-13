#include <dht.h>

dht DHT;

#define DHT11_PIN 5
const int analogInPin = A0;  
const int analogOutPin = 9; 
int analog[5] = {A0,A1,A2,A3,A4};
int sensorValue = 0;      
int value = 0;
bool st = 0;
char txt[20];
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
    st=1;
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    //Serial.print("ER1"); 
    st=0;
    break;
    
    case DHTLIB_ERROR_TIMEOUT: 
    //Serial.print("ER2"); 
    st=0;
    break;
    case DHTLIB_ERROR_CONNECT:
      //  Serial.print("ER3");
    st=0;
    break;
    case DHTLIB_ERROR_ACK_L:
        //Serial.print("ER4");
    st=0;
    break;
    case DHTLIB_ERROR_ACK_H:
        //Serial.print("ER5");
    st=0;
    break;
    default: 
    //Serial.print("ER0"); 
    st=0;
    break;
  }
  // DISPLAY DATA
  //sprintf(txt,"%d,%d,%d",DHT.humidity,DHT.temperature,25);
//  Serial.print(DHT.humidity,1);
//  Serial.print(DHT.temperature,1);
//  Serial.println(25);  
 char buf[4];
 char tmp[2];
 char str[15];
  dtostrf(DHT.humidity,3, 0, buf);
  dtostrf(DHT.temperature,2, 0, tmp);
  sprintf(str,"%s,%s,%d",buf,tmp,25);
  Serial.println(str);
  delay(1000);
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

