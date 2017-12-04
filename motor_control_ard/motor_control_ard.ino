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

void setup()
{
  // set all the motor control pins to outputs
  Serial.begin(19200);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  dir = Serial.read();
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

