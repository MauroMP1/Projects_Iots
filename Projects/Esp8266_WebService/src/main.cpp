#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "";
const char *password = "";

// Establecer IP, Puerta de Enlace y Máscara
IPAddress ip(183, 153, 0, 45);
IPAddress gateway(183, 153, 0, 1);
IPAddress subnet(255, 255, 0, 0);

// Puerto del servidor web
ESP8266WebServer server(3838);

#define Luz D3
#define LuzL D4

void handleRoot()
{
  server.send(200, "text/plain", "Hola Mundo");
}

void encender()
{
  server.send(200, "text/plain", "Encender Living");
  digitalWrite(Luz, LOW);
}

void apagar()
{
  server.send(200, "text/plain", "http://localhost:8080/");
  digitalWrite(Luz, HIGH);
}

void encender2()
{
  server.send(200, "text/plain", "Encender Cobacha");
  digitalWrite(LuzL, LOW);
}

void apagar2()
{
  server.send(200, "text/plain", "Apagar Cobacha");
  digitalWrite(LuzL, HIGH);
}

void setup()
{
  Serial.begin(9600);
  Serial.print("Arranco Serial");

  // Conectar a la WiFi
  WiFi.begin(ssid, password);

  // Modo cliente
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);

  // Esperar hasta conectar
  Serial.print("Entro While");
  while (WiFi.status() != WL_CONNECTED)
    delay(200);

  Serial.print("Paso While");

  // Arrancar el servidor
  server.on("/", handleRoot);
  server.on("/1/on", encender);
  server.on("/1/off", apagar);
  server.on("/2/on", encender2);
  server.on("/2/off", apagar2);
  server.begin();
  Serial.print("Arranca Server");

  // Led
  pinMode(Luz, OUTPUT);
  pinMode(LuzL, OUTPUT);
  //digitalWrite(3, LOW);
  Serial.print("Pin mode");
}

void loop()
{
  // Comprobar si estamos conectados
  if (WiFi.status() == WL_CONNECTED)
  {
    server.handleClient();
  }
  else
  {
    Serial.print("no entra al if");
  }
}
