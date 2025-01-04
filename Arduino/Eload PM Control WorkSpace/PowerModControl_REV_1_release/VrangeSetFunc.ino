void VrangeSetFunc(int SetVReftoZero) {

  if (SetVReftoZero == 1) {

    digitalWrite(VbiasGND, HIGH); // prepares pot for incoming instuctions from main controller

  }

  else {

    digitalWrite(VbiasGND, LOW); // returns pot to normal operating state

  }

}
