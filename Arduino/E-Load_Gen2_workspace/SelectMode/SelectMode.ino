
void DualLoadSetup(void) {


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

        break;

      case 1:

        HWserial.print("LDA_Bmode.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("CR");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 2:

        HWserial.print("LDA_Bmode.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("CP");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

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

        break;

      case 2:

        HWserial.print("LDB_Bmode.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("CP");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

    }//end of LDB mode switch case
  }

  //********************************************Load A Voltage Range Config*****************************************

  if (LoadA_VrangeSel_Cap == 1) {

    LoadA_VrangeSel_Cap = 0; // change the button pressed polling flag back to zero

    LDA_Bmode.setValue(LoadA_VrangeSel_Cap);// reset the dual state button value back to zero

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
        HWserial.print("0.5A");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);


        HWserial.println(LDA.volt.range);
        HWserial.print("LDA_B_VR.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("400V");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 1:

        if (LDA.current.range > 1) {

          LDA.current.range = 1;
          HWserial.print("LDA_B_IR.txt=");  // Update the nex display
          HWserial.print("\"");
          HWserial.print("2A");  // Update the nex display
          HWserial.print("\"");
          HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
          HWserial.write(0xff);
          HWserial.write(0xff);

        }

        HWserial.print("LDA_B_VR.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("100V");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 2:

        HWserial.print("LDA_B_VR.txt=");  // Update the nex display
        HWserial.print("\"");
        HWserial.print("20V");  // Update the nex display
        HWserial.print("\"");
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

    }//end of LDA volt switch case

    LDA_Range_Cal_Coeff(); // update current and voltage cal coeff


  }//end of function
