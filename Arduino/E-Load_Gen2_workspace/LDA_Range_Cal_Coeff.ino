void LDA_Range_Cal_Coeff(void){

//load temp cal coeff

LDA.temp.calGain = -0.09793;
LDA.temp.calOffset =190.37;

switch (LDA.volt.range){

case 0: // load High range cal coeff

//get Hi range voltage slope from nex eeprom
    
VRH_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDA.volt.NexRecieve = buffer;
LDA.volt.calGain = LDA.volt.NexRecieve.toFloat();
 
//get Hi range voltage offset from nex eeprom

VRH_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDA.volt.NexRecieve = buffer;   
LDA.volt.calOffset = LDA.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

break;

case 1:// load med range cal coeff

//get Hi range voltage slope from nex eeprom

VRM_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer  
LDA.volt.NexRecieve = buffer;  
LDA.volt.calGain = LDA.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Med range voltage offset from nex eeprom
VRM_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer  
LDA.volt.NexRecieve = buffer;    
LDA.volt.calOffset = LDA.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

break;

case 2:// load Low range cal coeff
 
VRL_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDA.volt.NexRecieve = buffer;
LDA.volt.calGain = LDA.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Hi range voltage offset from nex eeprom

VRL_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDA.volt.NexRecieve = buffer;  
LDA.volt.calOffset = LDA.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

break;
  
  }//end of voltage range switch

switch (LDA.current.range){

case 0: // load low range cal coeff

IRL_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.current.NexRecieve = buffer;  
LDA.current.calGain = LDA.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPL_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.SetPoint.NexRecieve = buffer;  
LDA.SetPoint.calGain = LDA.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Low range current offset from nex eeprom

IRL_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDA.current.NexRecieve = buffer;  
LDA.current.calOffset = LDA.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPL_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.SetPoint.NexRecieve = buffer;  
LDA.SetPoint.calOffset = LDA.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 

break;

case 1:// load med range cal coeff

IRM_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.current.NexRecieve = buffer;    
LDA.current.calGain = LDA.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPM_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.SetPoint.NexRecieve = buffer;  
LDA.SetPoint.calGain = LDA.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
 
//get Med range current offset from nex eeprom

IRM_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDA.current.NexRecieve = buffer;   
LDA.current.calOffset = LDA.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPM_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.SetPoint.NexRecieve = buffer;  
LDA.SetPoint.calOffset = LDA.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
break;

case 2:// load high range cal coeff
  
IRH_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer 
LDA.current.NexRecieve = buffer;    
LDA.current.calGain = LDA.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPH_SlopeA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.SetPoint.NexRecieve = buffer;  
LDA.SetPoint.calGain = LDA.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Hi range voltage offset from nex eeprom

IRH_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDA.current.NexRecieve = buffer;   
LDA.current.calOffset = LDA.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPH_OffsetA.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDA.SetPoint.NexRecieve = buffer;  
LDA.SetPoint.calOffset = LDA.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 

break;  

} //end of current range switch


} // end of function
