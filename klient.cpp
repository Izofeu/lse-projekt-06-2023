#include <WiFi.h>

int mainclock = 15;
int datainput = 16;
int datainput2 = 17;
int clocksub = 14;

const uint16_t port = 444;
int getData(int pinnum)
{
  int inp = 0;
  int value = 0;
  int curbit = 2048;
  for (int i = 15; i>=3; i--)
  {
    if (i==15)
    {
      digitalWrite(mainclock, LOW);
      delay(10);
      digitalWrite(clocksub, LOW);
      delay(10);
      digitalWrite(clocksub, HIGH);
      delay(10);
      continue;
    }
    digitalWrite(clocksub, LOW);
    delay(10);
    inp = digitalRead(pinnum);
    if (inp)
    {
      value = value + curbit;
    }
    curbit = curbit/2;
    digitalWrite(clocksub, HIGH);
    delay(10);
  }
  digitalWrite(mainclock, HIGH);
  int16_t ret = value/4;
  return ret;
}
void setup()
{
  Serial.begin(9600);
  pinMode(mainclock, OUTPUT);
  pinMode(datainput, INPUT);
  pinMode(datainput2, INPUT);
  pinMode(clocksub, OUTPUT);
  digitalWrite(mainclock, HIGH);
  delay(10);
  digitalWrite(clocksub, HIGH);
  delay(100);

  WiFi.begin("nazwa wifi", "haslo wifi");
  delay(500);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("laczenie...");
    delay(500);
  }
  Serial.print("polaczono, adres IP:");
  Serial.println(WiFi.localIP());
  delay(500);
}

void loop()
{
  int n1 = getData(16);
  delay(15);
  int n2 = getData(17);
  ///uint32_t tosend = (n1 << 16) | n2;
  arduino::String a1 = String(n1);
  arduino::String a2 = String(n2);
  arduino::String a3 = a1 + a2;
  Serial.print("16: ");
  Serial.print(n1);
  Serial.print(", 17: ");
  Serial.println(n2);
  WiFiClient klient;
  if(!klient.connect("ip serwera", port))
  {
    Serial.println("blad polaczenia");
    delay(7000);
    klient.stop();
  }
  else 
  {
    klient.println(a3);
  }
  klient.stop();
  delay(5000);
}
