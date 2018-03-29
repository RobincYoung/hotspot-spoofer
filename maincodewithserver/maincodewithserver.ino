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
unsigned long timeintvl = 30000;


ESP8266WebServer server(80);

void handleRoot() {
  /*incert html for the default page (this will apear if the text after the "/" doesn't match any other pages)*/
  server.send(200, "text/html", "<h1>ha!</h1>");
} 

void handletest() {
  /*just a random example page*/
  server.send(200, "text/html", "<h1>example</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  server.on("/test", handletest);/*you can replace the "/test" with /what ever you want and "handletest" with the name of a function (see "void handletest") to have a unique responce for that page"*/
  server.onNotFound ( handleRoot );/*this is what happens if the url doesn't match anything else(see 404 comment)*/
  server.begin();
  Serial.println("HTTP server started");
  randomSeed(analogRead(0));
  dnsServer.start(53, "*", WiFi.softAPIP());/*responds to all dns requests with its own ip address*/
}

void loop() {
  server.handleClient();
  dnsServer.processNextRequest();
  if ((millis() - pms) > timeintvl and WiFi.softAPgetStationNum() == 0)
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
    pms = millis();
  }
}
