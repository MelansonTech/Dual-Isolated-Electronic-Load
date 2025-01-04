void bcaliVoltOffSetFunc(void) {

  String OffSet;

  if (LDACal == 1) {

    if (BcalVDefFlag == 1) {

      LDA.volt.calOffset = 0;

    }

    else {

      LDA.volt.calOffset += (LDA.volt.offsetRead - LDA.volt.offsetMeas);

    }

    switch (LDA.volt.range) {

      case 0: // High volt range



        OffSet = "page0.VRH_OffsetA.txt=\"" + String(LDA.volt.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.VRH_OffsetA.txt,225";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 1:


        OffSet = "page0.VRM_OffsetA.txt=\"" + String(LDA.volt.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.VRM_OffsetA.txt,125";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 2:

        OffSet = "page0.VRL_OffsetA.txt=\"" + String(LDA.volt.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.VRL_OffsetA.txt,25";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

    }//end of LDA.volt.range switch case

  }//end of LDACal == 1

  if (LDBCal == 1) {

    if (BcalVDefFlag == 1) {

      LDB.volt.calOffset = 0;

    }

    else {

      LDB.volt.calOffset += (LDB.volt.offsetRead - LDB.volt.offsetMeas);

    }

    switch (LDB.volt.range) {

      case 0: // Low volt range

        OffSet = "page0.VRH_OffsetB.txt=\"" + String(LDB.volt.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.VRH_OffsetB.txt,525";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 1:

        OffSet = "page0.VRM_OffsetB.txt=\"" + String(LDB.volt.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.VRM_OffsetB.txt,425";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 2:

        OffSet = "page0.VRL_OffsetB.txt=\"" + String(LDB.volt.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.VRL_OffsetB.txt,325";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

    }//end of LDB.volt.range switch case

  }//end of LDBCal == 1

}//end of function
