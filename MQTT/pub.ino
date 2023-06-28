#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi
const char* ssid = "Scott";
const char* password = "1505scott";

// Configuración del broker
const char* mqttServer = "192.168.0.111";
const int mqttPort = 9000;
const char* mqttTopic = "topic test";
//definición de constantes
float valor;
float lum;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);

  // Conexión a WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi!");

  // Connexión al broker mqtt
  mqttClient.setServer(mqttServer, mqttPort);
  while (!mqttClient.connected()) {
    if (mqttClient.connect("arduino-client")) {
      Serial.println("Connected to MQTT broker!");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  //recopilación de valores
  int Sensor=analogRead(A3);
  valor=analogRead(A2);          //lectura de la medida de la LDR
  lum=valor*3.3/4096;            //conversión de unidades a voltios.
  valor=log(3.3*4600/(1800*lum)-4600/1800)/0.7;
  valor=exp(valor);
  valor=560/valor;
  String message = String(Sensor)+" "+String(valor,2);    //montamos el mensaje
  mqttClient.publish(mqttTopic, message.c_str());         //lo publico bajo el topic el mensaje convertido a char.
  
  Serial.println("Message sent to MQTT broker!");
  Serial.println(message);



  delay(2000);  // Send message every 5 seconds
}
