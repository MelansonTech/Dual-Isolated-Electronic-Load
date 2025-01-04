void DualLoadSetupLoop(void) {

  // turn off the loads
  LDA_OnOff_State = 0;
  Wire.beginTransmission(LDA_ADD); //U1B
  Wire.write(onOffStateChange);
  Wire.write(LDA_OnOff_State);   // sends instruction byte
  Wire.endTransmission();     // stop transmitting


  LDB_OnOff_State = 0;
  Wire.beginTransmission(LDB_ADD); //U1B
  Wire.write(onOffStateChange);
  Wire.write(LDB_OnOff_State);   // sends instruction byte
  Wire.endTransmission();     // stop transmitting

  //note the range flag is used to set the mode of operation for the load
  
  while (CurrentPage == 3)

  {

    delay(100);// delay helps slow the button response time - too fast with out
    CurrentPage = currentNexPage();
    DBserial.println(CurrentPage);

    //********************************************Dual State Button Press Polling*****************************************


    LDA_Bmode.getValue(&LoadA_ModeSel_Cap);
    LDB_Bmode.getValue(&LoadB_ModeSel_Cap);
    LDA_B_VR.getValue(&LoadA_VrangeSel_Cap);
    LDB_B_VR.getValue(&LoadB_VrangeSel_Cap);
    LDA_B_IR.getValue(&LoadA_IrangeSel_Cap);
    LDB_B_IR.getValue(&LoadB_IrangeSel_Cap);


    //********************************************Load A Mode Config*****************************************

    if (LoadA_ModeSel_Cap == 1) {

      LoadA_ModeSel_Cap = 0; // change the button pressed polling flag back to zero

      LDA_Bmode.setValue(LoadA_ModeSel_Cap);// reset the dual state button value back to zero

      DBserial.println("LDA_SelectMode");

      LDA.Mode.range += 1;

      if (LDA.Mode.range > 2) {
        LDA.Mode.range  = 0;
      }

      switch (LDA.Mode.range) {

        case 0:

          DBserial.println(LDA.Mode.range);
          HWserial.print("LDA_Bmode.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("CC");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          Wire.beginTransmission(LDA_ADD); //U1B
          Wire.write(modeChange);
          Wire.write(0);   // sends instruction byte  - Constant Current
          Wire.endTransmission();     // stop transmitting

          LDA.Units = " A";

          break;

        case 1:

          HWserial.print("LDA_Bmode.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("CR");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          Wire.beginTransmission(LDA_ADD); //U1B
          Wire.write(modeChange);
          Wire.write(1);   // sends instruction byte  - Constant Res
          Wire.endTransmission();     // stop transmitting

          LDA.Units = " Ohm";

          break;

        case 2:

          HWserial.print("LDA_Bmode.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("CP");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          Wire.beginTransmission(LDA_ADD); //U1B
          Wire.write(modeChange);
          Wire.write(2);   // sends instruction byte  - Constant Power
          Wire.endTransmission();     // stop transmitting

          LDA.Units = " W";

          break;

      }//end of LDA mode switch case
    }

    //********************************************Load B Mode Config*****************************************
    if (LoadB_ModeSel_Cap == 1) {

      LoadB_ModeSel_Cap = 0; // change the button pressed polling flag back to zero
      LDB_Bmode.setValue(LoadB_ModeSel_Cap);// reset the dual state button value back to zero


      LDB.Mode.range += 1;

      if (LDB.Mode.range > 2) {

        LDB.Mode.range  = 0;

      }

      switch (LDB.Mode.range) {

        case 0:

          DBserial.println(LDB.Mode.range);
          HWserial.print("LDB_Bmode.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("CC");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB.Units = " A";


          break;

        case 1:

          DBserial.println(LDB.Mode.range);
          DBserial.print("mode 1");
          HWserial.print("LDB_Bmode.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("CR");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB.Units = " Ohm";


          break;

        case 2:

          HWserial.print("LDB_Bmode.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("CP");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);
          
          LDB.Units = " W";

          break;

      }//end of LDB mode switch case
    }

    //********************************************Load A Voltage Range Config*****************************************

    if (LoadA_VrangeSel_Cap == 1) {

      LoadA_VrangeSel_Cap = 0; // change the button pressed polling flag back to zero

      LDA_B_VR.setValue(LoadA_VrangeSel_Cap);// reset the dual state button value back to zero

      DBserial.println("LDA_Voltage Range");

      LDA.volt.range += 1;

      if (LDA.volt.range > 2) {

        LDA.volt.range  = 0;

      }

      switch (LDA.volt.range) {

        case 0:

          LDA.current.range = 0;
          HWserial.print("LDA_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("0.35A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDA.CurrentMax = 0.35;

          Wire.beginTransmission(LDA_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(0);   // sends instruction byte  - Low range set
          Wire.endTransmission();     // stop transmitting

          DBserial.println(LDA.volt.range);
          HWserial.print("LDA_B_VR.txt=");  // Update the nex display
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
            HWserial.print("LDA_B_IR.txt=");  // Update the nex display
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

    //********************************************Load B Voltage Range Config*****************************************

    if (LoadB_VrangeSel_Cap == 1) {

      LoadB_VrangeSel_Cap = 0; // change the button pressed polling flag back to zero

      LDB_B_VR.setValue(LoadB_VrangeSel_Cap);// reset the dual state button value back to zero

      DBserial.println("LDB_B_VRPopCallback");

      LDB.volt.range += 1;

      if (LDB.volt.range > 2) {

        LDB.volt.range  = 0;

      }

      switch (LDB.volt.range) {

        case 0:

          LDB.current.range = 0;
          HWserial.print("LDB_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("0.35A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB.CurrentMax = 0.35;

          Wire.beginTransmission(LDB_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(0);   // sends instruction byte  - low range set
          Wire.endTransmission();     // stop transmitting

          DBserial.println(LDB.volt.range);
          HWserial.print("LDB_B_VR.txt=");  // Update the nex display
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

          if (LDB.current.range > 1) {

            LDB.current.range = 1;
            HWserial.print("LDB_B_IR.txt=");  // Update the nex display
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

          HWserial.print("LDB_B_VR.txt=");  // Update the nex display
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

          HWserial.print("LDB_B_VR.txt=");  // Update the nex display
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

      LDB_Range_Cal_Coeff(); // update current and voltage cal coeff
    }

    //********************************************Load A Current Range Config*****************************************

    if (LoadA_IrangeSel_Cap == 1) {

      LoadA_IrangeSel_Cap = 0; // change the button pressed polling flag back to zero

      LDA_B_IR.setValue(LoadA_IrangeSel_Cap);// reset the dual state button value back to zero

      DBserial.println("Load A Current Range Config");

      LDA.current.range += 1;

      if (LDA.current.range > LDA.volt.range) {

        LDA.current.range  = 0;

      }

      switch (LDA.current.range) {

        case 0:


          HWserial.print("LDA_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("0.35A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDA.CurrentMax = 0.35;

          Wire.beginTransmission(LDA_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(0);   // sends instruction byte  - low range set
          Wire.endTransmission();     // stop transmitting

          break;

        case 1:

          HWserial.print("LDA_B_IR.txt=");  // Update the nex display
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

          break;

        case 2:

          HWserial.print("LDA_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("10A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDA.CurrentMax = 10;

          Wire.beginTransmission(LDA_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(2);   // sends instruction byte  - High range set
          Wire.endTransmission();     // stop transmitting

          break;

      }//end of LDA current range switch case

      delay(50);

      LDA_Range_Cal_Coeff(); // update current and voltage cal coeff
    }

    //********************************************Load B Current Range Config*****************************************

    if (LoadB_IrangeSel_Cap == 1) {

      LoadB_IrangeSel_Cap = 0; // change the button pressed polling flag back to zero

      LDB_B_IR.setValue(LoadB_IrangeSel_Cap);// reset the dual state button value back to zero
      DBserial.println("LDB_B_IRPopCallback");
      LDB.current.range += 1;

      if (LDB.current.range > LDB.volt.range) {
        LDB.current.range  = 0;
      }

      switch (LDB.current.range) {

        case 0:

          DBserial.println(LDB.current.range);
          HWserial.print("LDB_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("0.35A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB.CurrentMax = 0.35;

          Wire.beginTransmission(LDB_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(0);   // sends instruction byte  - low range set
          Wire.endTransmission();     // stop transmitting


          break;

        case 1:

          HWserial.print("LDB_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("3A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB.CurrentMax = 3;

          Wire.beginTransmission(LDB_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(1);   // sends instruction byte  - MED range set
          Wire.endTransmission();     // stop transmitting

          break;

        case 2:

          HWserial.print("LDB_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("10A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

          LDB.CurrentMax = 10;

          Wire.beginTransmission(LDB_ADD); //U1B
          Wire.write(currentRangeChange);
          Wire.write(2);   // sends instruction byte  - High range set
          Wire.endTransmission();     // stop transmitting

          break;

      }//end of LDB current switch case

      LDB_Range_Cal_Coeff(); // update current and voltage cal coeff

    }





  }//end of current page while loop


}
