#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "Scott";
const char* password = "1505scott";

// MQTT broker configuration
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

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi!");

  // Connect to MQTT broker
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
  valor=analogRead(A2);
  lum=valor*3.3/4096;
  valor=log(3.3*4600/(1800*lum)-4600/1800)/0.7;
  valor=exp(valor);
  valor=560/valor;
  String message = String(Sensor)+" "+String(valor,2);
  mqttClient.publish(mqttTopic, message.c_str());
  
  Serial.println("Message sent to MQTT broker!");
  Serial.println(message);



  delay(2000);  // Send message every 5 seconds
}
