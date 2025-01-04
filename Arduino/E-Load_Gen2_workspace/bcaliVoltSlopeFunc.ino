void bcaliVoltSlopeFunc(void) {

  String Gain;
  String EEPROM;

  if (LDACal == 1) {

    if (BcalVDefFlag == 1) {

      LDA.volt.calGain = 1;

    }

    else {

      LDA.volt.calGain *= (LDA.volt.CalHighRead - LDB.volt.CalLowRead) / (LDA.volt.CalHighMeas - LDB.volt.CalLowMeas);

    }

    switch (LDA.volt.range) {

      case 0: // High volt range

        Gain = "page0.VRH_SlopeA.txt=\"" + String(LDA.volt.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.VRH_SlopeA.txt,200";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 1:

        Gain = "page0.VRM_SlopeA.txt=\"" + String(LDA.volt.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.VRM_SlopeA.txt,100";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 2:

        Gain = "page0.VRL_SlopeA.txt=\"" + String(LDA.volt.calGain, 8) + "\"";
        DBserial.println(Gain); //for debug only
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.VRL_SlopeA.txt,0";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

    }//end of LDA.volt.range switch case

  }//end of LDACal == 1

  if (LDBCal == 1) {

    if (BcalVDefFlag == 1) {

      LDB.volt.calGain = 1;

    }
    else {

      LDB.volt.calGain *= (LDB.volt.CalHighRead - LDB.volt.CalLowRead) / (LDB.volt.CalHighMeas - LDB.volt.CalLowMeas);

    }

    switch (LDB.volt.range) {

      case 0: // Low volt range


        Gain = "page0.VRH_SlopeB.txt=\"" + String(LDB.volt.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.VRH_SlopeB.txt,500";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 1:

        Gain = "page0.VRM_SlopeB.txt=\"" + String(LDB.volt.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.VRM_SlopeB.txt,400";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

      case 2:

        Gain = "page0.VRL_SlopeB.txt=\"" + String(LDB.volt.calGain, 8) + "\"";
        DBserial.println(Gain); //for debug only
        HWserial.print(Gain);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.VRL_SlopeB.txt,300";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        break;

    }//end of LDB.volt.range switch case

  }//end of LDBCal == 1

}//end of function
