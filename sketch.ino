#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT22
#define POTPIN 32
#define LEDPIN 14
#define BTNPIN 26

const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";
const char* THINGSPEAK_API_KEY = "2CLD8HFB5TXVX3OW";
const char* THINGSPEAK_URL = "https://api.thingspeak.com/update";

DHT dht(DHTPIN, DHTTYPE);

void connectWiFi() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("WiFi conectado.");
}

void sendToThingSpeak(float temp, float hum, int nivel, int chuva) {
  HTTPClient http;
  http.begin(THINGSPEAK_URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // ⚠️ Ordem corrigida para o painel: field1 = nivel, field2 = umidade, field3 = temp, field4 = chuva
  String data = "api_key=" + String(THINGSPEAK_API_KEY);
  data += "&field1=" + String(nivel);   // Nivel do rio
  data += "&field2=" + String(hum);     // Umidade
  data += "&field3=" + String(temp);    // Temperatura
  data += "&field4=" + String(chuva);   // Chuva (0 ou 1)

  int statusCode = http.POST(data);
  Serial.print("Enviado ao ThingSpeak. HTTP Status: ");
  Serial.println(statusCode);
  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Inicializando...");
  dht.begin();
  pinMode(LEDPIN, OUTPUT);
  pinMode(BTNPIN, INPUT_PULLUP);
  connectWiFi();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int nivel = analogRead(POTPIN);
  bool chuva = digitalRead(BTNPIN) == LOW;

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" °C | Umidade: "); Serial.print(hum);
  Serial.print(" % | Nível: "); Serial.print(nivel);
  Serial.print(" | Chuva: "); Serial.println(chuva ? "SIM" : "NAO");

  if (nivel > 2048) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  sendToThingSpeak(temp, hum, nivel, chuva);
  delay(15000); // mínimo 15 segundos entre requisições
}
