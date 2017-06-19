

#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>
const byte RX = 3;
const byte TX = 2;
const int trig = 5;
const int echo = 4;
const int tri = 7;
const int ech = 8;
 int t=12;
 int d=13;
 SoftwareSerial mySerial = SoftwareSerial(RX, TX); 
SerialCommand sCmd(mySerial);
int racSensor;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.print("Xin Chao");
    Serial.begin(57600);     // giao tiếp Serial với baudrate 9600
    mySerial.begin(57600);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(t,OUTPUT);
    pinMode(d,OUTPUT);
    pinMode(tri,OUTPUT);
    pinMode(ech,INPUT);
    digitalWrite(t,LOW);
  digitalWrite(d,HIGH);
  delay(1000);
}
   void loop() {
    unsigned long bien;
    int bien1;
    digitalWrite(tri,0);   // tắt chân trig
    delayMicroseconds(1);
    digitalWrite(tri,1);   // phát xung từ chân trig
    delayMicroseconds(1);   // xung có độ dài 5 microSeconds
    digitalWrite(tri,0);   // tắt chân trig
    
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    bien = pulseIn(ech,HIGH);  
    // Tính khoảng cách đến vật.
    bien1 = int(bien/2/29.412); 
    unsigned long duration; // biến đo thời gian
    int distance; // biến lưu khoảng cách
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(1);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(1);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    if ((distance <= 38) && (distance != 0)) {
    digitalWrite(t,LOW);
  digitalWrite(d,HIGH);
  delay(1000);
  while( (distance <= 38) && (distance != 0)) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    racSensor = 0;
    root["digital"] = racSensor;
    root["message"] = racSensor ? "thung rac day" : "thung rac chua day";
    mySerial.print("RAC");   //gửi tên lệnh
    mySerial.print('\r');           // gửi \r
    root.printTo(mySerial);        //gửi chuỗi JSON
    mySerial.print('\r');
    lcd.clear();
    lcd.print("Xin Cam On");
    sCmd.readSerial();
    while (bien1 <= 15) {
      StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
      racSensor = 1;
      root["digital"] = racSensor;
    root["message"] = racSensor ? "thung rac day" : "thung rac chua day";
    mySerial.print("RAC");   //gửi tên lệnh
    mySerial.print('\r');           // gửi \r
    root.printTo(mySerial);        //gửi chuỗi JSON
    mySerial.print('\r');
    lcd.clear();
    lcd.print("Thung Rac Day");
    sCmd.readSerial();
        digitalWrite(tri,0);   // tắt chân trig
    delayMicroseconds(1);
    digitalWrite(tri,1);   // phát xung từ chân trig
    delayMicroseconds(1);   // xung có độ dài 5 microSeconds
    digitalWrite(tri,0); 
    bien = pulseIn(ech,HIGH);  
    bien1 = int(bien/2/29.412);
    digitalWrite(t,LOW);
  digitalWrite(d,LOW);
      }
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(1);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(1);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    digitalWrite(t,LOW);
  digitalWrite(d,LOW);
  delay(500);
  }
}
  else {
    digitalWrite(t,HIGH);
    digitalWrite(d,LOW);
    delay(1000);
    while( (distance > 38) || (distance == 0)) {
      StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
      racSensor = 0;
      root["digital"] = racSensor;
    root["message"] = racSensor ? "thung rac day" : "thung rac chua day";
    mySerial.print("RAC");   //gửi tên lệnh
    mySerial.print('\r');           // gửi \r
    root.printTo(mySerial);        //gửi chuỗi JSON
    mySerial.print('\r');
    lcd.clear();
    lcd.print("Xin Cam On");
    sCmd.readSerial();
      while (bien1 <= 15) {
        StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
        racSensor = 1;
        root["digital"] = racSensor;
    root["message"] = racSensor ? "thung rac day" : "thung rac chua day";
    mySerial.print("RAC");   //gửi tên lệnh
    mySerial.print('\r');           // gửi \r
    root.printTo(mySerial);        //gửi chuỗi JSON
    mySerial.print('\r');
    lcd.clear();
    lcd.print("Thung Rac Day");
    sCmd.readSerial();
        digitalWrite(tri,0);   // tắt chân trig
    delayMicroseconds(1);
    digitalWrite(tri,1);   // phát xung từ chân trig
    delayMicroseconds(1);   // xung có độ dài 5 microSeconds
    digitalWrite(tri,0); 
    bien = pulseIn(ech,HIGH);  
    bien1 = int(bien/2/29.412);
    digitalWrite(t,LOW);
  digitalWrite(d,LOW);
      }
      digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(1);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(1);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    digitalWrite(t,LOW);
  digitalWrite(d,LOW);
  delay(500);
  }
  }
}
   
