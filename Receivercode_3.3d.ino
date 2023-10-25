#include <ArduinoMqttClient.h>

// Check the board type and include the appropriate WiFi library
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
#include <WiFiNINA.h>

// Define the network credentials
char ssid[] ="matangini gupta's iphone";
char pass[] = Matangini@1811;

int light = 2; // Define the pin for controlling an LED
// To connect with SSL/TLS:
// 1) Change WiFiClient to WiFiSSLClient.
// 2) Change port value from 1883 to 8883.
// 3) Change broker value to a server with a known SSL/TLS root certificate
//    flashed in the WiFi module.

WiFiClient wifiClient; // Create a WiFi client object
MqttClient mqttClient(wifiClient); // Create an MQTT client object

const char broker[] = "mqtt-dashboard.com"; // Define the MQTT broker address
int port = 1883; // Define the MQTT broker port
const char topic[] = "Matangini/wave"; // Define the MQTT topic to subscribe to

void setup() {
  // Initialize serial communication and wait for the port to open:
  Serial.begin(9600);
  pinMode(light, OUTPUT); // Set the LED pin as an output

  while (!Serial) {
    ; // Wait for the serial port to connect. Needed for the native USB port only
  }

  // Attempt to connect to the WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // Connection failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("I'm connected to the network");
  Serial.println();

  // You can provide a unique client ID; if not set, the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  // You can provide a username and password for authentication
  // mqttClient.setUsernamePassword("username", "password");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("I'm connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // Subscribe to a topic
  mqttClient.subscribe(topic);
  // Topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {
    // We received a message, print out the topic and contents
    Serial.print("Received a message with topic '' ");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    // Use the Stream interface to print the message contents
    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
    Serial.println();

    // Blink the LED
    digitalWrite(light, HIGH);   // Turn the LED on (HIGH is the voltage level)
    delay(200);                       // Wait for a second
    digitalWrite(light, LOW);    // Turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(light, HIGH);   // Turn the LED on (HIGH is the voltage level)
    delay(200);                       // Wait for a second
    digitalWrite(light, LOW);    // Turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(light, HIGH);   // Turn the LED on (HIGH is the voltage level)
    delay(200);                       // Wait for a second
    digitalWrite(light, LOW);    // Turn the LED off by making the voltage LOW
    delay(200);

    Serial.println();
  }
}
