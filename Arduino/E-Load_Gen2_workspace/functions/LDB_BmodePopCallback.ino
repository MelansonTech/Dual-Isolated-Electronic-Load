void LDB_BmodePopCallback(void *ptr){

LDB.Mode.range += 1;

if(LDB.Mode.range > 2){

  LDB.Mode.range  = 0;
  
}

switch(LDB.Mode.range){
          
          case 0:
            
            DBserial.println(LDB.Mode.range);
            HWserial.print("LDB_Bmode.txt=");  // Update the nex display
            HWserial.print("\"");
            HWserial.print("CC");  // Update the nex display
            HWserial.print("\"");
            HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
            HWserial.write(0xff);
            HWserial.write(0xff); 
          
          break;
          
          case 1: 
            
            DBserial.println(LDB.Mode.range);
            DBserial.print("mode 1");
            HWserial.print("LDB_Bmode.txt=");  // Update the nex display
            HWserial.print("\"");
            HWserial.print("CR");  // Update the nex display
            HWserial.print("\"");
            HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
            HWserial.write(0xff);
            HWserial.write(0xff); 
          
          break;
          
          case 2:  
            
            HWserial.print("LDB_Bmode.txt=");  // Update the nex display
            HWserial.print("\"");
            HWserial.print("CP");  // Update the nex display
            HWserial.print("\"");
            HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
            HWserial.write(0xff);
            HWserial.write(0xff); 
          
          break;
          
     }//end of LDB mode switch case    

}
