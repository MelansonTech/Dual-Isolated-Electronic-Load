void IrangeSetFunc(void) {
  
        switch (IrangeSet) {

          case 0: // Low Current Range

            digitalWrite(I_Range_Current_Low, HIGH);
            digitalWrite(I_Range_Current_Med, LOW);
            digitalWrite(I_Range_Current_High, LOW);
            Serial.println("Low Current Range");
            CR_SPI_GAIN = 10175.828313105;
           
            break;

          case 1: // Med Current Range

            digitalWrite(I_Range_Current_Low, LOW);
            digitalWrite(I_Range_Current_Med, HIGH);
            digitalWrite(I_Range_Current_High, LOW);
            Serial.println("Med Current Range");
            CR_SPI_GAIN = 925.075301191364;
            
            break;

          case 2: // High Current Range

            digitalWrite(I_Range_Current_Low, LOW);
            digitalWrite(I_Range_Current_Med, LOW);
            digitalWrite(I_Range_Current_High, HIGH);
            Serial.println("High Current Range");
            CR_SPI_GAIN = 308.358433730455;
           

            break;
        }
}
