void bcaliCurrentOffSetFunc(void) {

  String OffSet;
  float SPoffsetRef;


 if (LDACal == 1) {

 if (dsbCaLIset == 1) {

    SPoffsetRef = 500/LDA.SetPoint.calGain;
    
  }

  else {

    SPoffsetRef = 3500/LDA.SetPoint.calGain;

  }

    if (BcalIDefFlag == 1) {

      LDA.current.calOffset = 0;
      LDA.SetPoint.calOffset = 0;

    }

    else {

      LDA.current.calOffset += (LDA.current.offsetRead - LDA.current.offsetMeas);
      LDA.SetPoint.calOffset = (SPoffsetRef - LDA.SetPoint.offsetMeas);

    }

    switch (LDA.current.range) {

      case 0: // Low current range

        OffSet = "page0.IRL_OffsetA.txt=\"" + String(LDA.current.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.IRL_OffsetA.txt,75";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "page0.SPL_OffsetA.txt=\"" + String(LDA.SetPoint.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.SPL_OffsetA.txt,625";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 1:

        OffSet = "page0.IRM_OffsetA.txt=\"" + String(LDA.current.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.IRM_OffsetA.txt,175";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "page0.SPM_OffsetA.txt=\"" + String(LDA.SetPoint.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.SPM_OffsetA.txt,675";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 2:

        OffSet = "page0.IRH_OffsetA.txt=\"" + String(LDA.current.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.IRH_OffsetA.txt,275";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "page0.SPH_OffsetA.txt=\"" + String(LDA.SetPoint.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.SPH_OffsetA.txt,725";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDA Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

    }//end of LDA.current.range switch case

  }//end of LDACal == 1

  if (LDBCal == 1) {

      if (dsbCaLIset == 1) {

    SPoffsetRef = 500/LDB.SetPoint.calGain;
    
  }

  else {

    SPoffsetRef = 3500/LDB.SetPoint.calGain;
  }
    if (BcalIDefFlag == 1) {

      LDB.current.calOffset = 0;
      LDB.SetPoint.calOffset = 0;

    }

    else {

      LDB.current.calOffset += (LDB.current.offsetRead - LDB.current.offsetMeas);
      LDB.SetPoint.calOffset += (SPoffsetRef - LDB.SetPoint.offsetMeas);

    }

    switch (LDB.current.range) {

      case 0: // Low current range

        OffSet = "page0.IRL_OffsetB.txt=\"" + String(LDB.current.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.IRL_OffsetB.txt,375";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "page0.SPL_OffsetB.txt=\"" + String(LDB.SetPoint.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.SPL_OffsetB.txt,775";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 1:

        OffSet = "page0.IRM_OffsetB.txt=\"" + String(LDB.current.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.IRM_OffsetB.txt,475";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "page0.SPM_OffsetB.txt=\"" + String(LDB.SetPoint.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.SPM_OffsetB.txt,825";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        break;

      case 2:

        OffSet = "page0.IRH_OffsetB.txt=\"" + String(LDB.current.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.IRH_OffsetB.txt,575";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);
        
        OffSet = "page0.SPH_OffsetB.txt=\"" + String(LDB.SetPoint.calOffset, 8) + "\"";
        DBserial.println(OffSet);
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);

        delay(500);

        OffSet = "wepo page0.SPH_OffsetB.txt,875";
        DBserial.println(OffSet); //for debug only
        HWserial.print(OffSet);  // Update the nex display with the new LDB Set Point
        HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
        HWserial.write(0xff);
        HWserial.write(0xff);
        break;

    }//end of LDB.current.range switch case

  }//end of LDBCal == 1

}//end of function
