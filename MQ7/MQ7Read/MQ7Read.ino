#include <MQUnifiedsensor.h>
//Definitions
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-7" //MQ7
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ7CleanAir 27.5 //RS / R0 = 27.5 ppm 
#define PWMPin 5 // Pin connected to mosfet

//Declare Sensor
MQUnifiedsensor MQ7(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
unsigned long oldTime = 0;
void setup() {  
  Serial.begin(9600); 
  pinMode(PWMPin, OUTPUT);
  MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ7.setA(99.042); MQ7.setB(-1.518); // Configure the equation to calculate CO concentration value
  MQ7.setR0(3.3);//set R0
  MQ7.setRl(1);//set Rl
  /*
    Exponential regression:
  GAS     | a      | b
  H2      | 69.014  | -1.374
  LPG     | 700000000 | -7.703
  CH4     | 60000000000000 | -10.54
  CO      | 99.042 | -1.518
  Alcohol | 40000000000000000 | -12.35
  */
  MQ7.init(); 
  //prepare
// 60s cycle
  oldTime = millis();
  while(millis() - oldTime <= (60*1000))
  {
    // VH 5 Volts
    analogWrite(5, 255); // 255 is DC 5V output
    MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ7.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    MQ7.serialDebug(); // Will print the table on the serial port
    delay(500); //Sampling frequency
  }

  // 90s cycle
  oldTime = millis();
  while(millis() - oldTime <= (90*1000))
  {
    // VH 1.4 Volts
    analogWrite(5, 20); // 255 is 100%, 20.4 is aprox 8% of Duty cycle for 90s
    MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ7.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    MQ7.serialDebug(); // Will print the table on the serial port
    delay(500); //Sampling frequency
  } 
  // Total: 60 + 90s =  2.5 minutes.

}

void loop() {
  
}