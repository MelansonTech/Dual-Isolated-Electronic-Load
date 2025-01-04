void LoadButtonPressCheckFunc(void) {

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

      DBserial.println("onOffStateChange");
      DBserial.println(LDA_OnOff_State);

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
      
      LDB_OnOff_State = LoadB_On_Off_BState_Cap;
      
      Wire.beginTransmission(LDB_ADD); //U1B
      Wire.write(onOffStateChange);
      Wire.write(LDB_OnOff_State);   // sends instruction byte
      Wire.endTransmission();     // stop transmitting

    }

  }
