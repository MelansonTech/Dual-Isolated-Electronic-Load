
void Load_Monitor_Loop(void) {

  // declare variables to govern encoder acceleration

  int KNOB_A_TMR_REF = millis();
  int KNOB_B_TMR_REF = millis();
  int KNOB_A_TMR_OUT = millis();
  int KNOB_B_TMR_OUT = millis();
  int pulsecountA = 0;
  int pulsecountB = 0;
  newPositionA = oldPositionA;
  newPositionB = oldPositionB;
  MAF_sizeSlow = 49;
  CurrentPage = currentNexPage();
  uint32_t LoadA_On_Off_BState_Cap = 0;
  uint32_t LoadB_On_Off_BState_Cap = 0;
  
 

  while (CurrentPage == 2) { // load monitor loop

  // Check for user load on/off request and update and send the command to the load
  
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

//  LoadB_ON_OFF.getValue(&LoadB_On_Off_BState_Cap);
//  
//  if (LDB_OnOff_State != LoadB_On_Off_BState_Cap)
//  {
//    
//  LDB_OnOff_State = LoadB_On_Off_BState_Cap;
//  Wire.beginTransmission(LDB_ADD); //U1B
//  Wire.write(onOffStateChange);
//  Wire.write(LDB_OnOff_State);   // sends instruction byte 
//  Wire.endTransmission();     // stop transmitting 
//  
//  }

    // The Below section Checks for a encoder button pushes and turns the load on and off

    DBserial.println("Load Monitor");
    //PageIndex.getValue(&CurrentPage);
    DBserial.println(CurrentPage);
    // the below sections captures the encoder changes and writes proportional value to the DAC. This is used to control current of the corresponding LOAD


    //update Load A and B set points
    newPositionA = LDA_Knob.read() / 4;         // get encoder postition

    if (pulsecountA < 3) {

      KNOB_A_TMR_REF = millis();

    }

    if (newPositionA != oldPositionA) {       // check to see if position has changed since the last check

      LDA.SetPoint.capVal = encoder_position_move(newPositionA, oldPositionA, LDA.SetPoint.capVal);

      pulsecountA++;

      KNOB_A_TMR_OUT = millis();

      if (KNOB_A_TMR_OUT > (KNOB_A_TMR_REF + 1500)) {

        pulsecountA = 0;

      }

      if (pulsecountA > 3) {

        LDA.SetPoint.capVal += ((newPositionA - oldPositionA));

        if (KNOB_A_TMR_OUT > (KNOB_A_TMR_REF + 1200)) {

          KNOB_A_TMR_REF += 1000;

        }
      }

      LDA.SetPoint.capVal = constrain(LDA.SetPoint.capVal, 0, 100);
      oldPositionA = newPositionA;
      DBserial.println("encode LDA new pos");
      DBserial.println("LDA Val SP Change");
      //****DAC LEVEL needs to be set here

      String LDA_SP = "tsetA.txt=\"" + String(LDA.SetPoint.capVal) + "\"";
      DBserial.println(LDA_SP);
      HWserial.print(LDA_SP);  // Update the nex display with the new LDA Set Point
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);

      HWserial.print("j0.val=");  // Update the nex display with the new LDA Set Point
      HWserial.print(LDA.SetPoint.capVal);  // This is the value you want to send to that object and atribute mentioned before.
      HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
      HWserial.write(0xff);
      HWserial.write(0xff);


    }//end of if encoder A position changes statement


      //Load B Current Adjust and Display update

      // the below sections captures the encoder changes and writes proportional value to the DAC. This is used to control current of the corresponding LOAD

      newPositionB = LDB_Knob.read() / 4;         // get encoder postition

      if (pulsecountB < 3) {

        KNOB_B_TMR_REF = millis();

      }

      if (newPositionB != oldPositionB) {       // check to see if position has changed since the last check

        LDB.SetPoint.capVal = encoder_position_move(newPositionB, oldPositionB, LDB.SetPoint.capVal);

        pulsecountB++;

        KNOB_B_TMR_OUT = millis();

        if (KNOB_B_TMR_OUT > (KNOB_B_TMR_REF + 1500)) {

          pulsecountB = 0;

        }

        if (pulsecountB > 3) {

          LDB.SetPoint.capVal += ((newPositionB - oldPositionB));

          if (KNOB_B_TMR_OUT > (KNOB_B_TMR_REF + 1200)) {

            KNOB_B_TMR_REF += 1000;

          }
        }


        LDB.SetPoint.capVal = constrain(LDB.SetPoint.capVal, 0, 100);
        oldPositionB = newPositionB;
        //LDB.SetPoint.capVal = encoder_position_limit(0,100,LDB.SetPoint.capVal);

        //****DAC LEVEL needs to be set here


        String LDB_SP = "tsetB.txt=\"" + String(LDB.SetPoint.capVal) + "\"";
        DBserial.println(LDB_SP);
        HWserial.print(LDB_SP);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        HWserial.print("j1.val=");  // Update the nex display with the new LDB Set Point
        HWserial.print(LDB.SetPoint.capVal);  // This is the value you want to send to that object and atribute mentioned before.
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);
      }//end of if encoder B position changes statement


      //volt acquistion

//      LDA.volt.capVal = analogRead(LDA_Vin);
      LDA.volt = AVG_Filter(LDA.volt, LDA.volt.capVal);
      LDA.volt.calibrated = calibration(LDA.volt.filteredSlow, LDA.volt.calGain, LDA.volt.calOffset);
      LDA.volt = ValChangeDetected(LDA.volt, LDA.volt.calibrated, 0.1, 0.1); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change
      DBserial.println(LDA.volt.calibrated);


      if (LDA.volt.ChangeDetectFlag == 1) {

        String LDA_Volt = "tvoltA.txt=\"" + String(LDA.volt.calibrated, (1 + LDA.volt.range)) + "\"";
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


//      LDB.volt.capVal = analogRead(LDB_Vin);
      LDB.volt = AVG_Filter(LDB.volt, LDB.volt.capVal);
      LDB.volt.calibrated = calibration(LDB.volt.filteredSlow, LDB.volt.calGain, LDB.volt.calOffset);
      LDB.volt = ValChangeDetected(LDB.volt, LDB.volt.calibrated, 0.1, 0.1); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change

      if (LDB.volt.ChangeDetectFlag == 1) {

        String LDB_Volt = "tvoltB.txt=\"" + String(LDB.volt.calibrated, (1 + LDB.volt.range)) + "\"";
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

      //current acquistion

//      LDA.current.capVal = analogRead(LDA_Iin);
      LDA.current = AVG_Filter(LDA.current, LDA.current.capVal);
      LDA.current.calibrated = calibration(LDA.current.filteredSlow, LDA.current.calGain, LDA.current.calOffset);
      LDA.current = ValChangeDetected(LDA.current, LDA.current.calibrated, 0.01, 0.01); // check for a change in the filtered value and return the LCD print flag 1 if changed 0 if no change



      if (LDA.current.ChangeDetectFlag == 1) {

        String LDA_Current = "tcurrentA.txt=\"" + String(LDA.current.calibrated, (4 - LDA.current.range)) + "\"";
        DBserial.println(LDA_Current);
        HWserial.print(LDA_Current);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }

      //current acquistion

//      LDB.current.capVal = analogRead(LDB_Iin);
      LDB.current = AVG_Filter(LDB.current, LDB.current.capVal);
      LDB.current.calibrated = calibration(LDB.current.filteredSlow, LDB.current.calGain, LDB.current.calOffset);
      LDB.current = ValChangeDetected(LDB.current, LDB.current.calibrated, 0.01, 0.01); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change

      if (LDB.current.ChangeDetectFlag == 1) {

        String LDB_Current = "tcurrentB.txt=\"" + String(LDB.current.calibrated, (4 - LDB.current.range)) + "\"";
        DBserial.println(LDB_Current);
        HWserial.print(LDB_Current);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }

      //temp acquistion

//      LDA.temp.capVal = analogRead(PIN_LDA_TEMP);
      LDA.temp = AVG_Filter(LDA.temp, LDA.temp.capVal);
      LDA.temp.calibrated = calibration(LDA.temp.filteredSlow, LDA.temp.calGain, LDA.temp.calOffset);
      LDA.temp = ValChangeDetected(LDA.temp, LDA.temp.calibrated, 0.1, 0.1); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change


      if (LDA.temp.ChangeDetectFlag == 1) {

        String LDA_Temp = "ttempA.txt=\"" + String(LDA.temp.calibrated, 2) + "\"";
        DBserial.println(LDA_Temp);
        HWserial.print(LDA_Temp);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }



//      LDB.temp.capVal = analogRead(PIN_LDB_TEMP);
      LDB.temp = AVG_Filter(LDB.temp, LDB.temp.capVal);
      LDB.temp.calibrated = calibration(LDB.temp.filteredSlow, LDB.temp.calGain, LDB.temp.calOffset);
      LDB.temp = ValChangeDetected(LDB.temp, LDB.temp.calibrated, 0.1, 0.1); // check for a change in the filteredSlow value and return the LCD print flag 1 if changed 0 if no change

      //if (LDB.temp.calibrated > overTemp){
      //
      //          LDB_State = 0;    //if the load is on turn it off
      //          LDB_Disable();
      //          //LDB_PB_State_CAP = 0;
      //
      //}

      if (LDB.temp.ChangeDetectFlag == 1) {

        String LDB_Temp = "ttempB.txt=\"" + String(LDB.temp.calibrated, 2) + "\"";
        DBserial.println(LDB_Temp);
        HWserial.print(LDB_Temp);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);
      }
  
      if (SD_log_active == true) { // if the dual stat "log Data" button is pressed then begin logging load data to sd card

        SD_log_count += 1;
        HWserial.print("n9.val=");
        HWserial.print(SD_log_count);  // Update the nex display
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        WriteLoadDataToSD(SD_log_count);// function gathers all of the loads senors data and save it to the datalog.txt file

      }// SD logging active if end

     
  

      KPA.getValue(&KPAFlag);
      KPEFlag = 0;
      KPE.getValue(&KPEFlag); // get the text box pressed variable state.(KP Enter)

      if (KPAFlag == 1 && KPEFlag == 1) {

        DBserial.println("KPAFlag = 1 && KPEFlag == 1");


        KPAFlag = 0;
        KPA.setValue(KPAFlag);
        KPEFlag = 0;
        KPE.setValue(KPEFlag);
        newPositionA = oldPositionA;
        newPositionB = oldPositionB;

        memset(buffer, 0, sizeof(buffer));  // Clear the buffer, so we can start using it
        tsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
        LDA.SetPoint.NexRecieve = buffer;
        LDA.SetPoint.calibrated = LDA.SetPoint.NexRecieve.toFloat();
        LDA.SetPoint.calibrated = constrain(LDA.SetPoint.calibrated, 1, 100);
        LDA.SetPoint.capVal = (int)LDA.SetPoint.calibrated;

        DBserial.println(buffer);
        DBserial.println(LDA.SetPoint.NexRecieve);
        DBserial.println(LDA.SetPoint.calibrated);

        HWserial.print("tsetA.txt=");
        HWserial.print("\"");
        HWserial.print(LDA.SetPoint.calibrated, 1); // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        HWserial.print("j0.val=");
        HWserial.print(LDA.SetPoint.capVal);
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

      }  //end of KPA if statement

     

     

      KPB.getValue(&KPBFlag);
      KPEFlag = 0;
      KPE.getValue(&KPEFlag);

      if (KPBFlag == 1 && KPEFlag == 1) {

        KPBFlag = 0;
        KPB.setValue(KPBFlag);
        KPEFlag = 0;
        KPE.setValue(KPEFlag);
        newPositionA = oldPositionA;
        newPositionB = oldPositionB;

        tsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
        LDB.SetPoint.NexRecieve = buffer;
        LDB.SetPoint.calibrated = LDB.SetPoint.NexRecieve.toFloat();
        LDB.SetPoint.calibrated = constrain(LDB.SetPoint.calibrated, 1, 100);
        LDB.SetPoint.capVal = (int)LDB.SetPoint.calibrated;

        HWserial.print("tsetB.txt=");
        HWserial.print("\"");
        HWserial.print(LDB.SetPoint.calibrated, 1); // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        HWserial.print("j1.val=");
        HWserial.print(LDB.SetPoint.capVal);
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);


      }//end of KPB if statement

     
     
      CurrentPage = currentNexPage(); // check the current page status

      if (CurrentPage == 5) {

        CurrentPage = 2; //if the current page is the keypad page(page5) then remain in the monitor loop by setting the currentpage to page 2

      }

    }// while current page 2 end
    return;

  }
