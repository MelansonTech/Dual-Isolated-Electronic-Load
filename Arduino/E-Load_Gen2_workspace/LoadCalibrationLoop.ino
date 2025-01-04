void  LoadCalibrationLoop(void) {


  //note the range flag is used to set the mode of operation for the load

  // Shut Down the loads and load the defaults

  LDA_OnOff_State = 0; // Shut down load A
  LDB_OnOff_State = 0; // Shut down load B

  Wire.beginTransmission(LDA_ADD); //U1B
  Wire.write(onOffStateChange);
  Wire.write(LDA_OnOff_State);   // sends instruction byte
  Wire.endTransmission();     // stop transmitting

  Wire.beginTransmission(LDB_ADD); //U1B
  Wire.write(onOffStateChange);
  Wire.write(LDB_OnOff_State);   // sends instruction byte
  Wire.endTransmission();     // stop transmitting


  // set default button states

  dsbCaLIsetLow.setValue(1);
  dsbCaLIsetHigh.setValue(0);

  // Set Load to Low current Cal point

  Wire.beginTransmission(LDA_ADD); //U1B
  Wire.write(SetPointChange);
  Wire.write(500 & 0xFF);
  Wire.write(500 >> 8 & 0xFF);
  Wire.endTransmission();     // stop transmitting


  Wire.beginTransmission(LDB_ADD); //U1B
  Wire.write(SetPointChange);
  Wire.write(500 & 0xFF);
  Wire.write(500 >> 8 & 0xFF);
  Wire.endTransmission();     // stop transmitting


  while (CurrentPage == 4) {

    CurrentPage = currentNexPage();//check which page the display is on

    if (CurrentPage == 5) { //if the current page is page 4 (the key pad) don't break the loop

      CurrentPage = 4;

    }

    dsbCalSetA.getValue(&LDACal);
    dsbCalSetB.getValue(&LDBCal);
    DBserial.println("CurrentPage");
    DBserial.println(CurrentPage);
   

    if (LDACal == 1 && LDBCal == 0) {

      // turn off load B
      LDB_OnOff_State = 0;
      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(onOffStateChange);
      Wire.write(LDB_OnOff_State);   // sends instruction byte
      Wire.endTransmission();     // stop transmitting

      dsbCalonOff.setValue(0);


      LDA.volt.range = 0;
      LDA.current.range = 0;
      LDA_Range_Cal_Coeff();

      HWserial.print("bIrangeCal.txt=");  // Update the nex display
      HWserial.print("\"");
      HWserial.print("0.35A");  // Update the nex display
      HWserial.print("\"");
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      LDA.CurrentMax = 0.35;

      Wire.beginTransmission(LDA_ADD); //U1B
      Wire.write(currentRangeChange);
      Wire.write(0);   // sends instruction byte  - High range set
      Wire.endTransmission();     // stop transmitting

      DBserial.println(LDA.volt.range);
      HWserial.print("bVrangeCal.txt=");  // Update the nex display
      HWserial.print("\"");
      HWserial.print("400V");  // Update the nex display
      HWserial.print("\"");
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      Wire.beginTransmission(LDA_ADD); //U1B
      Wire.write(voltRangeChange);
      Wire.write(1);   // sends instruction byte  - Set digital pot reference to ground
      Wire.write(LDA.volt.range);
      Wire.endTransmission();     // stop transmitting

      delay(500);

      Wire.beginTransmission(potADD_1); //U1B
      Wire.write(potInstrucSelA);   // sends instruction byte
      Wire.write(Vamp_Range_High);  // sends potentiometer value byte
      Wire.endTransmission();     // stop transmitting

      Wire.beginTransmission(potADD_1); //U1B
      Wire.write(potInstrucSelB);   // sends instruction byte
      Wire.write(Vamp_Range_High);  // sends potentiometer value byte
      Wire.endTransmission();     // stop transmitting

      Wire.beginTransmission(LDA_ADD); //U1B
      Wire.write(voltRangeChange);
      Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
      Wire.write(LDA.volt.range);
      Wire.endTransmission();     // stop transmitting

    }

    while (LDACal == 1) {

      DBserial.println("LDACal == true");
      CurrentPage = currentNexPage();
      dsbCalSetA.getValue(&LDACal);

       DBserial.println("LDA.volt.range");
    DBserial.println(LDA.volt.range);

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

      dsbCalonOff.getValue(&LoadA_On_Off_BState_Cap);
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

      //******************  Check Current Set Point Buttons

      dsbCaLIsetLow.getValue(&dsbCaLIset);

      if (dsbCaLIset == 1) {

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(SetPointChange);
        Wire.write(500 & 0xFF);
        Wire.write(500 >> 8 & 0xFF);
        Wire.endTransmission();     // stop transmitting

      }

      else {

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(SetPointChange);
        Wire.write(3500 & 0xFF);
        Wire.write(3500 >> 8 & 0xFF);
        Wire.endTransmission();     // stop transmitting

      }


      bVrangeCal.getValue(&bVrangeCalFlag); // dual state button current state check (voltage range)

      if (bVrangeCalFlag == 1) {

        bVrangeCalFunc();
        delay(250);
        bVrangeCalFlag = 0;
        bVrangeCal.setValue(bVrangeCalFlag);

      }

      bIrangeCal.getValue(&bIrangeCalFlag); // dual state button current state check (voltage range)

      if (bIrangeCalFlag == 1) {

        bIrangeCalFunc();
        delay(250);
        bIrangeCalFlag = 0;
        bIrangeCal.setValue(bIrangeCalFlag);
      }

      bcaliCurrSlope.getValue(&bcaliCurrSlopeFlag); // dual state button current state check (execute slope calibration)

      if (bcaliCurrSlopeFlag == 1) {

        delay(250);
        bcaliCurrSlopeFunc();
        bcaliCurrSlopeFlag = 0;
        bcaliCurrSlope.setValue(bcaliCurrSlopeFlag);


      }

      bcaliCurrOff.getValue(&bcaliCurrOffFlag); // dual state button current state check (execute slope calibration)

      if (bcaliCurrOffFlag == 1) {

        delay(250);
        bcaliCurrentOffSetFunc();
        bcaliCurrOffFlag = 0;
        bcaliCurrOff.setValue(bcaliCurrOffFlag);
      }

      // bcaliCurrentOffSetFunc();
      bcaliVoltSlope.getValue(&bcaliVoltSlopeFlag);

      if (bcaliVoltSlopeFlag == 1) {

        delay(250);
        bcaliVoltSlopeFunc();
        bcaliVoltSlopeFlag = 0;
        bcaliVoltSlope.setValue(bcaliVoltSlopeFlag);

      }

      bcaliVoltOff.getValue(&bcaliVoltOffFlag);

      if (bcaliVoltOffFlag == 1) {

        delay(250);
        bcaliVoltOffSetFunc();
        bcaliVoltOffFlag = 0;
        bcaliVoltOff.setValue(bcaliVoltOffFlag);

      }

      BcalVDef.getValue(&BcalVDefFlag);

      if (BcalVDefFlag == 1) {

        delay(250);
        bcaliVoltSlopeFunc();
        bcaliVoltOffSetFunc();
        BcalVDefFlag = 0;
        BcalVDef.setValue(BcalVDefFlag);

      }

      BcalIDef.getValue(&BcalIDefFlag);

      if (BcalIDefFlag == 1) {

        delay(250);
        bcaliCurrSlopeFunc();
        bcaliCurrentOffSetFunc();
        BcalIDefFlag = 0;
        BcalIDef.setValue(BcalIDefFlag);
      }


      if (CurrentPage == 5) { //if the current page is page 4 (the key pad) don't break the loop
        CurrentPage = 4;

      }

      if (CurrentPage != 4) { //check for nex page change and break the loop

        DBserial.println("break");
        break;

      }

      //reset all of the calibration button flags

      CalVoltHighFlag = 0;
      CalVoltLowFlag = 0;
      CalVoffSetFlag = 0;
      CalAmpLowFlag = 0;
      CalAmpHighFlag = 0;
      CalIoffSetFlag = 0;
      KPEFlag = 0;


      //************************Hi volt set Flag check

      CalSetVoltHigh.getValue(&CalVoltHighFlag);  // Read the text on the object and store it on the buffer

      //************************Low volt set Flag check

      CalSetVoltLow.getValue(&CalVoltLowFlag);  // Read the text on the object and store it on the buffer

      //************************Volt offset set flag

      CalVoffSet.getValue(&CalVoffSetFlag); // get the text box pressed variable state.(cal current offset text box entry)


      //************************High Current set Flag check

      CalSetAmpHigh.getValue(&CalAmpHighFlag);  // Read the text on the object and store it on the buffer

      //************************Low Current set Flag check

      CalSetAmpLow.getValue(&CalAmpLowFlag);  // Read the text on the object and store it on the buffer

      //************************Current offset set flag

      CalIoffSet.getValue(&CalIoffSetFlag); // get the text box pressed variable state.(cal current offset text box entry)


      while (CalVoltHighFlag == 1) {

        DBserial.println("CalVoltHighFlag == 1");

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalVoltHighFlag = 0;
          CalSetVoltHigh.setValue(CalVoltHighFlag);
          delay(100);

          tVcalSetH.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDA.volt.NexRecieve = buffer;
          LDA.volt.CalHighRead = LDA.volt.NexRecieve.toFloat();
          DBserial.println("LDA.volt.NexRecieve = " + LDA.volt.NexRecieve);

          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the volt 50 and average the samples

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

            LDA.volt = AVG_Filter(LDA.volt, LDA.volt.capVal);  // Filter ADC Reading
            
          }

          LDA.volt.calibrated = calibration(LDA.volt.filteredSlow, LDA.volt.calGain, LDA.volt.calOffset);
          LDA.volt.CalHighMeas = LDA.volt.calibrated;//store the measured high voltage value

          String LDA_voltH = "tVcalSenH.txt=\"" + String(LDA.volt.CalHighMeas, 3) + "\"";
          DBserial.println(LDA_voltH);
          HWserial.print(LDA_voltH);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);


        }//end of the if key pad enter
        
      }//end of while CalVoltHighFlag == 1

      while (CalVoltLowFlag == 1) {

        DBserial.println("CalSetVoltLow  == true");

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalVoltLowFlag = 0;
          CalSetVoltLow.setValue(CalVoltLowFlag);
          delay(100);

          tVcalSetL.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDA.volt.NexRecieve = buffer;
          LDA.volt.CalLowRead = LDA.volt.NexRecieve.toFloat();

          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the volt 50 and average the samples

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

          }

          LDA.volt.calibrated = calibration(LDA.volt.filteredSlow, LDA.volt.calGain, LDA.volt.calOffset);
          LDA.volt.CalLowMeas = LDA.volt.calibrated;//store the measured high voltage value

          String LDA_voltL = "tVcalSenL.txt=\"" + String(LDA.volt.CalLowMeas, 3) + "\"";
          DBserial.println(LDA_voltL);
          HWserial.print(LDA_voltL);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of the if key pad enter
        
      }//end of while CalVoltLowFlag == 1

      while (CalVoffSetFlag == 1) { //volt offset text box pressed flag variable

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalVoffSetFlag = 0; // set flag to 0
          CalVoffSet.setValue(CalVoffSetFlag); // set nex variable to 0
          delay(100);

          memset(buffer, 0, sizeof(buffer));  // Clear the buffer
          tVoffSet.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDA.volt.NexRecieve = buffer;
          LDA.volt.offsetRead = LDA.volt.NexRecieve.toFloat();

          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the measured volt and average the samples

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

          }

          LDA.volt.calibrated = calibration(LDA.volt.filteredSlow, LDA.volt.calGain, LDA.volt.calOffset);
          LDA.volt.offsetMeas = LDA.volt.calibrated;//store the measured high voltage value

          String LDA_voltOffset = "tVcalSenL.txt=\"" + String(LDA.volt.offsetMeas, 3) + "\"";
          DBserial.println(LDA_voltOffset);
          HWserial.print(LDA_voltOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDA_voltOffset = "tVcalSenH.txt=\"" + String(LDA.volt.offsetMeas, 3) + "\"";
          DBserial.println(LDA_voltOffset);
          HWserial.print(LDA_voltOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of "if (KPE == 1)"

      }//end of "while (CalVoffSetFlag == 1)"

      while (CalAmpHighFlag == 1) {

        DBserial.println("CalSetCurrentHigh == true");
        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");
          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalAmpHighFlag = 0;
          CalSetAmpHigh.setValue(CalAmpHighFlag);//set the variable back to 0 (CalSetAmpHigh)
          delay(100);

          tIcalSetH.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDA.current.NexRecieve = buffer;
          LDA.current.CalHighRead = LDA.current.NexRecieve.toFloat();

          LDA.SetPoint.CalHighMeas = LDA.current.NexRecieve.toFloat();
          LDA.SetPoint.CalHighMeas = (LDA.SetPoint.CalHighMeas / LDA.CurrentMax) * 4095;

          DBserial.println(LDA.current.NexRecieve);


          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the current and average the samples

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

          }

          LDA.current.calibrated = calibration(LDA.current.filteredSlow, LDA.current.calGain, LDA.current.calOffset);
          LDA.current.CalHighMeas = LDA.current.calibrated;//store the measured high current value


          String LDA_currentH = "tIcalSenH.txt=\"" + String(LDA.current.CalHighMeas, 3) + "\"";
          DBserial.println(LDA_currentH);
          HWserial.print(LDA_currentH);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);


        }//end of the if key pad enter and current high set text box statement
      }//end while CalSetAmpHigh == true

      while (CalAmpLowFlag == 1) {

        DBserial.println("CalAmpLowFlag == 1");

        KPE.getValue(&KPEFlag);

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");


          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalAmpLowFlag = 0;
          CalSetAmpLow.setValue(CalAmpLowFlag);
          delay(100);

          tIcalSetL.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDA.current.NexRecieve = buffer;
          LDA.current.CalLowRead = LDA.current.NexRecieve.toFloat();

          LDA.SetPoint.CalLowMeas =  LDA.current.NexRecieve.toFloat();
          LDA.SetPoint.CalLowMeas = (LDA.SetPoint.CalLowMeas / LDA.CurrentMax) * 4095;

          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the current 50 and average the samples

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

          }

          LDA.current.calibrated = calibration(LDA.current.filteredSlow, LDA.current.calGain, LDA.current.calOffset);
          LDA.current.CalLowMeas = LDA.current.calibrated;//store the measured high current value

          String LDA_currentL = "tIcalSenL.txt=\"" + String(LDA.current.CalLowMeas, (3 - LDA.current.range)) + "\"";
          DBserial.println(LDA_currentL);
          HWserial.print(LDA_currentL);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of the if key pad enter and current high set text box statement

      }// end CalAmpHighFlag == 1

      while (CalIoffSetFlag == 1) { //current offset text box pressed flag variable

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          CalIoffSetFlag = 0; // set flag to 0
          CalIoffSet.setValue(CalIoffSetFlag); // set nex variable to 0

          tIoffSet.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDA.current.NexRecieve = buffer;
          LDA.current.offsetRead = LDA.current.NexRecieve.toFloat();

          LDA.SetPoint.offsetMeas = LDA.current.NexRecieve.toFloat();
          LDA.SetPoint.offsetMeas = (LDA.SetPoint.offsetMeas / LDA.CurrentMax) * 4095;


          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the measured current and average the samples

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

          }

          LDA.current.calibrated = calibration(LDA.current.filteredSlow, LDA.current.calGain, LDA.current.calOffset);
          LDA.current.offsetMeas = LDA.current.calibrated;//store the measured high currentage value

          String LDA_currentOffset = "tIcalSenL.txt=\"" + String(LDA.current.offsetMeas, 3) + "\"";
          DBserial.println(LDA_currentOffset);
          HWserial.print(LDA_currentOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDA_currentOffset = "tIcalSenH.txt=\"" + String(LDA.current.offsetMeas, 3) + "\"";
          DBserial.println(LDA_currentOffset);
          HWserial.print(LDA_currentOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of "if (KPE == 1)"

      }//end of "while (CalIoffSetFlag == 1)"

    }//end of while LDA Calibration loop


    //****************************************************************************************************************

    if (LDBCal == 1 && LDACal == 0) {

      // turn off load B

      LDA_OnOff_State = 0;
      Wire.beginTransmission(LDA_ADD); //U1B
      Wire.write(onOffStateChange);
      Wire.write(LDA_OnOff_State);   // sends instruction byte
      Wire.endTransmission();     // stop transmitting

      dsbCalonOff.setValue(0);


      LDB.volt.range = 0;
      LDB.current.range = 0;
      LDB_Range_Cal_Coeff();

      HWserial.print("bIrangeCal.txt=");  // Update the nex display
      HWserial.print("\"");
      HWserial.print("0.35A");  // Update the nex display
      HWserial.print("\"");
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      LDB.CurrentMax = 0.35;

      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(currentRangeChange);
      Wire.write(0);   // sends instruction byte  - High range set
      Wire.endTransmission();     // stop transmitting

      DBserial.println(LDB.volt.range);
      HWserial.print("bVrangeCal.txt=");  // Update the nex display
      HWserial.print("\"");
      HWserial.print("400V");  // Update the nex display
      HWserial.print("\"");
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(voltRangeChange);
      Wire.write(1);   // sends instruction byte  - Set digital pot reference to ground
      Wire.write(LDB.volt.range);
      Wire.endTransmission();     // stop transmitting

      delay(500);

      Wire.beginTransmission(potADD_2); //U1B
      Wire.write(potInstrucSelA);   // sends instruction byte
      Wire.write(Vamp_Range_High);  // sends potentiometer value byte
      Wire.endTransmission();     // stop transmitting

      Wire.beginTransmission(potADD_2); //U1B
      Wire.write(potInstrucSelB);   // sends instruction byte
      Wire.write(Vamp_Range_High);  // sends potentiometer value byte
      Wire.endTransmission();     // stop transmitting

      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(voltRangeChange);
      Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
      Wire.write(LDB.volt.range);
      Wire.endTransmission();     // stop transmitting

    }

    while (LDBCal == 1) {

      DBserial.println("LDBCal == true");
      CurrentPage = currentNexPage();
      dsbCalSetB.getValue(&LDBCal);

       DBserial.println("LDB.volt.range");
    DBserial.println(LDB.volt.range);

      // ********************Load B ONOFF Button Check and Load Update

      LDB.Button.StateNow = digitalRead(LDB_PB);
      DBserial.println("LDB.Button.StateNow");
      DBserial.println(LDB.Button.StateNow );


      if (LDB.Button.StateNow == false && LDB.Button.StateLast == false) { // check if there has been a state change in the push button

        DBserial.println("button press detected");
        LDB.Button.StateLast = true;
        LoadB_On_Off_BState_Cap ^= 1; // toggle the state of the nex on off button
        LoadB_ON_OFF.setValue(LoadB_On_Off_BState_Cap);

      }

      if (LDB.Button.StateNow == true && LDB.Button.StateLast == true) {

        LDB.Button.StateLast = false;

      }

      dsbCalonOff.getValue(&LoadB_On_Off_BState_Cap);
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

      //******************  Check Current Set Point Buttons

      dsbCaLIsetLow.getValue(&dsbCaLIset);

      if (dsbCaLIset == 1) {

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(SetPointChange);
        Wire.write(500 & 0xFF);
        Wire.write(500 >> 8 & 0xFF);
        Wire.endTransmission();     // stop transmitting

      }

      else {

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(SetPointChange);
        Wire.write(3500 & 0xFF);
        Wire.write(3500 >> 8 & 0xFF);
        Wire.endTransmission();     // stop transmitting

      }


      bVrangeCal.getValue(&bVrangeCalFlag); // dual state button current state check (current range)

      if (bVrangeCalFlag == 1) {

        bVrangeCalFunc();
        delay(250);
        bVrangeCalFlag = 0;
        bVrangeCal.setValue(bVrangeCalFlag);

      }

      bIrangeCal.getValue(&bIrangeCalFlag); // dual state button current state check (voltage range)

      if (bIrangeCalFlag == 1) {

        bIrangeCalFunc();
        delay(250);
        bIrangeCalFlag = 0;
        bIrangeCal.setValue(bIrangeCalFlag);
      }

      bcaliCurrSlope.getValue(&bcaliCurrSlopeFlag); // dual state button current state check (execute slope calibration)

      if (bcaliCurrSlopeFlag == 1) {

        delay(250);
        bcaliCurrSlopeFunc();
        bcaliCurrSlopeFlag = 0;
        bcaliCurrSlope.setValue(bcaliCurrSlopeFlag);


      }

      bcaliCurrOff.getValue(&bcaliCurrOffFlag); // dual state button current state check (execute slope calibration)

      if (bcaliCurrOffFlag == 1) {

        delay(250);
        bcaliCurrentOffSetFunc();
        bcaliCurrOffFlag = 0;
        bcaliCurrOff.setValue(bcaliCurrOffFlag);


      }

      // bcaliCurrentOffSetFunc();
      bcaliVoltSlope.getValue(&bcaliVoltSlopeFlag);

      if (bcaliVoltSlopeFlag == 1) {

        delay(250);
        bcaliVoltSlopeFunc();
        bcaliVoltSlopeFlag = 0;
        bcaliVoltSlope.setValue(bcaliVoltSlopeFlag);

      }

      bcaliVoltOff.getValue(&bcaliVoltOffFlag);

      if (bcaliVoltOffFlag == 1) {

        delay(250);
        bcaliVoltOffSetFunc();
        bcaliVoltOffFlag = 0;
        bcaliVoltOff.setValue(bcaliVoltOffFlag);

      }

      BcalVDef.getValue(&BcalVDefFlag);

      if (BcalVDefFlag == 1) {

        delay(250);
        bcaliVoltSlopeFunc();
        bcaliVoltOffSetFunc();
        BcalVDefFlag = 0;
        BcalVDef.setValue(BcalVDefFlag);

      }

      BcalIDef.getValue(&BcalIDefFlag);

      if (BcalIDefFlag == 1) {

        delay(250);
        bcaliCurrSlopeFunc();
        bcaliCurrentOffSetFunc();
        BcalIDefFlag = 0;
        BcalIDef.setValue(BcalIDefFlag);
      }


      if (CurrentPage == 5) { //if the current page is page 4 (the key pad) don't break the loop
        CurrentPage = 4;

      }

      if (CurrentPage != 4) { //check for nex page change and break the loop

        DBserial.println("break");
        break;

      }

      //reset all of the calibration button flags

      CalVoltHighFlag = 0;
      CalVoltLowFlag = 0;
      CalVoffSetFlag = 0;
      CalAmpLowFlag = 0;
      CalAmpHighFlag = 0;
      CalIoffSetFlag = 0;
      KPEFlag = 0;


      //************************Hi volt set Flag check

      CalSetVoltHigh.getValue(&CalVoltHighFlag);  // Read the text on the object and store it on the buffer

      //************************Low volt set Flag check

      CalSetVoltLow.getValue(&CalVoltLowFlag);  // Read the text on the object and store it on the buffer

      //************************Volt offset set flag

      CalVoffSet.getValue(&CalVoffSetFlag); // get the text box pressed variable state.(cal current offset text box entry)


      //************************High Current set Flag check

      CalSetAmpHigh.getValue(&CalAmpHighFlag);  // Read the text on the object and store it on the buffer

      //************************Low Current set Flag check

      CalSetAmpLow.getValue(&CalAmpLowFlag);  // Read the text on the object and store it on the buffer

      //************************Current offset set flag

      CalIoffSet.getValue(&CalIoffSetFlag); // get the text box pressed variable state.(cal current offset text box entry)


      while (CalVoltHighFlag == 1) {

        DBserial.println("CalVoltHighFlag == 1");

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalVoltHighFlag = 0;
          CalSetVoltHigh.setValue(CalVoltHighFlag);
          delay(100);

          tVcalSetH.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDB.volt.NexRecieve = buffer;
          LDB.volt.CalHighRead = LDB.volt.NexRecieve.toFloat();
          DBserial.println("LDB.volt.NexRecieve = " + LDB.volt.NexRecieve);

          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the volt 50 and average the samples

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

            LDB.volt = AVG_Filter(LDB.volt, LDB.volt.capVal);  // Filter ADC Reading
          }

          LDB.volt.calibrated = calibration(LDB.volt.filteredSlow, LDB.volt.calGain, LDB.volt.calOffset);
          LDB.volt.CalHighMeas = LDB.volt.calibrated;//store the measured high voltage value

          String LDB_voltH = "tVcalSenH.txt=\"" + String(LDB.volt.CalHighMeas, 3) + "\"";
          DBserial.println(LDB_voltH);
          HWserial.print(LDB_voltH);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of the if key pad enter
      }//end of while CalVoltHighFlag == 1

      while (CalVoltLowFlag == 1) {

        DBserial.println("CalSetVoltLow  == true");

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalVoltLowFlag = 0;
          CalSetVoltLow.setValue(CalVoltLowFlag);
          delay(100);

          tVcalSetL.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDB.volt.NexRecieve = buffer;
          LDB.volt.CalLowRead = LDB.volt.NexRecieve.toFloat();

          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the volt 50 and average the samples

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

          }

          LDB.volt.calibrated = calibration(LDB.volt.filteredSlow, LDB.volt.calGain, LDB.volt.calOffset);
          LDB.volt.CalLowMeas = LDB.volt.calibrated;//store the measured high voltage value

          String LDB_voltL = "tVcalSenL.txt=\"" + String(LDB.volt.CalLowMeas, 3) + "\"";
          DBserial.println(LDB_voltL);
          HWserial.print(LDB_voltL);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of the if key pad enter
      }//end of while CalVoltLowFlag == 1

      while (CalVoffSetFlag == 1) { //volt offset text box pressed flag variable

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalVoffSetFlag = 0; // set flag to 0
          CalVoffSet.setValue(CalVoffSetFlag); // set nex variable to 0
          delay(100);

          memset(buffer, 0, sizeof(buffer));  // Clear the buffer
          tVoffSet.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDB.volt.NexRecieve = buffer;
          LDB.volt.offsetRead = LDB.volt.NexRecieve.toFloat();

          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the measured volt and average the samples

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

          }

          LDB.volt.calibrated = calibration(LDB.volt.filteredSlow, LDB.volt.calGain, LDB.volt.calOffset);
          LDB.volt.offsetMeas = LDB.volt.calibrated;//store the measured high voltage value

          String LDB_voltOffset = "tVcalSenL.txt=\"" + String(LDB.volt.offsetMeas, 3) + "\"";
          DBserial.println(LDB_voltOffset);
          HWserial.print(LDB_voltOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB_voltOffset = "tVcalSenH.txt=\"" + String(LDB.volt.offsetMeas, 3) + "\"";
          DBserial.println(LDB_voltOffset);
          HWserial.print(LDB_voltOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of "if (KPE == 1)"

      }//end of "while (CalVoffSetFlag == 1)"

      while (CalAmpHighFlag == 1) {

        DBserial.println("CalSetCurrentHigh == true");
        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");
          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalAmpHighFlag = 0;
          CalSetAmpHigh.setValue(CalAmpHighFlag);//set the variable back to 0 (CalSetAmpHigh)
          delay(100);

          tIcalSetH.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDB.current.NexRecieve = buffer;
          LDB.current.CalHighRead = LDB.current.NexRecieve.toFloat();

          LDB.SetPoint.CalHighMeas = LDB.current.NexRecieve.toFloat();
          LDB.SetPoint.CalHighMeas = (LDB.SetPoint.CalHighMeas / LDB.CurrentMax) * 4095;

          DBserial.println(LDB.current.NexRecieve);


          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the current and average the samples

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

          }

          LDB.current.calibrated = calibration(LDB.current.filteredSlow, LDB.current.calGain, LDB.current.calOffset);
          LDB.current.CalHighMeas = LDB.current.calibrated;//store the measured high current value


          String LDB_currentH = "tIcalSenH.txt=\"" + String(LDB.current.CalHighMeas, 3) + "\"";
          DBserial.println(LDB_currentH);
          HWserial.print(LDB_currentH);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);


        }//end of the if key pad enter and current high set text box statement
      }//end while CalSetAmpHigh == true

      while (CalAmpLowFlag == 1) {

        DBserial.println("CalAmpLowFlag == 1");

        KPE.getValue(&KPEFlag);

        if (KPEFlag == 1) {

          DBserial.println("KPEFlag == 1");


          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          delay(100);
          CalAmpLowFlag = 0;
          CalSetAmpLow.setValue(CalAmpLowFlag);
          delay(100);

          tIcalSetL.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDB.current.NexRecieve = buffer;
          LDB.current.CalLowRead = LDB.current.NexRecieve.toFloat();

          LDB.SetPoint.CalLowMeas =  LDB.current.NexRecieve.toFloat();
          LDB.SetPoint.CalLowMeas = (LDB.SetPoint.CalLowMeas / LDB.CurrentMax) * 4095;



          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the current 50 and average the samples

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

          }

          LDB.current.calibrated = calibration(LDB.current.filteredSlow, LDB.current.calGain, LDB.current.calOffset);
          LDB.current.CalLowMeas = LDB.current.calibrated;//store the measured high current value

          String LDB_currentL = "tIcalSenL.txt=\"" + String(LDB.current.CalLowMeas, 3) + "\"";
          DBserial.println(LDB_currentL);
          HWserial.print(LDB_currentL);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of the if key pad enter and current high set text box statement

      }// end CalAmpHighFlag == 1

      while (CalIoffSetFlag == 1) { //current offset text box pressed flag variable

        KPE.getValue(&KPEFlag); // get the text box pressed variable state.(cal current offset text box entry)

        if (KPEFlag == 1) {

          KPEFlag = 0;
          KPE.setValue(KPEFlag);
          CalIoffSetFlag = 0; // set flag to 0
          CalIoffSet.setValue(CalIoffSetFlag); // set nex variable to 0

          tIoffSet.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
          LDB.current.NexRecieve = buffer;
          LDB.current.offsetRead = LDB.current.NexRecieve.toFloat();

          LDB.SetPoint.offsetMeas = LDB.current.NexRecieve.toFloat();
          LDB.SetPoint.offsetMeas = (LDB.SetPoint.offsetMeas / LDB.CurrentMax) * 4095;


          for (int i = 0; i <= (MAF_sizeSlow); ++i) { //sample the measured current and average the samples

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

          }

          LDB.current.calibrated = calibration(LDB.current.filteredSlow, LDB.current.calGain, LDB.current.calOffset);
          LDB.current.offsetMeas = LDB.current.calibrated;//store the measured high currentage value

          String LDB_currentOffset = "tIcalSenL.txt=\"" + String(LDB.current.offsetMeas, 3) + "\"";
          DBserial.println(LDB_currentOffset);
          HWserial.print(LDB_currentOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB_currentOffset = "tIcalSenH.txt=\"" + String(LDB.current.offsetMeas, 3) + "\"";
          DBserial.println(LDB_currentOffset);
          HWserial.print(LDB_currentOffset);  // Update the nex display
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }//end of "if (KPE == 1)"

      }//end of "while (CalIoffSetFlag == 1)"

    }//end of while LDB Calibration loop

  }//end of current page while loop

}//end of function
