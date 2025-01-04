
#include <PID_v1.h>
#include <i2c_t3.h>
#define HWSERIAL Serial1

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

// Controls and Measurement variables

unsigned long int LD_CRSetPoint = 0;
unsigned long int CP_SetPoint = 0;
double AC_CR_SetPoint = 0;
double AC_CC_SetPoint = 0;
float LD_Res_Set = 1500;

const int Ref_Offset = 1861;

struct RMS {
  
  unsigned int INITIAL  = 2000; // starting Value for the calculated RMS voltage
  unsigned int SAMPLES = 100; // number of samples to avg - note that with 12biat ADC max value is 4095 - if the sum of the ADC samples Squared is larger than 32bytes there will be issues -  4,294,967,295/4095*4095 = max samples =  256 max - more samples = slower filter response
  double RMS = INITIAL; // Calculated RMS of ADC Sample
  unsigned long int Sum_of_Samples_Squared = 1UL * SAMPLES * INITIAL * INITIAL; // Stores the sum of all samples
  unsigned long int Delay_SampleRate = 2;
  unsigned long int Millis_LastTime = 0;
  
};

struct RMS RMS_Volt;
struct RMS RMS_Current;


// ADC measurement storage vars

int LD_Current;
int LD_Volt;
int LD_Temp;
int LD_ADJ;

//protections variables

unsigned short int ActiveProtections = 0;
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
volatile float CR_SP_GAIN = 0;

// Protection Limits

const int maxCurrent = 3900;
const int HysCurrent = 100;
const int maxVoltage = 3800;
const int minVoltage = 100;
const int HysVolt = 1000;
const int minTemp = 206; // 75 deg C
const int maxTemp = 3000; // 5 deg C
const int HysTemp = 100;

//Specify the links and initial tuning parameters

//Define PID Control Variables

//double I_RMS_Out, I_RMS_Out, CP_SetPoint;
double AC_CC_Kp = 2, AC_CC_Ki = 5, AC_CC_Kd = 1;
double PID_SetPoint = LD_SetPoint;
PID PID_LoadConstCurrent(&RMS_Current.RMS, &AC_CC_SetPoint, &PID_SetPoint, AC_CC_Kp, AC_CC_Ki, AC_CC_Kd, REVERSE);


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
#define RMS_ADCReadingVolt        0xE0
#define RMS_ADCReadingCurrent     0xF0

#define AddressLoadA              0x44
#define AddressLoadB              0x54

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
struct RMS Function_RMS_Calc(struct RMS RMSCalc, unsigned short ADC_Sample);

void setup() {
  
  // put your setup code here, to run once:
  PID_LoadConstCurrent.SetOutputLimits(0, 5000);
  Serial.begin(9600);
  analogWriteResolution(12); // Set DAC and PWM Resolution to 12Bit
  delay(10);
  analogReadResolution(12); // Set ADC Resolution to 12Bit
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
  
  switch (opMode) {

    case 0://CC mode

      while (opMode == 0) {

        ProtectionsCheck();

        while (onOffState == 1 && opMode == 0) {

          ProtectionsCheck();

          analogWrite(DAC_Iref, LD_SetPoint);

        }
     
      }
      break;

    case 1:

      while (opMode == 1) {

        //CR Loop

        CR_SP_GAIN = CR_SPI_GAIN / CR_SPV_GAIN;

        ProtectionsCheck();

        while (onOffState == 1 && opMode == 1) {// constant Res

          ProtectionsCheck();
          LD_CRSetPoint = (int)abs(((analogRead(ADC_VSense) - Ref_Offset) * CR_SP_GAIN) / LD_SetPoint);
          analogWrite(DAC_Iref, LD_CRSetPoint);

        }
      }

      break;

    case 2:

      while (opMode == 2 ) {// constant power

        ProtectionsCheck();

        while (onOffState == 1 && opMode == 2) {

          ProtectionsCheck();
          CP_SetPoint =  (int)abs((CR_SPI_GAIN * CR_SPV_GAIN * LD_SetPoint) / (analogRead(ADC_VSense) - Ref_Offset));
          analogWrite(DAC_Iref, CP_SetPoint);

        }

      }

      break;

    case 3: //AC Constant Current Mode

      while (opMode == 3) { //AC Constant Current Mode

        ProtectionsCheck();

        while (onOffState == 1 && opMode == 3) {


          if (millis() - RMS_Current.Millis_LastTime > RMS_Current.Delay_SampleRate) { // Calculate RMS Current

            RMS_Current = Function_RMS_Calc(RMS_Current, abs((analogRead(ADC_ISense) - Ref_Offset)));
            PID_LoadConstCurrent.Compute();
            RMS_Current.Millis_LastTime = millis();

          }

          AC_CC_SetPoint = PID_LoadConstCurrent.Compute();
          AC_CR_SetPoint =  (int)abs(((analogRead(ADC_VSense) - Ref_Offset) * CR_SP_GAIN) / AC_CC_SetPoint);
          analogWrite(DAC_Iref, AC_CR_SetPoint);

          ProtectionsCheck(); // make sure that the load isn't exceeding its operating limits

        } // while (onOffState == 1 && opMode == 3) END

      }//while (onOffState == 1 && opMode == 3) END

      break;
  }// opMode Switch END
}// Void Loop END
