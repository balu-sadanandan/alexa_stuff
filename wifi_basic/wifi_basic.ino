/*
 *  This sketch sends a message to a TCP server
 *
 */
/************************* WIFI Info ****************************************/
#define WLAN_SSID                             "tatooine"
#define WLAN_PASS                             "p4ssword"



#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

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
void setup()
{
    Serial.begin(115200);
    delay(10);
     configureWIFI();
    // We start by connecting to a WiFi network
   
}


void loop()
{
    const uint16_t port = 80;
    const char * host = "192.168.1.1"; // ip or dns

  checkForWifiStatus();
delay(1000);
}
