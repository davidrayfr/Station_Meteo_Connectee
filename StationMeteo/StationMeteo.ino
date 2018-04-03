/*************************************************************************************
Nom     
        StationMeteo.ino
Role    
        Station météo connectée basée sur module NodeMCU ESP8266 Wifi
        Fonction :
          - Acquérir la température et l'hygrométrie avec un BME280
          - Acquérir la pression atmosphérique BME280
          - Mesurer la pluviométrie (a venir)
          - Mettre à disposition ces informations par l'intermédiare d'un serveur web
          - Transmettre ces informations sur un serveur distant (type thingspeak)

Auteur
        Laurent Macron
        Thierry Dezormeaux

Version / Date / Commentaire / Auteur
        0.01 / 03-01-2017 / Version initial        
*************************************************************************************/

/***********  Ajout de bibliothèque  ************************************************/
#include <dht.h> //Librairie pour le capteur DHT http://arduino.cc/playground/Main/DHTLib
#include <Network_Setting.h> //Network settings: ssid & password in separate file

/***********  Déclaration des CONSTANTES  *******************************************/
#define DHT11_PIN 5 //The data I/O pin connected to the DHT11 sensor : GPIO5 = D1 of NodeMCU ESP8266 Board

/***********  Déclaration des variables globales  ***********************************/
dht DHT;  //Creation de l'objet DHT

/***********  setup, to run once  ***************************************************/
void setup() {
  //On ouvre un connexion série pour le terminal
  Serial.begin(115200);
  Serial.println("Programme Station Meteo initialisée");
  Serial.println();

  Serial.print("DHTLib LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

/***********  main, run repeatedly **************************************************/
void loop() {

  //READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);

  delay(2000);
}
