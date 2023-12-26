void setup() {
 Serial.begin(9600);

}

void loop() {
  // int mq7output=ReadMQ7();
  // Serial.println("MQ7 value: ");
  // Serial.println(mq7output);
   int mq135output=ReadMQ135();
  Serial.println("MQ135 value: ");
  Serial.println(mq135output);
  delay(1000);  
}

int ReadMQ7(){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  return sensorValue;
 
}

int ReadMQ135(){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A5);
  return sensorValue;
 
}