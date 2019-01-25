void connectWiFi() {
  
  const char* ssid = "My ASUS";     // вписываем SSID для вашей WiFi-сети
  const char* password = "9876543210";       // вписываем пароль для вашей WiFi-сети
  
  Serial.println();
  Serial.print("Подключаемся к - "); 
  Serial.print(ssid);
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Подключение к WiFi выполнено"); 
 
  
}
