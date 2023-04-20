#include <DHT.h>

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
