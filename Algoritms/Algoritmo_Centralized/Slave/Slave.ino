#include <WiFi101.h>
#include <WiFiUdp.h>
#include <stdlib.h>
#include "secret2.h"


int resval = 0;                        // holds the valuel
int respin = A0;                        // sensor pin used
const int pumpPin = 7;              // Pin digitale per controllare la pompa


// Credenziali WiFi
//char ssid[] = "Iphone di Silvia";           // SSID della rete WiFi
//char pass[] = "ciauciau";       // Password della rete WiFi


// Credenziali WiFi
char ssid[] = "Giulia";           // SSID della rete WiFi
char pass[] = "giuxxxxx";       // Password della rete WiFi

//char ssid[] = "Scx";           // SSID della rete WiFi
//char pass[] = "coppolino1";       // Password della rete WiFi

//Credenziali WiFi
//char ssid[] = "Redmi Note 9 Pro";           // SSID della rete WiFi
//char pass[] = "angela123";       // Password della rete WiFi

// Indirizzo IP e porta del secondo Arduino
IPAddress remoteIP(192, 168, 158, 222);  // Cambia con l'indirizzo IP del secondo Arduino  
unsigned int remotePort = 8888;        // Porta su cui ascolta il secondo Arduino

WiFiUDP Udp;
unsigned int localPort = 8888;         // Porta su cui ascolta questo Arduino

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Attende che la porta seriale sia connessa
  }

  // Connessione alla rete WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connesso al WiFi");

  Udp.begin(localPort);

  // Inizializza il pin della pompa come output
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW); // Assicura che la pompa sia spenta all'inizio
}

void loop() {

  resval = analogRead(respin); //Read data from analog pin and store it to resval variable

  // Invia il valore al secondo Arduino
  Udp.beginPacket(remoteIP, remotePort);
  Udp.print(resval);
  Udp.endPacket();
  
  Serial.println("Valore inviato: " + String(resval));
  if (resval<=Low1){
  Serial.println("Water Level of this Tank: Empty");
  }
  else if (resval>Low1 && resval<=Medium1){
  Serial.println("Water Level  of this Tank: Low");
  }

  else if (resval>Medium1 && resval<=High1){
  Serial.println("Water Level of this Tank: Medium");
  }

  else if (resval>High1){
  Serial.println("Water Level of this Tank: High");
  }

  delay(1000);  // Attende 2 secondi prima di inviare nuovi dati

  // Riceve il valore dall'altro Arduino
  char packetBuffer[255];  // Buffer per memorizzare i pacchetti ricevuti
  int packetSize = Udp.parsePacket();
  int flag=0;
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;  // Null-terminate the string
    }
    Serial.println("Valore ricevuto: " + String(packetBuffer));
    flag = atoi(packetBuffer);
    Serial.println("flag");
    Serial.println(flag);
  }

    if (flag==1){
    digitalWrite(pumpPin, HIGH);
    Serial.println("Pompa accesa");
    }
    else{
      //Spegne la pompa
    digitalWrite(pumpPin, LOW);
    Serial.println("Pompa spenta");
  }

  delay(1000);  // Attende 1 secondi prima di ricevere nuovi dati
}
