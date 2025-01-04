void WriteLoadDataToSD(int scanCount){

  String dataString = "";
 
    dataString += String(scanCount);
    
    dataString += String(LDA.volt.calibrated,2);
    dataString += ","; 
    dataString += String(LDA.current.calibrated,2);
    dataString += ","; 
    dataString += String(LDA.Power,2);
    dataString += ","; 
    dataString += String(LDA.temp.calibrated,2);
    dataString += ","; 
    
    
    dataString += String(LDB.volt.calibrated,2);
    dataString += ","; 
    dataString += String(LDB.current.calibrated,2);
    dataString += ","; 
    dataString += String(LDB.Power,2);
    dataString += ","; 
    dataString += String(LDB.temp.calibrated,2);
    dataString += ","; 
     
  LoggerData = SD.open("LoggerData.txt");
  
  if (LoggerData) {
    Serial.println("LoggerData.txt");
    myFile.println(dataString);
  
   
    myFile.close();
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

 
   
}

