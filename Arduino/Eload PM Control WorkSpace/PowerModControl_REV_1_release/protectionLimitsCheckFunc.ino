bool protectionLimitCheckFunc(int testSample, int minLimit, int maxLimit) {

  if (testSample < minLimit or testSample > maxLimit) {

   return true;

  }
  
else{
  
  return false;
  
  }
}
