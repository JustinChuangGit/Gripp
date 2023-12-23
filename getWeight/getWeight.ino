#include "HX711.h"

// #define calibration_factor -740.0 
#define calibration_factor -620.0 

#define DOUT 19  
#define CLK  18

HX711 scale;
#define MAX_BUFF_LEN        255 
#define CMD_BUFF_LEN        6

// Satates of the LED
#define READ_STATE             0       // Normal blinking state
#define TARE_STATE             1       // ON for delay state
#define IDLE_STATE             2       // OFF for delay state
#define H_STATE             3       // Halt state

// LED configs
#define LED_PIN             2
#define DEFAULT_DELAY       1000

unsigned long prev_time;

float runTrial();


void setup() {
  Serial.begin(115200);
  //Serial.println("HX711 scale demo");

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); 
  scale.tare();

  pinMode(2,OUTPUT);

}

void loop() {
  
  
  while (!Serial.available());
    //Serial.println('hello');

    int x = Serial.readString().toInt();

    switch (x) {
      case 1:
        digitalWrite(2,HIGH);
        Serial.println(runTrial(), 1); //scale.get_units() returns a float
        digitalWrite(2, LOW);
      case 2:
        scale.tare();
    }

    
  }


float runTrial(){

  unsigned long timed_event;
  unsigned long current_time = millis(); 
  unsigned long start_time = current_time;
  const int interval = 5000;
  float maxForce = 0;

  while (current_time - start_time <= interval) {
    current_time = millis();
    if(abs(scale.get_units())>maxForce){
      maxForce = scale.get_units();
     }
  }
   return maxForce;
 }

