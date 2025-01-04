
#include <SD_t3.h>

// inclue teensy IIC library Files

#include <i2c_t3.h>

//encoder library file

#include <Encoder.h>

//SD card library files

#include <SPI.h>
#include <SD.h>


// Nextion display library files

#include <Nextion.h>
#include <SoftwareSerial.h>
#define HWserial Serial1
#define DBserial Serial

// initialize the encoder by associating any needed encoder interface pins
// encoder pin use definitions

const int CCWA = 27, CWA = 28;
const int CCWB = 2, CWB = 30;
Encoder LDA_Knob(CCWA, CWA);
Encoder LDB_Knob(CCWB, CWB);

// setup digial PIN use definitions

const int LDA_PB = 29;                // LDA Encoder P\B on\off push button
const int LDB_PB = 14;                // LDB Encoder P\B on\off push button
const int SDcard_CS = 10;             // SD card chip select

// ***IIC Pin Use definitions

const int IICData = 18;
const int IICCLK = 19;

// IIC Variables

int LDA_ADD = 0x44; //LDA IIC address
int LDB_ADD = 0x54; //LDA IIC address

#define SetPointChange      0x10
#define modeChange          0x20
#define onOffStateChange    0x30
#define voltRangeChange     0x40
#define currentRangeChange  0x50
#define ADCReadingVolt      0x60
#define ADCReadingCurrent   0x70
#define ADCReadingTemp      0x80
#define ADCReadingRequest   0x90
#define RangeStatusRequest  0xA0


// digi-POT Load A Constants
const int potADD_1 = B0101111;; //I2C address of digital pot 2 (U2)(Write)Load A
const int potADD_2 = B0101110; //I2C address of digital pot 2 (U2)(Write)Load B
const int potInstrucSelB =  0x80; //Instuction POT B Select
const int potInstrucSelA =  0x00; //Instuction POT A Select
const int potInstrucReset = B01000000; //Instuction Reset
const int potInstrucSD =    B00100000; //Instuction ShutDownSelect
const int potInstrucO1 =    B00010000; //Instuction O1 State Change
const int potInstrucO2 =    B00001000; //Instuction O2 State Change

const int Vamp_Range_Low = 0xAF;
const int Vamp_Range_Med = 0x46;
const int Vamp_Range_High = 0x0A;

const float CSLowandVSHIGH = 2500; // Constant resistance Gain
const float CSLowandVSLow = 130; // Constant resistance Gain
const float Voffset = 1860;
float CR_SP_GAIN = CSLowandVSHIGH;

// Load limits

const float maxCurrentRangeLow = 0.35;
const float maxCurrentRangeMed = 3;
const float maxCurrentRangeHigh = 10;

const float VinMaxRangeHigh = 400;
const float VinMaxRangeMed = 60;
const float VinMaxRangeLow = 20;


//Moving average filteres sample size

//int MAF_sizeFast = 5;  // max value is 500 (array is set to 500)
int MAF_sizeSlow = 1; // max value is 500 (array is set to 500)

// SD Card Variables

unsigned int SD_log_count = 0;
unsigned int SD_ss_count = 0;
unsigned int long SD_log_active = 0;



// structs

struct VARS

{


  uint32_t capVal;
  bool StateNow;
  bool StateLast;
  float setVal;
  float calibrated;
  float calGain;
  float calOffset;
  float filteredFast;
  float filteredSlow;
  float ChangeDetectRef;
  // float ARRFast[1];
  float ARRSlow[50];
  int indexFast;
  int indexSlow;
  bool ChangeDetectFlag = 1;
  int range;
  String NexRecieve;
  float CalHighMeas;
  float CalLowMeas;
  float CalHighRead;
  float CalLowRead;
  float offsetRead;
  float offsetMeas;


};

struct SENSE {

  struct VARS SetPoint;
  struct VARS ENCODER;
  struct VARS temp;
  struct VARS volt;
  struct VARS current;
  struct VARS Power;
  struct VARS Mode;
  struct VARS Button;
  float power;
  float CurrentMax;
  int voltageLimit;
  int CurrentLimit;
  int SetPointLow;
  int SetPointHigh;
  int SetPointOffSet;
  String Units;

};


struct SENSE LDA;
struct SENSE LDB;

// nex dual state button cap variables

uint32_t LDACal = 0;
uint32_t LDBCal = 0;
uint32_t LDA_OnOff_State = 0;
uint32_t LDB_OnOff_State = 0;


// encoder variables

long newPositionA;
long newPositionB; // stores the encoder position afer a read
int pointerPosition; // used to set the position of the menu selection icon.

unsigned long int CurrentPage = 10;  // Nextion - Create a variable to store which page is currently loaded

//**************************button pressed flags

uint32_t CalVoltHighFlag = 0;
uint32_t CalVoltLowFlag = 0;

uint32_t CalAmpHighFlag = 0;
uint32_t CalAmpLowFlag = 0;

uint32_t tVoffSetFlag = 0;
uint32_t tIoffSetFlag = 0;

uint32_t bVrangeCalFlag = 0;
uint32_t bIrangeCalFlag = 0;

uint32_t bcaliVoltSlopeFlag = 0;
uint32_t bcaliVoltOffFlag = 0;

uint32_t bcaliCurrSlopeFlag = 0;
uint32_t bcaliCurrOffFlag = 0;

uint32_t CalVoffSetFlag = 0;
uint32_t CalIoffSetFlag = 0;

uint32_t BcalIDefFlag = 0;
uint32_t BcalVDefFlag = 0;

uint32_t KPEFlag = 0;
uint32_t KPXFlag = 0;

uint32_t KPAFlag = 0;
uint32_t KPBFlag = 0;

uint32_t dsbCaLIset = 0;

uint32_t LoadA_On_Off_BState_Cap = 0;
uint32_t LoadB_On_Off_BState_Cap = 0;
uint32_t LoadA_ModeSel_Cap = 0;
uint32_t LoadB_ModeSel_Cap = 0;
uint32_t LoadA_IrangeSel_Cap = 0;
uint32_t LoadB_IrangeSel_Cap = 0;
uint32_t LoadA_VrangeSel_Cap = 0;
uint32_t LoadB_VrangeSel_Cap = 0;



//**************************button pressed flags End

bool Relay_enable = 0;
bool RelayTimerStart = 0;

int RelayTimerRef = 0;
float Relay_onTime = 0;
float Relay_period = 0;

float overTemp = 60; // calibrated over temp fault threshold value
const float PowerLimit = -200; // calibrated over power fault threshold value

//***************************Nextion widget Declarations


//***********declare buttons

//page 1 buttons

NexButton PgSelStatic = NexButton(1, 1, "PgSelStatic");  // Button added
NexButton PgSelDyn = NexButton(1, 2, "PgSelDyn");  // Button added
NexButton PgSelAuto = NexButton(1, 3, "PgSelAuto");  // Button added
NexButton PgSelCal = NexButton(1, 4, "PgSelCal");  // Button added


//Page 2 buttons


NexDSButton LoadA_ON_OFF = NexDSButton(2, 5, "LoadA_ON_OFF");  // Button added
NexDSButton LoadB_ON_OFF = NexDSButton(2, 6, "LoadB_ON_OFF");  // Dual state button added

NexDSButton RunDataLog = NexDSButton(2, 27, "RunDataLog");  // Dual state button added
NexDSButton TakeSnapShot = NexDSButton(2, 33, "TakeSnapShot");  // Dual state button added




//Page 3 buttons

NexDSButton LDA_Bmode = NexDSButton(3, 2, "LDA_Bmode");  // Button added
NexDSButton LDB_Bmode = NexDSButton(3, 3, "LDB_Bmode");  // Button added
NexDSButton LDA_B_VR = NexDSButton(3, 7, "LDA_B_VR");  // Button added
NexDSButton LDB_B_VR = NexDSButton(3, 4 , "LDB_B_VR"); // Button added
NexDSButton LDA_B_IR = NexDSButton(3, 6, "LDA_B_IR");  // Button added
NexDSButton LDB_B_IR = NexDSButton(3, 5, "LDB_B_IR");  // Button added

//Page 4 buttons

NexDSButton bcaliVoltSlope = NexDSButton(4, 21, "bcaliVoltSlope");  // Button added
NexDSButton bcaliCurrSlope = NexDSButton(4, 22, "bcaliCurrSlope");  // Button added
NexDSButton BcalVDef = NexDSButton(4, 23, "BcalVDef"); // Button added
NexDSButton bcaliVoltOff = NexDSButton(4, 23, "bcaliVoltOff");  // Button added
NexDSButton bcaliCurrOff = NexDSButton(4, 25, "bcaliCurrOff");  // Button added
NexDSButton BcalIDef = NexDSButton(4, 26, "BcalIDef");  // Button added
NexDSButton dsbCalSetA = NexDSButton(4, 2, "dsbCalSetA");  // Dual state button added
NexDSButton dsbCalSetB = NexDSButton(4, 3, "dsbCalSetB");  // Dual state button added
NexDSButton bVrangeCal = NexDSButton(4, 19, "bVrangeCal");  // Dual state button added
NexDSButton bIrangeCal = NexDSButton(4, 20, "bIrangeCal");  // Dual state button added
NexDSButton dsbCalonOff = NexDSButton(4, 38, "dsbCalonOff");  // Dual state button added
NexDSButton dsbCaLIsetHigh = NexDSButton(4, 36, "dsbCaLIsetHigh");  // Dual state button added
NexDSButton dsbCaLIsetLow = NexDSButton(4, 37, "dsbCaLIsetLow");  // Dual state button added


// Declare Text Boxes

NexText tsetA = NexText(2, 17, "tsetA");  // Text box added, so we can read it
NexText tsetB = NexText(2, 18, "tsetB");  // Text box added, so we can read it

NexText tVcalSenH = NexText(4, 7, "tVcalSenH");  // Text box added, so we can read it
NexText tVcalSetH = NexText(4, 1, "tVcalSetH");  // Text box added, so we can read it
NexText tVcalSenL = NexText(4, 8, "tVcalSenL");  // Text box added, so we can read it
NexText tVcalSetL = NexText(4, 5, "tVcalSetL");  // Text box added, so we can read it
NexText tIcalSenH = NexText(4, 9, "tIcalSenH");  // Text box added, so we can read it
NexText tIcalSetH = NexText(4, 4, "tIcalSetH");  // Text box added, so we can read it
NexText tIcalSenL = NexText(4, 10, "tIcalSenL");  // Text box added, so we can read it
NexText tIcalSetL = NexText(4, 6, "tIcalSetL");  // Text box added, so we can read it
NexText tVoffSet = NexText(4, 28, "tVoffSet");  // Text box added, so we can read it
NexText tIoffSet = NexText(4, 29, "tIoffSet");  // Text box added, so we can read it

String nexTextBoxAddressBuff; 

//Declare variables

NexVariable VRL_SlopeA =  NexVariable(0, 3, "VRL_SlopeA");
NexVariable VRL_OffsetA =  NexVariable(0, 4, "VRL_OffsetA");
NexVariable IRL_SlopeA =  NexVariable(0, 2, "IRL_SlopeA");
NexVariable IRL_OffsetA =  NexVariable(0, 5, "IRL_OffsetA");

NexVariable VRM_SlopeA =  NexVariable(0, 6, "VRM_SlopeA");
NexVariable VRM_OffsetA =  NexVariable(0, 7, "VRM_OffsetA");
NexVariable IRM_SlopeA =  NexVariable(0, 9, "IRM_SlopeA");
NexVariable IRM_OffsetA =  NexVariable(0, 8, "IRM_OffsetA");

NexVariable VRH_SlopeA =  NexVariable(0, 10, "VRH_SlopeA");
NexVariable VRH_OffsetA =  NexVariable(0, 12, "VRH_OffsetA");
NexVariable IRH_SlopeA =  NexVariable(0, 11, "IRH_SlopeA");
NexVariable IRH_OffsetA =  NexVariable(0, 13, "IRH_OffsetA");

NexVariable VRL_SlopeB =  NexVariable(0, 15, "VRL_SlopeB");
NexVariable VRL_OffsetB =  NexVariable(0, 14, "VRL_OffsetB");
NexVariable IRL_SlopeB =  NexVariable(0, 16, "IRL_SlopeB");
NexVariable IRL_OffsetB =  NexVariable(0, 17, "IRL_OffsetB");

NexVariable VRM_SlopeB =  NexVariable(0, 18, "VRM_SlopeB");
NexVariable VRM_OffsetB =  NexVariable(0, 25, "VRM_OffsetB");
NexVariable IRM_SlopeB =  NexVariable(0, 19, "IRM_SlopeB");
NexVariable IRM_OffsetB =  NexVariable(0, 20, "IRM_OffsetB");

NexVariable VRH_SlopeB =  NexVariable(0, 21, "VRH_SlopeB");
NexVariable VRH_OffsetB =  NexVariable(0, 22, "VRH_OffsetB");
NexVariable IRH_SlopeB =  NexVariable(0, 24, "IRH_SlopeB");
NexVariable IRH_OffsetB =  NexVariable(0, 23, "IRH_OffsetB");

NexVariable SPL_SlopeA =  NexVariable(0, 25, "SPL_SlopeA");
NexVariable SPL_SlopeB =  NexVariable(0, 26, "SPL_SlopeB");
NexVariable SPM_SlopeA =  NexVariable(0, 27, "SPM_SlopeA");
NexVariable SPM_SlopeB =  NexVariable(0, 28, "SPM_SlopeB");
NexVariable SPH_SlopeA =  NexVariable(0, 29, "SPH_SlopeA");
NexVariable SPH_SlopeB =  NexVariable(0, 30, "SPH_SlopeB");

NexVariable SPL_OffsetA =  NexVariable(0, 31, "SPL_OffsetA");
NexVariable SPL_OffsetB =  NexVariable(0, 32, "SPL_OffsetB");
NexVariable SPM_OffsetA =  NexVariable(0, 33, "SPM_OffsetA");
NexVariable SPM_OffsetB =  NexVariable(0, 34, "SPM_OffsetB");
NexVariable SPH_OffsetA =  NexVariable(0, 35, "SPH_OffsetA");
NexVariable SPH_OffsetB =  NexVariable(0, 36, "SPH_OffsetB");

NexVariable CalSetVoltHigh =  NexVariable(4, 20, "CalSetVoltHigh");
NexVariable CalSetVoltLow =  NexVariable(4, 21, "CalSetVoltLow");

NexVariable CalSetAmpHigh =  NexVariable(4, 22, "CalSetAmpHigh");
NexVariable CalSetAmpLow =  NexVariable(4, 23, "CalSetAmpLow");

NexVariable CalVoffSet =  NexVariable(4, 30, "CalVoffSet");
NexVariable CalIoffSet =  NexVariable(4, 31, "CalIoffSet");

NexVariable KPX =  NexVariable(4, 35, "KPX");
NexVariable KPE =  NexVariable(4, 34, "KPE");
NexVariable KPA =  NexVariable(2, 20, "KPA");
NexVariable KPB =  NexVariable(2, 21, "KPB");

char buffer[100] = {0};  // This is needed only if you are going to receive a text from the display. You can remove it otherwise.
// Further on this sketch I do receive text so that's why I created this buffer.

// Declare temp sense lookup table Arrays

const unsigned short int ArraytempAddress[] = {3708, 3693, 3679, 3665, 3651, 3637, 3622, 3608, 3594, 3580, 3567, 3553, 3539, 3525, 3511, 3498, 3484, 3471, 3457, 3444, 3430, 3417, 3403, 3390, 3377, 3364, 3350, 3337, 3324, 3311, 3298, 3285, 3272, 3259, 3247, 3234, 3221, 3208, 3196, 3183, 3171, 3158, 3146, 3133, 3121, 3108, 3096, 3084, 3072, 3059, 3047, 3035, 3023, 3011, 2999, 2987, 2975, 2964, 2952, 2940, 2928, 2917, 2905, 2893, 2882, 2870, 2859, 2847, 2836, 2825, 2813, 2802, 2791, 2780, 2769, 2758, 2747, 2736, 2725, 2714, 2703, 2692, 2681, 2670, 2660, 2649, 2638, 2628, 2617, 2607, 2596, 2586, 2575, 2565, 2555, 2544, 2534, 2524, 2514, 2503, 2493, 2483, 2473, 2463, 2453, 2443, 2434, 2424, 2414, 2404, 2394, 2385, 2375, 2365, 2356, 2346, 2337, 2327, 2318, 2309, 2299, 2290, 2281, 2271, 2262, 2253, 2244, 2235, 2226, 2217, 2208, 2199, 2190, 2181, 2172, 2163, 2154, 2146, 2137, 2128, 2120, 2111, 2102, 2094, 2085, 2077, 2068, 2060, 2052, 2043, 2035, 2027, 2018, 2010, 2002, 1994, 1986, 1978, 1970, 1962, 1954, 1946, 1938, 1930, 1922, 1914, 1906, 1899, 1891, 1883, 1876, 1868, 1860, 1853, 1845, 1838, 1830, 1823, 1815, 1808, 1800, 1793, 1786, 1779, 1771, 1764, 1757, 1750, 1743, 1736, 1728, 1721, 1714, 1707, 1700, 1694, 1687, 1680, 1673, 1666, 1659, 1653, 1646, 1639, 1633, 1626, 1619, 1613, 1606, 1600, 1593, 1587, 1580, 1574, 1567, 1561, 1555, 1548, 1542, 1536, 1529, 1523, 1517, 1511, 1505, 1499, 1492, 1486, 1480, 1474, 1468, 1462, 1456, 1451, 1445, 1439, 1433, 1427, 1421, 1416, 1410, 1404, 1398, 1393, 1387, 1381, 1376, 1370, 1365, 1359, 1354, 1348, 1343, 1337, 1332, 1326, 1321, 1316, 1310, 1305, 1300, 1295, 1289, 1284, 1279, 1274, 1269, 1263, 1258, 1253, 1248, 1243, 1238, 1233, 1228, 1223, 1218, 1213, 1208, 1204, 1199, 1194, 1189, 1184, 1180, 1175, 1170, 1165, 1161, 1156, 1151, 1147, 1142, 1137, 1133, 1128, 1124, 1119, 1115, 1110, 1106, 1101, 1097, 1093, 1088, 1084, 1080, 1075, 1071, 1067, 1062, 1058, 1054, 1050, 1045, 1041, 1037, 1033, 1029, 1025, 1021, 1016, 1012, 1008, 1004, 1000, 996, 992, 988, 984, 981, 977, 973, 969, 965, 961, 957, 954, 950, 946, 942, 938, 935, 931, 927, 924, 920, 916, 913, 909, 905, 902, 898, 895, 891, 888, 884, 881, 877, 874, 870, 867, 863, 860, 857, 853, 850, 846, 843, 840, 836, 833, 830, 827, 823, 820, 817, 814, 810, 807, 804, 801, 798, 795, 792, 788, 785, 782, 779, 776, 773, 770, 767, 764, 761, 758, 755, 752, 749, 746, 743, 740, 738, 735, 732, 729, 726, 723, 720, 718, 715, 712, 709, 707, 704, 701, 698, 696, 693, 690, 688, 685, 682, 680, 677, 674, 672, 669, 667, 664, 661, 659, 656, 654, 651, 649, 646, 644, 641, 639, 636, 634, 631, 629, 627, 624, 622, 619, 617, 615, 612, 610, 608, 605, 603, 601, 598, 596, 594, 591, 589, 587, 585, 582, 580, 578, 576, 574, 571, 569, 567, 565, 563, 561, 558, 556, 554, 552, 550, 548, 546, 544, 542, 540, 538, 536, 534, 532, 530, 528, 526, 524, 522, 520, 518, 516, 514, 512, 510, 508, 506, 504, 502, 500, 498, 497, 495, 493, 491, 489, 487, 485, 484, 482, 480, 478, 476, 475, 473, 471, 469, 468, 466, 464, 462, 461, 459, 457, 456, 454, 452, 450, 449, 447, 445, 444, 442, 440, 439, 437, 436, 434, 432, 431, 429, 428, 426, 424, 423, 421, 420, 418, 417, 415, 414, 412, 411, 409, 408, 406, 405, 403, 402, 400, 399, 397, 396, 394, 393, 391, 390, 388, 387, 386, 384, 383, 381, 380, 379, 377, 376, 375, 373, 372, 370, 369, 368, 366, 365, 364, 362, 361, 360, 358, 357, 356, 355, 353, 352, 351, 349, 348, 347, 346, 344, 343, 342, 341, 340, 338, 337, 336, 335, 333, 332, 331, 330, 329, 327, 326, 325, 324, 323, 322, 321, 319, 318, 317, 316, 315, 314, 313, 311, 310, 309, 308, 307, 306, 305, 304, 303, 302, 301, 299, 298, 297, 296, 295, 294, 293, 292, 291, 290, 289, 288, 287, 286, 285, 284, 283, 282, 281, 280, 279, 278, 277, 276, 275, 274, 273, 272, 271, 270, 269, 268, 267, 266, 266, 265, 264, 263, 262, 261, 260, 259, 258, 257, 256, 256, 255, 254, 253, 252, 251, 250, 249, 249, 248, 247, 246, 245, 244, 243, 243, 242, 241, 240, 239, 238, 238, 237, 236, 235, 234, 233, 233, 232, 231, 230, 229, 229, 228, 227, 226, 226, 225, 224, 223, 223, 222, 221, 220, 219, 219, 218, 217, 216, 216, 215, 214, 214, 213, 212, 211, 211, 210, 209, 209, 208, 207, 206, 206, 205, 204, 204, 203, 202, 202, 201, 200, 200, 199, 198, 198, 197, 196, 196, 195, 194, 194, 193, 192, 192, 191, 190, 190, 189, 188, 188, 187, 187, 186, 185, 185, 184, 183, 183, 182, 182, 181, 180, 180, 179, 179, 178, 177, 177, 176, 176, 175, 175, 174, 173, 173, 172, 172, 171, 171, 170, 169, 169, 168, 168, 167, 167, 166, 166, 165, 164, 164, 163, 163, 162, 162, 161, 161, 160, 160, 159, 159, 158, 158, 157, 157, 156, 155, 155, 154, 154, 153, 153, 152, 152, 151, 151, 151, 150, 150, 149, 149, 148, 148, 147, 147, 146, 146, 145, 145, 144, 144, 143, 143, 142, 142, 142, 141, 141, 140, 140, 139, 139, 138, 138, 137, 137, 137, 136, 136, 135, 135, 134, 134, 134, 133, 133, 132, 132, 131, 131, 131, 130, 130, 129, 129, 129, 128, 128, 127, 127, 127, 126, 126, 125, 125, 125, 124, 124, 123, 123, 123, 122, 122, 121, 121, 121, 120, 120, 120, 119, 119, 118, 118, 118, 117, 117, 117, 116, 116, 115, 115, 115, 114, 114, 114, 113, 113, 113, 112, 112, 112, 111, 111, 111, 110, 110, 109, 109, 109, 108, 108, 108, 107, 107, 107, 106, 106, 106, 105, 105, 105, 105, 104, 104, 104, 103, 103, 103, 102, 102, 102, 101, 101, 101, 100, 100, 100, 99, 99, 99, 99, 98, 98, 98, 97, 97, 97, 96, 96, 96, 96, 95, 95, 95, 94, 94, 94, 94, 93, 93, 93, 92, 92, 92, 92, 91, 91, 91, 91, 90, 90, 90, 89, 89, 89, 89, 88, 88, 88, 88, 87, 87, 87, 87, 86, 86, 86, 85, 85, 85, 85, 84, 84, 84, 84, 83, 83, 83, 83, 82, 82, 82, 82, 81, 81, 81, 81, 81, 80, 80, 80, 80, 79, 79, 79, 79, 78, 78, 78, 78, 77, 77, 77, 77, 77, 76, 76, 76, 76, 75, 75, 75, 75, 75, 74, 74, 74, 74, 73, 73, 73, 73, 73, 72, 72, 72, 72, 72, 71, 71, 71, 71, 71, 70, 70, 70, 70, 70, 69, 69, 69, 69, 69, 68, 68, 68, 68, 68, 67, 67, 67, 67, 67, 66, 66, 66, 66, 66, 65, 65, 65, 65, 65, 64, 64, 64, 64, 64, 64, 63, 63, 63, 63, 63, 62, 62, 62, 62, 62, 62, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 59, 59, 59, 59, 59, 59, 58, 58, 58, 58, 58, 58, 57, 57, 57, 57, 57, 57, 56, 56, 56, 56, 56, 56, 55, 55, 55, 55, 55, 55, 55, 54, 54, 54, 54, 54, 54, 53, 53, 53, 53, 53, 53, 53, 52, 52, 52, 52, 52, 52, 52, 51, 51, 51, 51, 51, 51, 51, 50, 50, 50, 50, 50, 50, 50, 49, 49, 49, 49, 49, 49, 49, 49, 48, 48, 48, 48, 48, 48, 48, 47, 47, 47, 47, 47, 47, 47, 47, 46, 46, 46, 46, 46, 46, 46, 46, 45, 45, 45, 45, 45, 45, 45, 45, 44, 44, 44, 44, 44, 44, 44, 44, 44, 43, 43, 43, 43, 43, 43, 43, 43, 42, 42, 42, 42, 42, 42, 42, 42, 42, 41, 41, 41, 41, 41, 41, 41, 41, 41, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 39, 39, 39, 39, 39, 39, 39, 39, 39, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 30};
float arraytemps[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6, 6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9, 7, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9, 8, 8.1, 8.2, 8.3, 8.4, 8.5, 8.6, 8.7, 8.8, 8.9, 9, 9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9, 10, 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8, 10.9, 11, 11.1, 11.2, 11.3, 11.4, 11.5, 11.6, 11.7, 11.8, 11.9, 12, 12.1, 12.2, 12.3, 12.4, 12.5, 12.6, 12.7, 12.8, 12.9, 13, 13.1, 13.2, 13.3, 13.4, 13.5, 13.6, 13.7, 13.8, 13.9, 14, 14.1, 14.2, 14.3, 14.4, 14.5, 14.6, 14.7, 14.8, 14.9, 15, 15.1, 15.2, 15.3, 15.4, 15.5, 15.6, 15.7, 15.8, 15.9, 16, 16.1, 16.2, 16.3, 16.4, 16.5, 16.6, 16.7, 16.8, 16.9, 17, 17.1, 17.2, 17.3, 17.4, 17.5, 17.6, 17.7, 17.8, 17.9, 18, 18.1, 18.2, 18.3, 18.4, 18.5, 18.6, 18.7, 18.8, 18.9, 19, 19.1, 19.2, 19.3, 19.4, 19.5, 19.6, 19.7, 19.8, 19.9, 20, 20.1, 20.2, 20.3, 20.4, 20.5, 20.6, 20.7, 20.8, 20.9, 21, 21.1, 21.2, 21.3, 21.4, 21.5, 21.6, 21.7, 21.8, 21.9, 22, 22.1, 22.2, 22.3, 22.4, 22.5, 22.6, 22.7, 22.8, 22.9, 23, 23.1, 23.2, 23.3, 23.4, 23.5, 23.6, 23.7, 23.8, 23.9, 24, 24.1, 24.2, 24.3, 24.4, 24.5, 24.6, 24.7, 24.8, 24.9, 25, 25.1, 25.2, 25.3, 25.4, 25.5, 25.6, 25.7, 25.8, 25.9, 26, 26.1, 26.2, 26.3, 26.4, 26.5, 26.6, 26.7, 26.8, 26.9, 27, 27.1, 27.2, 27.3, 27.4, 27.5, 27.6, 27.7, 27.8, 27.9, 28, 28.1, 28.2, 28.3, 28.4, 28.5, 28.6, 28.7, 28.8, 28.9, 29, 29.1, 29.2, 29.3, 29.4, 29.5, 29.6, 29.7, 29.8, 29.9, 30, 30.1, 30.2, 30.3, 30.4, 30.5, 30.6, 30.7, 30.8, 30.9, 31, 31.1, 31.2, 31.3, 31.4, 31.5, 31.6, 31.7, 31.8, 31.9, 32, 32.1, 32.2, 32.3, 32.4, 32.5, 32.6, 32.7, 32.8, 32.9, 33, 33.1, 33.2, 33.3, 33.4, 33.5, 33.6, 33.7, 33.8, 33.9, 34, 34.1, 34.2, 34.3, 34.4, 34.5, 34.6, 34.7, 34.8, 34.9, 35, 35.1, 35.2, 35.3, 35.4, 35.5, 35.6, 35.7, 35.8, 35.9, 36, 36.1, 36.2, 36.3, 36.4, 36.5, 36.6, 36.7, 36.8, 36.9, 37, 37.1, 37.2, 37.3, 37.4, 37.5, 37.6, 37.7, 37.8, 37.9, 38, 38.1, 38.2, 38.3, 38.4, 38.5, 38.6, 38.7, 38.8, 38.9, 39, 39.1, 39.2, 39.3, 39.4, 39.5, 39.6, 39.7, 39.8, 39.9, 40, 40.1, 40.2, 40.3, 40.4, 40.5, 40.6, 40.7, 40.8, 40.9, 41, 41.1, 41.2, 41.3, 41.4, 41.5, 41.6, 41.7, 41.8, 41.9, 42, 42.1, 42.2, 42.3, 42.4, 42.5, 42.6, 42.7, 42.8, 42.9, 43, 43.1, 43.2, 43.3, 43.4, 43.5, 43.6, 43.7, 43.8, 43.9, 44, 44.1, 44.2, 44.3, 44.4, 44.5, 44.6, 44.7, 44.8, 44.9, 45, 45.1, 45.2, 45.3, 45.4, 45.5, 45.6, 45.7, 45.8, 45.9, 46, 46.1, 46.2, 46.3, 46.4, 46.5, 46.6, 46.7, 46.8, 46.9, 47, 47.1, 47.2, 47.3, 47.4, 47.5, 47.6, 47.7, 47.8, 47.9, 48, 48.1, 48.2, 48.3, 48.4, 48.5, 48.6, 48.7, 48.8, 48.9, 49, 49.1, 49.2, 49.3, 49.4, 49.5, 49.6, 49.7, 49.8, 49.9, 50, 50.1, 50.2, 50.3, 50.4, 50.5, 50.6, 50.7, 50.8, 50.9, 51, 51.1, 51.2, 51.3, 51.4, 51.5, 51.6, 51.7, 51.8, 51.9, 52, 52.1, 52.2, 52.3, 52.4, 52.5, 52.6, 52.7, 52.8, 52.9, 53, 53.1, 53.2, 53.3, 53.4, 53.5, 53.6, 53.7, 53.8, 53.9, 54, 54.1, 54.2, 54.3, 54.4, 54.5, 54.6, 54.7, 54.8, 54.9, 55, 55.1, 55.2, 55.3, 55.4, 55.5, 55.6, 55.7, 55.8, 55.9, 56, 56.1, 56.2, 56.3, 56.4, 56.5, 56.6, 56.7, 56.8, 56.9, 57, 57.1, 57.2, 57.3, 57.4, 57.5, 57.6, 57.7, 57.8, 57.9, 58, 58.1, 58.2, 58.3, 58.4, 58.5, 58.6, 58.7, 58.8, 58.9, 59, 59.1, 59.2, 59.3, 59.4, 59.5, 59.6, 59.7, 59.8, 59.9, 60, 60.1, 60.2, 60.3, 60.4, 60.5, 60.6, 60.7, 60.8, 60.9, 61, 61.1, 61.2, 61.3, 61.4, 61.5, 61.6, 61.7, 61.8, 61.9, 62, 62.1, 62.2, 62.3, 62.4, 62.5, 62.6, 62.7, 62.8, 62.9, 63, 63.1, 63.2, 63.3, 63.4, 63.5, 63.6, 63.7, 63.8, 63.9, 64, 64.1, 64.2, 64.3, 64.4, 64.5, 64.6, 64.7, 64.8, 64.9, 65, 65.1, 65.2, 65.3, 65.4, 65.5, 65.6, 65.7, 65.8, 65.9, 66, 66.1, 66.2, 66.3, 66.4, 66.5, 66.6, 66.7, 66.8, 66.9, 67, 67.1, 67.2, 67.3, 67.4, 67.5, 67.6, 67.7, 67.8, 67.9, 68, 68.1, 68.2, 68.3, 68.4, 68.5, 68.6, 68.7, 68.8, 68.9, 69, 69.1, 69.2, 69.3, 69.4, 69.5, 69.6, 69.7, 69.8, 69.9, 70, 70.1, 70.2, 70.3, 70.4, 70.5, 70.6, 70.7, 70.8, 70.9, 71, 71.1, 71.2, 71.3, 71.4, 71.5, 71.6, 71.7, 71.8, 71.9, 72, 72.1, 72.2, 72.3, 72.4, 72.5, 72.6, 72.7, 72.8, 72.9, 73, 73.1, 73.2, 73.3, 73.4, 73.5, 73.6, 73.7, 73.8, 73.9, 74, 74.1, 74.2, 74.3, 74.4, 74.5, 74.6, 74.7, 74.8, 74.9, 75, 75.1, 75.2, 75.3, 75.4, 75.5, 75.6, 75.7, 75.8, 75.9, 76, 76.1, 76.2, 76.3, 76.4, 76.5, 76.6, 76.7, 76.8, 76.9, 77, 77.1, 77.2, 77.3, 77.4, 77.5, 77.6, 77.7, 77.8, 77.9, 78, 78.1, 78.2, 78.3, 78.4, 78.5, 78.6, 78.7, 78.8, 78.9, 79, 79.1, 79.2, 79.3, 79.4, 79.5, 79.6, 79.7, 79.8, 79.9, 80, 80.1, 80.2, 80.3, 80.4, 80.5, 80.6, 80.7, 80.8, 80.9, 81, 81.1, 81.2, 81.3, 81.4, 81.5, 81.6, 81.7, 81.8, 81.9, 82, 82.1, 82.2, 82.3, 82.4, 82.5, 82.6, 82.7, 82.8, 82.9, 83, 83.1, 83.2, 83.3, 83.4, 83.5, 83.6, 83.7, 83.8, 83.9, 84, 84.1, 84.2, 84.3, 84.4, 84.5, 84.6, 84.7, 84.8, 84.9, 85, 85.1, 85.2, 85.3, 85.4, 85.5, 85.6, 85.7, 85.8, 85.9, 86, 86.1, 86.2, 86.3, 86.4, 86.5, 86.6, 86.7, 86.8, 86.9, 87, 87.1, 87.2, 87.3, 87.4, 87.5, 87.6, 87.7, 87.8, 87.9, 88, 88.1, 88.2, 88.3, 88.4, 88.5, 88.6, 88.7, 88.8, 88.9, 89, 89.1, 89.2, 89.3, 89.4, 89.5, 89.6, 89.7, 89.8, 89.9, 90, 90.1, 90.2, 90.3, 90.4, 90.5, 90.6, 90.7, 90.8, 90.9, 91, 91.1, 91.2, 91.3, 91.4, 91.5, 91.6, 91.7, 91.8, 91.9, 92, 92.1, 92.2, 92.3, 92.4, 92.5, 92.6, 92.7, 92.8, 92.9, 93, 93.1, 93.2, 93.3, 93.4, 93.5, 93.6, 93.7, 93.8, 93.9, 94, 94.1, 94.2, 94.3, 94.4, 94.5, 94.6, 94.7, 94.8, 94.9, 95, 95.1, 95.2, 95.3, 95.4, 95.5, 95.6, 95.7, 95.8, 95.9, 96, 96.1, 96.2, 96.3, 96.4, 96.5, 96.6, 96.7, 96.8, 96.9, 97, 97.1, 97.2, 97.3, 97.4, 97.5, 97.6, 97.7, 97.8, 97.9, 98, 98.1, 98.2, 98.3, 98.4, 98.5, 98.6, 98.7, 98.8, 98.9, 99, 99.1, 99.2, 99.3, 99.4, 99.5, 99.6, 99.7, 99.8, 99.9, 100, 100.1, 100.2, 100.3, 100.4, 100.5, 100.6, 100.7, 100.8, 100.9, 101, 101.1, 101.2, 101.3, 101.4, 101.5, 101.6, 101.7, 101.8, 101.9, 102, 102.1, 102.2, 102.3, 102.4, 102.5, 102.6, 102.7, 102.8, 102.9, 103, 103.1, 103.2, 103.3, 103.4, 103.5, 103.6, 103.7, 103.8, 103.9, 104, 104.1, 104.2, 104.3, 104.4, 104.5, 104.6, 104.7, 104.8, 104.9, 105, 105.1, 105.2, 105.3, 105.4, 105.5, 105.6, 105.7, 105.8, 105.9, 106, 106.1, 106.2, 106.3, 106.4, 106.5, 106.6, 106.7, 106.8, 106.9, 107, 107.1, 107.2, 107.3, 107.4, 107.5, 107.6, 107.7, 107.8, 107.9, 108, 108.1, 108.2, 108.3, 108.4, 108.5, 108.6, 108.7, 108.8, 108.9, 109, 109.1, 109.2, 109.3, 109.4, 109.5, 109.6, 109.7, 109.8, 109.9, 110, 110.1, 110.2, 110.3, 110.4, 110.5, 110.6, 110.7, 110.8, 110.9, 111, 111.1, 111.2, 111.3, 111.4, 111.5, 111.6, 111.7, 111.8, 111.9, 112, 112.1, 112.2, 112.3, 112.4, 112.5, 112.6, 112.7, 112.8, 112.9, 113, 113.1, 113.2, 113.3, 113.4, 113.5, 113.6, 113.7, 113.8, 113.9, 114, 114.1, 114.2, 114.3, 114.4, 114.5, 114.6, 114.7, 114.8, 114.9, 115, 115.1, 115.2, 115.3, 115.4, 115.5, 115.6, 115.7, 115.8, 115.9, 116, 116.1, 116.2, 116.3, 116.4, 116.5, 116.6, 116.7, 116.8, 116.9, 117, 117.1, 117.2, 117.3, 117.4, 117.5, 117.6, 117.7, 117.8, 117.9, 118, 118.1, 118.2, 118.3, 118.4, 118.5, 118.6, 118.7, 118.8, 118.9, 119, 119.1, 119.2, 119.3, 119.4, 119.5, 119.6, 119.7, 119.8, 119.9, 120, 120.1, 120.2, 120.3, 120.4, 120.5, 120.6, 120.7, 120.8, 120.9, 121, 121.1, 121.2, 121.3, 121.4, 121.5, 121.6, 121.7, 121.8, 121.9, 122, 122.1, 122.2, 122.3, 122.4, 122.5, 122.6, 122.7, 122.8, 122.9, 123, 123.1, 123.2, 123.3, 123.4, 123.5, 123.6, 123.7, 123.8, 123.9, 124, 124.1, 124.2, 124.3, 124.4, 124.5, 124.6, 124.7, 124.8, 124.9, 125, 125.1, 125.2, 125.3, 125.4, 125.5, 125.6, 125.7, 125.8, 125.9, 126, 126.1, 126.2, 126.3, 126.4, 126.5, 126.6, 126.7, 126.8, 126.9, 127, 127.1, 127.2, 127.3, 127.4, 127.5, 127.6, 127.7, 127.8, 127.9, 128, 128.1, 128.2, 128.3, 128.4, 128.5, 128.6, 128.7, 128.8, 128.9, 129, 129.1, 129.2, 129.3, 129.4, 129.5, 129.6, 129.7, 129.8, 129.9, 130, 130.1, 130.2, 130.3, 130.4, 130.5, 130.6, 130.7, 130.8, 130.9, 131, 131.1, 131.2, 131.3, 131.4, 131.5, 131.6, 131.7, 131.8, 131.9, 132, 132.1, 132.2, 132.3, 132.4, 132.5, 132.6, 132.7, 132.8, 132.9, 133, 133.1, 133.2, 133.3, 133.4, 133.5, 133.6, 133.7, 133.8, 133.9, 134, 134.1, 134.2, 134.3, 134.4, 134.5, 134.6, 134.7, 134.8, 134.9, 135, 135.1, 135.2, 135.3, 135.4, 135.5, 135.6, 135.7, 135.8, 135.9, 136, 136.1, 136.2, 136.3, 136.4, 136.5, 136.6, 136.7, 136.8, 136.9, 137, 137.1, 137.2, 137.3, 137.4, 137.5, 137.6, 137.7, 137.8, 137.9, 138, 138.1, 138.2, 138.3, 138.4, 138.5, 138.6, 138.7, 138.8, 138.9, 139, 139.1, 139.2, 139.3, 139.4, 139.5, 139.6, 139.7, 139.8, 139.9, 140, 140.1, 140.2, 140.3, 140.4, 140.5, 140.6, 140.7, 140.8, 140.9, 141, 141.1, 141.2, 141.3, 141.4, 141.5, 141.6, 141.7, 141.8, 141.9, 142, 142.1, 142.2, 142.3, 142.4, 142.5, 142.6, 142.7, 142.8, 142.9, 143, 143.1, 143.2, 143.3, 143.4, 143.5, 143.6, 143.7, 143.8, 143.9, 144, 144.1, 144.2, 144.3, 144.4, 144.5, 144.6, 144.7, 144.8, 144.9, 145, 145.1, 145.2, 145.3, 145.4, 145.5, 145.6, 145.7, 145.8, 145.9, 146, 146.1, 146.2, 146.3, 146.4, 146.5, 146.6, 146.7, 146.8, 146.9, 147, 147.1, 147.2, 147.3, 147.4, 147.5, 147.6, 147.7, 147.8, 147.9, 148, 148.1, 148.2, 148.3, 148.4, 148.5, 156.6};
size_t ArraytempAddressSize = sizeof(ArraytempAddress) / sizeof(int);
float Arraytemplookup[4095] = {0};


//*****************************functions declaration

int encoder_position_limit (int encoderMin, int encoderMax, int encoderPosition); //function to limit the max values of the encoder while setting the range
int encoder_position_move(int newPosition, int oldPosition, int encoder_position); // function to move the encoder position


void LDA_Disable(void); // function turns off load A
void LDA_Enable(void); // function turns on load A
void LDB_Disable(void); // function turns off load B
void LDB_Enable(void); // function turns on load B

struct VARS AVG_Filter(struct VARS avg, float filter); // function runs a moving avg filter
struct VARS ValChangeDetected(struct VARS values , float value, float LESS_VAL, float GREATER_VAL); // function checks to see if a value has changed more than a specified lower\higher value

float calibration(float val, float gain, float offset); // used to calc slope and offset

void load_range_selection(void); // used to select the load range ***needs to change

void LDA_range_select(void); // load a range selection ****
void LDB_range_select(void); // load b range selection*****

void RelaySetup(void); // needs changes****

void LDA_Range_Cal_Coeff(void); // used to store and upload the calibration coeff for the different load ranges
void LDB_Range_Cal_Coeff(void);// used to store and upload the calibration coeff for the different load ranges

void SSDATA_CAP(void); // function that saves ADC measurements to single shot file SD card
void LOGGERDATA_CAP(void); // funtion that saves ADC measurements to logger file on SD card

void bIrangeCalFunc(void);// used to set nex button state flag
void bVrangeCalFunc(void);//  used to set nex button state flag

void bcaliVoltSlopeFunc(void);// Execute Voltage Calibration function
void bcaliCurrSlopeFunc(void);// Execute Current Calibration function
void bcaliVoltOffSetFunc(void);// Execute Voltage Calibration function
void bcaliCurrentOffSetFunc(void);// Execute Current Calibration function
float CalibrationCalc(float HighRead, float HighMeas, float LowRead, float Lowmeas);

void WriteLoadDataToSD(int scanCount);

void loadOnOffUpdateFunc(int address, int OnOffState);// used to turn the load on or off



//main page loops

void DualLoadSetupLoop(void);
void LoadCalibrationLoop(void);
void Load_Monitor_Loop(void); // monitor the load condition and updates the display, checks for faults as well *** Needs changes
//*************nextion function calls


//Buttons function calls

void TakeSnapShotPopCallback(void *ptr);
void LDA_BmodePopCallback(void *ptr);
void LDB_BmodePopCallback(void *ptr);
void LDA_B_VRPopCallback(void *ptr);
void LDB_B_VRPopCallback(void *ptr);
void LDA_B_IRPopCallback(void *ptr);
void LDB_B_IRPopCallback(void *ptr);
void KP_EnterPopCallback(void *ptr);
void KP_ExitPopCallback(void *ptr);

//Text Box function calls


void tVcalSetHPopCallback(void *ptr);
void tVcalSetLPopCallback(void *ptr);


//nex comm functions

int currentNexPage(void);

void setup() {

  LDA.SetPoint.ChangeDetectFlag = 0;
  LDB.SetPoint.ChangeDetectFlag = 0;
  LDA.CurrentMax = 0.35;
  LDB.CurrentMax = 0.35;
  LDA.Units = " A";
  LDB.Units = " A";



  // **********************************Nextion display setup

  nexInit(); // *****initalize nextion display
  delay(25);

  HWserial.begin(115200); // must set the the default baud rate in the nex display using the "baudz" command also edit the "nextion header" to set the

  while (!HWserial)
  {
    ;
  }

  HWserial.print("rest");  //Reset Nex Display
  HWserial.write(0xff);
  HWserial.write(0xff);
  HWserial.write(0xff);

  //*********************SD card Setup

  // Open serial communications and wait for port to open:
  DBserial.begin(9600);
  //  while (!DBserial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  // Start IIC Serial COMM

  Wire.begin(100000);

  // ************Setup SD Card

  //  SPI.setMISO(8);  // config miso pin
  //  SPI.setMOSI(7);  // config mosi pin
  //  SPI.setSCK(14);  // config serial clock pin

  DBserial.print("Initializing SD card...");
  //see if the card is present and can be initialized:
  delay(100);
  if (!SD.begin(SDcard_CS)) {
    DBserial.println("Card failed, or not present");
    // don't do anything more:
  }
  if (SD.begin(SDcard_CS)) {
    DBserial.println("card initialized.");
    // don't do anything more:
  }

  // write headers to datalog file
  String CSVheader = "Scan #,LOAD A Volt,LOAD A Current,LOAD A Power,LOAD A Temp,LOAD B Volt,LOAD B Current,LOAD B POWER,LOAD B Temp"; // enter the CSV headings into the variable

  File SSData = SD.open("SSData.txt", FILE_WRITE);//create SSData.txt
  delay(100);
  // if the files are available, write the CSV headings to them:
  if (SSData) {
    SSData.println(CSVheader);
    SSData.close();
    // print to the serial port too:
    DBserial.println(CSVheader);
  }
  // if the file isn't open, pop up an error:
  else {
    DBserial.println("error opening DATA.txt");
  }

  File LoggerData = SD.open("DATALOG.txt", FILE_WRITE);//create DataLog.txt
  delay(100);
  if (LoggerData) {
    LoggerData.println(CSVheader);
    LoggerData.close();
    // print to the serial port too:
    DBserial.println(CSVheader);
  }
  // if the file isn't open, pop up an error:
  else {
    DBserial.println("error opening DATALOG.txt");
  }

  //**********************SD Card Setup end



  // Set default range

  LDA.volt.range = 0;
  LDB.volt.range = 0;

  LDA.current.range = 0;
  LDB.current.range = 0;

  // load default calibration values

  LDA_Range_Cal_Coeff();
  LDB_Range_Cal_Coeff();

  DBserial.println("call back functions registered");


  //*********************Nextion Setup end

  //**********************initalize MAF arrays

  //for (int k = 0; k < MAF_sizeFast; ++k)
  //
  //{
  ////LDA.temp.ARRFast[k] = 0;
  ////LDA.volt.ARRFast[k] = 0;
  ////LDA.current.ARRFast[k] = 0;
  ////LDA.Power.ARRFast[k] = 0;
  //////LDA.Iadj.ARRFast[k] = 0;
  //
  //LDB.temp.ARRFast[k] = 0;
  //LDB.volt.ARRFast[k] = 0;
  //LDB.current.ARRFast[k] = 0;
  //LDB.Power.ARRFast[k] = 0;
  ////LDB.Iadj.ARRFast[k] = 0;
  //
  //}



  for (int k = 0; k < MAF_sizeSlow; ++k)

  {
    LDA.temp.ARRSlow[k] = 0;
    LDA.volt.ARRSlow[k] = 0;
    LDA.current.ARRSlow[k] = 0;
    LDA.Power.ARRSlow[k] = 0;
    //LDA.Iadj.ARRSlow[k] = 0;

    LDB.temp.ARRSlow[k] = 0;
    LDB.volt.ARRSlow[k] = 0;
    LDB.current.ARRSlow[k] = 0;
    LDB.Power.ARRSlow[k] = 0;
    //LDB.Iadj.ARRSlow[k] = 0;

  }

  //****************Config O/P GPIOs


  pinMode(SDcard_CS, OUTPUT);
  digitalWrite(SDcard_CS, HIGH);

  // Config I/P GPIOs

  //pinMode(encoder_PB,INPUT);

  pinMode(LDB_PB, INPUT_PULLUP);
  pinMode(LDA_PB, INPUT_PULLUP);

  // set analog read and write res to 12 bit
  analogReadResolution(12); // set analog resolution to 12 bits
  analogWriteResolution(12); // set analog resolution to 12 bits


  //*******************************************Temp Sense Array initalization*************************************


  for (int index = 0; index <= ArraytempAddressSize; index++) {

    Arraytemplookup[ArraytempAddress[index]] = arraytemps[index];

  }

  LDA.volt.range = 0;
  LDB.current.range = 0;
  LDA.volt.range = 0;
  LDB.current.range = 0;

  delay(2000);

  // set default config of the load A to high voltage range

  Wire.beginTransmission(LDA_ADD); //U1B
  Wire.write(voltRangeChange);
  Wire.write(1);   // sends instruction byte  - Set digital pot reference to ground
  Wire.write(LDA.volt.range);
  Wire.endTransmission();     // stop transmitting

  delay(500);

  Wire.beginTransmission(potADD_1); //U1B
  Wire.write(potInstrucSelA);   // sends instruction byte
  Wire.write(Vamp_Range_High);  // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(potADD_1); //U1B
  Wire.write(potInstrucSelB);   // sends instruction byte
  Wire.write(Vamp_Range_High);  // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(LDA_ADD); //U1B
  Wire.write(voltRangeChange);
  Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
  Wire.write(LDA.volt.range);
  Wire.endTransmission();     // stop transmitting

  // set default config of the load B to high voltage range

  Wire.beginTransmission(LDB_ADD); //U1B
  Wire.write(voltRangeChange);
  Wire.write(1);   // sends instruction byte  - Set digital pot reference to ground
  Wire.write(LDB.volt.range);
  Wire.endTransmission();     // stop transmitting

  delay(500);

  Wire.beginTransmission(potADD_2); //U1B
  Wire.write(potInstrucSelA);   // sends instruction byte
  Wire.write(Vamp_Range_High);  // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(potADD_2); //U1B
  Wire.write(potInstrucSelB);   // sends instruction byte
  Wire.write(Vamp_Range_High);  // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(LDB_ADD); //U1B
  Wire.write(voltRangeChange);
  Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
  Wire.write(LDB.volt.range);
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(LDA_ADD); //U1B
  Wire.write(currentRangeChange);
  Wire.write(0);   // sends instruction byte  - High range set
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(LDB_ADD); //U1B
  Wire.write(currentRangeChange);
  Wire.write(0);   // sends instruction byte  - High range set
  Wire.endTransmission();     // stop transmitting

  LDA_Range_Cal_Coeff(); // update current and voltage cal coeff
  LDB_Range_Cal_Coeff(); // update current and voltage cal coeff

  HWserial.print("page 1");  //Goto Page 1
  HWserial.write(0xff);
  HWserial.write(0xff);
  HWserial.write(0xff);

  DBserial.println("Setup Complete");


}// end of Arduino Setup

long oldPositionA  = -999; //stores the last know encoder position
long oldPositionB  = -999; //stores the last know encoder position


void loop() {

  DBserial.println("Main Loop");

  CurrentPage = currentNexPage();


  // Set Defaults


  switch (CurrentPage) {

    case 0:

      break;

    case 1:

      break;

    case 2:

      Load_Monitor_Loop(); // go to the load monitoring loop

      break;

    case 3:

      DualLoadSetupLoop(); // go to the load setup loop

      break;

    case 4:

      LoadCalibrationLoop();

      break;
  } //end of current page if statement

  delay(25);
}//end of main arduino loop
