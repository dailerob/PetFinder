char foo;

#include<SoftwareSerial.h>//softserialportheaderfile 
SoftwareSerial Serial1(2,3);


int dist;
int strength; 
int check;
int i;
int uart[9];
const int HEADER =0x59;

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
char dir = ' '; 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//settheBaudrateofArduinoandcomputerserialport 
  Serial1.begin(115200);//settheBaudrateofLiDARandArduinoserialport
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //lidar_scan();
  dir = Serial.read();
  switch (dir) {
    case 'F':
      goForward();
      break;
    case 'B':
      goBack();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':
      STOP();
      break;
  }
}

void lidar_scan() {
  if(Serial1.available())
  {
    if(Serial1.read()==HEADER) 
    {
      uart[0]=HEADER; 
      if(Serial1.read()==HEADER)//determinedatapackageframeheader0x59 
      {
        uart[1]=HEADER; 
        for(i=2;i<9;i++)//storedatatoarray 
        {
          uart[i] = Serial1.read();
        }
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7]; 
        if(uart[8]==(check&0xff))//checkthereceiveddataasperprotocols 
        {
          dist=uart[2]+uart[3]*256;//calculatedistancevalue 
          strength=uart[4]+uart[5]*256;//calculatesignalstrengthvalue 
          //Serial.print("dist="); 
          Serial.print(dist);//outputLiDARtestsdistancevalue
          Serial.print(' '); 
          //Serial.print("strength="); 
          Serial.print(strength);//outputsignalstrengthvalue 
          Serial.print('\n');
      }
      }
      }
      }
    }

void goForward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);
}

void goBack()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 150);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 150);
}

void turnLeft()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 150);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 150);
}

void turnRight()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 150);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 150);
}

void STOP()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

