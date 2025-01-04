void LoadOnOffControlFunc(int EnableLoad) {

  if (EnableLoad == 1) {

    digitalWrite(Load_ON_OFF_Control, HIGH);

  }

  else {

    digitalWrite(Load_ON_OFF_Control, LOW);
    analogWrite(DAC_Iref, 0); // set the current to 0

  }

}
