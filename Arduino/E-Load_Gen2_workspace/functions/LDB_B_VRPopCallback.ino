void LDB_B_VRPopCallback(void *ptr){
DBserial.println("LDB_B_VRPopCallback"); 
LDB.volt.range += 1;

if(LDB.volt.range > 2){

  LDB.volt.range  = 0;
  
}

switch(LDB.volt.range){

case 0:
  
  LDB.current.range= 0;  
  HWserial.print("LDB_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("0.5A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 
  
  DBserial.println(LDB.volt.range);
  HWserial.print("LDB_B_VR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("400V");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 1: 
  
  if (LDB.current.range > 1){

    LDB.current.range = 1;
    HWserial.print("LDB_B_IR.txt=");  // Update the nex display
    HWserial.print("\"");
    HWserial.print("2A");  // Update the nex display
    HWserial.print("\"");
    HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    HWserial.write(0xff);
    HWserial.write(0xff); 
        
  }
  
  HWserial.print("LDB_B_VR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("100V");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 2:  
  
  HWserial.print("LDB_B_VR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("20V");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

}//end of LDB volt switch case

LDB_Range_Cal_Coeff(); // update current and voltage cal coeff

}
