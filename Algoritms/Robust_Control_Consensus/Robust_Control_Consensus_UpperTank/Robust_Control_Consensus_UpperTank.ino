#include <WiFi101.h>
#include <WiFiUdp.h>
#include <stdlib.h>
#include "secret1.h"

//Inizializzazione variabili
int resval ;      // holds the value
int livello;    // valore in fascia del sensore
float x1=0,x2=0,x3=0; // stime dei 3 serbatoi
int z =0; 
int z_pre=0;
float epsilon=0.4; // 1/max (di)
int counter=0;

float delta12=0, delta13=0;
float delta12_pre=0, delta13_pre=0;
bool ricevuta2=false,ricevuta3=false;
int counter2=0, counter3=0;
int counter_while=0;

int respin = A0; // sensor pin used

// flag per ricezione dati
bool new_x_ricevuta_1 = false;
bool new_x_ricevuta_2 = false;


bool new_x_ricevutaa_1 = false;
bool new_x_ricevutaa_2 = false;


// Credenziali WiFi
//char ssid[] = "Iphone di Silvia";           // SSID della rete WiFi di Silvia
//char pass[] = "ciauciau";                   // Password della rete WiFi di Silvia

char ssid[] = "Giulia";           // SSID della rete WiFi di Giulia
char pass[] = "giuxxxxx";         // Password della rete WiFi di Giulia

//char ssid[] = "Redmi Note 9 Pro";           // SSID della rete WiFi
//char pass[] = "angela123";       // Password della rete WiFi

// Indirizzo IP e porta della prima pompa
IPAddress remoteIP2(192, 168, 158, 224);    // Cambia con l'indirizzo IP del primo Arduino 
unsigned int remotePort2 = 8889;        // Porta su cui ascolta il primo Arduino

// Indirizzo IP e porta della seconda pompa
IPAddress remoteIP3(192, 168, 158, 39);    // Cambia con l'indirizzo IP del secondo Arduino 
unsigned int remotePort3 = 8890;            // Porta su cui ascolta il secondo Arduino


WiFiUDP Udp;
unsigned int localPort = 8888;         // Porta su cui ascolta questo Arduino

//Dichiaro vettori per salvare stime e li inizializzo a 0 per ogni nuova run del programma
const int maxValues = 200;
int z_vet[maxValues] = {0};
float x1_vet[maxValues] = {0.0};
float x2_vet[maxValues] = {0.0};
float x3_vet[maxValues] = {0.0};
int i = 0;
int counter_stampa=0; 

//Inizializzazione z, x1, attesa x2 e x3 per mandare dati
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

  resval = analogRead(respin); //Read data from analog pin and store it to resval variable

  if (resval<=Low1){
  Serial.println("Water Level of this Tank: Empty");
  livello=0;
  }
  else if (resval>Low1 && resval<=Medium1){
  Serial.println("Water Level of this Tank: Low");
  livello=1;
  }

  else if (resval>Medium1 && resval<=High1){
  Serial.println("Water Level of this Tank: Medium");
  livello=2;
  }

  else if (resval>High1){
  Serial.println("Water Level of this Tank: High");
  livello=3;
  }

  z=livello;
  x1=z;

  // Attende finché non riceve le stime iniziali dagli altri due Arduino
  while (!new_x_ricevuta_1 || !new_x_ricevuta_2) {

    char packetBuffer[255]; // Buffer per memorizzare i pacchetti ricevuti
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      IPAddress remoteIP = Udp.remoteIP();
      int remotePort = Udp.remotePort();
      int len = Udp.read(packetBuffer, 255);
      if (len > 0) {
        packetBuffer[len] = 0; // Termina la stringa con un carattere nullo
      }
      if (remoteIP == remoteIP2 && remotePort == remotePort2) {
        x2=atof(packetBuffer);
        Serial.print("Stima di Arduino 2: ");
        Serial.println(x2);
        new_x_ricevuta_1=true;

      } 
      else if (remoteIP == remoteIP3 && remotePort == remotePort3) {
      x3=atof(packetBuffer);
      Serial.print("Stima di Arduino 3: ");
      Serial.println(x3);
      new_x_ricevuta_2=true;
    } 
  }
  delay(500);
}

//Invio dei dati iniziali agli altri due arduino
  Udp.beginPacket(remoteIP2, remotePort2);
  Udp.print(x1);
  Udp.endPacket();

  Udp.beginPacket(remoteIP3, remotePort3);
  Udp.print(x1);
  Udp.endPacket();
  
  Serial.println("Stima inviata");
  Serial.print(x1);
}

//Aggiornamento x1 con algoritmo del consenso
void loop() {

  z_pre=z; // conservo dato precedente del sensore mio
  delta12_pre=delta12;
  delta13_pre=delta13;

  resval = analogRead(respin); //Read data from analog pin and store it to resval variable

  bool new_x_ricevutaa_1 = false;
  bool new_x_ricevutaa_2 = false;

  if (resval<=Low1){
  Serial.println("Water Level of this Tank: Empty");
  livello=0;
  }
  else if (resval>Low1 && resval<=Medium1){
  Serial.println("Water Level of this Tank: Low");
  livello=1;
  }

  else if (resval>Medium1 && resval<=High1){
  Serial.println("Water Level of this Tank: Medium");
  livello=2;
  }

  else if (resval>High1){
  Serial.println("Water Level of this Tank: High");
  livello=3;
  }

  Serial.println("livello:");
  Serial.println(livello);

  // quando x1, x2 e x3 sono uguali aggiorno z del master col livello corrente
  if((abs(x1-x2)<0.01 && abs(x1-x3)<0.01) || (abs(x1-x2)<0.01 && delta13 == 0) || (abs(x1-x3)<0.01 && delta12 == 0)){
    counter++;
      if(counter==7){
      z = livello;
      Serial.print("valore aggiornato di z:");
      Serial.println(z);
      counter=0;
      }
  }
  else{
    counter=0;

  }

  counter_stampa++;
  Serial.print("counter: ");
  Serial.println(counter_stampa);
   
  // Salva i valori nei vettori
  x1_vet[i] = x1;
  x2_vet[i] = x2;
  x3_vet[i] = x3;
  z_vet[i] = z;
  i++;

  // Controlla se i vettori sono pieni
  if (i == maxValues) {
    // Stampa i valori nel monitor seriale
    Serial.println("Valori stima x1:");
    for (int i = 0; i < maxValues; i++) {
      Serial.print(x1_vet[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
    }
      Serial.println();

      Serial.println("Valori stima x2:");
      for (int i = 0; i < maxValues; i++) {
      Serial.print(x2_vet[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
   }
    Serial.println();

      Serial.println("Valori stima x3:");
      for (int i = 0; i < maxValues; i++) {
      Serial.print(x3_vet[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
   }

      Serial.println();

      Serial.println("Valori z1:");
      for (int i = 0; i < maxValues; i++) {
      Serial.print(z_vet[i]);
      if (i < maxValues - 1) {
        Serial.print(", ");
      }
   }
   i=0;
  }

  
  if(ricevuta2==true){
    
    delta12= delta12_pre -(x1-x2);
    Serial.println("delta12 aggiornata");
    counter2=0;

  }

  else {
    counter2++;
    if(counter2==3){
      delta12=0;
      counter2=0;
      Serial.println("misura 2 non ricevuta");
    }
    
  }

  if(ricevuta3==true){
    
    delta13= delta13_pre-(x1-x3);
    Serial.println("delta13 aggiornata");
    counter3=0;

  }
  else {
    counter3++;
    if(counter3==3){
      delta13=0;
      counter3=0;
      Serial.println("misura 3 non ricevuta");

    }
  }

  //Aggiorna x1 con l'algoritmo del consenso
  x1=epsilon*(delta12 + delta13)+z;
  // resettiamo i valori a false in attesa di ricevere nuove stime
  ricevuta2=false;
  ricevuta3=false;


  Serial.print("Stima di Arduino 1: ");
  Serial.println(x1);
  

  //delay(500);
  counter_while=0;

  while ((!ricevuta2 || !ricevuta3) && counter_while<5 ) {
 
    counter_while++;

    char packetBuffer[255]; // Buffer per memorizzare i pacchetti ricevuti
    int packetSize = Udp.parsePacket();
    if (packetSize) {
      IPAddress remoteIP = Udp.remoteIP();
      int remotePort = Udp.remotePort();
      int len = Udp.read(packetBuffer, 255);
      if (len > 0) {
        packetBuffer[len] = 0; // Termina la stringa con un carattere nullo
      }
      if (remoteIP == remoteIP2 && remotePort == remotePort2) {
        x2=atof(packetBuffer);
        Serial.print("Stima di Arduino 2: ");
        Serial.println(x2);
        ricevuta2=true;

      } 
      else if (remoteIP == remoteIP3 && remotePort == remotePort3) {
      x3=atof(packetBuffer);
      Serial.print("Stima di Arduino 3: ");
      Serial.println(x3);
      ricevuta3=true;
    } 
  }

    delay(500); 

}

    Serial.print("counter_while");
    Serial.println(counter_while);

    //Invio della stima aggiornata agli altri due arduino

    
    Udp.beginPacket(remoteIP2, remotePort2);
    Udp.print(x1);
    Udp.endPacket();

    Udp.beginPacket(remoteIP3, remotePort3);
    Udp.print(x1);
    Udp.endPacket();



    

delay(500);  // Attende 2 secondi prima di ricevere nuovi dati

}
