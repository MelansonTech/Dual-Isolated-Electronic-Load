
void SetVoltageRangeFunc(int Load) {

  //************************Load A Voltage Range Update

  if (Load == 0) {

    switch (LDA.volt.range) {

      case 0:

        //set the current range

        LDA.current.range = 0;

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

        nexTextboxWriteFunc(nexTextBoxAddressBuff, maxCurrentRangeLow, 0);

        SetPointMinMaxUpdate();

        //set the voltage range

        SetDigialPotResFunc(potADD_1, LDA_ADD, LDA.volt.range, Vamp_Range_High);// set the digi pot val

        //update text box for current nex page

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDA_B_VR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bVrangeCal.txt=";

        }

        nexTextboxWriteFunc(nexTextBoxAddressBuff, VinMaxRangeHigh, 0);

        break;

      case 1:

        if (LDA.current.range > 1) {

          //set the current range

          LDA.current.range = 1;

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

          SetPointMinMaxUpdate();
          nexTextboxWriteFunc(nexTextBoxAddressBuff, maxCurrentRangeMed, 0);

        }

        //set the voltage range

        SetDigialPotResFunc(potADD_1, LDA_ADD,LDA.volt.range, Vamp_Range_Med);

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDA_B_VR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bVrangeCal.txt=";

        }

        nexTextboxWriteFunc(nexTextBoxAddressBuff, VinMaxRangeMed, 0);

        break;

      case 2:

        //set the voltage range

        SetDigialPotResFunc(potADD_1, LDA_ADD, LDA.volt.range, Vamp_Range_Low);

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDA_B_VR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bVrangeCal.txt=";

        }

        nexTextboxWriteFunc(nexTextBoxAddressBuff, VinMaxRangeLow, 0);

        break;

    }//end of LDA volt switch case

    LDA_Range_Cal_Coeff(); // update current and voltage cal coeff

  }

  //************************Load B Voltage Range Update

  if (Load == 1) {

    switch (LDB.volt.range) {

      case 0:

        //set the current range

        LDB.current.range = 0;

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

        SetPointMinMaxUpdate();
        nexTextboxWriteFunc(nexTextBoxAddressBuff, LDB.CurrentMax, 0);


        //set the voltage range

        SetDigialPotResFunc(potADD_2, LDB_ADD, LDB.volt.range, Vamp_Range_High);// set the digi pot val

        //update text box for current nex page

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDB_B_VR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bVrangeCal.txt=";

        }

        nexTextboxWriteFunc(nexTextBoxAddressBuff, VinMaxRangeHigh, 0);

        break;

      case 1:

        if (LDB.current.range > 1) {

          //set the current range

          LDB.current.range = 1;

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

          SetPointMinMaxUpdate();
          nexTextboxWriteFunc(nexTextBoxAddressBuff, LDB.CurrentMax, 0);

        }

        //set the voltage range

        SetDigialPotResFunc(potADD_2, LDB_ADD, LDB.volt.range, Vamp_Range_Med);

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDB_B_VR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bVrangeCal.txt=";

        }

        nexTextboxWriteFunc(nexTextBoxAddressBuff, VinMaxRangeMed, 0);

        break;

      case 2:

        //set the voltage range

        SetDigialPotResFunc(potADD_2, LDB_ADD, LDB.volt.range, Vamp_Range_Low);

        if (CurrentPage == 3) {

          nexTextBoxAddressBuff = "LDB_B_VR.txt=";

        }

        if (CurrentPage == 4) {

          nexTextBoxAddressBuff = "bVrangeCal.txt=";

        }

        nexTextboxWriteFunc(nexTextBoxAddressBuff, VinMaxRangeLow, 0);

        break;

    }//end of LDB volt switch case

    LDB_Range_Cal_Coeff(); // update current and voltage cal coeff

  }
}
