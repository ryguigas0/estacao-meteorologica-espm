#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11

// Wi-Fi
const char* ssid = "";
const char* password = "";

DHT dht(D1, DHT11);

float temperatura; //variável para armazenar a temperatura
float umidade; //Variável para armazenar a umidade

bool conectarWiFi() {
  Serial.println("Tentando estabelecer uma conexao com a rede Wi-Fi...");
  
  const unsigned long tempoInicial = millis();
  
  WiFi.begin(ssid, password);
  
  do {
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Conexao Wi-Fi estabelecida com sucesso!");
      
      IPAddress ip = WiFi.localIP();
      Serial.print("IP local: ");
      Serial.printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
      
      return true;
    }
    
    delay(1000);
    
  } while ((millis() - tempoInicial) < 30000L);
  
  Serial.println("Impossivel estabelecer uma conexao com a rede Wi-Fi!");
  
  return false;
}

bool verificarWiFi() {
  if (WiFi.status() == WL_CONNECTED)
    return true;
  
  Serial.println("Conexao Wi-Fi perdida.");
  
  WiFi.disconnect(true);
  
  delay(5000);
  
  return conectarWiFi();
}

void setup() {
  Serial.begin(115200);
  
  // Para evitar perder as primeiras mensagens do console
  Serial.println();
  Serial.flush();
  delay(1000);
  Serial.println();
  Serial.flush();
  delay(1000);
  
  Serial.println("Iniciando...");

  dht.begin();
  
  WiFi.mode(WIFI_STA);
  conectarWiFi();
}

void loop() {
  if (!verificarWiFi())
    return;

  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  
  WiFiClientSecure secureClient;
  secureClient.setInsecure(); // Belo trocadilho... :) //Odeio piadas >:(
  
  HTTPClient httpClient;

  String json = "{\"leitura\":{\"temperatura\":";
  json += temperatura;
  json +=  ",\"umidade\":";
  json += umidade;
  json += "}}";
  
  httpClient.begin(secureClient, "estacao-metereologia.glitch.me", 443, "/leitura", true);
  
  // Configura o tempo máximo de espera.
  httpClient.setTimeout(60 * 60 * 1000);
  
  // Configura o cabeçalho HTTP Connection: close,
  // para pedir para o servidor encerrar a conexão TCP ao final.
  // Por padrão HTTPClient envia o cabeçalho Connection: keep-alive,
  // e tenta reaproveitar a conexão TCP.
  httpClient.setReuse(false);
  
  // Vamos precisar enviar ao menos um cabeçalho, com o tipo do dado
  // que estamos enviando para o servidor. Estou definindo application/json
  // porque o servidor simplesmente devolve para nós o que enviamos para ele.
  httpClient.addHeader("Content-Type", "application/json");

  httpClient.addHeader("ADMIN_KEY", "**********");
  
  Serial.println("Enviando requisicao POST HTTPS...");

  Serial.println("JSON: ");
  Serial.println(json);

  int statusCode = httpClient.POST(json);
  
  if (statusCode > 0) {
    Serial.print("Status code: ");
    Serial.println(statusCode);

    String body = httpClient.getString();
    Serial.println(body);
    
    if (statusCode != HTTP_CODE_CREATED) {
      Serial.println("ERRO DE REQUISICAO");
    }
  } else {
    Serial.print("Ocorreu um erro de comunicacao: ");
    Serial.println(httpClient.errorToString(statusCode));
  }
  
  httpClient.end();
  
  Serial.println();
  Serial.println();
  Serial.println("Aguardando para repetir o processo...");
  Serial.println();
  Serial.println();
  
  delay(15 * 60 * 1000);
  
}