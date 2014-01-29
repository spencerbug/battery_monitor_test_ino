//battery monitor test
//For interfacing with the LTC4151
//by spencer neilan, 2014

#include <Wire.h>

#define SHUNT_R 0.02

#define BADDRESS   0xCC //address of all LTC4151 devices
//register address on device
#define BSENSEMSB  0x00 //most sig bit sense current 
#define BSENSELSB  0x01
#define BVOLTSMSB  0x02
#define BVOLTSLSB  0x03
#define BADINMSB   0x04
#define BADINLBSB  0x05
#define BCONTROL   0x06

void (*i2cHandler)(int);

uint16_t current=5;
uint16_t voltage=5;
float realVoltage, realCurrent;
bool I2CBusy = false;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Wire.onReceive((*i2cHandler));
}



void loop() { 
//  //uint16_t voltage_n=(voltageMSB<<8)+voltageLSB;
//  float voltage=102.4/4096.0*(float)voltage_n; //full scale range 0 - 4095 corresponds to 0 to 102.4V
//  uint16_t sense_n =(voltageMSB<<8)+voltageLSB;
//  float sensevolts=0.08192/4095.0*(float)sense_n;//full scale range 0-4095 corresponds to 0 to 81.92mV
//  float current=sensevolts/0.01;  //i=v/rshunt
//  
  requestIandV;
  
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("V.  current: ");
  Serial.print(current);
  Serial.println("A.");
}

static void getCurrentHandler(int byteCount){
  current=(Wire.read()<<8) | Wire.read();
  realCurrent=(0.08192/4095.0*(float)current)/SHUNT_R;//full scale range 0-4095 corresponds to 0 to 81.92mV
  I2CBusy=false;
}
static void getVoltageHandler(int byteCount){
  voltage=(Wire.read()<<8) | Wire.read();
  realVoltage=102.4/4096.0*(float)voltage; //full scale range 0 - 4095 corresponds to 0 to 102.4V
  I2CBusy=false;
}
static void getIandVHandler(int byteCout){
  current=(Wire.read()<<8) | Wire.read();
  realCurrent=(0.08192/4095.0*(float)current)/SHUNT_R;
  voltage=(Wire.read()<<8) | Wire.read();
  realVoltage=102.4/4096.0*(float)voltage; //full scale range 0 - 4095 corresponds to 0 to 102.4V
  I2CBusy=false;
    
}

void requestCurrent(){
  Wire.beginTransmission(BADDRESS);
  Wire.write(BSENSEMSB);//write the (starting) register master wants to read from. 
  Wire.endTransmission();
  Wire.requestFrom(BADDRESS, 2,false);
  i2cHandler = &getCurrentHandler;
  I2CBusy=true;
}

void requestVoltage(){
  Wire.beginTransmission(BADDRESS);
  Wire.write(BVOLTSMSB);
  Wire.endTransmission();
  Wire.requestFrom(BADDRESS, 2, false);
  i2cHandler = &getVoltageHandler;
  I2CBusy=true;
}

void requestIandV(){
  Wire.beginTransmission(BADDRESS);
  Wire.write(BSENSEMSB);
  Wire.endTransmission();
  Wire.requestFrom(BADDRESS, 4, false);
  i2cHandler = &getIandVHandler;
  I2CBusy=true;
}
