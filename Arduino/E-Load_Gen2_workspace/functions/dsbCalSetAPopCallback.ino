void dsbCalSetAPopCallback(void *ptr){

  
  dsbCalSetA.getValue(&LDACal);  
  
  if (LDACal == 0){

    LDBCal = 1;
    
  }

  
}
