// подключаем библиотеку «ESP8266WiFi»:
#include <ESP8266WiFi.h>
#include <DallasTemperature.h>




#define key1 LED_BUILTIN  // контакт1 управляемый через Web
#define term1 5    // контакт для передачи данных подключен к D1 на ESP8266 12-E (GPIO5):
#define host "sovmet.000webhostapp.com"   //адрес хоста sovmet.000webhostapp.com

char temperatureCString[7];  // массив хранения данных температуры в градусах
char temperatureFString[7];  // массив хранения данных температуры в фаренгейтах
 
OneWire oneWire(term1); // создаем экземпляр класса oneWire; с его помощью
                        // можно коммуницировать с любыми девайсами, работающими
                        // через интерфейс 1-Wire, а не только с температурными датчиками
                        // от компании Maxim/Dallas:
DallasTemperature DS18B20(&oneWire);   // передаем объект oneWire объекту DS18B20:

void setup() {
  
  pinMode(key1 , OUTPUT); // настройка ключа1
  digitalWrite(key1, 1);  // установка параметра ключа1 по умолчанию

  serial();
  DS18B20.begin(); // по умолчанию разрешение датчика – 9-битное;
                   // если у вас какие-то проблемы, его имеет смысл
                   // поднять до 12 бит; если увеличить задержку,
                   // это даст датчику больше времени на обработку
                   // температурных данных
  connectWiFi();
  espServer();
}
 
void loop() {
  
  //getTemperature();
  sendWeb();
  delay (10000);
  
  
  // начинаем прослушку входящих клиентов:
//  WiFiClient client = server.available();
// 
//  if (client) {
//    Serial.println("New client");  //  "Новый клиент"
//    // создаем переменную типа «boolean»,
//    // чтобы определить конец HTTP-запроса:
//    boolean blank_line = true;
//    while (client.connected()) {
//      if (client.available()) {
//        char c = client.read();
//       
//        if (c == '\n' && blank_line) {
//            getTemperature();
//            client.println("HTTP/1.1 200 OK");
//            client.println("Content-Type: text/html");
//            client.println("Connection: close");
//            client.println();
//            // веб-страница с данными о температуре:
//            client.println("<!DOCTYPE HTML>");
//            client.println("<html>");
//            client.println("<head><meta charset=\"utf-8\" http-equiv=\"Refresh\" content=\"20\"> <title>Уличная температура</title></head><body bgcolor=\"#E6E6FA\"><h1>Уличная температура</h1><h3>Температура в градусах Цельсия:  <span style=\"color:#B22222\">");
//            client.println(temperatureCString);
//            client.println("&#176C</span></h3><h3>Температура в градусах Фаренгейта: <span style=\"color:#B22222\">");    //&#176 спецсимвол HTML градусы
//            client.println(temperatureFString);
//            client.println("&#176F</span></h3></body></html>");  
//            break;
//        }
//        if (c == '\n') {
//          // если обнаружен переход на новую строку:
//          blank_line = true;
//        }
//        else if (c != '\r') {
//          // если в текущей строчке найден символ:
//          blank_line = false;
//        }
//      }
//    }  
//    // закрываем соединение с клиентом:
//    delay(1);
//    client.stop();
//    Serial.println("Client disconnected.");
//               //  "Клиент отключен."
//  }
}
