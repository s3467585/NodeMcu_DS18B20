void espServer(){
  WiFiServer server(80);   // веб-сервер на порте 80:
  server.begin();          // запускаем веб-сервер:
  server.begin();  // запускаем веб-сервер:
  Serial.println("Веб-сервер запущен. Ожидание IP-адреса ESP...");
  delay(10000);  
  Serial.println(WiFi.localIP()); // печатаем IP-адрес ESP:
}
