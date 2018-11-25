

/*
 *  This sketch sends a message to a TCP server
 *
 */
/************************* WIFI Info ****************************************/
#define WLAN_SSID                             "tatooine"
#define WLAN_PASS                             "p4ssword"
#define BUILTIN_LED                           2

#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
WiFiClient esp32;
PubSubClient client(esp32);


const char* mqtt_server = "mqtt.thingspeak.com";

void checkForWIFI(void)
{
  if (WiFi.status() != WL_CONNECTED)
  {
  Serial.println("Wait for WIFI ");
    Serial.println(WLAN_SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
       Serial.print(".");
      delay(1000);
    }
     Serial.println(" ");
     Serial.println("Connected");
  }
}
void checkForWifiStatus(void)
{
  if (WiFi.status() != WL_CONNECTED)
  {
  Serial.println("Waiting for ");
    Serial.println(WLAN_SSID);
    WiFi.reconnect();
    while (WiFi.status() != WL_CONNECTED)
    {
       Serial.println(".");
      delay(1000);
    }
     Serial.println(" ");
     Serial.println("Connected");
  }
}
void configureWIFI(void)
{
  // WIFI Connection
   
  // Connect to WiFi access point.
    WiFi.persistent(false);
    WiFi.mode(WIFI_OFF);   // this is a temporary line, to be removed after SDK update to 1.5.4
    WiFi.mode(WIFI_STA);
    Serial.println("Connecting to ");
    Serial.println(WLAN_SSID);
    WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  checkForWIFI();
  delay(100);
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    String userName = "Led_node";
    String password="0XRW3H01EHTT3LOO";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),userName.c_str(),password.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
//      client.publish("channels/636087/publish/SIL2NZOBYKW80QU6", "field1=72&status=MQTTPUBLISH");
      // ... and resubscribe
      client.subscribe("channels/636087/subscribe/fields/field1/SIL2NZOBYKW80QU6");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setup()
{   pinMode(BUILTIN_LED, OUTPUT); 
    Serial.begin(115200);
    delay(10);
    configureWIFI();    // We start by connecting to a WiFi network
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
   
}


void loop()
{
    const uint16_t port = 80;
    const char * host = "192.168.1.1"; // ip or dns

  checkForWifiStatus();
delay(1000);
if (!client.connected()) {
    checkForWifiStatus();  
    reconnect();
  }
  client.loop();
}
