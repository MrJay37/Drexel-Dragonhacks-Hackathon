#include "DHT.h"
#include "SparkFunCCS811.h" //Click here to get the library: http://librarymanager/All#SparkFun_CCS811#include <SPI.h>
#include <Ethernet.h>
 
#define DHTPIN 2   
#define DHTTYPE DHT11   // DHT 11

int dtemp = 4;
int val = 0;
int pin = A0;
int co;
String str;
int flag = 0;

DHT dht(DHTPIN, DHTTYPE);

//-------------------------------------------------------------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address
char server[] = "api.pushingbox.com"; //pushingbox API server
IPAddress ip(192,168,1,2); //Arduino IP address. Only used when DHCP is turned off.
EthernetClient client; //define 'client' as object
String data; //GET query with data
String dataString; //suhu (bahasa Indonesia) means temperature
boolean connected = false;
//------------------------------------------------------------------------------
void setup() {
  pinMode(dtemp,INPUT);
  pinMode(pin,INPUT);
  dht.begin();
  
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
  //Serial.println("Failed to configure Ethernet using DHCP");
  Ethernet.begin(mac, ip);
  }
  delay(1000);
}
//------------------------------------------------------------------------------
void loop(){
   char c;       
   //Serial.println(" ");
   val = digitalRead(dtemp);
   delay(100);
    
   int h = dht.readHumidity();
   str.concat(String(h));
   str.concat(",");
    
   // Read temperature as Fahrenheit (isFahrenheit = true)
   int f = dht.readTemperature(true);
   str.concat(String(f));
   str.concat(",");
   //Serial.println(f);
    
   co = analogRead(pin);
   str.concat(String(co));
   Serial.println(str); 

   if(f >= 50)
    {
      flag = 0x61;
      Serial.write(flag);
      //break;
    }
    else if(co>300)
    {
      flag = 0x62;
      Serial.write(flag);
      //break;
    }
    else if(f >= 120 && f < 140 && co > 300 && val == 1)
    {
      flag = 0x63;
      
      Serial.write(flag);
      //break;
    }
    
   dataString = str;
   createData(); //packing GET query with data
   //Serial.println("connecting...");
   if (client.connect(server, 80)) {
     sendData();  
     connected = true; //connected = true
   }
   else{
     //Serial.println("connection failed");
   }
  // loop
  while(connected){
    if (client.available()) {
    char c = client.read(); //save http header to c
    //Serial.print(c); //print http header to serial monitor
    }
    if (!client.connected()) {
    //Serial.println();
    //Serial.println("disconnecting.");
          //Serial.print("Temperature Sent :");
          //Serial.println(dataString); //print sent value to serial monitor
    client.stop(); 
          connected = false; 
          data = ""; //data reset
    }
  }
  delay(2000); // interval
  str = " "; 
  
}

void createData(){
  data+="";
  data+="GET /pushingbox?devid=v76B9C04567FDCA8&tempData="; //GET request query to pushingbox API
  data+=dataString;
  data+=" HTTP/1.1";
}
void sendData(){
  //Serial.println("connected");
  client.println(data);
  client.println("Host: api.pushingbox.com");
  client.println("Connection: close");
  client.println();
}
