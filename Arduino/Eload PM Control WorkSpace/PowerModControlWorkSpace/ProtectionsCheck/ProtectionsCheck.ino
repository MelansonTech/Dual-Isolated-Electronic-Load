void ProtectionsCheck(void) {

  LD_Temp = analogRead(ADC_TempSense);
  if (protectionLimitCheckFunc(LD_Temp, minTemp, maxTemp)) {

    ActiveProtections &= OverTempBit;

  }

  LD_Current = analogRead(ADC_ISense);
  if ( protectionLimitCheckFunc(LD_Current, 0, maxCurrent)) {

    ActiveProtections &= OverCurrentBit;

  }

  LD_Volt = analogRead(ADC_VSense);
  if (protectionLimitCheckFunc(LD_Volt, 0, maxVoltage)) {

    ActiveProtections &= OverVoltageBit;

  }

  if (ActiveProtections) {

    onOffState = 0;
    LoadOnOffControlFunc(onOffState); // update load on\off state

  }
}
