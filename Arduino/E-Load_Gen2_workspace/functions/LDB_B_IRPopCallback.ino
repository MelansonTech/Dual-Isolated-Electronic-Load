void LDB_B_IRPopCallback(void *ptr){
DBserial.println("LDB_B_IRPopCallback"); 
LDB.current.range += 1;

if(LDB.current.range > LDB.volt.range){

  LDB.current.range  = 0;  
  
}

switch(LDB.current.range){

case 0:
  
  DBserial.println(LDB.current.range);
  HWserial.print("LDB_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("0.5A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 1: 
  
  HWserial.print("LDB_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("2A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

case 2:  
  
  HWserial.print("LDB_B_IR.txt=");  // Update the nex display
  HWserial.print("\"");
  HWserial.print("10A");  // Update the nex display
  HWserial.print("\"");
  HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  HWserial.write(0xff);
  HWserial.write(0xff); 

break;

}//end of LDB current switch case

LDB_Range_Cal_Coeff(); // update current and voltage cal coeff
  
}
