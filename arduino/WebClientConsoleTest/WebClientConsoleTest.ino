#include <DHT.h>
#include <UIPEthernet.h>
#include <Adafruit_CCS811.h>

Adafruit_CCS811 ccs;

EthernetClient client;
//server address
char server[] = "192.168.1.28";
//server port
int serverPort = 8080;

//my address
uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
IPAddress myIP(192,168,1,63);

//Pin DHT
int inputPin = 3;
#define DHTTYPE DHT11
DHT dht(inputPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("t, h, TVOC, CO2"));
  pinMode(inputPin, INPUT);
  
  dht.begin();
  if(!ccs.begin()){
    while(1);
  }
  while(!ccs.available());
  // ccs.setEnvironmentalData(dht.readHumidity(), dht.readTemperature());
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 if(ccs.available()){
  // ccs.setEnvironmentalData(h, t);
  delay(500);
  if(!ccs.readData()){
  Serial.print(t);
  Serial.print(F(", "));
  Serial.print(h);
  Serial.print(F(", "));
  Serial.print(ccs.getTVOC());
  Serial.print(F(", "));
  Serial.println(ccs.geteCO2());
  }
 }
//  doGet(String(t)); //seng GET request  
//  while(client.connected()){
//    if(client.available()){
//      char c = client.read();
//      Serial.print(c);  
//    }
//  }
delay(10000);
}

// http get request
void doGet(String param) {
    Ethernet.begin(mac,myIP);
    if (client.connect(server,serverPort)){
      //Serial.println("Connected to server");
      client.print(F("GET /sens?t="));
      client.print(param);
      client.println(F(" HTTP/1.1"));
      client.print(F("Host: "));
      client.println(server);
      client.println();
  }else{
      //Serial.println("Connection to server failed");
  }
}
