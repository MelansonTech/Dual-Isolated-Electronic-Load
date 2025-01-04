void VrangeSetFunc(void) {
  
 switch(VrangeSet){

        case 2://400V Range

        CR_SPV_GAIN = 2.4331550802139;
        IrangeSet = 0;
      

        case 1://60V range

        CR_SPV_GAIN =17.0320855614973;
        IrangeSet = 1;

        case 0://20V range

        CR_SPV_GAIN =42.5802139037433;
        IrangeSet = 2;       
      }
  
}
