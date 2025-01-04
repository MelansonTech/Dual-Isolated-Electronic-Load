struct VARS ValChangeDetected(struct VARS values,float value , float LESS_VAL, float GREATER_VAL){

  if (value >= (values.ChangeDetectRef+GREATER_VAL) or value <= (values.ChangeDetectRef - LESS_VAL)){

    values.ChangeDetectRef = value; 
    values.ChangeDetectFlag = 1;    
 }

 else{

values.ChangeDetectFlag = 0; 
  
 }
 return values;
 }


