
#include <MQUnifiedsensor.h>
//Definitions
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-131" //MQ131
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ131CleanAir 15 //RS / R0 = 15 ppm
//Declare Sensor
MQUnifiedsensor MQ131(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  Serial.begin(9600); 
  MQ131.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ131.setA(23.943); MQ131.setB(-1.11); // Configure the equation to to calculate O3 concentration
  /*
    Exponential regression:
  GAS     | a      | b
  NOx     | -462.43 | -2.204
  CL2     | 47.209 | -1.186
  O3      | 23.943 | -1.11
  */
  MQ131.init(); 
  MQ131.setRL(1);  
  Serial.print("Calibrating please wait.");
}

void loop() {
 MQ131.update(); // Update data, the arduino will read the voltage from the analog pin
 float calcR0 = MQ131.calibrate(RatioMQ131CleanAir);
 Serial.println(calcR0);
 MQ131.serialDebug(true);
 MQ
 delay(500);
}