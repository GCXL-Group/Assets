#include<Servo.h>
#define S1 A1
#define S2 A2
#define S3 A3

const float base = 0;
const float middle = 90 + base;

float cm1;
float cm2;
float cm3;
Servo s;

void setup()
{
  Serial.begin(9600);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  s.attach(13);
  s.write(90);
  //delay(2000);
}
void loop()
{
  // 灰度传感器检测黑带
  if (0) {
    Track();
  }
  else {
    Avoidance();
  }
}

// 避障
void Avoidance() {
  cm1 = distance(S1, 100);
  cm2 = distance(S2, 100);
  cm3 = distance(S3, 100);
  Serial.print("cm1=");
  Serial.print(cm1);
  Serial.print("\t");
  Serial.print("cm2=");
  Serial.print(cm2);
  Serial.println();

  if (cm1 < 30) {
    orientation(150);
  }
  else if (cm2 < 30) {
    orientation(30);
  }
  else if (cm2 > cm1) {
    if (cm2 - cm1<25 & cm2>100 & cm1 > 100) {
      orientation(100);
    }
    else if (cm2 - cm1 > 40) {
      orientation(130);
    }
    else {
      orientation(90);
    }
  }
  else {
    if (cm1 - cm2<25 & cm2>100 & cm1 > 100) {
      orientation(80);
    }
    else if (cm1 - cm2 > 40) {
      orientation(50);
    }
    else {
      orientation(90);
    }
  }
  delay(500);
}

// 转向
void orientation(int pos) {
  pos += base;
  if (pos >= middle) {
    for (int i = middle; i <= pos; i++) {
      s.write(i);
      //      delay(15);
    }
  }
  else if (pos < middle) {
    for (int i = middle; i >= pos; i--) {
      s.write(i);
      //      delay(15);
    }
  }
}

// 获取传感器距离
float distance(int pin, int average_count) {
  int sum = 0;
  for (int i = 0; i < average_count; i++) {
    int sensor_value = analogRead(pin);
    int distance_cm = pow(3027.4 / sensor_value, 1.2134);
    if (distance_cm>50){
      distance_cm=50;
    }
    sum += distance_cm;
  }
  return (sum / average_count+5);
  delay(500);
}

// 循迹
void Track() {
}

