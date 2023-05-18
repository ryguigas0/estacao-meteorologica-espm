#include<ESP8266WiFi.h> //Biblioteca para funcionamento do WiFi do ESP
#include<ESP8266WebServer.h> //Biblioteca para o ESP funcionar como servidor
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11
#include <ESP8266HTTPClient.h>
const char* ssid = "sua_rede_wifi";  // Rede WiFi
const char* password = "senha_do_seu_wifi";  //Senha da Rede WiFi

ESP8266WebServer server(80); //server na porta 80

#define DHTPIN D7 //Pino digital D2 ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

float temperatura; //variável para armazenar a temperatura
float umidade; //Variável para armazenar a umidade

void setup() {
  Serial.begin(115200); //Inicializa a comunicação serial
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

  server.begin(); //Inicializa o servidor
  Serial.println("Servidor HTTP inicializado");

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

}

void handle_NotFound() { //Função para lidar com o erro 404
  server.send(404, "text/plain", "Não encontrado"); //Envia o código 404, especifica o conteúdo como "text/pain" e envia a mensagem "Não encontrado"

}

String montarHTML(float Temperaturastat, float Umidadestat) { //Exibindo a página da web em HTML
  String ptr = "<!DOCTYPE html> <html>\n"; //Indica o envio do código HTML
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; //Torna a página da Web responsiva em qualquer navegador Web
  ptr += "<meta http-equiv='refresh' content='2'>";//Atualizar browser a cada 2 segundos
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>Monitor de Temperatura e Umidade</title>\n"; //Define o título da página

  //Configurações de fonte do título e do corpo do texto da página web
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #000000;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += "h2 {margin: 40px auto 20px;}\n";
  ptr += "p {font-size: 24px;color: #000000;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Monitor de Temperatura e Umidade</h1>\n";
  
  //Exibe as informações de temperatura e umidade na página web
  ptr += "<p><b>Temperatura: </b>";
  ptr += (float)Temperaturastat;
  ptr += " Graus Celsius</p>";
  ptr += "<p><b>Umidade: </b>";
  ptr += (float)Umidadestat;
  ptr += " %</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;

/*
#include <ESP8266WiFi.h>

// A biblioteca HttpClient padrão do Arduino é essa aqui:
// https://www.arduino.cc/reference/en/libraries/httpclient/
// Mas, como estamos utilizando o ESP8266, vamos utilizar a biblioteca própria dele:
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h
#include <ESP8266HTTPClient.h>

// Atenção...
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiClientSecure.h
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiClientSecureBearSSL.h
// Se incluir diretamente WiFiClientSecureBearSSL.h, precisará referenciar o namespace explicitamente:
// BearSSL::WiFiClientSecure client;
#include <WiFiClientSecure.h>

// Impressão digital (Fingerprint) do certificado do servidor remoto...
// Pode ser ignorado, com cuidado...!
//const byte fingerprint[] = { 0x1b, 0x46, 0x22, 0x4e, 0x27, 0x6f, 0x0d, 0xdc, 0x77, 0xd1, 0xb1, 0x58, 0x24, 0x71, 0x8b, 0xe5, 0x0d, 0x44, 0x45, 0xdb };

// Wi-Fi
extern const char* ssid;
extern const char* password;

// Muitos exemplos utilizam o ESP8266WiFiMulti por ser prático. Mas, se não formos efetivamente
// tentar utilizar múltiplos SSIDs, podemos economizar memória fazendo o processo na mão!
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiMulti.h
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiMulti.cpp
//#include <ESP8266WiFiMulti.h>
//ESP8266WiFiMulti WiFiMulti;


#define DHTPIN D7
#define DHTTYPE DHT11 //Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

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
  
  WiFi.mode(WIFI_STA);
  conectarWiFi();
}

void loop() {
temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  umidade = dht.readHumidity(); //Realiza a leitura da umidade
  
  if (!verificarWiFi())
    return;
  
  WiFiClientSecure secureClient;
  secureClient.setInsecure(); // Belo trocadilho... :)
  //secureClient.setFingerprint(fingerprint);
  
  HTTPClient httpClient;
  
  // begin() não realiza nenhum tipo de comunicação via rede, apenas
  // prepara o objeto para ser utilizado depois. Existe uma forma mais
  // prática, mas consome mais memória:
  // httpClient.begin(secureClient, "https://academico.espm.br/echo");
  httpClient.begin(secureClient, "https://estacao-metereologia.glitch.me", "/echo", true);
  
  // Configura o tempo máximo de espera.
  httpClient.setTimeout(30000);
  
  // Configura o cabeçalho HTTP Connection: close,
  // para pedir para o servidor encerrar a conexão TCP ao final.
  // Por padrão HTTPClient envia o cabeçalho Connection: keep-alive,
  // e tenta reaproveitar a conexão TCP.
  httpClient.setReuse(false);
  
  // Vamos precisar enviar ao menos um cabeçalho, com o tipo do dado
  // que estamos enviando para o servidor. Estou definindo application/octet-stream
  // apenas para que o retorno do servidor fique diferente do outro exemplo :)
  // Poderíamos enviar qualquer outro tipo, como application/json, text/plain,
  // application/x-www-form-urlencoded etc.
  httpClient.addHeader("Content-Type", "application/octet-stream");
  
  // Se não precisar ler os valores dos cabeçalhos da resposta, basta
  // remover o trecho de código abaixo, junto com o array.
  // Os nomes dos cabeçalhos são tratados ignorando caixa alta ou caixa baixa,
  // mas a busca utilizada no método httpClient.header(name) não ignora!!!
  const char* cabecalhos[] = { "Content-Type", "Date", "Last-Modified", "Server" };
  httpClient.collectHeaders(cabecalhos, 4);
  
  Serial.println("Enviando requisicao POST HTTPS...");
  // Aqui pode ser enviado tanto um array de bytes como uma String:
  //https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h#L192
  // Importante!!! Aqui nenhum tipo de conversão é realizada pela classe HTTPClient!
  // Ou seja, precisamos saber direitinho o formato/codificação dos dados
  // que estão sendo enviados para o servidor!
  const byte dados[] = { 'o', 'i', ',', 'm', 'u', 'n', 'd', 'o' };
  int statusCode = httpClient.POST(dados, 8);
  
  // Valores negativos não são códigos HTTP válidos, e indicam
  // um erro de comunicação, ou do hardware.
  if (statusCode > 0) {
    Serial.print("Status code: ");
    Serial.println(statusCode);
    
    // Veja a descrição da classe para outros métodos úteis,
    // e outras formas de fazer isso:
    // https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h#L206
    Serial.println("Cabecalhos recebidos:");
    for (byte i = 0; i < 4; i++) {
      Serial.print(cabecalhos[i]);
      Serial.print(": ");
      Serial.println(httpClient.header(i));
    }
    
    // O cabeçalho Content-Length não precisa ser pedido
    // explicitamente, porque ele é sempre tratado.
    Serial.print("Content-Length: ");
    Serial.println(httpClient.getSize());
    
    // Para ver todas as contantes disponíveis:
    // https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h#L64
    if (statusCode == HTTP_CODE_OK) {
      // Podemos pedir para o httpClient ler todo o conteúdo
      // na memória, para depois ser trabalhado, ou podemos
      // simplesmente pedir para o conteúdo ser redirecionado
      // para outro stream, como a porta serial.
      //String body = httpClient.getString();
      //Serial.println(body);
      httpClient.writeToStream(&Serial);
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
  
  delay(5000);
}
*/

}
