void sendWeb() {

int buff = 0;
WiFiClient client ;

//getTemperature();
  DS18B20.requestTemperatures();
  if (client.connect(host, 80)) {
      client.print( "GET /add_data.php?");
      client.print("temperature=");
      client.print(DS18B20.getTempCByIndex(0));
      client.print("&");
      client.print("&");
      client.print("temperature1=");
      client.print(DS18B20.getTempCByIndex(0));
      client.println( " HTTP/1.0");
      client.print( "Host: " );
      client.println(host);
      client.println( "Connection: close" );
      client.println();
      client.println();
      delay(500);                   // задержка на ответ сервера (нужна обязательно дя приёма состояния ключа)
      
      while (client.available()) {
      char c = client.read();
Serial.print(c);
      if ( c=='1') {
        buff=1;
        }
      if ( c=='0'){
         buff=0;
         }
      } 
    client.stop();
    client.flush();
    delay(100); 
    } else {
    client.stop();
    delay(1000);
    client.connect(host, 80);
    }
  if ( buff==1){
    digitalWrite (key1, 0);
    } else {
    digitalWrite(key1, 1);
    }
  delay(500);
}
