/*********
  Руи Сантос (Rui Santos)
  Более подробно о проекте на: http://randomnerdtutorials.com  
*********/
 
// подключаем библиотеку «ESP8266WiFi»:
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
// вписываем здесь SSID и пароль для вашей WiFi-сети:
const char* ssid = "My ASUS";
const char* password = "9876543210";
 
// контакт для передачи данных подключен к D1 на ESP8266 12-E (GPIO5):
#define ONE_WIRE_BUS 5
 
// создаем экземпляр класса oneWire; с его помощью
// можно коммуницировать с любыми девайсами, работающими
// через интерфейс 1-Wire, а не только с температурными датчиками
// от компании Maxim/Dallas:
OneWire oneWire(ONE_WIRE_BUS);
 
// передаем объект oneWire объекту DS18B20:
DallasTemperature DS18B20(&oneWire);
char temperatureCString[6];
char temperatureFString[6];
 
// веб-сервер на порте 80:
WiFiServer server(80);
 
// блок setup() запускается только один раз – при загрузке:
void setup() {
  // инициализируем последовательный порт (для отладочных целей):
  Serial.begin(115200);
  delay(10);
 
  DS18B20.begin(); // по умолчанию разрешение датчика – 9-битное;
                   // если у вас какие-то проблемы, его имеет смысл
                   // поднять до 12 бит; если увеличить задержку,
                   // это даст датчику больше времени на обработку
                   // температурных данных
 
  // подключаемся к WiFi-сети:
  Serial.println();
  Serial.print("Connecting to "); // "Подключаемся к "
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); // "Подключение к WiFi выполнено"
 
  // запускаем веб-сервер:
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
              // "Веб-сервер запущен. Ожидание IP-адреса ESP..."
  delay(10000);
 
  // печатаем IP-адрес ESP:
  Serial.println(WiFi.localIP());
}
 
void getTemperature() {
  float tempC;
  float tempF;
  do {
    DS18B20.requestTemperatures();
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 2, 2, temperatureCString);
    tempF = DS18B20.getTempFByIndex(0);
    dtostrf(tempF, 3, 2, temperatureFString);
    delay(100);
  } while (tempC == 85.0 || tempC == (-127.0));
}
 
// блок loop() будет запускаться снова и снова:
void loop() {
  // начинаем прослушку входящих клиентов:
  WiFiClient client = server.available();
 
  if (client) {
    Serial.println("New client");  //  "Новый клиент"
    // создаем переменную типа «boolean»,
    // чтобы определить конец HTTP-запроса:
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       
        if (c == '\n' && blank_line) {
            getTemperature();
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // веб-страница с данными о температуре:
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head><meta http-equiv=\"Refresh\" content=\"20\" /></head><body><h1>ESP8266 - Temperature</h1><h3>Temperature in Celsius: ");
            client.println(temperatureCString);
            client.println("*C</h3><h3>Temperature in Fahrenheit: ");
            client.println(temperatureFString);
            client.println("*F</h3></body></html>");  
            break;
        }
        if (c == '\n') {
          // если обнаружен переход на новую строку:
          blank_line = true;
        }
        else if (c != '\r') {
          // если в текущей строчке найден символ:
          blank_line = false;
        }
      }
    }  
    // закрываем соединение с клиентом:
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
               //  "Клиент отключен."
  }
}
