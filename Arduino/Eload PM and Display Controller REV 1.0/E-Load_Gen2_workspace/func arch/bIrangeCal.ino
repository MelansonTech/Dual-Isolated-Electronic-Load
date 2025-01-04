void bIrangeCalFunc(void) {

  if (LDACal == 1) {

    LDA.current.range += 1;

    if (LDA.current.range > LDA.volt.range) {

      LDA.current.range  = 0;

    }

    switch (LDA.current.range) {

      case 0:

        HWserial.print("bIrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("0.35A");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(0);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        LDA.CurrentMax = 0.35;

        break;

      case 1:

        HWserial.print("bIrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("3A");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(1);   // sends instruction byte  -Med range set
        Wire.endTransmission();     // stop transmitting

        LDA.CurrentMax = 3; 

        break;

      case 2:

        HWserial.print("bIrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("10A");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(2);   // sends instruction byte  -High range set
        Wire.endTransmission();     // stop transmitting

        LDA.CurrentMax = 10;

        break;


    }//end of LDA current range switch case

    LDA_Range_Cal_Coeff(); // update current and voltage cal coeff

  }//end of LDA Cal active if statement

    if (LDBCal == 1) {

    LDB.current.range += 1;

    if (LDB.current.range > LDB.volt.range) {

      LDB.current.range  = 0;

    }

    switch (LDB.current.range) {

      case 0:

        HWserial.print("bIrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("0.35A");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(0);   // sends instruction byte  - Low range set
        Wire.endTransmission();     // stop transmitting

        LDB.CurrentMax = 0.35;

        break;

      case 1:

        HWserial.print("bIrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("3A");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(1);   // sends instruction byte  -Med range set
        Wire.endTransmission();     // stop transmitting

        LDB.CurrentMax = 3;
       

        break;

      case 2:

        HWserial.print("bIrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("10A");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(2);   // sends instruction byte  -High range set
        Wire.endTransmission();     // stop transmitting

        LDB.CurrentMax = 10;

        break;


    }//end of LDB current range switch case

    LDB_Range_Cal_Coeff(); // update current and voltage cal coeff

  }//end of LDB Cal active if statement

}//end of function
