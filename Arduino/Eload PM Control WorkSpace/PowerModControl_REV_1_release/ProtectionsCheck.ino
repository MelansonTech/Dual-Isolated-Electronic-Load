void ProtectionsCheck(void) {

  Serial.println("ProtectionsCheck");
  Serial.println(ActiveProtections);

  LD_Temp = analogRead(ADC_TempSense);
  if (protectionLimitCheckFunc(LD_Temp, minTemp, maxTemp)) {
    ActiveProtections |= OverTempBit;
  }

  else {
    ActiveProtections &= !OverTempBit;
  }

  Serial.println("tempCheck");
  Serial.println(LD_Temp);

  LD_Current = analogRead(ADC_ISense);

  if (protectionLimitCheckFunc(LD_Current, 0, maxCurrent)) {
    ActiveProtections |= OverCurrentBit;
    Serial.println("over current detected");
    Serial.println(ActiveProtections);    
  }

  else {
    ActiveProtections &= !OverCurrentBit;
  }
  
  Serial.println("currentCheck");
  Serial.println(LD_Current);

  LD_Volt = analogRead(ADC_VSense);

  if (protectionLimitCheckFunc(LD_Volt, minVoltage, maxVoltage)) {
    ActiveProtections |= OverVoltageBit;
  }

  else {
    ActiveProtections &= !OverVoltageBit;
  }

  Serial.println("voltCheck");
  Serial.println(LD_Volt);

  Serial.println("ActiveProtections");
  Serial.println(ActiveProtections);
   
  if (ActiveProtections > 0) {

    Serial.println("Fault detetected turn off the load");  
    onOffState = 0;
    LoadOnOffControlFunc(onOffState); // update load on\off state
  }
}
