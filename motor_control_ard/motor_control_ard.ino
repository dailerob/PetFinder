
////////////////////////////////////////////////////LIDAR VARIABLES////////////////////////////////////////////
//include struct definition before called
struct dataTime{
  long data;
  long timeVal;
};


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
int LidarEnValue;
//Lidar Motor
//Handled by raspberry pi

//Lidar Data Variable
struct dataTime lidarData;

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


////////////////////////////////////////////////////ENCODER VARIABLES///////////////////////////////////////////

 #define outputA1 11
 #define outputB1 12
 #define outputA2 0
 #define outputB2 1
 int counter1 = 0; 
 int counter2 = 0;
 int aState;
 int aLastState;  
 int bState;
 int bLastState;

 int motor1position;
 int motor2position;

 long encoderTime;
////////////////////////////////////////////////////ENCODER VARIABLES///////////////////////////////////////////




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
  pinMode(lidarEnPin, INPUT);

  //////////////////////ENCODER PIN SETUP//////
  //Encoder pin setup
   pinMode (outputA1,INPUT);
   pinMode (outputB1,INPUT);
   pinMode (outputA2,INPUT);
   pinMode (outputB2,INPUT);

   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA1); 
   aLastState = digitalRead(outputA2);  
   ///////////////////////ENCODER PIN SETUP/////

}
///////////////////////////////////////////////////SETUP//////////////////////////////////////////////////////

void loop()
{ 
  ////////////////////READ INFO FROM PYTHON/////////////////
  //Will become more complex as we can send more commands
  dir = Serial.read();
  ////////////////////READ INFO FROM PYTHON/////////////////

  /////////////////////Get lidar data ///////////////////////
  lidarData = getLidarData();
  LidarEnValue = digitalRead(LidarEnValue);//reads the current state of the lidar encoder
  
  
  ///////////////////////////////////////////GET ENCODER DATA////////////////////////////////////////////////
  //I would like to eventually have this be a method, but variable dependancies made by this script's creator make that a bit difficult. 

  //read both encoders at the same time so we get the most even reading possible
  aState = digitalRead(outputA1); // Reads the "current" state of the outputA
  bState = digitalRead(outputA2); // Reads the "current" state of the outputA
  encoderTime = millis();

  //Stuff for motor one
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB1) != aState) { 
       counter1 ++;
     } else {
       counter1 --;
     }
     //Serial.print("Position A: ");
     //Serial.println(counter1);
     motor1position = counter1;
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state

   //stuff for motor two
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (bState != bLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB2) != bState) { 
       counter2 ++;
     } else {
       counter2 --;
     }
     //Serial.print("Position B: ");
     //Serial.println(counter2);
     motor2position = counter2;

   } 
   bLastState = bState; // Updates the previous state of the outputA with the current state

  ///////////////////////////////////////////GET ENCODER DATA////////////////////////////////////////////////

  //////////////////////////////////////////INTERPERATE PYTHON COMMANDS/////////////////////////////////////
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

  //////////////////////////////////////////SEND INFO TO PYTHON//////////////////////////////////////////////////
  if(lidarData.data!=-1){
      Serial.print("S"); // first sanity check 
      Serial.print(",");  
      Serial.print(lidarData.data); //send lidar distance
      Serial.print(",");  
      Serial.print(lidarData.timeVal); //send time lidar distance was recorded
      Serial.print(",");  
      Serial.print(LidarEnValue); //send time lidar distance was recorded
      Serial.print(",");
      Serial.print(motor1position); //send motor one position
      Serial.print(",");  
      Serial.print(motor2position); //send motor two position 
      Serial.print(",");
      Serial.print(encoderTime); //send the time that the motor position was recorded 
      Serial.print(",");
      Serial.print("E"); // Last sanity check
      Serial.println();//end the line
  }
 
  //////////////////////////////////////////SEND INFO TO PYTHON//////////////////////////////////////////////////
}

void goForward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 250);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 250);
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

dataTime getLidarData(){
  //set up the struct to return data to the loop function 
  dataTime dataTimeVal = {0,0};

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
        // check the time on the arduino 
        dataTimeVal.timeVal = millis();
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7]; 
        if(uart[8]==(check&0xff))//checkthereceiveddataasperprotocols 
        {
          dist=uart[2]+uart[3]*256;//calculate distance value 

          //strength=uart[4]+uart[5]*256;//calculate signal strength value 
          dataTimeVal.data = dist;

          return dataTimeVal;
          break;

        }//last sanity check 
      }//check if the second sanity check comes back true 
    }//check if the first sanity check comes back true 
  }//check if the serial is available

  dataTimeVal.data = -1; // the case where the lidar did not return any data
  dataTimeVal.timeVal = millis();
  return dataTimeVal;
}



