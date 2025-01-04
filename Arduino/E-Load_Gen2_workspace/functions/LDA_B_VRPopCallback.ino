void LDA_B_VRPopCallback(void *ptr){
DBserial.println("LDA_B_VRPopCallback"); 
LDA.volt.range += 1;

if(LDA.volt.range > 2){

  LDA.volt.range  = 0;
  
}

switch(LDA.volt.range){

case 0:
  
  LDA.current.range= 0;  
  HWserial.print("LDA_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("0.5A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 
  
  
  HWserial.println(LDA.volt.range);
  HWserial.print("LDA_B_VR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("400V");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 1: 
  
  if (LDA.current.range > 1){

    LDA.current.range = 1;
    HWserial.print("LDA_B_IR.txt=");  // Update the nex display
    HWserial.print("\"");
    HWserial.print("2A");  // Update the nex display
    HWserial.print("\"");
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff); 
        
  }
  
  HWserial.print("LDA_B_VR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("100V");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 2:  
  
  HWserial.print("LDA_B_VR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("20V");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

}//end of LDA volt switch case

delay(250);
LDA_Range_Cal_Coeff(); // update current and voltage cal coeff

}
