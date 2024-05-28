#include<Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;
Servo s7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  s4.attach(5);
  s5.attach(6);
  s6.attach(7);
  s7.attach(8);

  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("M1=");
  Serial.print(" ");
  Serial.print(ps(1));
  Serial.print(" ");

  Serial.print("M2=");
  Serial.print(" ");
  Serial.print(ps(2));
  Serial.print(" ");

//  Serial.print("M3=");
//  Serial.print(" ");
//  Serial.print(ps(3));
//  Serial.print(" ");

  Serial.print("M4=");
  Serial.print(" ");
  Serial.print(ps(4));
  Serial.print(" ");

  Serial.print("M5=");
  Serial.print(" ");
  Serial.print(ps(5));
  Serial.print(" ");

//  Serial.print("M6=");
//  Serial.print(" ");
//  Serial.print(ps(6));
//  Serial.print(" ");

  Serial.print("M7=");
  Serial.print(" ");
  Serial.println(ps(7));

s1.write(90);
s2.write(125);
s3.write(90);
s4.write(90);
s5.write(90);
s6.write(90);
s7.write(90);



// pid(1,130);
// pid(2,157);
// pid(4,93);
// pid(5,77);
// pid(7,40);
// 


  

}
float ps(int x) { // reads current position and returns it
  int y;
  switch (x) {
    case 1:
      y = analogRead(A0);
      y = map(y, 143, 528, 180, 0);
      return y;
      break;
    case 2:
      y = analogRead(A1);
      y = map(y, 136, 567, 180, 0);
      return y;
      break;
    case 3:
      y = analogRead(A2);
      y = map(y, 143, 528, 180, 0);
      return y;
      break;
    case 4:
      y = analogRead(A3);
      y = map(y, 107, 556, 180, 0);
      return y;
      break;
    case 5:
      y = analogRead(A4);
      y = map(y, 63, 595, 0, 180);
      return y;
      break;
    case 6:
      y = analogRead(A5);
      return y;
      break;
    case 7:
      y = analogRead(A6);
      y = map(y, 141, 529, 180, 0);
      return y;
      break;
    default:
      return 0;
      break;
  }
}
void pid(int s, int g) { // s is the servo number ,g is the goal which degree to be at
  float pos;
  pos = ps(s);
  Serial.print(g); Serial.print(" ");
  Serial.print(pos); Serial.print(" ");
  if (g - ps(s) >= 2)
  { pos = ps(s) + (g - ps(s)) * 1;

    if (pos > 180)pos = 180;
    if (pos < 0)pos = 0;
  }
  else
  { pos = ps(s) + (g - ps(s)) * 1;

    if (pos > 180)pos = 180;
    if (pos < 0)pos = 0;

  }
  switch (s) {
    case 1:
      s1.write(int(pos));
      break;
    case 2:
      s2.write(int(pos));
      break;
    case 3:
      s3.write(int(pos));
      break;
    case 4:

      Serial.print(int(pos));
      s4.write(int(pos));
      break;
    case 5:
      s5.write(int(pos));
      break;
    case 6:
      s6.write(int(pos));
      break;
    case 7:
      s7.write(int(pos));
      break;
  }
}
