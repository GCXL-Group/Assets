#include<Servo.h>
Servo s;
const int T1 2;
const int E1 3;
const int T2 6;
const int E2 7;
const float down_val = 40;
const float up_val = 60;
float cm1;
float cm2;

void setup()
{
  Serial.begin(9600);
  pinMode(T1, OUTPUT);
  pinMode(E1, INPUT);
  pinMode(T2, OUTPUT);
  pinMode(E2, INPUT);
  s.attach(10);
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
  cm1 = distance(2, 3);
  cm2 = distance(6, 7);
  Serial.print("cm1=");
  Serial.print(cm1);
  Serial.print("\t");
  Serial.print("cm2=");
  Serial.print(cm2);
  Serial.println();

  if (cm1 > 50) {
    if (cm2 > up_val & cm2 < 200) {
      orientation(120);
    }
    else if (cm2 < down_val) {
      orientation(60);
    }
    // 小车刚出挡板，此时与挡板处于平行状态。
    else if (cm2 > 200) {
      orientation(90);
      delay(500);
      orientation(150);
    }
    else {
      orientation(90);
    }
  }
  else {
    orientation(45);
  }
  delay(500);
}

// 转向
void orientation(int pos) {
  if (pos >= 90) {
    for (int i = 90; i <= pos; i++) {
      s.write(i);
      //延时的作用：舵机转动需要时间的
      delay(15);
    }
  }
  else if (pos < 90) {
    for (int i = 90; i >= pos; i--) {
      s.write(i);
      delay(15);
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

