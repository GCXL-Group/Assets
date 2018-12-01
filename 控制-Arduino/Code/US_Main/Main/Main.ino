#include<Servo.h>
const int T1=2;
const int E1=3;
const int T2=4;
const int E2=5;

const float base = 0;
const float middle = 90+base;

float cm1;
float cm2;
Servo s;

void setup()
{
  Serial.begin(9600);
  pinMode(T1, OUTPUT);
  pinMode(E1, INPUT);
  pinMode(T2, OUTPUT);
  pinMode(E2, INPUT);
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
  cm1 = distance(T1, E1);
  cm2 = distance(T2, E2);
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
  pos+=base;
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
float distance(int t, int e) {
  digitalWrite(t, LOW); //低高低电平发一个短时间脉冲去T1
  delayMicroseconds(2);
  digitalWrite(t, HIGH);
  delayMicroseconds(10);
  digitalWrite(t, LOW);
  float cm = pulseIn(e, HIGH) / 58.0; //将回波时间换算成cm
  cm = (int(cm * 100.0)) / 100.0; //保留两位小数
  //  if (cm >= 100) {
  //    return 100;
  //  }`````````````````````````````````````````
  //  else {
  return cm;
  //  }

}

// 循迹
void Track() {
}

