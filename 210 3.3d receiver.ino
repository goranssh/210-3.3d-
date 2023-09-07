#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010)  defined(ARDUINO_SAMD_NANO_33_IOT)  defined(ARDUINO_AVR_UNO_WIFI_REV2)
#include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
#include <WiFi101.h>
#include <WiFi.h>
#endif

// #include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Goransh's iphone";  
char pass[] = "goransh23";

int light = 2;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "mqtt-dashboard.com";
int        port     = 1883;
const char topic[]  = "SIT210/waves";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(light, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }  

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    
    Serial.print("Received a message with topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
    Serial.println();
    digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
    delay(200);

    Serial.println();
  }
} 
