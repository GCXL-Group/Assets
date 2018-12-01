#include<Servo.h>
#define T1 2
#define E1 3
#define T2 6
#define E2 7
float cm1;
float cm2;
float base = 0;
Servo s;

void setup()
{
  Serial.begin(9600);
  pinMode(T1, OUTPUT);
  pinMode(E1, INPUT);
  pinMode(T2, OUTPUT);
  pinMode(E2, INPUT);
  s.attach(13);
}
void loop()
{
  // 灰度传感器检测黑带
  if (0) {
    Track();
  }
  else {
    Dodge();
  }
}

// 避障
void Dodge() {
  cm1 = distance(2, 3);
  cm2 = distance(6, 7);
  cm2 = cm2 + 45;
  Serial.print("cm1=");
  Serial.print(cm1);
  Serial.print("\t");
  Serial.print("cm2=");
  Serial.print(cm2);
  Serial.println();
  s.write(90);

//  {
//    s.write(60);
//  }
//  if (cm2 - cm1 > 20)
//  {
//    s.write(120);
//  }
}

// 获取传感器距离
float distance(int t, int e) {
  digitalWrite(t, LOW); //低高低电平发一个短时间脉冲去T1
  delayMicroseconds(2);
  digitalWrite(t, HIGH);
  delayMicroseconds(10);
  digitalWrite(t, LOW);

  float cm = pulseIn(e, HIGH) / 58.0; //将回波时间换算成cm
  cm = (int(cm * 100.0)) / 100.0; //保留两位小数
  return cm;
}

// 循迹
void Track() {
}

