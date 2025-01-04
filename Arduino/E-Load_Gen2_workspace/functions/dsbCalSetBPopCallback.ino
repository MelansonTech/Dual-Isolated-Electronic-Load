void dsbCalSetBPopCallback(void *ptr){

  dsbCalSetB.getValue(&LDBCal);
    
  if (LDBCal == 0){

    LDACal = 1;
    
  }

  
}
