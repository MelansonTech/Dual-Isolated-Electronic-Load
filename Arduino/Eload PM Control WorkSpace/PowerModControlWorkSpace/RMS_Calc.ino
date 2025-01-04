
struct RMS Function_RMS_Calc(RMS RMSCalc, unsigned short ADC_Sample) {

  RMSCalc.Sum_of_Samples_Squared -= (RMSCalc.Sum_of_Samples_Squared / RMSCalc.SAMPLES);
  RMSCalc.Sum_of_Samples_Squared += (ADC_Sample * ADC_Sample);
  if (RMSCalc.RMS == 0) {
    RMSCalc.RMS = 1;
  }    /* do not divide by zero */

  RMSCalc.RMS = (RMSCalc.RMS + (RMSCalc.Sum_of_Samples_Squared / RMSCalc.SAMPLES / RMSCalc.RMS)) / 2;

  return RMSCalc;

}

// if (millis() - RMSCalc_Millis_LastTime > RMSCalc.Delay_SampleRate) {
//
//    RMSCalc_SAMPLES = ;
//    RMSCalc_RMS = RMS Function_RMS_Calc(RMS.Volt,abs(LD_Volt-Ref_Offset));
//    RMSCalc_Millis_LastTime = millis();
//
// }
