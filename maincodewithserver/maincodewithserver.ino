#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

DNSServer dnsServer;
/*list of ssid's to cycle through*/
char* names[] = {"Im watching you", "secret camera #%d", "I see you","MI5reconvanID#%d","loading..." , "no free wifi because Tories", "yell CARROT for password", "FBIvanID#%d", "Fellowship of the Ping", "get off my LAN! darn kids!", "free wifi", "no free wifi because brexit", NULL};
int n = 0;
unsigned long ms = 0;
unsigned long pms = 0;
/*time between ssid change in miliseconds*/
unsigned long timeintvl = 120000;


ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/html", "<h1>ha!</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
 randomSeed(analogRead(0));
  dnsServer.start(53, "*", WiFi.softAPIP());
}

void loop() {
  server.handleClient();
  dnsServer.processNextRequest();
  if (ms > timeintvl and WiFi.softAPgetStationNum() == 0)
  {
   char buff[100];
   sprintf(buff, names[n], random(1000, 9999));
   if (names[n] == "yell CARROT for password" or names[n] == "no free wifi because Tories" or names[n] == "no free wifi because brexit")
   {
   WiFi.softAP(buff, "offmylan"); 
   }
   else 
   {
    WiFi.softAP(buff); 
   }
   IPAddress myIP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(myIP);
   n = n + 1;
   if (names[n] == NULL)
   {
    n = 0;
   }
   ms = 0;
  }
  ms = ms + (millis()-pms);
  pms = millis();
}
