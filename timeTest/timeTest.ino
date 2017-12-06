int startTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  startTime = millis();

  Serial.print(millis());
  Serial.print(",");
  Serial.print(millis());
  Serial.print(",");
  Serial.print(millis());
  Serial.print(",");
  Serial.print(millis());
  Serial.print(",");
  Serial.print("\n");

}
