#include <WiFi.h>

const uint16_t port = 444;

void setup()
{
  Serial.begin(9600);
  WiFi.begin("nazwa wifi", "haslo wifi");
  delay(500);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.println("laczenie..");
    delay(1000);
  }
  Serial.print("polaczono, adres IP:");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

void loop()
{
  WiFiServer serwer(port);
  serwer.begin();
  WiFiClient klient = serwer.available();
  if(!klient)
  {
    return;
  }
    while(klient.available())
    {
      char ch = static_cast<char>(klient.read());
      Serial.print(ch);
    }
    Serial.println("");
    klient.stop();
  delay(2);
}
