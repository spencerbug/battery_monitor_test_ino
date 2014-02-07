//this program interfaces the Arduino Due to the LTC4151.
//Wire library's implementation for the Due does not currently support repeated start
//

#include <Arduino.h>
#include <Wire.h>


#define _LTC4151   0x66
//#define _LTC4151 205  //read address
#define _SENSEMSB  0 //most sig bit sense current 
#define _SENSELSB  1
#define _VOLTSMSB  2
#define _VOLTSLSB  3
#define _ADINMSB   4
#define _ADINLBSB  5
#define _CONTROL   6

struct{
  uint16_t current;
  uint16_t voltage;
  uint16_t ADIN
  uint8_t control
} powerFrame;

void getBatterySnapshot(powerFrame *frame){
    Wire.beginTransmission(byte(_LTC4151)); // this sends start condition and device address, followed by r/w = (0)
    //this is a hack for repeated start. This sends seven 0s followed by a 1 from r/w bit. (The slave sees this as command=0x01)
    Wire.requestFrom( 0, 7 );
    while(7 <= Wire.available()){
      frame->(current<<8
    }

}

//this function is a hack, because arduino due library doesn't support repeated start.
//It basically uses what the hardware treats as the address combined with r/w bit as a command
void batteryMonitor_getAll(uint8_t command, uint8_t numBytesRequested, false ){
  uint8_t commandToAddress = command >> 1 ;
  uint8_t commandToRW      = command & 1;
  if (commandToRW == 1){
    //this sends repeated start, first 7 bits of command, then a 1 as the 8th command bit.
    //This is the easy one since it automatically returns the stream of data.
    Wire.requestFrom(commandToAddress, numBytesRequested);
  }
  if (commandToRW == 0){
    //this sends a repeated start, first 7 bits of command, then a 0 as the 8th command bit
    //then it will 
    Wire.beginTransmission(commandToAddress);
    Wire.
  }
}

uint16_t current, voltage;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(byte(_LTC4151)); // this sends start condition and device address, followed by 
  //arduino due doesn't support the master sending repeated starts, so disable
  Wire.
  Wire.beginTransmission();
  //delay(15);
  Wire.requestFrom(_LTC4151, 4, false);  //request 4 bytes from slave. (0x00,1,2, and 3) in order of sensea, senseb, voltsa, voltsb
  //false is for repeated start, as specified by the datasheet.
  if(4 <= Wire.available()){  //if 4 bytes were received
    //Serial.print(Wire.available());
    current = ( Wire.read() << 8) | Wire.read();
    voltage = (Wire.read() << 8) | Wire.read();
  }
  Wire.endTransmission();
  Serial.print(voltage);
  Serial.print("V ");
  Serial.print(current);
  Serial.println("A ");  
}
