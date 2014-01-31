#include <Wire.h>

#define _LTC4151   0x66  //write address
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
  //delay(15);
  Wire.requestFrom(_LTC4151, 4, false);  //request 4 bytes from slave. (0x00,1,2, and 3) in order of sensea, senseb, voltsa, voltsb
  //false is for repeated start, as specified by the datasheet.
  if(4 <= Wire.available()){  //if 4 bytes were received
    //Serial.print(Wire.available());
    current = (Wire.read())<<8 | Wire.read();
    voltage = (Wire.read())<<8 | Wire.read();
  }
  Wire.endTransmission();
  Serial.print(voltage);
  Serial.print("V ");
  Serial.print(current);
  Serial.println("A ");  
}
