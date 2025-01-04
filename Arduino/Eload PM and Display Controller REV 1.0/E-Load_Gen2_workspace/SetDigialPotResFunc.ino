void SetDigialPotResFunc(int PotAddress, int LoadAddress, int VoltageRange, int PotValue) {

  Wire.beginTransmission(LoadAddress); //U1B
  Wire.write(voltRangeChange);
  Wire.write(1);   // sends instruction byte  - Set digital pot reference to ground
  Wire.endTransmission();     // stop transmitting

  delay(500);

  Wire.beginTransmission(PotAddress); //U1B
  Wire.write(potInstrucSelA);   // sends instruction byte
  Wire.write(PotValue);  // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(PotAddress); //U1B
  Wire.write(potInstrucSelB);   // sends instruction byte
  Wire.write(PotValue);  // sends potentiometer value byte
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(LoadAddress); //U1B
  Wire.write(voltRangeChange);
  Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(LoadAddress);
  Wire.write(CRVGainChange); // send range setting to load controller
  Wire.write(VoltageRange); // send range setting to load controller
  Wire.endTransmission();     // stop transmitting
}
