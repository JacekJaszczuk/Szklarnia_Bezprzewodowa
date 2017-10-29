#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Tu należy podać dane do punktu dostępowego WiFi:
const char ssid[] = "UPC3758752";
const char password[] = "ETPXYMPH";

void setup()
{
  // Uruchom UART do debugowania:
  Serial.begin(9600);

  // Zainicjuj połączenie WiFi:
  WiFi.begin(ssid, password);

  // Czekaj na uzyskanie połaczenia i wypisz uzyskany adres IP:
  Serial.println("\nŁączenie z WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(400);
  }
  Serial.println(" Połączono!");
  Serial.print("Twój adres IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Rozpoczynam wysyałanie zapytań...");
}

void loop()
{
  int id = 7;            // ID urządzenia.
  char bufAdres[200];    // Bufor na stworzenie adresu dla HTTP.
  int getReturn = 0;     // Wartość zwracana przez metodę GET.
  
  // Utwórz klienta HTTP:
  HTTPClient http;

  // Odczytaj wartość z ADC i połącz z adresem MASTER:
  sprintf(bufAdres, "http://192.168.20:3000/data?id=%d&value=%d", id, analogRead(0));
  Serial.println(bufAdres);

  // Ustaw adres do którego zostanie wysłane zapytanie:
  http.begin(bufAdres);

  // Wyślij zapytanie GET i sprawdź kod zwrócony przez serwer:
  getReturn = http.GET();
  if (getReturn == 200)
  {
    Serial.print("OK ");
    Serial.println(getReturn);
  }
  else
  {
    Serial.print("Błąd ");
    Serial.println(getReturn);
  }

  // Zakończ połączenie HTTP:
  http.end();

  delay(3000);
}
