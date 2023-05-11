#include<ESP8266WiFi.h> //Biblioteca para funcionamento do WiFi do ESP
#include<ESP8266WebServer.h> //Biblioteca para o ESP funcionar como servidor
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11

const char* ssid = "sua_rede_wifi";  // Rede WiFi
const char* password = "senha_do_seu_wifi";  //Senha da Rede WiFi


#define DHTPIN D7 //Pino digital D2 ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11
DHT dht(DHTPIN, DHTTYPE); 

float temperatura; 
float umidade; 



void setup() {
  Serial.begin(9600); //Inicializa a comunicação serial
  delay(50); // Intervalo para aguardar a estabilização do sistema
  dht.begin(); //Inicializa o sensor DHT11

  Serial.println("Conectando a Rede: "); //Imprime na serial a mensagem
  Serial.println(ssid); //Imprime na serial o nome da Rede Wi-Fi

  WiFi.begin(ssid, password); //Inicialização da comunicação Wi-Fi

  //Verificação da conexão
  while (WiFi.status() != WL_CONNECTED) { //Enquanto estiver aguardando status da conexão
    delay(1000);
    Serial.print("."); //Imprime pontos
  }
  Serial.println("");
  Serial.println("WiFi Conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); //Função para exibir o IP da ESP

  server.on("/", handle_OnConnect); //Servidor recebe uma solicitação HTTP - chama a função handle_OnConnect
  server.onNotFound(handle_NotFound); //Servidor recebe uma solicitação HTTP não especificada - chama a função handle_NotFound

  //server.begin(); //Inicializa o servidor
  //Serial.println("Servidor HTTP inicializado");

}

void loop() {


   server.handleClient(); //Chama o método handleClient() para lidar com as solicitações do cliente
}

void handle_OnConnect() {
  temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  umidade = dht.readHumidity(); //Realiza a leitura da umidade
  Serial.print("Temperatura: ");
  Serial.print(temperatura); //Imprime no monitor serial o valor da temperatura lida
  Serial.println(" ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade); //Imprime no monitor serial o valor da umidade lida
  Serial.println(" %");
  server.send(200, "text/html", montarHTML(temperatura, umidade)); //Envia as informações usando o código 200, especifica o conteúdo como "text/html" e chama a função montarHTML
/*||||||||||||||||||||||||||||
 if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;


// Your Domain name with URL path or IP address with path
      http.begin(client, https://estacao-metereologia.glitch.me);

// If you need Node-RED/server authentication, insert user and password below
http.setAuthorization("https://estacao-metereologia.glitch.me", "*********");


 // Specify content-type header
      http.addHeader("Content-Type", "text/plain");
      // Data to send with HTTP POST
      String httpRequestData = "Temperatura: "+ temperatura+ " Umidade: "+ umidade;           
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

*/||||||||||||||||
}

void handle_NotFound() { //Função para lidar com o erro 404
  server.send(404, "text/plain", "Não encontrado"); //Envia o código 404, especifica o conteúdo como "text/pain" e envia a mensagem "Não encontrado"

}


