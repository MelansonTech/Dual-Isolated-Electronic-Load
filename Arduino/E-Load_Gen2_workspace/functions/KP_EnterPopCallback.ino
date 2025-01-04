
void KP_EnterPopCallback(void *ptr){
  
Serial.println("KP_EnterPopCallback");   
newPositionA = oldPositionA;
newPositionB = oldPositionB;
KPEFlag = 1;
//CalVoltHighFlag = 0;
//CalVoltLowFlag = 0;
//CalAmpHighFlag = 0;
//CalAmpLowFlag = 0;
  
}// end of function
