#include <WiFi101.h>
#include <WiFiUdp.h>
#include <stdlib.h>
#include "secret2.h"

//Inizializzazione
int resval;         // holds the valuel
int livello;        // valore in fascia del sensore
float x1 = 0, x2 = 0;     //stime dei 3 serbatoi 
int counter = 0, counter_pompa = 0;                //contatore per leggere il valor ogni 10 volte 
int z = 0, z_pre = 0;
float epsilon=0.3; // 1/max (di);
const int maxValues = 200; 
int z_vet[maxValues] = {0};
float x2_vet[maxValues] = {0};
int i = 0;
bool ricevuto=false;

int respin = A0;                     // sensor pin used
const int pumpPin = 7;              // Pin digitale per controllare la pompa

// Credenziali WiFi
//char ssid[] = "Iphone di Silvia";           // SSID della rete WiFi di Silvia
//char pass[] = "ciauciau";                   // Password della rete WiFi di Silvia

char ssid[] = "Giulia";           // SSID della rete WiFi di Giulia
char pass[] = "giuxxxxx";         // Password della rete WiFi di Giulia

//Credenziali WiFi
//char ssid[] = "Redmi Note 9 Pro";           // SSID della rete WiFi
//char pass[] = "angela123";       // Password della rete WiFi

// Indirizzo IP e porta della prima pompa
IPAddress remoteIP1(192, 168, 158, 222);    // Cambia con l'indirizzo IP del primo Arduino 
unsigned int remotePort1 = 8888;        // Porta su cui ascolta il primo Arduino

/*// Indirizzo IP e porta della seconda pompa
IPAddress remoteIP3(192, 168, 194, 189);    // Cambia con l'indirizzo IP del secondo Arduino 
unsigned int remotePort3 = 8888;            // Porta su cui ascolta il secondo Arduino
*/

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

  //Leggo il primo valore 
  resval = analogRead(respin);    //Read data from analog pin and store it to resval variable

  if (resval<=Low2){
  Serial.println("Water Level of this Tank: Empty");
  livello=0;
  }
  else if (resval>Low2 && resval<=Medium2){
  Serial.println("Water Level of this Tank: Low");
  livello=1;
  }

  else if (resval>Medium2 && resval<=High2){
  Serial.println("Water Level of this Tank: Medium");
  livello=2;
  }

  else if (resval>High2){
  Serial.println("Water Level of this Tank: High");
  livello=3;
  }
  z = livello;
  x2 = z;

  while(ricevuto ==false){

    Udp.beginPacket(remoteIP1, remotePort1);
    Udp.print(x2);
    Udp.endPacket();

    char packetBuffer[255]; // Buffer per memorizzare i pacchetti ricevuti
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      int len = Udp.read(packetBuffer, 255);
      ricevuto=true;
    if (len > 0) {
      packetBuffer[len] = 0; // Termina la stringa con un carattere nullo
    }
    x1 = atof(packetBuffer);
    Serial.print("Stima di Arduino 1: ");
    Serial.println(x1);
    } 
    delay(500);

  }

}

void loop() {
 
  z_pre = z;    //conservo dato precedente del sensore mio

  resval = analogRead(respin); //Read data from analog pin and store it to resval variable

  if (resval<=Low2){
  Serial.println("Water Level of this Tank: Empty");
  livello=0;
  }
  else if (resval>Low2 && resval<=Medium2){
  Serial.println("Water Level of this Tank: Low");
  livello=1;
  }
  else if (resval>Medium2 && resval<=High2){
  Serial.println("Water Level of this Tank: Medium");
  livello=2;
  }
  else if (resval>High2){
  Serial.println("Water Level of this Tank: High");
  livello=3;
  }

  Serial.print("Livello: ");
  Serial.println(livello);


  // quando x1 e x2 sono uguali aggiorno z del master col livello corrente
  if (abs(x2 - x1)<0.01){
      counter ++; 
      if(counter == 4){
        z = livello;
        Serial.print("valore aggiornato di z:");
        Serial.println(z);
        counter = 0;
      }
  }
  else{
    counter = 0; 
  }

  x2_vet[i] = x2;
  z_vet[i] = z;
  i++;  

  //Algoritmo del consenso
  x2 = x2 - epsilon*(x2-x1) + z - z_pre;

  Serial.print("Stima di Arduino 2: ");
  Serial.println(x2);

  Udp.beginPacket(remoteIP1, remotePort1);
  Udp.print(x2);
  Udp.endPacket();

  // Controlla se i vettori sono pieni
  if (i == maxValues) {
    Serial.println("Valori z2:");
      for (int i = 0; i < maxValues; i++) {
      Serial.print(z_vet[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
   }
   Serial.println();
   Serial.println("Valori x2:");
      for (int i = 0; i < maxValues; i++) {
      Serial.print(x2_vet[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
   }
   Serial.println();
   i=0;
  }

  char packetBuffer[255]; // Buffer per memorizzare i pacchetti ricevuti
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0; // Termina la stringa con un carattere nullo
    }
    x1 = atof(packetBuffer);
    Serial.print("Stima di Arduino 1: ");
    Serial.println(x1);
  } 
  
  if (livello>1 && x2 > x1 ){
    digitalWrite(pumpPin, HIGH);
    Serial.println("Pompa accesa");
  }
  else{
    //Spegne la pompa
    digitalWrite(pumpPin, LOW);
    Serial.println("Pompa spenta");
    //counter_pompa = 0;
  }

  delay(1000);  // Attende 2 secondi

}
