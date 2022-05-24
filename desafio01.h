
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "http://api.openweathermap.org/data/2.5/weather?q=Sorocaba,br&APPID=cebc60ca0120bfe26aaadcc54c82481e&units=metric";


LiquidCrystal_I2C lcd(0x27, 16, 2);

HTTPClient http;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Temperatura");

  Serial.begin(115200);
  WiFi.begin(ssid, password, 6);  // rede, senha e canal do WiFi

  Serial.print("Conectando-se ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.print("Buscando " + url + "... ");

  http.begin(url);
}

void loop() {

  

  int httpResponseCode = http.GET();
 
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
   

    char *ptr = strstr((const char *)payload.c_str(), "name");  // procura cidade
    String cidade = &ptr[7];
    cidade.replace('"', '\0');    // coloca o '\0' para finalizar o nome da cidade
    ptr = strstr((const char *)payload.c_str(), "temp");  // procura temperatura
    String temperatura = &ptr[6];
    temperatura.replace(',', '\0'); // coloca o '\0' para finalizar a temperatura
    ptr = strstr((const char *)payload.c_str(), "humidi"); //procura a umidade
    String Umidade = &ptr[10];
    Umidade.replace(',', '\0'); // coloca o '\0' para finalizar a umidade

    Serial.println();
    Serial.println(cidade.c_str());
    Serial.print(temperatura.c_str()); // temperatura
    Serial.println("º""C");
    Serial.print(Umidade.c_str()); // Umidade
    Serial.println("%");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cidade.c_str());      // cidade
    lcd.setCursor(0,1);
    lcd.print(temperatura.c_str()); // temperatura
    lcd.print("\xDF""C");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cidade.c_str());       // cidade
    lcd.setCursor(0,1);
    lcd.print(Umidade.c_str()); // Umidade
    lcd.print("%");

  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }

  delay(10000);
}
