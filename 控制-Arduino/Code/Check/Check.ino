#include<Servo.h>
Servo s;

void setup()
{
  s.attach(13);
}
void loop()
{
  s.write(90);
}
