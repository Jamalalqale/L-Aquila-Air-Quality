#include "MQ135.h"
MyMQ135Class myMQ135;

void setup() {
  Serial.begin(9600);
  myMQ135.setMQ135();
}

void loop() {
  myMQ135.readMQ135();
  // Additional code if needed
}