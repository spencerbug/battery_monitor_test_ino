//battery monitor test
//For interfacing with the LTC4151
//by spencer neilan, 2014

#include <Wire.h>

#define BADDRESS   0xCC //address of all LTC4151 devices
//register address on device
#define BSENSEMSB  0x00 //most sig bit sense current 
#define BSENSELSB  0x01
#define BVOLTSMSB  0x02
#define BVOLTSLSB  0x03
#define BADINMSB   0x04
#define BADINLBSB  0x05
#define BCONTROL   0x06

uint16_t voltage, current;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

}

void I2CHandler( int byteCount)
Wire.onReceive(I2CInterface::I2CHandler);


class I2CInterface{
  public:
  bool busy;
  static void I2CHandler(int byteCount);
  I2CInterface();
};

  I2CInterface::I2CInterface(){
    Wire.onReceive(I2CInterface::I2CHandler); //creates an event handler when receiving an incoming transmission
    busy=false;
  }
  class BatteryMonitorInterface : public I2CInterface{
    public:
    uint16_t current;
    uint16_t voltage;
    void getAll();
  }
  
  BatteryMonitorInterface
  

//according to the datasheet, if the master keeps ACKing after each recieved transmission,
//the slave will continue to send each conscutive with each incrementing address pointer until it hits 0x00
void getBatteryIV(uint16_t* current, uint16_t* voltage){
  Wire.requestFrom(BADDRESS, 0x00); //this just requests sens MSB, but master will keep ACKing.
  Wire.onReceive(batteryMonitorHandler); //sets up an event handler that upon reception, will call BatteryMonitorHandler. 
          //This overrides quadratureEventHandler.
}


void loop() {
  Wire.requestFrom(BADDRESS,BVOLTSMSB);
  Wire.onReceive(
  if(Wire.available() > 7){
    voltage=Wire.read();    //slave first sends MSB
    voltage = voltage << 8;  //shift high byte over
    
  }
  while(Wire.available());

 =Wire.requestFrom(BADDRESS,BVOLTSLSB);
  uint16_t voltage_n=(voltageMSB<<8)+voltageLSB;
  float voltage=102.4/4096.0*(float)voltage_n; //full scale range 0 - 4095 corresponds to 0 to 102.4V
  
  uint8_t senseMSB=Wire.requestFrom(BADDRESS,BSENSEMSB);
  uint8_t senseLSB=Wire.requestFrom(BADDRESS,BSENSELSB);
  uint16_t sense_n =(voltageMSB<<8)+voltageLSB;
  float sensevolts=0.08192/4095.0*(float)sense_n;//full scale range 0-4095 corresponds to 0 to 81.92mV
  float current=sensevolts/0.01;  //i=v/rshunt
  
  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("V.  current: ");
  Serial.print(current);
  Serial.println("A.");
  
}
