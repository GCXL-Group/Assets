#include<Servo.h>
#define S1 A1
#define S2 A2
#define S3 A3

const float down_val = 15 ;
const float up_val = 20;
const int average_count = 10;
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
  float sum = 0;
  for (int i = 0; i < 500; i++) {
    float sensor_value = analogRead(S3);
    sum += sensor_value;
  }
  float average_val = sum/500;
  Serial.print(average_val);
  Serial.print("\t");
  Serial.print(pow(2822.11/average_val,1.2401));
  Serial.print("\t");
  Serial.print(pow(3027.4 / average_val, 1.2134));
  Serial.println();
  return 0;
}

