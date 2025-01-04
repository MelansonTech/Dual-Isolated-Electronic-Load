void WriteLoadDataToSD(int scanCount){

  String dataString = "";
 
    dataString += String(scanCount);
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
     
File LoggerData = SD.open("DATALOG.txt",FILE_WRITE);
  delay(1000);
  if (LoggerData) {
    
    DBserial.println("DATA.txt");
    LoggerData.println(dataString);
    DBserial.println(dataString);   
    LoggerData.close();
    
  } 
  
  else {
    // if the file didn't open, print an error:
    DBserial.println("error opening test.txt");
  }
   
}//end of function
