
////////////////////////////////////////////////////LIDAR VARIABLES////////////////////////////////////////////

//include software serial to allow serial communication with Lidar
#include<SoftwareSerial.h>//softserialportheaderfile 
//set the pins Lidar will use
SoftwareSerial Serial1(2,3);

//Lidar communication variables
int dist;
int strength; 
int check;
int i;
int uart[9];
const int HEADER =0x59;

//Lidar Encoder
const byte lidarEnPin = 13;
//Lidar Motor
//Handled by raspberry pi

////////////////////////////////////////////////////LIDAR VARIABLES////////////////////////////////////////////

////////////////////////////////////////////////////MOTOR VARIABLES///////////////////////////////////////////

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

////////////////////////////////////////////////////MOTOR VARIABLES///////////////////////////////////////////


///////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////
void setup()
{
  //Setup serial communication with the usb
  Serial.begin(9600);
  //Setup Serial communication with the Lidar
  Serial1.begin(115200);

  // Drive motor control pins 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //Lidar motor Control pins
  //Handled by raspberry pi now. 

  //Lidar encoder pin 
  pinMode(liEncoderPin, INPUT);

}

void loop()
{
  //Check external inputs 

  /*
  ///////////////////////////////////////////GET LIDAR DATA//////////////////////////////////////////////////
  //Distance is saved under variable name dist

  if(Serial1.available())
  {
    //Serial.println(Serial1.read());
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
          dist=uart[2]+uart[3]*256;//calculate distance value 
          strength=uart[4]+uart[5]*256;//calculate signal strength value 
        }
      }
    }
  }

  //Get Lidar encoder data
  lidarState = digitalRead(pinNum);
  lidarTime = millis()
  ///////////////////////////////////////////GET LIDAR DATA//////////////////////////////////////////////////
  */
  
  ///////////////////////////////////////////GET ENCODER DATA////////////////////////////////////////////////
  //TODO

  ///////////////////////////////////////////GET ENCODER DATA////////////////////////////////////////////////


  ///////////////////////////////////////////READ INFO FROM PYTHON///////////////////////////////////////////
  //Will become more complex as we can send more commands
  dir = Serial.read();
  ///////////////////////////////////////////READ INFO FROM PYTHON///////////////////////////////////////////
  switch (dir) {
    case 'F':
      goForward();
      STOP();
      break;
    case 'B':
      goBack();
      STOP();
      break;
    case 'L':
      turnLeft();
      STOP();
      break;
    case 'R':
      turnRight();
      STOP();
      break;
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
  delay(5000);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void goBack()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 150);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 150);
  delay(5000);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void turnLeft()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 150);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 150);
  delay(2000);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void turnRight()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 150);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 150);
  delay(2000);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void STOP()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

