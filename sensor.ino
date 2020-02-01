#include <ThingSpeak.h>

/* 
 *  Für ESP12, Node MCU 1.0 Auswählen
 *  Adafruit ESP8266 by Adafruit
 *  Adafruit Unified Sensor by Adafruit
 *  DHT Sensor Library by Adafruid
 */
#include <DHT.h> //cargamos la librera DHT
#define DHTPIN 2 //Seleccionamos el pin en el que se conectar el sensor
#define DHTTYPE DHT22 //Se selecciona el DHT22(hay otros DHT)
DHT dht(DHTPIN, DHTTYPE); //Se inicia una variable que ser usada por Arduino para comunicarse con el sensor
#include <ESP8266WiFi.h>

unsigned long myChannelNumber = 963215; //ChannelID
const char * myWriteAPIKey = "API-KEY";

const char* ssid = "SSID-Wlan";
const char* password = "W-LanPasswd";

 WiFiClient  client;
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
   dht.begin(); //Se inicia el sensor

 

 
  
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  
  // Start the server
 // server.begin();
 // Serial.println("Server started");
   
 

  // Print the IP address
  Serial.println(WiFi.localIP());

ThingSpeak.begin(client);
   
}

void loop() {

float h = dht.readHumidity(); //Se lee la humedad
  float t = dht.readTemperature(); //Se lee la temperatura
  //Se imprimen las variables
  Serial.println("Humedad: "); 
  Serial.println(h);
  Serial.println("Temperatura: ");
  Serial.println(t);
  delay(2000); //Se espera 2 segundos para seguir leyendo //datos
 

ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(20000); 
  

ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  delay(60000); 
  
  


 
   }
