#include<Servo.h>
#define S1 A1
#define S2 A2
#define S3 A3
#define S4 A4
#define S5 A5

const float down_val = 15 ;
const float up_val = 20;
const int average_count = 10;
float cm1;
float cm2;
float cm3;
float cm4;
float cm5;

Servo s;

void setup()
{
  Serial.begin(9600);                                    
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S5, INPUT);
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
  cm1 = distance(S1, average_count);
  cm2 = distance(S2, average_count);
  cm3 = distance(S3, average_count);
  cm4 = distance(S4, average_count);
  cm5 = distance(S5, average_count);
  Serial.print("cm1=");
  Serial.print(cm1);
  Serial.print("\t");
  Serial.print("cm2=");
  Serial.print(cm2);
  Serial.print("\t");
  Serial.print("cm3=");
  Serial.print(cm3);
  Serial.print("\t");
  Serial.print("cm4=");
  Serial.print(cm4);
  Serial.print("\t");
  Serial.print("cm5=");
  Serial.print(cm5);
  Serial.println();

  if (cm4 > 50) {
    orientation(130);
    delay(1500);
  }
  else if (cm5 < 30) {
    orientation(45);
  }
  else if (cm4 > up_val & cm4<60) {
    orientation(120);
  }
  else if (cm4 < down_val) {
    orientation(60);
  }
  else {
    orientation(90);
  }
  //  delay(500);
}

// 转向
void orientation(int pos) {
  //  if (pos >= 90) {
  //    for (int i = 90; i <= pos; i++) {
  //      s.write(i);
  //      //延时的作用：舵机转动需要时间的
  //      delay(15);
  //    }
  //  }
  //  else if (pos < 90) {
  //    for (int i = 90; i >= pos; i--) {
  //      s.write(i);
  //      delay(15);
  //    }
  //  }
  s.write(pos);
  delay(200);
}

// 获取传感器距离
float distance(int pin, int average_count) {
  int sum = 0;
  for (int i = 0; i < average_count; i++) {
    int sensor_value = analogRead(pin);
    int distance_cm = pow(3027.4 / sensor_value, 1.2134);
    if (distance_cm > 60) {
      distance_cm = 60;
    }
    sum += distance_cm;
  }
  return (sum / average_count + 5);
//  delay(200);
}

// 循迹
void Track() {
}
