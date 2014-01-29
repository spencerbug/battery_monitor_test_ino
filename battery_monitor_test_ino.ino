//battery monitor test
//For interfacing with the LTC4151
//by spencer neilan, 2014

#include <Wire.h>

#define BADDRESS   0xCC //address of all LTC4151 devices
#define BSENSEMSB  0x00 //most sig bit sense current 
#define BSENSELSB  0x01
#define BVOLTSMSB  0x02
#define BVOLTSLSB  0x03
#define BADINMSB   0x04
#define BADINLBSB  0x05
#define BCONTROL   0x06



void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  
  uint16_t voltageMSB=Wire.requestFrom(BADDRESS,BVOLTSMSB);
  uint16_t voltageLSB=Wire.requestFrom(BADDRESS,BVOLTSLSB);
  uint16_t voltage_n=(voltageMSB<<8)+voltageLSB;
  float voltage=102.4/4096.0*(float)voltage_n; //full scale range 0 - 4095 corresponds to 0 to 102.4V
  
  uint16_t senseMSB=Wire.requestFrom(BADDRESS,BSENSEMSB);
  uint16_t senseLSB=Wire.requestFrom(BADDRESS,BSENSELSB);
  uint16_t sense_n =(voltageMSB<<8)+voltageLSB;
  float sensevolts=0.08192/4095.0*(float)sense_n;//full scale range 0-4095 corresponds to 0 to 81.92mV
  float current=sensevolts/0.01;  //i=v/rshunt
  
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("V.  current: ");
  Serial.print(current);
  Serial.println("A.");
  
}
