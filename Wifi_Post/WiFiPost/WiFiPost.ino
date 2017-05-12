/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include <Servo.h>
 
int servoPin = D7;

#define LRL D1 //12
#define LRF D0  // 11
#define BRL D3 //10
#define BRF D2 //9
#define KTL D4 //8

const char* ssid     = "HomeWIFI";
const char* password = "03004245944";
const char* host = "home-test.000webhostapp.com";
int sensorValue = 0;
Servo servo;  
int servoAngle = 0;
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LRL,OUTPUT);
  pinMode(LRF,OUTPUT);
  pinMode(BRL,OUTPUT);
  pinMode(BRF,OUTPUT);
  pinMode(KTL,OUTPUT);
  
  digitalWrite(LRL, LOW);
  digitalWrite(LRF, LOW);
  digitalWrite(BRL, LOW);
  digitalWrite(BRF, LOW);
  digitalWrite(KTL, LOW);
    
  servo.attach(servoPin);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(10);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/add.php";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  String PostData = "temp1=77&hum1=77&water=77";
  // This will send the request to the server
 client.println("POST /switch_read.php HTTP/1.1");
client.println("Host: home-test.000webhostapp.com");
client.println("Cache-Control: no-cache");
client.println("Content-Type: application/x-www-form-urlencoded");
client.print("Content-Length: ");
client.println(PostData.length());
client.println();
client.println(PostData);
String line;
int count = 0;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    line.concat(client.readStringUntil('\r'));
  }
  Serial.println(line);
  Serial.println("Last index");

  if(line.indexOf("L11") > 0)
  {
    Serial.println("L11");
     digitalWrite(LRL, HIGH);
  }
  if(line.indexOf("L10") > 0)
  {
    Serial.println("L10");
     digitalWrite(LRL, LOW);
  }
  if(line.indexOf("L21") > 0)
  {
    Serial.println("L21");
     digitalWrite(LRF, HIGH);
  }
  if(line.indexOf("L20") > 0)
  {
    Serial.println("L20");
     digitalWrite(LRF, LOW);
  }
  if(line.indexOf("L31") > 0)
  {
    Serial.println("L31");
     digitalWrite(BRL, HIGH);
  }
  if(line.indexOf("L30") > 0)
  {
    Serial.println("L30");
     digitalWrite(BRL, LOW);
  }
  if(line.indexOf("L41") > 0)
  {
    Serial.println("L41");
     digitalWrite(BRF, HIGH);
  }
  if(line.indexOf("L40") > 0)
  {
    Serial.println("L40");
     digitalWrite(BRF, LOW);
  }
  if(line.indexOf("L51") > 0)
  {
    Serial.println("L51");
     digitalWrite(KTL, HIGH);
  }
  if(line.indexOf("L50") > 0)
  {
    Serial.println("L50");
     digitalWrite(KTL, LOW);
  }
  if(line.indexOf("L61") > 0)
  {
   Serial.println("L61");
   for(servoAngle = 10; servoAngle < 121; servoAngle++)  //now move back the micro servo from 0 degrees to 180 degrees
    {                                
      servo.write(servoAngle);          
      delay(10);      
    }
  }
  if(line.indexOf("L60") > 0)
  {
    Serial.println("L60");
      servo.write(10);
  }  
  Serial.println();
  Serial.println("closing connection");
}

