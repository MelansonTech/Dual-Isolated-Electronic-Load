void requestEvent(void) {

  switch (MeaurementSelection) {

    case SendProtectionStatus: //send active protections to controller

      Serial.println("send ActiveProtections");
      Serial.println(ActiveProtections);
      Wire1.write(ActiveProtections);
      break;

    case SendRangeStatus://send current range status to controller

      Wire1.write(VrangeSet);
      Wire1.write(IrangeSet);
      break;
      
    case ADCReadingVolt: //send voltage reading

      Wire1.write(LD_Volt & 0xFF);
      Wire1.write(LD_Volt >> 8 & 0xFF);

      break;

    case ADCReadingCurrent://send current reading

      Wire1.write(LD_Current & 0xFF);
      Wire1.write(LD_Current >> 8 & 0xFF);

      break;

    case ADCReadingTemp://send temp reading

      Wire1.write(LD_Temp & 0xFF);
      Wire1.write(LD_Temp >> 8 & 0xFF);

      break;
  }
}
