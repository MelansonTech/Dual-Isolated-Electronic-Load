(void)nexTextboxWriteFunc(String TextBoxName, int TextboxValueAsFloat, String TextboxValueAsString) {

  if (TextboxValueAsFloat) {

    HWserial.print(TextBoxName);  // Update the nex display
    HWserial.print("\"");
    HWserial.print(TextboxValueAsFloat);  // Update the nex display
    HWserial.print("\"");
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff);

  }

  else {
    
    HWserial.print(TextBoxName);  // Update the nex display
    HWserial.print("\"");
    HWserial.print(TextboxValueAsString);  // Update the nex display
    HWserial.print("\"");
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff);

  }

}
