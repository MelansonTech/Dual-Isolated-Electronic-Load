int encoder_position_move(int newPosition,int oldPosition,int encoder_position){
   
 if (newPosition < oldPosition) {        

          encoder_position -= 1;
          
        }  
         
        if (newPosition > oldPosition) {

          encoder_position += 1;
        
        }    


return (encoder_position);
  
}

