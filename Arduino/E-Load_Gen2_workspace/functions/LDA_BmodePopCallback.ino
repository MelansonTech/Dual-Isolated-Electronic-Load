void LDA_BmodePopCallback(void *ptr){

DBserial.println("LDA_BmodePopCallback"); 
LDA.Mode.range += 1;

if(LDA.Mode.range > 2){

  LDA.Mode.range  = 0;
  
}

switch(LDA.Mode.range){

case 0:
  
  DBserial.println(LDA.Mode.range);
  HWserial.print("LDA_Bmode.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("CC");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 1: 
  
  HWserial.print("LDA_Bmode.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("CR");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 2:  
  
  HWserial.print("LDA_Bmode.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("CP");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

}//end of LDA mode switch case

  
}//end of function
