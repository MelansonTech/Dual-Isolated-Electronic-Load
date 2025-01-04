void CR_Coeff_Update(int Vrange) {

  switch (Vrange) {

    case 0://400V Range

      //CR_SPV_GAIN = 2.4331550802139;
      CR_SPV_GAIN = 4.43974629969902;

      //IrangeSet = 0;

      break;


    case 1://60V range

      //CR_SPV_GAIN =17.0320855614973;
      CR_SPV_GAIN = 30.3655621176758;
      //IrangeSet = 1;

      break;

    case 2://20V range

      //CR_SPV_GAIN =42.5802139037433;
      CR_SPV_GAIN = 82.5699965433805;
      //IrangeSet = 2;

      break;
  }

}
