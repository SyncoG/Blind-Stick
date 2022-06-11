
#define DUMP_REGS
#include "pitches.h"
#include <Wire.h>
#include <APDS9930.h>

// Global Variables
APDS9930 apds = APDS9930();
uint16_t proximity_data = 0;
int proximity_max = 0;
float ambient_light = 0; // can also be an unsigned long
uint16_t ch0 = 0;
uint16_t ch1 = 1;

const int front_trigPin = 13; // Trigger Pin of Ultrasonic Sensor
const int front_echoPin = 12; // Echo Pin of Ultrasonic Sensor

const int right_trigPin = 11; // Trigger Pin of Ultrasonic Sensor
const int right_echoPin = 10; // Echo Pin of Ultrasonic Sensor

const int left_trigPin = 9; // Trigger Pin of Ultrasonic Sensor
const int left_echoPin = 8; // Echo Pin of Ultrasonic Sensor

long front_duration, right_duration, left_duration;
int front_cm, right_cm, left_cm;


void setup() {
  //analogReference(EXTERNAL);
  
  // Initialize Serial port
  Serial.begin(9600);
  pinMode(front_trigPin, OUTPUT);
  pinMode(front_echoPin, INPUT);

  pinMode(right_trigPin, OUTPUT);
  pinMode(right_echoPin, INPUT);

  pinMode(left_trigPin, OUTPUT);
  pinMode(left_echoPin, INPUT);

  
  // Initialize APDS-9930 (configure I2C and initial values)
  if ( apds.init() ) { } else {}
  
  // Start running the APDS-9930 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {} else {}

    if ( !apds.setProximityGain(PGAIN_1X) ) {}
  
  // Start running the APDS-9930 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {} else {
    
  

  

#ifdef DUMP_REGS
  /* Register dump */
  uint8_t reg;
  uint8_t val;

  for(reg = 0x00; reg <= 0x19; reg++) {
    if( (reg != 0x10) && \
    
        (reg != 0x11) )
    {
      apds.wireReadDataByte(reg, val);
    }
  }
  apds.wireReadDataByte(0x1E, val);

#endif

  // Wait for initialization and calibration to finish
  delay(500);
}
}

void loop() {
  
  // Read the light levels (ambient, red, green, blue)
  if (  !apds.readAmbientLightLux(ambient_light) ||
        !apds.readCh0Light(ch0) || 
        !apds.readCh1Light(ch1) ) {} else {}
  
  // Wait 1 second before next reading
  delay(500);
 
  if ( !apds.readProximity(proximity_data) ) { } else {}
  
  // Wait 250 ms before next reading
  delay(10);


  //FRONT ULTRASONIC WORK
  pinMode(front_trigPin, OUTPUT);
  digitalWrite(front_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(front_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(front_trigPin, LOW);
  pinMode(front_echoPin, INPUT);
  front_duration = pulseIn(front_echoPin, HIGH);
  front_cm = microsecondsToCentimeters(front_duration);
//  Serial.print("Front Ultra: ");
//  Serial.println(front_cm);


    //RIGHT ULTRASONIC WORK
  pinMode(right_trigPin, OUTPUT);
  digitalWrite(right_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(right_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(right_trigPin, LOW);
  pinMode(right_echoPin, INPUT);
  right_duration = pulseIn(right_echoPin, HIGH);
  right_cm = microsecondsToCentimeters(right_duration);

    //LEFT ULTRASONIC WORK
  pinMode(left_trigPin, OUTPUT);
  digitalWrite(left_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(left_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(left_trigPin, LOW);
  pinMode(left_echoPin, INPUT);
  left_duration = pulseIn(left_echoPin, HIGH);
  left_cm = microsecondsToCentimeters(left_duration);

  int am = ambient_light;
  int px = proximity_data;

  if(am > 2){
    if(px >= 600){
    
      if((front_cm < 100 && right_cm < 50)){
        tone(7, 1000, 500);
      }
      else if(front_cm < 100 && left_cm < 50){
        tone(7, 1000, 500);
      }
      else if(right_cm <50 && left_cm < 50){
        tone(7, 1000, 500);
      }
      else if(right_cm <50 || left_cm < 50){
        tone(7, 1000, 500);
      }
      else if(front_cm < 100){
        if(right_cm < 50){
          tone(7, 1000, 500);
        }
        else{
          tone(7, 1000, 500);
        }
      }
      else if(front_cm < 100 && right_cm < 50 && left_cm < 50){
        tone(7, 1000, 500);
      }
    }
    else{
      tone(7, 1000, 500);
    }
  }
  else{
    tone(7, 1000, 500);
  }

}


long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}
