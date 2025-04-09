void sendString(String data) {
  for (int i = 0; i < data.length(); i++) ESP_BT.write(data[i]);
  ESP_BT.write(';');
}