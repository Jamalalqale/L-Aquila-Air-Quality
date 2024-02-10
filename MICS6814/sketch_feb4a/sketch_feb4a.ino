#include "MICS6814.h"

#define PIN_CO  3
#define PIN_NO2 0
#define PIN_NH3 0

MICS6814 gas(PIN_CO, PIN_NO2, PIN_NH3);

void setup() {
  Serial.begin(9600);


  Serial.println("MICS-6814 Sensor Sample");
  Serial.print("Calibrating Sensor");
  gas.calibrate();
  Serial.println("OK!");

Serial.print("CO: ");
   Serial.println(gas.getBaseResistance(CH_CO));
   Serial.print("No2: ");
    Serial.println(gas.getBaseResistance(CH_NO2));
Serial.print("NH3: ");
 Serial.println(gas.getBaseResistance(CH_NH3));




}

void loop() {
 
//  Serial.print("NO2: ");
//  Serial.print(gas.getResistance(CH_NO2));
//  Serial.print("/");
//  Serial.print(gas.getBaseResistance(CH_NO2));
//  Serial.print(" = ");
//  Serial.print(gas.getCurrentRatio(CH_NO2));
//  Serial.print(" => ");
//  Serial.print(gas.measure(NO2));
//  Serial.println("ppm");
//  delay(500);

 


}
