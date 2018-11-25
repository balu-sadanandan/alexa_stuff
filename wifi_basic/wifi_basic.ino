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
       Serial.println(".");
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
  Serial.println("Wait for WIFI ");
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
   Serial.println("Connecting to ");
  Serial.println(WLAN_SSID);
  // Connect to WiFi access point.
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
   /* WiFiMulti.addAP(WLAN_SSID,WLAN_PASS);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);*/
}


void loop()
{
    const uint16_t port = 80;
    const char * host = "192.168.1.1"; // ip or dns

  checkForWifiStatus();
/*
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);

        return;
    }

    // This will send the request to the server
    client.print("Send this data to server");

    //read back one line from server
    String line = client.readStringUntil('\r');
    client.println(line);

    Serial.println("closing connection");
    client.stop();

    Serial.println("wait 5 sec...");
    delay(5000);*/
}
