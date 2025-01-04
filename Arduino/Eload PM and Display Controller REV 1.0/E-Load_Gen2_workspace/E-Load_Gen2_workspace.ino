
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

int LDA_ADD = 0x54; //LDA IIC address
int LDB_ADD = 0x44; //LDA IIC address

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
#define CRVGainChange             0xC0
#define CRIGainChange             0xD0


//protection bit definitions

#define OverVoltageBit  0x01
#define OverCurrentBit  0x02
#define OverTempBit     0x04


// digi-POT Load A Constants
const int potADD_1 = B0101111; //I2C address of digital pot 2 (U2)(Write)Load A
const int potADD_2 = B0101100; //I2C address of digital pot 2 (U2)(Write)Load B
const int potInstrucSelB =  0x80; //Instuction POT B Select
const int potInstrucSelA =  0x00; //Instuction POT A Select
const int potInstrucReset = B01000000; //Instuction Reset
const int potInstrucSD =    B00100000; //Instuction ShutDownSelect
const int potInstrucO1 =    B00010000; //Instuction O1 State Change
const int potInstrucO2 =    B00001000; //Instuction O2 State Change

const int Vamp_Range_Low = 0xAF;//175
const int Vamp_Range_Med = 0x43;//67
const int Vamp_Range_High = 0x0A;//10

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
int MAF_sizeSlow = 3; // max value is 500 (array is set to 500)

// SD Card Variables

unsigned int SD_log_count = 0;
unsigned int SD_ss_count = 0;
unsigned int long SD_log_active = 0;

// structs

struct VARS

{

  int capVal;
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
  float CurrentMin;
  int voltageLimit;
  int CurrentLimit;
  int SetPointLow;
  int SetPointHigh;
  int SetPointOffSet;
  String Units;
  int activeProtections;
  int OverVolt;
  int OverCurrent;
  int OverTemp;
  int MinLoad;

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
uint32_t TakeSnapShot_BstateCap = 0;



//**************************button pressed flags End

bool Relay_enable = 0;
bool RelayTimerStart = 0;

int RelayTimerRef = 0;
float Relay_onTime = 0;
float Relay_period = 0;

float overTemp = 60; // calibrated over temp fault threshold value
const float PowerLimit = -200; // calibrated over power fault threshold value

String LDA_SP;
String LDB_SP;

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

NexVariable KPX =  NexVariable(4, 34, "KPX");
NexVariable KPE =  NexVariable(4, 33, "KPE");
NexVariable KPA =  NexVariable(2, 20, "KPA");
NexVariable KPB =  NexVariable(2, 21, "KPB");

char buffer[100] = {0};  // This is needed only if you are going to receive a text from the display. You can remove it otherwise.
// Further on this sketch I do receive text so that's why I created this buffer.

// Declare temp sense lookup table Arrays

const unsigned short int ArraytempAddress[] = {4094,4092,4090,4088,4087,4085,4083,4081,4079,4077,4075,4073,4071,4069,4067,4065,4063,4061,4059,4057,4055,4053,4051,4049,4047,4045,4042,4040,4038,4036,4034,4032,4030,4028,4026,4023,4021,4019,4017,4015,4013,4010,4008,4006,4004,4002,3999,3997,3995,3993,3991,3988,3986,3984,3981,3979,3977,3975,3972,3970,3968,3965,3963,3961,3958,3956,3954,3951,3949,3946,3944,3942,3939,3937,3934,3932,3929,3927,3925,3922,3920,3917,3915,3912,3910,3907,3905,3902,3900,3897,3894,3892,3889,3887,3884,3882,3879,3876,3874,3871,3869,3866,3863,3861,3858,3855,3853,3850,3847,3845,3842,3839,3837,3834,3831,3828,3826,3823,3820,3817,3815,3812,3809,3806,3803,3801,3798,3795,3792,3789,3786,3784,3781,3778,3775,3772,3769,3766,3763,3760,3758,3755,3752,3749,3746,3743,3740,3737,3734,3731,3728,3725,3722,3719,3716,3713,3710,3707,3704,3701,3697,3694,3691,3688,3685,3682,3679,3676,3673,3669,3666,3663,3660,3657,3654,3650,3647,3644,3641,3638,3634,3631,3628,3625,3621,3618,3615,3612,3608,3605,3602,3598,3595,3592,3588,3585,3582,3578,3575,3572,3568,3565,3562,3558,3555,3551,3548,3545,3541,3538,3534,3531,3527,3524,3520,3517,3514,3510,3507,3503,3500,3496,3492,3489,3485,3482,3478,3475,3471,3468,3464,3460,3457,3453,3450,3446,3442,3439,3435,3432,3428,3424,3421,3417,3413,3410,3406,3402,3399,3395,3391,3387,3384,3380,3376,3373,3369,3365,3361,3358,3354,3350,3346,3342,3339,3335,3331,3327,3323,3320,3316,3312,3308,3304,3300,3297,3293,3289,3285,3281,3277,3273,3269,3266,3262,3258,3254,3250,3246,3242,3238,3234,3230,3226,3222,3218,3214,3210,3206,3202,3198,3194,3190,3186,3182,3178,3174,3170,3166,3162,3158,3154,3150,3146,3142,3138,3134,3130,3126,3122,3118,3114,3109,3105,3101,3097,3093,3089,3085,3081,3077,3072,3068,3064,3060,3056,3052,3048,3043,3039,3035,3031,3027,3023,3018,3014,3010,3006,3002,2997,2993,2989,2985,2981,2976,2972,2968,2964,2959,2955,2951,2947,2942,2938,2934,2930,2925,2921,2917,2913,2908,2904,2900,2896,2891,2887,2883,2878,2874,2870,2865,2861,2857,2853,2848,2844,2840,2835,2831,2827,2822,2818,2814,2809,2805,2801,2796,2792,2788,2783,2779,2775,2770,2766,2762,2757,2753,2749,2744,2740,2735,2731,2727,2722,2718,2714,2709,2705,2701,2696,2692,2687,2683,2679,2674,2670,2666,2661,2657,2652,2648,2644,2639,2635,2631,2626,2622,2617,2613,2609,2604,2600,2595,2591,2587,2582,2578,2573,2569,2565,2560,2556,2551,2547,2543,2538,2534,2530,2525,2521,2516,2512,2508,2503,2499,2494,2490,2486,2481,2477,2472,2468,2464,2459,2455,2451,2446,2442,2437,2433,2429,2424,2420,2415,2411,2407,2402,2398,2394,2389,2385,2381,2376,2372,2367,2363,2359,2354,2350,2346,2341,2337,2333,2328,2324,2320,2315,2311,2307,2302,2298,2293,2289,2285,2281,2276,2272,2268,2263,2259,2255,2250,2246,2242,2237,2233,2229,2224,2220,2216,2212,2207,2203,2199,2194,2190,2186,2182,2177,2173,2169,2164,2160,2156,2152,2147,2143,2139,2135,2130,2126,2122,2118,2114,2109,2105,2101,2097,2092,2088,2084,2080,2076,2071,2067,2063,2059,2055,2051,2046,2042,2038,2034,2030,2026,2021,2017,2013,2009,2005,2001,1997,1992,1988,1984,1980,1976,1972,1968,1964,1960,1955,1951,1947,1943,1939,1935,1931,1927,1923,1919,1915,1911,1907,1903,1899,1895,1891,1887,1882,1878,1874,1870,1866,1862,1858,1855,1851,1847,1843,1839,1835,1831,1827,1823,1819,1815,1811,1807,1803,1799,1795,1791,1788,1784,1780,1776,1772,1768,1764,1760,1756,1753,1749,1745,1741,1737,1733,1730,1726,1722,1718,1714,1710,1707,1703,1699,1695,1692,1688,1684,1680,1677,1673,1669,1665,1662,1658,1654,1650,1647,1643,1639,1636,1632,1628,1624,1621,1617,1613,1610,1606,1603,1599,1595,1592,1588,1584,1581,1577,1574,1570,1566,1563,1559,1556,1552,1548,1545,1541,1538,1534,1531,1527,1524,1520,1517,1513,1510,1506,1503,1499,1496,1492,1489,1485,1482,1478,1475,1472,1468,1465,1461,1458,1454,1451,1448,1444,1441,1437,1434,1431,1427,1424,1421,1417,1414,1411,1407,1404,1401,1397,1394,1391,1388,1384,1381,1378,1374,1371,1368,1365,1361,1358,1355,1352,1348,1345,1342,1339,1336,1332,1329,1326,1323,1320,1317,1313,1310,1307,1304,1301,1298,1295,1292,1288,1285,1282,1279,1276,1273,1270,1267,1264,1261,1258,1255,1252,1249,1246,1243,1240,1237,1234,1231,1228,1225,1222,1219,1216,1213,1210,1207,1204,1201,1198,1195,1192,1189,1186,1184,1181,1178,1175,1172,1169,1166,1163,1161,1158,1155,1152,1149,1146,1144,1141,1138,1135,1132,1130,1127,1124,1121,1119,1116,1113,1110,1108,1105,1102,1099,1097,1094,1091,1089,1086,1083,1081,1078,1075,1073,1070,1067,1065,1062,1059,1057,1054,1052,1049,1046,1044,1041,1039,1036,1033,1031,1028,1026,1023,1021,1018,1016,1013,1010,1008,1005,1003,1000,998,995,993,990,988,986,983,981,978,976,973,971,968,966,964,961,959,956,954,952,949,947};
const unsigned int short arraytemps[] = {18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,668,669,670,671,672,673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,732,733,734,735,736,737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,756,757,758,759,760,761,762,763,764,765,766,767,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,837,838,839,840,841,842,843,844,845,846,847,848,849,850,851,852,853};
size_t ArraytempAddressSize = sizeof(ArraytempAddress) / sizeof(int);
unsigned int Arraytemplookup[4095] = {0};


//*****************************functions declaration

int encoder_position_limit (int encoderMin, int encoderMax, int encoderPosition); //function to limit the max values of the encoder while setting the range
int encoder_position_move(int newPosition, int oldPosition, int encoder_position); // function to move the encoder position

void SetPointMinMaxUpdate(void);
//void LDA_Disable(void); // function turns off load A
//void LDA_Enable(void); // function turns on load A
//void LDB_Disable(void); // function turns off load B
//void LDB_Enable(void); // function turns on load B

struct VARS AVG_Filter(struct VARS avg, float filter); // function runs a moving avg filter
struct VARS ValChangeDetected(struct VARS values , float value, float LESS_VAL, float GREATER_VAL); // function checks to see if a value has changed more than a specified lower\higher value

float calibration(float val, float gain, float offset); // used to calc slope and offset

void load_range_selection(void); // used to select the load range ***needs to change

void LDA_range_select(void); // load a range selection ****
void LDB_range_select(void); // load b range selection*****

//void RelaySetup(void); // needs changes****

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


void SetVoltageRangeFunc(int Load);
void loadOnOffUpdateFunc(int address, int OnOffState);
void SetDigialPotResFunc(int PotAddress, int LoadAddress, int VoltageRange, int PotValue);
void nexTextboxWriteFunc(String TextBoxName, float TextboxValueAsFloat, String TextboxValueAsString);
void EncoderLoadSetFunc(void);
void SetCurrentRangeFunc(int Load);
void LoadButtonPressCheckFunc(void);
void GetActiveLoadProtections(void);
void TakeSnapShotFunc(void);

//main page loops

void DualLoadSetupLoop(void);
void LoadCalibrationLoop(void);
void Load_Monitor_Loop(void); // monitor the load condition and updates the display, checks for faults as well *** Needs changes
//*************nextion function calls


//Buttons function calls


//void LDA_BmodePopCallback(void *ptr);
//void LDB_BmodePopCallback(void *ptr);
//void LDA_B_VRPopCallback(void *ptr);
//void LDB_B_VRPopCallback(void *ptr);
//void LDA_B_IRPopCallback(void *ptr);
//void LDB_B_IRPopCallback(void *ptr);
//void KP_EnterPopCallback(void *ptr);
//void KP_ExitPopCallback(void *ptr);

//Text Box function calls


void tVcalSetHPopCallback(void *ptr);
void tVcalSetLPopCallback(void *ptr);


//nex comm functions

int currentNexPage(void);

void setup() {

  LDA.SetPoint.ChangeDetectFlag = 0;
  LDB.SetPoint.ChangeDetectFlag = 0;
  SetPointMinMaxUpdate();
  LDA.Units = " A";
  LDB.Units = " A";



  // **********************************Nextion display setup

  HWserial.begin(115200); // must set the the default baud rate in the nex display using the "baudz" command also edit the "nextion header" to set the

  while (!HWserial)
  {
    ;
  }
  nexInit(); // *****initalize nextion display
  delay(25);

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

  SetVoltageRangeFunc(0); //Set Load A Range
  SetVoltageRangeFunc(1); //Set Load B Range

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
