void bcaliCurrSlopeFunc(void) {

  String Gain;
  String EEPROM;

  if (LDACal == 1) {


    if (BcalIDefFlag == 1) { // if default flag is set then set the default value

      LDA.current.calGain = 1;
      LDA.SetPoint.calGain = 1;

    }

    else {//calc slope

      LDA.current.calGain *= (LDA.current.CalHighRead - LDA.current.CalLowRead) / (LDA.current.CalHighMeas - LDA.current.CalLowMeas);
      LDA.SetPoint.calGain *= 3000/(LDA.SetPoint.CalHighMeas - LDA.SetPoint.CalLowMeas); // low point is hard coded to 500 and High to 3500

    }

    switch (LDA.current.range) {

      case 0: // Low current range

        Gain = "page0.IRL_SlopeA.txt=\"" + String(LDA.current.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.IRL_SlopeA.txt,50";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        Gain = "page0.SPL_SlopeA.txt=\"" + String(LDA.SetPoint.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.SPL_SlopeA.txt,600";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 1:

        Gain = "page0.IRM_SlopeA.txt=\"" + String(LDA.current.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.IRM_SlopeA.txt,150";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        Gain = "page0.SPM_SlopeA.txt=\"" + String(LDA.SetPoint.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.SPM_SlopeA.txt,650";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 2:


        Gain = "page0.IRH_SlopeA.txt=\"" + String(LDA.current.calGain, 8) + "\"";
        DBserial.println(Gain); //for debug only
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.IRH_SlopeA.txt,250";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        Gain = "page0.SPH_SlopeA.txt=\"" + String(LDA.SetPoint.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.SPH_SlopeA.txt,700";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

    }//end of LDA.current.range switch case

  }//end of LDACal == 1

  if (LDBCal == 1) {

   if (BcalIDefFlag == 1) { // if default flag is set then set the default value

      LDB.current.calGain = 1;
      LDB.SetPoint.calGain = 1;

    }

    else {//calc slope

      LDB.current.calGain *= (LDB.current.CalHighRead - LDB.current.CalLowRead) / (LDB.current.CalHighMeas - LDB.current.CalLowMeas);
      LDB.SetPoint.calGain *= 3000/(LDB.SetPoint.CalHighMeas - LDB.SetPoint.CalLowMeas); // low point is hard coded to 500 and High to 3500

    }

    switch (LDB.current.range) {

      case 0: // Low current range


        Gain = "page0.IRL_SlopeB.txt=\"" + String(LDB.current.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.IRL_SlopeB.txt,350";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        Gain = "page0.SPL_SlopeB.txt=\"" + String(LDB.SetPoint.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.SPL_SlopeB.txt,750";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 1:


        Gain = "page0.IRM_SlopeB.txt=\"" + String(LDB.current.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.IRM_SlopeB.txt,450";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        Gain = "page0.SPM_SlopeB.txt=\"" + String(LDB.SetPoint.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.SPM_SlopeB.txt,800";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 2:


        Gain = "page0.IRH_SlopeB.txt=\"" + String(LDB.current.calGain, 8) + "\"";
        DBserial.println(Gain); //for debug only
        HWserial.print(Gain);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.IRH_SlopeB.txt,550";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        Gain = "page0.SPH_SlopeB.txt=\"" + String(LDB.SetPoint.calGain, 8) + "\"";
        DBserial.println(Gain);
        HWserial.print(Gain);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        EEPROM = "wepo page0.SPH_SlopeB.txt,850";
        DBserial.println(EEPROM); //for debug only
        HWserial.print(EEPROM);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

    }//end of LDB.current.range switch case

  }//end of LDBCal == 1

}//end of function
