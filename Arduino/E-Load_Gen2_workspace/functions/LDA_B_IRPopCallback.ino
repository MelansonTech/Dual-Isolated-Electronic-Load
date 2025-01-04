void LDA_B_IRPopCallback(void *ptr){

DBserial.println("LDA_B_IRPopCallback"); 
LDA.current.range += 1;

if(LDA.current.range > LDA.volt.range){

  LDA.current.range  = 0;
  
}

switch(LDA.current.range){

case 0:
  
 
  HWserial.print("LDA_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("0.5A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 1: 
  
  HWserial.print("LDA_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("2A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 2:  
  
  HWserial.print("LDA_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("10A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

}//end of LDA current range switch case

delay(250);
LDA_Range_Cal_Coeff(); // update current and voltage cal coeff

}//end of function
  
