
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "http://api.openweathermap.org/data/2.5/weather?q=Sorocaba,br&APPID=cebc60ca0120bfe26aaadcc54c82481e&units=metric";
const String url2 = "https://api.openweathermap.org/data/2.5/weather?q=S%C3%A3o+Paulo,br&APPID=cebc60ca0120bfe26aaadcc54c82481e&units=metric";


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
  http.begin(url2);
}

void loop() {

  const String url = "http://api.openweathermap.org/data/2.5/weather?q=Sorocaba,br&APPID=cebc60ca0120bfe26aaadcc54c82481e&units=metric";
 
 http.begin(url);
  

  int httpResponseCode = http.GET();
 
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

    delay(3000);

    const String url2 = "https://api.openweathermap.org/data/2.5/weather?q=Porto+Feliz,br&APPID=cebc60ca0120bfe26aaadcc54c82481e&units=metric";
  
    http.begin(url2);

    int httpResponseCode2 = http.GET();

    Serial.println(httpResponseCode2);
     payload = http.getString();

    char *ptr2 = strstr((const char *)payload.c_str(), "name");  // procura cidade
    String cidade2 = &ptr2[7];
    cidade2.replace('"', '\0');    // coloca o '\0' para finalizar o nome da cidade
    ptr2 = strstr((const char *)payload.c_str(), "temp");  // procura temperatura
    String temperatura2 = &ptr2[6];
    temperatura2.replace(',', '\0'); // coloca o '\0' para finalizar a temperatura
    ptr2 = strstr((const char *)payload.c_str(), "humidi"); //procura a umidade
    String Umidade2 = &ptr2[10];
    Umidade2.replace(',', '\0'); // coloca o '\0' para finalizar a umidade

    Serial.println();
    Serial.println(cidade2.c_str());
    Serial.print(temperatura2.c_str()); // temperatura
    Serial.println("º""C");
    Serial.print(Umidade2.c_str()); // Umidade
    Serial.println("%");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cidade2.c_str());      // cidade
    lcd.setCursor(0,1);
    lcd.print(temperatura2.c_str()); // temperatura
    lcd.print("\xDF""C");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cidade2.c_str());       // cidade
    lcd.setCursor(0,1);
    lcd.print(Umidade2.c_str()); // Umidade
    lcd.print("%");

  delay(5000);
}
