#include <WiFi101.h>
#include <WiFiUdp.h>
#include <stdlib.h>
#include "secret1.h"
#include "secret2.h"
#include "secret3.h"

int resval = 0;  // holds the valuel
int respin = A0; // sensor pin used
int livelloM=0,livello1=0,livello2=0;
// valore livello pompe
int num_1=0;
int num_2=0;
// 0 pompa spenta, 1 pompa accesa
int flag_1 = 0; 
int flag_2 = 0; 

// Credenziali WiFi
//char ssid[] = "Iphone di Silvia";           // SSID della rete WiFi di Silvia
//char pass[] = "ciauciau";                   // Password della rete WiFi di Silvia

char ssid[] = "Giulia";           // SSID della rete WiFi di Giulia
char pass[] = "giuxxxxx";         // Password della rete WiFi di Giulia

//char ssid[] = "Redmi Note 9 Pro";           // SSID della rete WiFi di Giulia
//char pass[] = "angela123";         // Password della rete WiFi di Giulia

// Indirizzo IP e porta della prima pompa
IPAddress remoteIP1(192, 168, 158, 39);    // Cambia con l'indirizzo IP del primo Arduino 
unsigned int remotePort1 = 8888;        // Porta su cui ascolta il primo Arduino

// Indirizzo IP e porta della seconda pompa
IPAddress remoteIP2(192, 168, 158, 224);    // Cambia con l'indirizzo IP del secondo Arduino 
unsigned int remotePort2 = 8888;            // Porta su cui ascolta il secondo Arduino


WiFiUDP Udp;
unsigned int localPort = 8888;         // Porta su cui ascolta questo Arduino


// Vettori per salvare i valori
const int maxValues = 200;
int livelliM[maxValues];
int livelli1[maxValues];
int livelli2[maxValues];
int flagg_1[maxValues];
int flagg_2[maxValues];
int i = 0;


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
  
}

void loop() {

  resval = analogRead(respin); //Read data from analog pin and store it to resval variable

  if (resval<=Low3){
  Serial.println("Water Level of this Tank: Empty");
  livelloM=0;
  }
  else if (resval>Low3 && resval<=Medium3){
  Serial.println("Water Level of this Tank: Low");
  livelloM=1;
  }

  else if (resval>Medium3 && resval<=High3){
  Serial.println("Water Level of this Tank: Medium");
   livelloM=2;
  }

  else if (resval>High3){
  Serial.println("Water Level of this Tank: High");
   livelloM=3;
  }

  // stampa valore ricevuto
  int stampa = 0;

 char packetBuffer[255]; // Buffer per memorizzare i pacchetti ricevuti
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    IPAddress remoteIP = Udp.remoteIP();
    int remotePort = Udp.remotePort();
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0; // Termina la stringa con un carattere nullo
    }
    Serial.print("Valore ricevuto da ");
    if (remoteIP == remoteIP1 && remotePort == remotePort1) {
      num_1=atoi(packetBuffer);
      Serial.print("Arduino slave1: ");
      Serial.println(num_1);
      stampa=1;

    } else if (remoteIP == remoteIP2 && remotePort == remotePort2) {
      num_2=atoi(packetBuffer);
      Serial.print("Arduino slave2: ");
      Serial.println(num_2);
      stampa=2;
    } 
  }

if(stampa==1){
    if (num_1<=Low1){
  Serial.println("Water Level of Tank 1: Empty");
   livello1=0;
  }
  else if (num_1>Low1 && num_1<=Medium1){
  Serial.println("Water Level of Tank 1: Low");
  livello1=1;
  }

  else if (num_1>Medium1 && num_1<=High1){
  Serial.println("Water Level of Tank 1: Medium");
  livello1=2;
  }

  else if (num_1>High1){
  Serial.println("Water Level of Tank 1: High");
  livello1=3;
  }
}
  else if (stampa==2){
  
    if (num_2<=Low2){
    Serial.println("Water Level of Tank 2: Empty");
    livello2=0;
    }

    else if (num_2>Low2 && num_2<=Medium2){
    Serial.println("Water Level of Tank 2: Low");
    livello2=1;
   }

    else if (num_2>Medium2 && num_2<=High2){
   Serial.println("Water Level of Tank 2: Medium");
   livello2=2;
   }

    else if (num_2>High2){
    Serial.println("Water Level of Tank 2: High");
    livello2=3;
   }
  }

  delay(500);  // Attende 2 secondi prima di ricevere nuovi dati

  Serial.print("Livelli");
  Serial.print(livelloM);
  Serial.print(livello1);
  Serial.println(livello2);

// Salva i valori nei vettori
  livelliM[i] = livelloM;
  livelli1[i] = livello1;
  livelli2[i] = livello2;
  flagg_1[i] = flag_1;
  flagg_2[i] = flag_2;
  i++;

  // Controlla se i vettori sono pieni
  if (i == maxValues) {
    // Stampa i valori nel monitor seriale
    Serial.println("Valori di livelloM:");
    for (int i = 0; i < maxValues; i++) {
      Serial.print(livelliM[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
    }
    Serial.println();

    Serial.println("Valori di livello1:");
    for (int i = 0; i < maxValues; i++) {
      Serial.print(livelli1[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
    }
    Serial.println();

    Serial.println("Valori di livello2:");
    for (int i = 0; i < maxValues; i++) {
      Serial.print(livelli2[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
    }
    Serial.println();

    Serial.println("Pompa1:");
    for (int i = 0; i < maxValues; i++) {
      Serial.print(flagg_1[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
    }
    Serial.println();

    Serial.println("Pompa2:");
    for (int i = 0; i < maxValues; i++) {
      Serial.print(flagg_2[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
    }
    Serial.println();

    // Reimposta l'indice per continuare a salvare nuovi valori
    i = 0;
  }

  if (resval<High3 && livello1>livelloM){
    flag_1=1;
    Udp.beginPacket(remoteIP1, remotePort1);
    Udp.print(flag_1);
    Udp.endPacket();
    Serial.println("Pump 1: accesa");
  }
  else if(flag_1==1){
    flag_1=0;
    Udp.beginPacket(remoteIP1, remotePort1);
    Udp.print(flag_1);
    Udp.endPacket();
    Serial.println("Pump 1: spenta");
  }

  if (resval<High3 && livello2>livelloM){
    flag_2=1;
    Udp.beginPacket(remoteIP2, remotePort2);
    Udp.print(flag_2);
    Udp.endPacket();
    Serial.println("Pump 2: accesa");
  }
  else if(flag_2==1){
    flag_2=0;
    Udp.beginPacket(remoteIP2, remotePort2);
    Udp.print(flag_2);
    Udp.endPacket();
    Serial.println("Pump 2: spenta");
  }

  delay(500);  // Attende 2 secondi prima di inviare nuovi dati

}
