#include <Wire.h>

#define SHUNT_R 0.02
#define _LTC4151 0b1100110  //write address
//#define _LTC4151 205  //read address
#define _SENSEMSB  0 //most sig bit sense current 
#define _SENSELSB  1
#define _VOLTSMSB  2
#define _VOLTSLSB  3
#define _ADINMSB   4
#define _ADINLBSB  5
#define _CONTROL   6

uint16_t current, voltage;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(byte(_LTC4151)); //transmit to write todevic
  Wire.write(0);  //tell device to point to register 0
  delay(15);
  Wire.requestFrom(_LTC4151, 4);  //request 4 bytes from slave. (0x00,1,2, and 3) in order of sensea, senseb, voltsa, voltsb
  if(4 <= Wire.available()){
    Serial.print("available!");
    current = (Wire.read())<<8 | Wire.read();
    voltage = (Wire.read())<<8 | Wire.read();
  }
  Serial.print(voltage);
  Serial.print("V ");
  Serial.print(current);
  Serial.println("A ");  
}
