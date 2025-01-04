void SetCurrentRangeFunc(int Load) {

  //************************Load A Voltage Range Update

  if (LDA.current.range > LDA.volt.range) {

    LDA.current.range  = LDA.volt.range;

  }

  if (Load == 0) {

    switch (LDA.current.range) {

      case 0:

        //set the current range

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(0);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDA_B_IR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bIrangeCal.txt=";

        }

        LDA.CurrentMax = maxCurrentRangeLow;
        nexTextboxWriteFunc(nexTextBoxAddressBuff, LDA.CurrentMax, 0);


        break;

      case 1:

        //set the current range

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(1);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDA_B_IR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bIrangeCal.txt=";

        }

        LDA.CurrentMax = maxCurrentRangeMed;
        nexTextboxWriteFunc(nexTextBoxAddressBuff, LDA.CurrentMax, 0);

      case 2:

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(2);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDA_B_IR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bIrangeCal.txt=";

        }

        LDA.CurrentMax = maxCurrentRangeHigh;
        nexTextboxWriteFunc(nexTextBoxAddressBuff, LDA.CurrentMax, 0);
    }//end of LDA current range switch case


  }// end if load A

  LDA_Range_Cal_Coeff(); // update current and voltage cal coeff


  //************************Load B Current Range Update

  if (Load == 1) {

    if (LDA.current.range > LDA.volt.range) {

      LDA.current.range  = LDA.volt.range;

    }

    switch (LDA.current.range) {

      case 0:

        //set the current range

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(0);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDB_B_IR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bIrangeCal.txt=";

        }

        LDB.CurrentMax = maxCurrentRangeLow;
        nexTextboxWriteFunc(nexTextBoxAddressBuff, LDB.CurrentMax, 0);

        break;

      case 1:

        //set the current range

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(1);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDB_B_IR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bIrangeCal.txt=";

        }

        LDB.CurrentMax = maxCurrentRangeMed;
        nexTextboxWriteFunc(nexTextBoxAddressBuff, LDB.CurrentMax, 0);

      case 2:

        //set the current range

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(1);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDB_B_IR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bIrangeCal.txt=";

        }

        LDB.CurrentMax = maxCurrentRangeHigh;
        nexTextboxWriteFunc(nexTextBoxAddressBuff, LDB.CurrentMax, 0);

    }//end of LDB Current switch case
    
    LDB_Range_Cal_Coeff(); // update current and voltage cal coeff
    
  }//end of if load B
}
