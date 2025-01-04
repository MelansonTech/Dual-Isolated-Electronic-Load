void receiveEvent(size_t count)

{

  Serial.println("IIC Recieve");

  if (count) {

    Serial.println("IIC Recieve");

    // grab command
    IICcmd = Wire1.readByte();
    Serial.println(IICcmd);

    switch (IICcmd) {

        Serial.println("IICcmd received");

      case ProtectionStatusRequest:

        MeaurementSelection = SendProtectionStatus;
        Serial.println("ProtectionStatusRequest");
        Serial.println(MeaurementSelection);

        break;

      case RangeStatusRequest: // display controller is requesting a range status update

        MeaurementSelection = SendRangeStatus;  // prepare to send voltage and current range status to the display controller
        break;

      case ADCReadingRequest:

        MeaurementSelection = Wire1.readByte();

        break;

      case SetPointChange:

        LD_SetPoint = Wire1.readByte();            // Get Voltage reading
        LD_SetPoint |= Wire1.readByte() << 8;
        Serial.println("Wire update LD_SetPoint");
        Serial.println(LD_SetPoint);
        break;

      case modeChange:

        opMode = Wire1.readByte();
      
        break;

      case onOffStateChange:

        onOffState = Wire1.readByte();
        Serial.println("onOffState");
        Serial.println(onOffState);

        LoadOnOffControlFunc(onOffState); // update load on\off state

      case voltRangeChange:

        VbiasStateSet = Wire1.readByte();
        VrangeSetFunc(VbiasStateSet);// update voltage range parameters and prepare to recieve or end digital pot setting

        break;

      case CRVGainChange:

        VrangeSet = Wire1.readByte();
        CR_Coeff_Update(VrangeSet);

        break;

      case currentRangeChange:

        IrangeSet = Wire1.readByte();
        IrangeSetFunc(IrangeSet);

        break;
    }
  }
}
