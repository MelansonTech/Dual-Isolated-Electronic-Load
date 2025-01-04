
void Load_Monitor_Loop(void) {

  // declare variables to govern encoder acceleration

  int iAcquisition = 0 ;
  newPositionA = oldPositionA;
  newPositionB = oldPositionB;
  CurrentPage = currentNexPage();
  uint32_t LoadA_On_Off_BState_Cap = 0;
  uint32_t LoadB_On_Off_BState_Cap = 0;




  ////NOTE: update load settings HERE in case of range change

  while (CurrentPage == 2) { // load monitor loop


    DBserial.println("Load Monitor");
    DBserial.println(CurrentPage);

    // Check for user load on/off request and update and send the command to the load

    // ********************LOAD A ONOFF Button Check and Load Update

    LDA.Button.StateNow = digitalRead(LDA_PB);
    DBserial.println("LDA.Button.StateNow");
    DBserial.println(LDA.Button.StateNow );


    if (LDA.Button.StateNow == false && LDA.Button.StateLast == false) { // check if there has been a state change in the push button

      DBserial.println("button press detected");
      LDA.Button.StateLast = true;
      LoadA_On_Off_BState_Cap ^= 1; // toggle the state of the nex on off button
      LoadA_ON_OFF.setValue(LoadA_On_Off_BState_Cap);

    }

    if (LDA.Button.StateNow == true && LDA.Button.StateLast == true) {

      LDA.Button.StateLast = false;

    }

    LoadA_ON_OFF.getValue(&LoadA_On_Off_BState_Cap);
    DBserial.println("LoadA_On_Off_BState_Cap");
    DBserial.println(LoadA_On_Off_BState_Cap);

    if (LDA_OnOff_State != LoadA_On_Off_BState_Cap)

    {

      DBserial.println("Load A ONOFF state Change");

      LDA_OnOff_State = LoadA_On_Off_BState_Cap;
      Wire.beginTransmission(LDA_ADD); //U1B
      Wire.write(onOffStateChange);
      Wire.write(LDA_OnOff_State);   // sends instruction byte
      Wire.endTransmission();     // stop transmitting

    }


    // ********************LOAD B ONOFF Button Check and Load Update


    LDB.Button.StateNow = digitalRead(LDB_PB);
    DBserial.println("LDA.Button.StateNow");
    DBserial.println(LDA.Button.StateNow );

    if (LDB.Button.StateNow == false && LDB.Button.StateLast == false) { // check if there has been a state change in the push button

      DBserial.println("button press detected");
      LDB.Button.StateLast = true;
      LoadB_On_Off_BState_Cap ^= 1; // toggle the state of the nex on off button
      LoadB_ON_OFF.setValue(LoadB_On_Off_BState_Cap);

    }

    if (LDB.Button.StateNow == true && LDB.Button.StateLast == true) {

      LDB.Button.StateLast = false;

    }

    LoadB_ON_OFF.getValue(&LoadB_On_Off_BState_Cap);
    DBserial.println("LoadB_On_Off_BState_Cap");
    DBserial.println(LoadB_On_Off_BState_Cap);

    if (LDB_OnOff_State != LoadB_On_Off_BState_Cap)

    {

      DBserial.println("Load B ONOFF state Change");
      LDB_OnOff_State = LoadB_On_Off_BState_Cap;
      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(onOffStateChange);
      Wire.write(LDB_OnOff_State);   // sends instruction byte
      Wire.endTransmission();     // stop transmitting

    }

    // the below sections captures the encoder changes and writes proportional value to the DAC. This is used to control current of the corresponding LOAD



    //********************* update Load A ** Encoder set point Update

    newPositionA = LDA_Knob.read() / 4;         // get encoder postition

    if (newPositionA != oldPositionA) {       // check to see if position has changed since the last check

      LDA.ENCODER.capVal = encoder_position_move(newPositionA, oldPositionA, LDA.ENCODER.capVal);

      LDA.ENCODER.capVal = constrain(LDA.ENCODER.capVal, 0, 100);
      oldPositionA = newPositionA;

      HWserial.print("j0.val=");  // Update the nex display with the new LDA Set Point
      HWserial.print(LDA.ENCODER.capVal);  // This is the value you want to send to that object and atribute mentioned before.
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      LDA.SetPoint.calibrated = (LDA.ENCODER.capVal * LDA.CurrentMax) / 100;
      DBserial.println("LDA.setPoint.setVal");
      DBserial.println(LDA.SetPoint.setVal);

      String LDA_SP = "tsetA.txt=\"" + String(LDA.SetPoint.calibrated, 2) + LDA.Units + "\"" ;

      DBserial.println(LDA_SP);
      HWserial.print(LDA_SP);  // Update the nex display with the new LDA Set Point
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      LDA.SetPoint.calibrated = (LDA.SetPoint.calibrated / LDA.CurrentMax) * 4095;
      LDA.SetPoint.capVal = (int)calibration(LDA.SetPoint.calibrated, LDA.SetPoint.calGain, LDA.SetPoint.calOffset);

      DBserial.println("LDA.current.capVal");
      DBserial.println(LDA.SetPoint.capVal);

      Wire.beginTransmission(LDA_ADD); //U1B
      Wire.write(SetPointChange);
      Wire.write(LDA.SetPoint.capVal & 0xFF);
      Wire.write(LDA.SetPoint.capVal >> 8 & 0xFF);
      Wire.endTransmission();     // stop transmitting


    }//end of if encoder A position changes statement


    //*********************update Load B Encoder set point Update

    // the below sections captures the encoder changes and writes proportional value to the DAC. This is used to control current of the corresponding LOAD

    newPositionB = LDB_Knob.read() / 4;         // get encoder postition

    if (newPositionB != oldPositionB) {       // check to see if position has changed since the last check

      LDB.ENCODER.capVal = encoder_position_move(newPositionB, oldPositionB, LDB.ENCODER.capVal);

      LDB.ENCODER.capVal = constrain(LDB.ENCODER.capVal, 0, 100);
      oldPositionB = newPositionB;

      HWserial.print("j1.val=");  // Update the nex display with the new LDB Set Point
      HWserial.print(LDB.ENCODER.capVal);  // This is the value you want to send to that object and atribute mentioned before.
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      LDB.SetPoint.calibrated = (LDB.ENCODER.capVal * LDB.CurrentMax) / 100;
      DBserial.println("LDB.setPoint.setVal");
      DBserial.println(LDB.SetPoint.setVal);

      String LDB_SP = "tsetB.txt=\"" + String(LDB.SetPoint.calibrated, 2) + LDB.Units + "\"" ;

      DBserial.println(LDB_SP);
      HWserial.print(LDB_SP);  // Update the nex display with the new LDB Set Point
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      LDB.SetPoint.calibrated = (LDB.SetPoint.calibrated / LDB.CurrentMax) * 4095;
      LDB.SetPoint.capVal = (int)calibration(LDB.SetPoint.calibrated, LDB.SetPoint.calGain, LDB.SetPoint.calOffset);

      DBserial.println("LDB.current.capVal");
      DBserial.println(LDB.SetPoint.capVal);

      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(SetPointChange);
      Wire.write(LDB.SetPoint.capVal & 0xFF);
      Wire.write(LDB.SetPoint.capVal >> 8 & 0xFF);
      Wire.endTransmission();     // stop transmitting


    }//end of if encoder B position changes statement

    //********************* update Load A ** KeyPad set point Update


    CurrentPage = currentNexPage();
    KPA.getValue(&KPAFlag);

    if (CurrentPage == 2 && KPAFlag == 1) {

      KPAFlag = 0;
      KPA.setValue(KPAFlag);

      // get the new set point typed in the Key pad
      memset(buffer, 0, sizeof(buffer));  // Clear the buffer, so we can start using it
      tsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
      LDA.SetPoint.NexRecieve = buffer;

      // limit to min max values
      LDA.SetPoint.calibrated = LDA.SetPoint.NexRecieve.toFloat();
      LDA.SetPoint.calibrated = constrain(LDA.SetPoint.calibrated, 0, LDA.CurrentMax);

      // scale to 0-100 and save as new rot encoder value
      LDA.ENCODER.capVal = (int)((LDA.SetPoint.calibrated / LDA.CurrentMax) * 100);

      DBserial.println("LDA.ENCODER.capVal");
      DBserial.println(LDA.ENCODER.capVal);
      delay(1000);

      DBserial.println(buffer);
      DBserial.println(LDA.SetPoint.NexRecieve);
      DBserial.println(LDA.SetPoint.calibrated);

      //update nex display bar graph with rot encoder val - 0 to 100

      HWserial.print("j0.val=");  // Update the nex display with the new LDA Set Point
      HWserial.print(LDA.ENCODER.capVal);  // This is the value you want to send to that object and atribute mentioned before.
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);


      // create nex display command string for Setpoint update and send
      String LDA_SP = "tsetA.txt=\"" + String(LDA.SetPoint.calibrated, 2) + LDA.Units + "\"" ;

      DBserial.println(LDA_SP);
      HWserial.print(LDA_SP);  // Update the nex display with the new LDA Set Point
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      // Calibrate the Set Point to send to the Load Module - used cap val because it an INT var
      DBserial.println("LDA.SetPoint.calibrated");
      DBserial.println(LDA.SetPoint.calibrated);

      LDA.SetPoint.calibrated = (LDA.SetPoint.calibrated / LDA.CurrentMax) * 4095;
      LDA.SetPoint.capVal = (int)calibration(LDA.SetPoint.calibrated, LDA.SetPoint.calGain, LDA.SetPoint.calOffset);
      DBserial.println("LDA.SetPoint.capVal");
      DBserial.println(LDA.SetPoint.capVal);

      Wire.beginTransmission(LDA_ADD); //U1B
      Wire.write(SetPointChange);
      Wire.write(LDA.SetPoint.capVal & 0xFF);
      Wire.write(LDA.SetPoint.capVal >> 8 & 0xFF);
      Wire.endTransmission();     // stop transmitting

    }

    //***************************************update Load B ** KeyPad set point Update

    DBserial.println("KPBFlag = 1 && KPEFlag == 1");

    CurrentPage = currentNexPage();
    KPB.getValue(&KPBFlag);

    if (CurrentPage == 2 && KPBFlag == 1) {

      KPBFlag = 0;
      KPB.setValue(KPBFlag);

      // get the new set point typed in the Key pad
      memset(buffer, 0, sizeof(buffer));  // Clear the buffer, so we can start using it
      tsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
      LDB.SetPoint.NexRecieve = buffer;

      // limit to min max values
      LDB.SetPoint.calibrated = LDB.SetPoint.NexRecieve.toFloat();
      LDB.SetPoint.calibrated = constrain(LDB.SetPoint.calibrated, 0, LDB.CurrentMax);

      // scale to 0-100 and save as new rot encoder value
      LDB.ENCODER.capVal = (int)((LDB.SetPoint.calibrated / LDB.CurrentMax) * 100);

      DBserial.println("LDB.ENCODER.capVal");
      DBserial.println(LDB.ENCODER.capVal);
      delay(1000);

      DBserial.println(buffer);
      DBserial.println(LDB.SetPoint.NexRecieve);
      DBserial.println(LDB.SetPoint.calibrated);

      //update nex display bar graph with rot encoder val - 0 to 100

      HWserial.print("j1.val=");  // Update the nex display with the new LDB Set Point
      HWserial.print(LDB.ENCODER.capVal);  // This is the value you want to send to that object and atribute mentioned before.
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);


      // create nex display command string for Setpoint update and send
      String LDB_SP = "tsetB.txt=\"" + String(LDB.SetPoint.calibrated, 2) + LDB.Units + "\"" ;

      DBserial.println(LDB_SP);
      HWserial.print(LDB_SP);  // Update the nex display with the new LDB Set Point
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      // Calibrate the Set Point to send to the Load Module - used cap val because it an INT var
      DBserial.println("LDB.SetPoint.calibrated");
      DBserial.println(LDB.SetPoint.calibrated);

      LDB.SetPoint.calibrated = (LDB.SetPoint.calibrated / LDB.CurrentMax) * 4095;
      LDB.SetPoint.capVal = (int)calibration(LDB.SetPoint.calibrated, LDB.SetPoint.calGain, LDB.SetPoint.calOffset);
      DBserial.println("LDB.SetPoint.capVal");
      DBserial.println(LDB.SetPoint.capVal);

      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(SetPointChange);
      Wire.write(LDB.SetPoint.capVal & 0xFF);
      Wire.write(LDB.SetPoint.capVal >> 8 & 0xFF);
      Wire.endTransmission();     // stop transmitting

    }


    //******************************************ADC Acquisition********************************

    if (iAcquisition == 0) {

      //volt acquistion

      Wire.beginTransmission(LDA_ADD);         // Send Load Address
      Wire.write(ADCReadingRequest);           // Send ADC reading request command
      Wire.write(ADCReadingVolt);              //  Specify ADC reading request
      Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
      Wire.sendRequest(LDA_ADD, 2, I2C_STOP);    // NON-blocking read (request 2 bytes)
      Wire.finish();                           // wait for IIC to finish before continueing

      if (Wire.available() >= 2)

      {
        LDA.volt.capVal = Wire.readByte();            // Get Voltage reading
        LDA.volt.capVal |= Wire.readByte() << 8;
      }


      LDA.volt = AVG_Filter(LDA.volt, LDA.volt.capVal);
      LDA.volt.calibrated = calibration(LDA.volt.filteredSlow, LDA.volt.calGain, LDA.volt.calOffset);
      LDA.volt = ValChangeDetected(LDA.volt, LDA.volt.calibrated, 0.01, 0.01); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change
      DBserial.println(LDA.volt.calibrated);


      if (LDA.volt.ChangeDetectFlag == 1) {

        String LDA_Volt = "tvoltA.txt=\"" + String(LDA.volt.calibrated, 3) + "\"";
        DBserial.println(LDA_Volt);
        HWserial.print(LDA_Volt);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDA.power = LDA.volt.calibrated * LDA.current.calibrated;

        String LDApower = "tpowerA.txt=\"" + String(LDA.power, 2) + "\"";
        DBserial.println(LDApower);
        HWserial.print(LDApower);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }
    }

    if (iAcquisition == 1) {

      Wire.beginTransmission(LDB_ADD);         // Send Load Address
      Wire.write(ADCReadingRequest);           // Send ADC reading request command
      Wire.write(ADCReadingVolt);              //  Specify ADC reading request
      Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
      Wire.sendRequest(LDB_ADD, 2, I2C_STOP);    // NON-blocking read (request 2 bytes)
      Wire.finish();                           // wait for IIC to finish before continueing

      if (Wire.available() >= 2)

      {
        LDB.volt.capVal = Wire.readByte();            // Get Voltage reading
        LDB.volt.capVal |= Wire.readByte() << 8;
      }

      LDB.volt = AVG_Filter(LDB.volt, LDB.volt.capVal);
      LDB.volt.calibrated = calibration(LDB.volt.filteredSlow, LDB.volt.calGain, LDB.volt.calOffset);
      LDB.volt = ValChangeDetected(LDB.volt, LDB.volt.calibrated, 0.1, 0.1); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change

      if (LDB.volt.ChangeDetectFlag == 1) {

        String LDB_Volt = "tvoltB.txt=\"" + String(LDB.volt.calibrated, 3) + "\"";
        DBserial.println(LDB_Volt);
        HWserial.print(LDB_Volt);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDB.power = LDB.volt.calibrated * LDB.current.calibrated;

        String LDBpower = "tpowerB.txt=\"" + String(LDB.power, 2) + "\"";
        DBserial.println(LDBpower);
        HWserial.print(LDBpower);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);


      }
    }
    if (iAcquisition == 2) {
      //current acquistion

      Wire.beginTransmission(LDA_ADD);         // Send Load Address
      Wire.write(ADCReadingRequest);           // Send ADC reading request command
      Wire.write(ADCReadingCurrent);              //  Specify ADC reading request
      Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
      Wire.sendRequest(LDA_ADD, 2, I2C_STOP);    // NON-blocking read (request 2 bytes)
      Wire.finish();                           // wait for IIC to finish before continueing

      if (Wire.available() >= 2)

      {
        LDA.current.capVal = Wire.readByte();            // Get Current reading
        LDA.current.capVal |= Wire.readByte() << 8;
      }

      LDA.current = AVG_Filter(LDA.current, LDA.current.capVal);
      LDA.current.calibrated = calibration(LDA.current.filteredSlow, LDA.current.calGain, LDA.current.calOffset);
      LDA.current = ValChangeDetected(LDA.current, LDA.current.calibrated, 0.001, 0.001); // check for a change in the filtered value and return the LCD print flag 1 if changed 0 if no change


      if (LDA.current.ChangeDetectFlag == 1) {

        String LDA_Current = "tcurrentA.txt=\"" + String(LDA.current.calibrated,3) + "\"";
        DBserial.println(LDA_Current);
        HWserial.print(LDA_Current);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }
    }
    if (iAcquisition == 3) {
      //current acquistion

      Wire.beginTransmission(LDB_ADD);         // Send Load Address
      Wire.write(ADCReadingRequest);           // Send ADC reading request command
      Wire.write(ADCReadingCurrent);              //  Specify ADC reading request
      Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
      Wire.sendRequest(LDB_ADD, 2, I2C_STOP);    // NON-blocking read (request 2 bytes)
      Wire.finish();                           // wait for IIC to finish before continueing

      if (Wire.available() >= 2)

      {
        LDB.current.capVal = Wire.readByte();            // Get Current reading
        LDB.current.capVal |= Wire.readByte() << 8;
      }

      LDB.current = AVG_Filter(LDB.current, LDB.current.capVal);
      LDB.current.calibrated = calibration(LDB.current.filteredSlow, LDB.current.calGain, LDB.current.calOffset);
      LDB.current = ValChangeDetected(LDB.current, LDB.current.calibrated, 0.001, 0.001); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change

      if (LDB.current.ChangeDetectFlag == 1) {

        String LDB_Current = "tcurrentB.txt=\"" + String(LDB.current.calibrated, 3) + "\"";
        DBserial.println(LDB_Current);
        HWserial.print(LDB_Current);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }
    }
    if (iAcquisition == 4) {

      //******************************temp acquistion

      Wire.beginTransmission(LDA_ADD);         // Send Load Address
      Wire.write(ADCReadingRequest);           // Send ADC reading request command
      Wire.write(ADCReadingTemp);              //  Specify ADC reading request
      Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
      Wire.sendRequest(LDA_ADD, 2, I2C_STOP);    // NON-blocking read (request 2 bytes)
      Wire.finish();                           // wait for IIC to finish before continueing

      if (Wire.available() >= 2)

      {
        LDA.temp.capVal = Wire.readByte();            // Get Current reading
        LDA.temp.capVal |= Wire.readByte() << 8;
      }

      while (Arraytemplookup[LDA.temp.capVal] == 0) {

        LDA.temp.capVal++;

      }

      LDA.temp.calibrated = Arraytemplookup[LDA.temp.capVal];
      //LDA.temp = AVG_Filter(LDA.temp, LDA.temp.capVal);
      //LDA.temp.calibrated = calibration(LDA.temp.filteredSlow, LDA.temp.calGain, LDA.temp.calOffset);
      LDA.temp = ValChangeDetected(LDA.temp, LDA.temp.calibrated, 0.1, 0.1); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change


      if (LDA.temp.ChangeDetectFlag == 1) {

        String LDA_Temp = "ttempA.txt=\"" + String(LDA.temp.calibrated, 1) + "\"";
        DBserial.println(LDA_Temp);
        HWserial.print(LDA_Temp);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }
    }
    if (iAcquisition == 5) {

      Wire.beginTransmission(LDB_ADD);         // Send Load Address
      Wire.write(ADCReadingRequest);           // Send ADC reading request command
      Wire.write(ADCReadingTemp);              //  Specify ADC reading request
      Wire.endTransmission(I2C_NOSTOP);        // blocking write (NOSTOP triggers RepSTART on next I2C command)
      Wire.sendRequest(LDB_ADD, 2, I2C_STOP);    // NON-blocking read (request 2 bytes)
      Wire.finish();                           // wait for IIC to finish before continueing

      if (Wire.available() >= 2)

      {
        LDB.temp.capVal = Wire.readByte();            // Get Current reading
        LDB.temp.capVal |= Wire.readByte() << 8;
      }

      while (Arraytemplookup[LDB.temp.capVal] == 0) {

        LDB.temp.capVal++;

      }

      LDB.temp.calibrated = Arraytemplookup[LDB.temp.capVal];
      //LDB.temp = AVG_Filter(LDB.temp, LDB.temp.capVal);
      //LDB.temp.calibrated = calibration(LDB.temp.filteredSlow, LDB.temp.calGain, LDB.temp.calOffset);
      LDB.temp = ValChangeDetected(LDB.temp, LDB.temp.calibrated, 0.1, 0.1); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change


      if (LDB.temp.ChangeDetectFlag == 1) {

        String LDB_Temp = "ttempB.txt=\"" + String(LDB.temp.calibrated, 1) + "\"";
        DBserial.println(LDB_Temp);
        HWserial.print(LDB_Temp);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }
    }

    iAcquisition++; // get the next adc reading

    if (iAcquisition > 5) {

      iAcquisition = 0;

    }

    //******************************************SD Card Data Logging and capture

    if (SD_log_active == true) { // if the dual stat "log Data" button is pressed then begin logging load data to sd card

      SD_log_count += 1;
      HWserial.print("n9.val=");
      HWserial.print(SD_log_count);  // Update the nex display
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      WriteLoadDataToSD(SD_log_count);// function gathers all of the loads senors data and save it to the datalog.txt file

    }// SD logging active if end



    CurrentPage = currentNexPage(); // check the current page status

    if (CurrentPage == 5) {

      CurrentPage = 2; //if the current page is the keypad page(page5) then remain in the monitor loop by setting the currentpage to page 2

    }

  }// while current page 2 end
  return;

}
