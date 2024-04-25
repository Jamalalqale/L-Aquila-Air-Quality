#include <MQUnifiedsensor.h>

class MyMQ135Class {
private:
  MQUnifiedsensor MQ135;

public:
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
//#define calibration_button 13 //Pin to calibrate your sensor
  MyMQ135Class() : MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type) {}

  void setMQ135() {
    MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b 
    MQ135.setRL(1);
    MQ135.setR0(0.06); //set R0
    MQ135.init();
  }

  void readMQ135() {
 MQ135.update(); 
  MQ135.setA(605.18); MQ135.setB(-3.937); 
  float CO = MQ135.readSensor(); 
  MQ135.setA(77.255); MQ135.setB(-3.18); 
  float Alcohol = MQ135.readSensor(); 
  MQ135.setA(110.47); MQ135.setB(-2.862); 
  float CO2 = MQ135.readSensor(); 
  MQ135.setA(44.947); MQ135.setB(-3.445);
  float Toluen = MQ135.readSensor(); 
  MQ135.setA(102.2 ); MQ135.setB(-2.473); 
  float NH4 = MQ135.readSensor(); 
  MQ135.setA(34.668); MQ135.setB(-3.369);
  float Aceton = MQ135.readSensor(); 
  Serial.print("MQ135 Co: "); Serial.println(CO); 
  Serial.print("MQ135 Alcohol: "); Serial.println(Alcohol);
  Serial.print("MQ135 CO2: "); Serial.println(CO2); 
  Serial.print("MQ135 Toluen: "); Serial.println(Toluen); 
  Serial.print("MQ135 NH4: "); Serial.println(NH4); 
  Serial.print("MQ135 Aceton: "); Serial.println(Aceton); 

  
  }
};