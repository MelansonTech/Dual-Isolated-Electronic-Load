void LoadOnOffControlFunc(int EnableLoad) {

  int Iset = 0;
  int IminLoadEnable = 25;

  if (EnableLoad == 1) {

    analogWrite(DAC_Iref, 0); // set the current to 0
    delay(2);
    digitalWrite(Load_ON_OFF_Control, HIGH);

    LD_Current = analogRead(ADC_ISense);

    while (LD_Current <= IminLoadEnable) {
      Iset++;
      analogWrite(DAC_Iref, Iset); // set the current to 0
      LD_Current = analogRead(ADC_ISense);
      if (Iset > 500){

        break;
        
      }
    }
  }

  else {

    digitalWrite(Load_ON_OFF_Control, LOW);
    analogWrite(DAC_Iref, 0); // set the current to 0
    
  }

}
