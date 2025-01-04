
#include <i2c_t3.h>
//#define HWSERIAL Serial1

// pin definitions

const int ADC_ISense = 16;
const int ADC_VSense = 17;
const int ADC_TempSense = 18;
const int ADC_IAdj_Man = 15;
const int DAC_Iref = 26;

const int IICData = 23;
const int IICCLK = 22;

const int I_Range_Current_Low = 2;
const int I_Range_Current_Med = 3;
const int I_Range_Current_High = 4;
const int VbiasGND = 6;

const int Load_ON_OFF_Control = 5;

// operating mode varibles


unsigned long int LD_CRSetPoint;
float LD_Res_Set = 1500;


// ADC measurement storage vars

int LD_Current;
int LD_Volt;
int LD_Temp;
int LD_ADJ;

//protections variables

int ActiveProtections = 0;
bool TempLimit = false;
bool overCurrent = false;
bool overVoltage = false;

//protection bit definitions

#define OverVoltageBit  0x01
#define OverCurrentBit  0x02
#define OverTempBit     0x04

//Comms variables

volatile uint8_t opMode = 0;
volatile uint8_t onOffState;
volatile uint32_t LD_SetPoint = 500;
volatile uint8_t VbiasStateSet;
volatile uint8_t IrangeSet;
volatile uint8_t VrangeSet;
volatile uint8_t MeaurementSelection;
volatile uint8_t IICcmd;
volatile uint8_t SetPointGainRecieve;
volatile float SetPointGain;
volatile uint8_t SetPointOffset;
volatile float CR_SPV_GAIN = 0;
volatile float CR_SPI_GAIN = 0;
//volatile float CR_SP_GAIN = 0;
const int Voffset = 1861;
 
// Protection Limits

const int maxCurrent = 3900;
const int HysCurrent = 100;
const int maxVoltage = 3800;
const int minVoltage = 100;
const int HysVolt = 1000;
const int minTemp = 1424; // 75 deg C
const int maxTemp = 4095; // 5 deg C
const int HysTemp = 100;


const int MaxPower = 200;//max power is 200W

// IIC Instuctions Definitions

#define SetPointChange            0x10
#define modeChange                0x20
#define onOffStateChange          0x30
#define voltRangeChange           0x40
#define currentRangeChange        0x50
#define ADCReadingVolt            0x60
#define ADCReadingCurrent         0x70
#define ADCReadingTemp            0x80
#define ADCReadingRequest         0x90
#define RangeStatusRequest        0xA0
#define ProtectionStatusRequest   0xB0
#define SendRangeStatus           0xC0
#define SendProtectionStatus      0xD0
#define CRVGainChange             0xC0
#define CRIGainChange             0xD0

#define AddressLoadA              0x54
#define AddressLoadB              0x44

// IIC memory  Definitions

#define MEM_LEN 256
uint8_t mem[MEM_LEN];
volatile size_t addr;

// function delcaration

void receiveEvent(size_t count); //IIC receiveEvent function
void requestEvent(void);//IIC requestEvent function
bool protectionLimitCheckFunc(int testSample, int minLimit, int maxLimit);
void LoadOnOffControlFunc(int EnableLoad);
void IrangeSetFunc(int currentRange);
void VrangeSetFunc(int SetVReftoZero);
void ProtectionsCheck(void);
void CR_Coeff_Update(int Vrange);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  analogWriteResolution(12); // Set DAC and PWM Resolution to 12Bit
  delay(10);
  analogReadResolution(12); // Set ADC Resolution to 12Bit
  delay(10);

  analogReference(EXTERNAL);
  delay(10);
  // Setup for Slave mode, address 0x44, pins 22/23, external pullups, 100kHz
  Wire1.begin(I2C_SLAVE, AddressLoadA , I2C_PINS_22_23, I2C_PULLUP_EXT, 100000); //

  // register events
  Wire1.onReceive(receiveEvent);
  Wire1.onRequest(requestEvent);

  // Pinmode config

  pinMode(I_Range_Current_Low, OUTPUT);

  pinMode(VbiasGND, OUTPUT);

  delay(10);
  pinMode(I_Range_Current_Med, OUTPUT);

  delay(10);
  pinMode(I_Range_Current_High, OUTPUT);

  delay(10);
  pinMode(Load_ON_OFF_Control, OUTPUT);

  delay(10);

  // Set the current Range
  digitalWrite(I_Range_Current_Low, HIGH);

  //delay(20);
  digitalWrite(I_Range_Current_Med, LOW);

  //delay(20);
  digitalWrite(I_Range_Current_High, LOW);

  // Turn Load ON

  digitalWrite(Load_ON_OFF_Control, LOW);

  // start debug serial port
  // Serial.begin(9600);

  digitalWrite(VbiasGND, LOW);

}

void loop() {

  Serial.println("Start Loop");
  delay(10);
  
  switch (opMode) {

    case 0://CC mode

      while (opMode == 0) {
        Serial.println("CC Mode Active");
        ProtectionsCheck();

        while (onOffState == 1 && opMode == 0) {
          ProtectionsCheck();
          analogWrite(DAC_Iref, LD_SetPoint);
        }

        delay(10);

      }
      break;

    case 1:
    
      Serial.println("CR Mode Active");

      while (opMode == 1) {

       float CR_SP_GAIN = CR_SPI_GAIN / CR_SPV_GAIN;

        while (onOffState == 1 && opMode == 1) {

          ProtectionsCheck();
          LD_CRSetPoint = (int)abs(((analogRead(ADC_VSense) - Voffset) * CR_SP_GAIN) / 100);
          analogWrite(DAC_Iref, LD_CRSetPoint);

        }
      }

      break;

    case 2:
      Serial.println("CP Mode Active");
      while (opMode == 2) {
        ProtectionsCheck();
        float CP_Gain = CR_SPI_GAIN * CR_SPV_GAIN;
        while (onOffState == 1 && opMode == 2) {
          ProtectionsCheck();
          LD_CRSetPoint =  (int)abs((CP_Gain * LD_SetPoint) / (analogRead(ADC_VSense) - Voffset));
          analogWrite(DAC_Iref, LD_CRSetPoint);
        }
      }
      break;
  }
}
