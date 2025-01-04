int encoder_position_limit (int encoderMin, int encoderMax,int encoderPosition){

 if (encoderPosition > encoderMax){  //set the maximum menu selection indicator movement 

          encoderPosition = encoderMin;
          
        }

        if (encoderPosition < encoderMin){ //set the min menu selection indicator movement 

          encoderPosition = encoderMax;        
        
        }

return (encoderPosition);
  
}


