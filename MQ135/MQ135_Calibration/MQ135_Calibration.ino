#include <MQUnifiedsensor.h>
//Definitions
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-135" 
#define ADC_Bit_Resolution 10 
#define RatioMQ135CleanAir 3.6

//Declare Sensor
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  Serial.begin(9600); 
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b 
  MQ135.init(); 
  MQ135.setRL(1);// set RL
}

void loop() {
  MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
  float calcR0 = MQ135.calibrate(RatioMQ135CleanAir);
  Serial.println(calcR0/10);
  delay(500); //Sampling frequency
}
