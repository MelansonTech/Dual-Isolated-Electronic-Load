void SetRangeFunc(int VoltageRange, int Load) {

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

        nexTextBoxAddressBuff = "LDA_B_VR.txt=";
        nexTextboxWrite(nexTextBoxAddressBuff, VinMaxRangeHigh);

        SetDigialPotResFunc(int potADD_1, int LDA_ADD, LDA.volt.range, int Vamp_Range_High);

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

        HWserial.print("LDA_B_VR.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("60V");  // Update the nex display
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
        Wire.write(Vamp_Range_Med);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(potADD_1); //U1B
        Wire.write(potInstrucSelB);   // sends instruction byte
        Wire.write(Vamp_Range_Med);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(voltRangeChange);
        Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
        Wire.write(LDA.volt.range);
        Wire.endTransmission();     // stop transmitting

        break;

      case 2:


        HWserial.print("LDA_B_VR.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("20V");  // Update the nex display
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
        Wire.write(Vamp_Range_Low);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(potADD_1); //U1B
        Wire.write(potInstrucSelB);   // sends instruction byte
        Wire.write(Vamp_Range_Low);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(voltRangeChange);
        Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
        Wire.write(LDA.volt.range);
        Wire.endTransmission();     // stop transmitting

        break;

    }//end of LDA volt switch case

    LDA_Range_Cal_Coeff(); // update current and voltage cal coeff


  }
}
