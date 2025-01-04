void EncoderLoadSetFunc(void) {

  //********************* update Load A ** Encoder set point Update

  newPositionA = LDA_Knob.read() / 4;         // get encoder postition

  if (newPositionA != oldPositionA) {       // check to see if position has changed since the last check

    LDA.ENCODER.capVal = encoder_position_move(newPositionA, oldPositionA, LDA.ENCODER.capVal);

    switch (LDA.Mode.range)
    {
      case 0://CC Mode

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

        LDA_SP = "tsetA.txt=\"" + String(LDA.SetPoint.calibrated, 2) + LDA.Units + "\"" ;
        DBserial.println(LDA_SP);
        HWserial.print(LDA_SP);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDA.SetPoint.calibrated = (LDA.SetPoint.calibrated / LDA.CurrentMax) * 4095;
        LDA.SetPoint.capVal = (int)calibration(LDA.SetPoint.calibrated, LDA.SetPoint.calGain, LDA.SetPoint.calOffset);
        break;

      case 1://CR mode

        LDA.ENCODER.capVal = constrain(LDA.ENCODER.capVal, 0, 100);

        oldPositionA = newPositionA;

        HWserial.print("j0.val=");  // Update the nex display with the new LDA Set Point
        HWserial.print(LDA.ENCODER.capVal);  // This is the value you want to send to that object and atribute mentioned before.
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDA.SetPoint.calibrated = (((LDA.ENCODER.capVal * (LDA.CurrentMax - LDA.CurrentMin)) / 100) + LDA.CurrentMin);
        DBserial.println("LDA.setPoint.setVal");
        DBserial.println(LDA.SetPoint.setVal);


        LDA_SP  = "tsetA.txt=\"" + String(LDA.SetPoint.calibrated, 0) + LDA.Units + "\"" ;
        DBserial.println(LDA_SP);
        HWserial.print(LDA_SP);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDA.SetPoint.capVal = (int)LDA.SetPoint.calibrated;
        break;

      case 2://CP Mode

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

        LDA_SP = "tsetA.txt=\"" + String(LDA.SetPoint.calibrated, 0) + LDA.Units + "\"" ;
        DBserial.println(LDA_SP);
        HWserial.print(LDA_SP);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDA.SetPoint.capVal = LDA.SetPoint.calibrated;
        break;

    }
    
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

    switch (LDB.Mode.range)
    {

      case 0://CC Mode

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

        LDB_SP = "tsetB.txt=\"" + String(LDB.SetPoint.calibrated, 2) + LDB.Units + "\"" ;
        DBserial.println(LDB_SP);
        HWserial.print(LDB_SP);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDB.SetPoint.calibrated = (LDB.SetPoint.calibrated / LDB.CurrentMax) * 4095;
        LDB.SetPoint.capVal = (int)calibration(LDB.SetPoint.calibrated, LDB.SetPoint.calGain, LDB.SetPoint.calOffset);

        break;

      case 1://CR mode

        LDB.ENCODER.capVal = constrain(LDB.ENCODER.capVal, 0, 100);
        oldPositionB = newPositionB;

        HWserial.print("j1.val=");  // Update the nex display with the new LDB Set Point
        HWserial.print(LDB.ENCODER.capVal);  // This is the value you want to send to that object and atribute mentioned before.
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDB.SetPoint.calibrated = (((LDB.ENCODER.capVal * (LDB.CurrentMax - LDB.CurrentMin)) / 100) + LDB.CurrentMin);
        DBserial.println("LDB.setPoint.setVal");
        DBserial.println(LDB.SetPoint.setVal);

        LDB_SP = "tsetB.txt=\"" + String(LDB.SetPoint.calibrated, 0) + LDB.Units + "\"" ;
        DBserial.println(LDB_SP);
        HWserial.print(LDB_SP);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDB.SetPoint.capVal = LDB.SetPoint.calibrated;

        break;
        
      case 2:// CP mode
      
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

        LDB_SP = "tsetB.txt=\"" + String(LDB.SetPoint.calibrated, 0) + LDB.Units + "\"" ;
        DBserial.println(LDB_SP);
        HWserial.print(LDB_SP);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        LDB.SetPoint.capVal = LDB.SetPoint.calibrated;
        break;

    }

    DBserial.println("LDB.current.capVal");
    DBserial.println(LDB.SetPoint.capVal);

    Wire.beginTransmission(LDB_ADD); //U1B
    Wire.write(SetPointChange);
    Wire.write(LDB.SetPoint.capVal & 0xFF);
    Wire.write(LDB.SetPoint.capVal >> 8 & 0xFF);
    Wire.endTransmission();     // stop transmitting

  }//end of if encoder B position changes statement

}
