void TakeSnapShotFunc(void){


  DBserial.println("SS function");
  String dataString = ""; // declare variables
  
      // create a single data string composed of all loadA and LoadB sesor readings and the number of screen shots taken to be sent to the SD card
    dataString += String(SD_ss_count); 
    dataString += ","; 
    
    dataString += String(LDA.volt.calibrated,2);
    dataString += ","; 
    dataString += String(LDA.current.calibrated,2);
    dataString += ","; 
    dataString += String(LDA.power,2);
    dataString += ","; 
    dataString += String(LDA.temp.calibrated,2);
    dataString += ","; 
    
    
    dataString += String(LDB.volt.calibrated,2);
    dataString += ","; 
    dataString += String(LDB.current.calibrated,2);
    dataString += ","; 
    dataString += String(LDB.power,2);
    dataString += ","; 
    dataString += String(LDB.temp.calibrated,2);
    dataString += ","; 


  DBserial.println("data string created");
     
  File SSData = SD.open("SSDATA.txt",FILE_WRITE); // open file and prepare to write
  delay(1000);
  if (SSData) {
    
    DBserial.println("SSDATA.txt"); // write data to the sd card
    SSData.println(dataString);
    DBserial.println(dataString);   
    SSData.close();
    
    
    HWserial.print("n8.val="); 
    HWserial.print(SD_ss_count);  // Update the nex display with the SS count
    HWserial.write(0xff);  // 
    HWserial.write(0xff);
    HWserial.write(0xff); 
    DBserial.println("data and count sent");
    SD_ss_count +=1;
  } 
  
  else {
    // if the file didn't open, print an error:
    DBserial.println("error opening SSDATA.txt");
  }
  
}
