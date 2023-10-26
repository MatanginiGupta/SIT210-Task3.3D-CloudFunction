/*
  SIT210 Embedded System Development
  Task 3.3D
  I am Matangini Gupta, Student ID 2210994810.
*/

// Import the ArduinoMqttClient library.
#include <ArduinoMqttClient.h>

// If using a board with WiFiNINA, I include the following library.
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
#include <WiFiNINA.h>

const int trigger = 18                   # GPIO pin for ultrasonic sensor trigger
const int echo = 24                      # GPIO pin for ultrasonic sensor echo

// I declared the SSID and password of my WiFi network.
char ssid[] ="matangini gupta's iphone";
char pass[] = Matangini@1811;

// I declared the name of the MQTT broker.
const char broker[] = "broker.mqttdashboard.com";

// I declared the port of the MQTT broker.
int port = 1883;

// I declared the topic to publish the sensor readings to.
const char topic[]  = "Matangini/wave";

// I declared the interval (in milliseconds) between sensor readings.
const long interval = 1000;

// I declare the previous time a sensor reading was published.
unsigned long previousMillis = 0;

// I declared the number of sensor readings that have been published.
int count = 0;

void setup() {
  // I initialized the serial port.
  Serial.begin(9600);

  // I connected to the WiFi network.
  Serial.print("Attempting to connect to WPA SSID");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("You're connected to the network");

  // I connect to the MQTT broker.
  Serial.print("Attempting to connect to the MQTTT broker: broker");
  if (!mqttClient.connect(broker, port)) {
    Serial.println("MQTT connection failed");
    while (1);
  }
  Serial.println("You're connected to the MQTT broker!");
}

void loop() {
  // I poll the MQTT client for incoming messages.
  mqttClient.poll();

  // I check if it's time to publish a sensor reading.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // I publish the sensor reading.
    mqttClient.beginMessage(topic);
    mqttClient.print("Distance: ");
    mqttClient.print(distance);
    mqttClient.endMessage();

    // I update the previous time.
    previousMillis = currentMillis;

    // I increment the number of sensor readings.
    count++;
  }
}
