#define NODE_ID 1

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <string.h>
 
const char* ssid = "Darth_Vader";//type your ssid
const char* password = "12345678";//type your password
 
int ledPin = 4; // GPIO2 of ESP8266
WiFiServer server(80);//Service Port
HTTPClient http;

int PIR = 4;
int mq2 = A0;

bool connect_wifi() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);

  for(int i=0; i<20 && WiFi.status() != WL_CONNECTED; i++) {
    delay(500);
    Serial.print(".");
  }
  if(WiFi.status()==WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
   
    // Print the IP address
    Serial.print(WiFi.localIP());
    Serial.println("/");

    return true;
  }
  return false;
}

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  pinMode(PIR, INPUT);
  pinMode(mq2, INPUT);
  connect_wifi();
  http.setReuse(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()!=WL_CONNECTED) connect_wifi();
  else {
    int pir = digitalRead(PIR);
    int mqtwo = analogRead(mq2);
    
    char gateway[100];
    sprintf(gateway, "http://192.168.0.101/submit_data.php?node_id=%d&pir=%d&mq2=%d", NODE_ID, pir, mqtwo);
    http.begin(gateway); //HTTP
    int httpCode = http.GET();
    //Serial.println(http.getString());
    if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK) {
        Serial.println("success");
        Serial.println(http.getString());
      }
      else Serial.println('HTTP error');
    }
    else Serial.println('Error');
    http.end();
  }
}
