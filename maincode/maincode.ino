#include <ESP8266WiFi.h>
/*list of ssid's to use*/
char* names[] = {"Im watching you", "secret camera #%d", "Hi there", "I see you","MI5reconvanID#%d","loading..." , "no free wifi because Tories", "yell CARROT for password", "FBIvanID#%d", "Fellowship of the Ping", "get off my LAN! darn kids!", "free wifi", "no free wifi because brexit", NULL};
int n = 0;
void setup()
{
randomSeed(analogRead(0));
}


void loop()
{
   /*time (in ms) between changing ssid*/
   delay(300000);
   char buff[100];
   sprintf(buff, names[n], random(1000, 9999));
   /*list of names to use password for*/
   if (names[n] == "yell CARROT for password" or names[n] == "no free wifi because Tories" or names[n] == "no free wifi because brexit")
   {
   WiFi.softAP(buff, "offmylan"); 
   }
   else 
   {
    WiFi.softAP(buff); 
   }
   n = n + 1;
   if (names[n] == NULL)
   {
    n = 0;
   }
}
