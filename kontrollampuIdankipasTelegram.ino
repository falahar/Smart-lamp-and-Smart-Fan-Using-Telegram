#include "CTBot.h"
CTBot robot;
int relay = D3;
int relay1 = D4;

String ssid_wifi = "Redmi 9T";
String password = "12345678";
String api_token = "5806034220:AAENPGyWX3njxswj079RnaqcMPmrEpj_yjo";

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, HIGH);

  // Konek ke wifi
  robot.wifiConnect(ssid_wifi, password);

  // Konek ke telegram
  robot.setTelegramToken(api_token);
  
  // Cek koneksi
  if(robot.testConnection())
    Serial.println("Terhubung :)");
  else
    Serial.println("Error!");
}

void loop() {

  TBMessage message;

  if(robot.getNewMessage(message)) {
  
    Serial.print("Ada pesan Masuk: ");
    Serial.println(message.text);     
    
    if(message.text.equalsIgnoreCase("/On_Lamp")) {
      digitalWrite(relay, LOW);
      robot.sendMessage(message.sender.id, "Lampu Menyala");
    } else if(message.text.equalsIgnoreCase("/Off_Lamp")) {
      digitalWrite(relay, HIGH);
      robot.sendMessage(message.sender.id, "Lampu Mati");   
    } else if(message.text.equalsIgnoreCase("/On_Fan")) {
      digitalWrite(relay1,  LOW);
      robot.sendMessage(message.sender.id, "Kipas Menyala");   
    } else if(message.text.equalsIgnoreCase("/Off_Fan")) {
      digitalWrite(relay1, HIGH);
      robot.sendMessage(message.sender.id, "Kipas Mati");   
    } else {
      String reply;
      reply = ("list kontrol :>>>> lampu :/On_Lamp atau /Off_Lamp    kipas : /On_Fan atau /Off_Fan");
      robot.sendMessage(message.sender.id, reply);
    }
    
  }
}
