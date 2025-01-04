void SetVoltageRangeFunc(int VoltageRange, int Load) {

    //************************Load A Voltage Range Update
    
  if (Load == 0) {

    switch (VoltageRange) {

      case 0:

        //set the current range

        LDA.current.range = 0;

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(0);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        nexTextBoxAddressBuff = "LDA_B_IR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, maxCurrentRangeLow);

        LDA.CurrentMax = maxCurrentRangeLow;

        //set the voltage range

        SetDigialPotResFunc(potADD_1, LDA_ADD, LDA.volt.range, Vamp_Range_High);
        nexTextBoxAddressBuff = "LDA_B_VR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, VinMaxRangeHigh);

        break;

      case 1:

        if (LDA.current.range > 1) {

          //set the current range

          LDA.current.range = 1;

          Wire.beginTransmission(LDA_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(1);   // sends instruction byte  - Low range set
          Wire.endTransmission();     // stop transmitting

          nexTextBoxAddressBuff = "LDA_B_IR.txt=";
          LDA.CurrentMax = maxCurrentRangeMed;
          nexTextboxWrite(nexTextBoxAddressBuff, maxCurrentRangeMed);

        }

        //set the voltage range

        SetDigialPotResFunc(potADD_1, LDA_ADD, LDA.volt.range, Vamp_Range_Med);
        nexTextBoxAddressBuff = "LDA_B_VR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, VinMaxRangeMed);

        break;

      case 2:

        //set the voltage range

        SetDigialPotResFunc(potADD_1, LDA_ADD, LDA.volt.range, Vamp_Range_Low);
        nexTextBoxAddressBuff = "LDA_B_VR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, VinMaxRangeLow);

        break;

    }//end of LDA volt switch case

    LDA_Range_Cal_Coeff(); // update current and voltage cal coeff   
     
  }

    //************************Load B Voltage Range Update
    
    if (Load == 1) {

    switch (VoltageRange) {

      case 0:

        //set the current range

        LDB.current.range = 0;

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(0);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        nexTextBoxAddressBuff = "LDB_B_IR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, maxCurrentRangeLow);

        LDB.CurrentMax = maxCurrentRangeLow;

        //set the voltage range

        SetDigialPotResFunc(potADD_2, LDB_ADD, LDB.volt.range, Vamp_Range_High);
        nexTextBoxAddressBuff = "LDB_B_VR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, VinMaxRangeHigh);

        break;

      case 1:

        if (LDB.current.range > 1) {

          //set the current range

          LDB.current.range = 1;

          Wire.beginTransmission(LDB_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(1);   // sends instruction byte  - Low range set
          Wire.endTransmission();     // stop transmitting

          nexTextBoxAddressBuff = "LDB_B_IR.txt=";
          LDB.CurrentMax = maxCurrentRangeMed;
          nexTextboxWrite(nexTextBoxAddressBuff, maxCurrentRangeMed);

        }

        //set the voltage range

        SetDigialPotResFunc(potADD_2, LDB_ADD, LDB.volt.range, Vamp_Range_Med);
        nexTextBoxAddressBuff = "LDB_B_VR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, VinMaxRangeMed);

        break;

      case 2:

        //set the voltage range

        SetDigialPotResFunc(potADD_2, LDB_ADD, LDB.volt.range, Vamp_Range_Low);
        nexTextBoxAddressBuff = "LDB_B_VR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, VinMaxRangeLow);

        break;

    }//end of LDB volt switch case

    LDB_Range_Cal_Coeff(); // update current and voltage cal coeff
    
  }
}
