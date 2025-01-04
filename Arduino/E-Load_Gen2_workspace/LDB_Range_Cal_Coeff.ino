void LDB_Range_Cal_Coeff(void){

//load temp cal coeff

LDB.temp.calGain = -0.09793;
LDB.temp.calOffset =190.37;

switch (LDB.volt.range){

case 0: // load High range cal coeff

//get Hi range voltage slope from nex eeprom
   
VRH_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDB.volt.NexRecieve = buffer;
LDB.volt.calGain = LDB.volt.NexRecieve.toFloat();

//get Hi range voltage offset from nex eeprom

VRH_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDB.volt.NexRecieve = buffer;   
LDB.volt.calOffset = LDB.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

break;

case 1:// load med range cal coeff

//get Hi range voltage slope from nex eeprom
VRM_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer  
LDB.volt.NexRecieve = buffer;  
LDB.volt.calGain = LDB.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Med range voltage offset from nex eeprom
VRM_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer  
LDB.volt.NexRecieve = buffer;    
LDB.volt.calOffset = LDB.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

break;

case 2:// load Low range cal coeff
 
VRL_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDB.volt.NexRecieve = buffer;
LDB.volt.calGain = LDB.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Hi range voltage offset from nex eeprom

VRL_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDB.volt.NexRecieve = buffer;  
LDB.volt.calOffset = LDB.volt.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

break;
  
  }//end of voltage range switch

switch (LDB.current.range){

case 0: // load low range cal coeff

IRL_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.current.NexRecieve = buffer;  
LDB.current.calGain = LDB.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPL_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.SetPoint.NexRecieve = buffer;  
LDB.SetPoint.calGain = LDB.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Low range Current offset from nex eeprom

IRL_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDB.current.NexRecieve = buffer;  
LDB.current.calOffset = LDB.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPL_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.SetPoint.NexRecieve = buffer;  
LDB.SetPoint.calOffset = LDB.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

break;

case 1:// load med range cal coeff

IRM_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.current.NexRecieve = buffer;    
LDB.current.calGain = LDB.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPM_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.SetPoint.NexRecieve = buffer;  
LDB.SetPoint.calGain = LDB.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
  
//get Med range current offset from nex eeprom
IRM_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDB.current.NexRecieve = buffer;   
LDB.current.calOffset = LDB.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPM_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.SetPoint.NexRecieve = buffer;  
LDB.SetPoint.calOffset = LDB.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
break;

case 2:// load high range cal coeff
  
IRH_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer 
LDB.current.NexRecieve = buffer;    
LDB.current.calGain = LDB.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPH_SlopeB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.SetPoint.NexRecieve = buffer;  
LDB.SetPoint.calGain = LDB.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 
//get Hi range voltage offset from nex eeprom

IRH_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer
LDB.current.NexRecieve = buffer;   
LDB.current.calOffset = LDB.current.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float

SPH_OffsetB.getText(buffer, sizeof(buffer));  // Read the text on the object and store it on the buffer
LDB.SetPoint.NexRecieve = buffer;  
LDB.SetPoint.calOffset = LDB.SetPoint.NexRecieve.toFloat(); //convert the text string recieved from the nex display to a float
 

break;  

} //end of current range switch


} // end of function
