#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

float temp, umid;
int pino_dht = 9;
DHT dht(pino_dht, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  temp = dht.readTemperature();
  umid = dht.readHumidity();

  Serial.print("TEMP: ");
  Serial.println(temp);
  Serial.print("UMID: ");
  Serial.println(umid);
}



const char* ssid = "colocar_o_SSID";
const char* password = "colocar_a_senha";

//Your Domain name with URL path or IP address with path
const char* serverName = "https://estacao-metereologia.glitch.me";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado com o WiFi e IP: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("timer de 5 segundos (timerDelay variable), vai levar 5 segundos.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
http.setAuthorization("https://estacao-metereologia.glitch.me", "GeriatricFilling");
POST /update-sensor HTTP/1.1
Host: example.com
{api_key: "tPmAT5Ab3j7F9", sensor_name: "dht", temperature: temp; humidity: umid; tempo: __TIME__}
Content-Type: application/json