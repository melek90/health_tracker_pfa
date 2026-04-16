#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"

// WiFi
const char* ssid = "nom_wifi";
const char* password = "mot de passe";
const char* serverName = "http://adresse_ip_du_serveur:5000/data";

// AD8232
#define ECG_PIN 34
#define LO_PLUS 32
#define LO_MINUS 33

// capteurs
Adafruit_MLX90614 mlx;
PulseOximeter pox;


float hp = 0, lp = 0, prev = 0;
int ecgValue = 0;


float bpm = 0;


float tempBody = 0;


// filtre ecg
int processECG(int raw){
  hp = 0.97 * (hp + raw - prev);
  prev = raw;
  lp = 0.15 * hp + 0.85 * lp;
  return constrain((int)(lp / 12 + 128), 0, 255);
}

void setup(){
  Serial.begin(115200);

  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);

  Wire.begin(21, 22);
  mlx.begin();

  if(!pox.begin()){
    Serial.println("MAX30100 ERROR");
  }

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(300);
  }

  Serial.println(" System Ready");
}

void loop(){

  // temperature
  float t = mlx.readObjectTempC();
  if(!isnan(t)) tempBody = t;

  //bpm
  pox.update();
  bpm = pox.getHeartRate();

  //
  if(digitalRead(LO_PLUS) == 1 || digitalRead(LO_MINUS) == 1){
    ecgValue = 0;
  } else {
    int raw = analogRead(ECG_PIN);
    ecgValue = processECG(raw);
  }

  
  Serial.print("ECG: ");
  Serial.print(ecgValue);
  Serial.print(" | BPM: ");
  Serial.print(bpm);
  Serial.print(" | Temp: ");
  Serial.println(tempBody);

  // envoi les données vers le serveur flask
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    String url = String(serverName) +
      "?ecg=" + ecgValue +
      "&bpm=" + bpm +
      "&temp=" + tempBody;

    http.begin(url);
    http.GET();
    http.end();
  }

  delay(10);
}