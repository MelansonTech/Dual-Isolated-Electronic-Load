// Page change event:
void KP_ExitPopCallback(void *ptr)  // If page 0 is loaded on the display, the following is going to execute:
{

  newPositionA = oldPositionA;
  newPositionB = oldPositionB;
  KPA = false;
  KPB = false;
  CalVoltHighFlag = 0;
  CalVoltLowFlag = 0;
  CalAmpHighFlag = 0;
  CalAmpLowFlag = 0;
  KPE = 0;
  CalIoffSetFlag = 0;
  CalVoffSetFlag = 0;
  
}  // End of press event
