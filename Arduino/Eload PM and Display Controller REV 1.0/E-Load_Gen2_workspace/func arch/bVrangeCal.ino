void bVrangeCalFunc(void) {


 DBserial.println("bVrangeCalFunc");
 
  if (LDACal == 1) {

    DBserial.println("LDACal == 1");

    LDA.volt.range += 1;

    if (LDA.volt.range > 2) {

      LDA.volt.range  = 0;

      DBserial.println("LDA.volt.range");

    }

    switch (LDA.volt.range) {

      case 0:

        LDA.current.range = 0;
        
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

        break;

      case 1:

        if (LDA.current.range > 1) {

          LDA.current.range = 1;
          HWserial.print("bIrangeCal.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("3A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDA.CurrentMax = 3;

        Wire.beginTransmission(LDA_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(1);   // sends instruction byte  - Med range set
        Wire.endTransmission();     // stop transmitting

        }

        HWserial.print("bVrangeCal.txt=");  // Update the nex display
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

        HWserial.print("bVrangeCal.txt=");  // Update the nex display
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

  }// end of if LDA cal active IF statement

 if (LDBCal == 1) {

  DBserial.println("LDBCal == 1");

    LDB.volt.range += 1;

    if (LDB.volt.range > 2) {

      LDB.volt.range  = 0;

    }

    switch (LDB.volt.range) {

      case 0:
        
        DBserial.println("LDBCal High Volt");
        LDB.current.range = 0;
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

        break;

      case 1:

      
        DBserial.println("LDBCal Med Volt");

        if (LDB.current.range > 1) {

          LDB.current.range = 1;
          HWserial.print("bIrangeCal.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("3A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB.CurrentMax = 3;

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(currentRangeChange);
        Wire.write(1);   // sends instruction byte  - Med range set
        Wire.endTransmission();     // stop transmitting

        }

        HWserial.print("bVrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("60V");  // Update the nex display
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
        Wire.write(Vamp_Range_Med);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(potADD_2); //U1B
        Wire.write(potInstrucSelB);   // sends instruction byte
        Wire.write(Vamp_Range_Med);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(voltRangeChange);
        Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
        Wire.write(LDB.volt.range);
        Wire.endTransmission();     // stop transmitting

        break;

      case 2:

        DBserial.println("LDBCal Low Volt");

        HWserial.print("bVrangeCal.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("20V");  // Update the nex display
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
        Wire.write(Vamp_Range_Low);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(potADD_2); //U1B
        Wire.write(potInstrucSelB);   // sends instruction byte
        Wire.write(Vamp_Range_Low);  // sends potentiometer value byte
        Wire.endTransmission();     // stop transmitting

        Wire.beginTransmission(LDB_ADD); //U1B
        Wire.write(voltRangeChange);
        Wire.write(0);   // sends instruction byte  - Set digital pot reference to 1.5Vdc
        Wire.write(LDB.volt.range);
        Wire.endTransmission();     // stop transmitting

        break;

    }//end of LDB volt switch case

   DBserial.println("LDB_Range_Cal_Coeff");
    LDB_Range_Cal_Coeff(); // update current and voltage cal coeff

  }// end of if LDB cal active IF statement

}//end of function
