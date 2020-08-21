#include <ESP32Servo.h>

Servo servo1;

int minUs = 1000;
int maxUs = 2000;

int servo1Pin = 18;

const int LEDPin = 13;    //กำหนด pin ที่ต้องการใช้งานคือ pin 13
const int trigPin = 26;   //กำหนด pin ที่ต้องการใช้งานคือ pin 26
const int echoPin = 27;   //กำหนด pin ที่ต้องการใช้งานคือ pin 27

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  
  servo1.setPeriodHertz(50);
  servo1.attach(servo1Pin, minUs, maxUs); //Servopin 18
  
  pinMode(LEDPin, OUTPUT);  //คำสั่งที่มีไว้สำหรับกำหนดการทำงานของ pin
  //ให้ทำงานเป็นแบบ INPUT หรือ OUTPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW); //กำหนดให้ trigpin มีสถานะ low หรือไม่ทำงานเป็นเวลา 2 ไมโครวินาที
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);//กำหนดให้ trigpin มีสถานะ high หรือทำงานเป็นเวลา 10 ไมโครวินาที
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //กำหนดให้ trigpin มีสถานะ low หรือไม่ทำงาน
  duration = pulseIn(echoPin, HIGH);  //อ่าน echoPin, คลื่นเสียงที่สะท้อนกลับมาเป็นไมโครวินาที

  distance = duration / 29 / 2; //เป็นค่าที่ได้จากการคำนวณระยะทางของเสียงที่ได้จากการสะท้อนกลับ

  //duration คือค่าที่ได้จาก echo นำมาหาร 29 microseconds/cm ซึ่งก็คือความเร็วของเสียง
  //และนำมาหารด้วย 2 อีกครั้ง เพราะใช้เวลาเดินทางเพียงครึ่งเดียว

  if (distance <= 10) { //เป็นการกำหนดเงื่อนไขของระยะทาง..
    servo1.write(180); //ชูนิ้ว
    digitalWrite(LEDPin, HIGH); //กำหนดให้มีสถานะ logic เป็น1(high = ไฟติด)
    //หรือ 0(low = ไฟดับ)
  } else
  {
    servo1.write(0); //งอนิ้ว
    digitalWrite(LEDPin, LOW);
  }
  Serial.print("Distance: ");
  Serial.println(distance);
}
