void sendWeb() {


//getTemperature();
  DS18B20.requestTemperatures();
  if (client.connect(host, 80)) {
      client.print( "GET /add_data.php?");
      client.print("temperature=");
      client.print(DS18B20.getTempCByIndex(0));
      client.print("&");
      //client.print("&");
      client.print("temperature1=");
      client.print(temperatureFString);
      client.println( " HTTP/1.1");
      client.print( "Host: " );
      client.println(host);
      client.println( "Connection: close" );
      client.println();
      client.println();
      delay(200);
        
        int c = client.read();
        //client.flush();
        Serial.println("Request from browser: ");
        Serial.println(c);
        Serial.println(DS18B20.getTempCByIndex(0));


      
  //    while (client.available()) {
  //      char c = client.read();
  //      if ( c=='1') {
  //        buff=1;
  //      }
  //      if ( c=='0'){
  //         buff=0;
  //      }
  //    } 
  //    client.stop();
  //    client.flush();
  //    delay(100); 
  }
  else {
     client.stop();
     delay(1000);
     client.connect(host, 80);
  }
  
}
