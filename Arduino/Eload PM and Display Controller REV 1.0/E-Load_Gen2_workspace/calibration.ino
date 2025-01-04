float calibration(float val, float gain, float offset){

  val = (val* gain) + offset;
  
  return val;
  
}
