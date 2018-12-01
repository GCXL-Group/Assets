#include<Servo.h>
#define S4 A4
#define S5 A5
#define LS A1
#define RS A2

const float down_val = 15 ;
const float up_val = 25;
const int average_count = 10;
float cm4;
float cm5;
float left_sensor;
float right_sensor;

Servo s;

void setup()
{
  Serial.begin(9600);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  s.attach(13);
  s.write(90);
}
void loop()
{
  // 灰度传感器检测黑带
  left_sensor = analogRead(LS);
  right_sensor = analogRead(RS);
  Serial.print("left sensor:");
  Serial.print(left_sensor);
  Serial.print("\t");
  Serial.print("right sensor:");
  Serial.print(right_sensor);
  if (0) {
    Track();
  }
  else {
    Avoidance();
  }
}

// 避障
void Avoidance() {
  cm4 = distance(S4, average_count);
  cm5 = distance(S5, average_count);
  Serial.print("cm4=");
  Serial.print(cm4);
  Serial.print("\t");
  Serial.print("cm5=");
  Serial.print(cm5);
  Serial.println();

  if (cm4 > 55) {
    orientation(130);
    delay(1000);
    cm4 = distance(S4, average_count);
    if (cm4 > 50) {
      orientation(120);
      delay(500);
      cm4 = distance(S4, average_count);
      if (cm4 < 20){
        orientation(75);
      }
    }
    else if(cm4 < 20){
      orientation(75);
    }
  }
  else if (cm5 < 40 ) {
    orientation(45);
  }
  else if (cm4 > up_val) {
    orientation(95);
  }
  else if (cm4 < down_val) {
    orientation(70);
  }
  else {
    orientation(90);
  }
  //  delay(500);
}

// 转向
void orientation(int pos) {
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
}

// 循迹
void Track() {
  if (left_sensor - right_sensor > 50) {
    s.write(70);
    delay(200);
  }
  else if (right_sensor - left_sensor > 50 ) {
    s.write(110);
    delay(200);
  }
  else {
    s.write(90);
  }
}

