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
  MQ7.setRL(1);//set Rl
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
   
}

void loop() {
  /*
   the sensor must be 'heated' at 5 V for 60 s to desorb the gases, then powered at 1.4 V for 90 s during the actual reading.
   According to MQ-7 datasheet, sensor has to run through high- and low-heating cycles in order to get proper measurements. 
   During low temperature phase, CO is absorbed on the plate, producing meaningful data.
  During high temperature phase, absorbed CO and other compounds evaporate from the sensor plate, cleaning it for the next measurement.
  */  
 unsigned long startTime = millis(); // Record the start time
  while (millis() - startTime <= 60000) {  // Run for 60 seconds
    analogWrite(5, 255); // 255 is DC 5V output
    MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ7.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup  
    delay(500); //Sampling frequency
  }
   startTime = millis(); // Record the start time
    while (millis() - startTime <= 90000) {  // Run for 90 seconds
    analogWrite(5, 20); // 255 is DC 5V output
    MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
    MQ7.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
    MQ7.serialDebug(); // Will print the table on the serial port
    delay(500); //Sampling frequency
  }  
}