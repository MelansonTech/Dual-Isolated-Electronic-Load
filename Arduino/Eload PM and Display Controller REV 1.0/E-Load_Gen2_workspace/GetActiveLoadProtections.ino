void GetActiveLoadProtections(void) {

  Wire.beginTransmission(LDA_ADD);         // Send Load Address
  Wire.write(ProtectionStatusRequest);
  DBserial.println("ProtectionStatusRequest");
  Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
  Wire.sendRequest(LDA_ADD, 1, I2C_STOP);    // NON-blocking read (request 2 bytes)
  Wire.finish();                           // wait for IIC to finish before continueing

  LDA.activeProtections = Wire.readByte();            // Get Current reading
  DBserial.println(" LDA.activeProtections");
  DBserial.println( LDA.activeProtections);

  Wire.beginTransmission(LDB_ADD);         // Send Load Address
  Wire.write(ProtectionStatusRequest);
  DBserial.println("ProtectionStatusRequest");
  Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
  Wire.sendRequest(LDB_ADD, 1, I2C_STOP);    // NON-blocking read (request 2 bytes)
  Wire.finish();                           // wait for IIC to finish before continueing

  LDB.activeProtections = Wire.readByte();            // Get Current reading
  DBserial.println(" LDB.activeProtections");
  DBserial.println( LDB.activeProtections);

  if (LDA.activeProtections > 0) {

    // turn the load off

    LDA_OnOff_State = 0;
    LoadA_On_Off_BState_Cap = 0;
    loadOnOffUpdateFunc(LDA_ADD, 0);
    LoadA_ON_OFF.setValue(LoadA_On_Off_BState_Cap);
    delay(50);
  }

  if (LDB.activeProtections > 0) {
    // turn the load off
    LDB_OnOff_State = 0;
    LoadB_On_Off_BState_Cap = 0;
    loadOnOffUpdateFunc(LDB_ADD, 0);
    LoadB_ON_OFF.setValue(LoadB_On_Off_BState_Cap);
    delay(50);

  }

  if (LDA.activeProtections or LDB.activeProtections) {

    LDA.OverVolt = LDA.activeProtections & OverVoltageBit;
    LDB.OverVolt = LDB.activeProtections & OverVoltageBit;
    LDA.OverCurrent = (LDA.activeProtections  & OverCurrentBit);
    LDB.OverCurrent = (LDB.activeProtections  & OverCurrentBit);
    LDA.OverTemp = (LDA.activeProtections & OverTempBit);
    LDB.OverTemp = (LDB.activeProtections & OverTempBit);

    DBserial.println("LDA.OverVolt");
    DBserial.println(LDA.OverVolt);
    DBserial.println("LDB.OverVolt");
    DBserial.println(LDB.OverVolt);

    DBserial.println("LDA.OverCurrent");
    DBserial.println(LDA.OverCurrent);
    DBserial.println("LDB.OverCurrent");
    DBserial.println(LDB.OverCurrent);

    DBserial.println("LDA.OverTemp");
    DBserial.println(LDA.OverTemp);
    DBserial.println("LDB.OverTemp");
    DBserial.println(LDB.OverTemp);

    if (LDA.OverVolt or LDB.OverVolt) {

      String bProtections = "bProtect.txt=\"Over Voltage\"";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      String DisplayShowProtectButton = "vis bProtect,1";
      HWserial.print(DisplayShowProtectButton);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }

    if (LDA.OverCurrent  == OverCurrentBit or LDB.OverCurrent == OverCurrentBit) {
      String bProtections = "bProtect.txt=\"Over Current\"";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      String DisplayShowProtectButton = "vis bProtect,1";
      HWserial.print(DisplayShowProtectButton);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }

    if (LDA.OverTemp == OverTempBit or LDB.OverTemp == OverTempBit) {

      String bProtections = "bProtect.txt=\"Over Temp\"";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      String DisplayShowProtectButton = "vis bProtect,1";
      HWserial.print(DisplayShowProtectButton);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }
  }

}
