void GetActiveLoadProtections() {

  Wire.beginTransmission(LDA_ADD);         // Send Load Address
  Wire.write(ProtectionStatusRequest);           // Send ADC reading request command
  Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
  Wire.sendRequest(LDA_ADD, 1, I2C_STOP);    // NON-blocking read (request 2 bytes)
  Wire.finish();                           // wait for IIC to finish before continueing

  if (Wire.available())

  {

    LDA.activeProtections = Wire.readByte();

  }

  if (LDA.activeProtections) {

    LDA.OverVolt = activeProtections & OverVoltageBit;
    
    if (LDA.OverVolt) {

      String bProtections = "bProtect.txt = Over Voltage";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }

    LDA.OverCurrent = (activeProtections >> 1) & OverCurrentBit;

     if (LDA.OverCurrent) {

      String bProtections = "bProtect.txt = Over Current";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }

    LDA.OverTemp = (activeProtections >> 2) & OverTempBit;

       if (LDA.OverTemp) {

      String bProtections = "bProtect.txt = Over Temp";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }


    String DisplayShowProtectButton = "vis bProtect,1"
    HWserial.print(DisplayShowProtectButton);  // Update the nex display
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff);

  }

  else {

    LDA.OverVolt = 0;
    LDA.OverCurrent = 0;
    LDA.OverTemp = 0;

    String DisplayShowProtectButton = "vis bProtect,0"
    HWserial.print(DisplayShowProtectButton);  // Update the nex display
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff);

  }

  Wire.beginTransmission(LDB_ADD);         // Send Load Address
  Wire.write(ProtectionStatusRequest);           // Send ADC reading request command
  Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
  Wire.sendRequest(LDB_ADD, 1, I2C_STOP);    // NON-blocking read (request 1 bytes)
  Wire.finish();                           // wait for IIC to finish before continueing

  if (Wire.available())

  {

    LDB.activeProtections = Wire.readByte();

  }

  if (LDB.activeProtections) {

    LDB.OverVolt = activeProtections & OverVoltageBit;
    
    if (LDB.OverVolt) {

      String bProtections = "bProtect.txt = Over Voltage";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }

    LDB.OverCurrent = (activeProtections >> 1) & OverCurrentBit;

     if (LDB.OverCurrent) {

      String bProtections = "bProtect.txt = Over Current";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }

    LDB.OverTemp = (activeProtections >> 2) & OverTempBit;

       if (LDB.OverTemp) {

      String bProtections = "bProtect.txt = Over Temp";
      HWserial.print(bProtections);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

    }


    String DisplayShowProtectButton = "vis bProtect,1"
    HWserial.print(DisplayShowProtectButton);  // Update the nex display
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff);

  }

  else {

    LDB.OverVolt = 0;
    LDB.OverCurrent = 0;
    LDB.OverTemp = 0;

    String DisplayShowProtectButton = "vis bProtect,0"
    HWserial.print(DisplayShowProtectButton);  // Update the nex display
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff);

  }
}
