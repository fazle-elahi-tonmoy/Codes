void send_text(){
  mySerial.println("AT+CMGS=\"+8801678090046\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("alarm"); //text content
  updateSerial();
  mySerial.write(26);
}
