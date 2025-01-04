bool debounce(int Switch, bool On){


bool PB_State = On;

Serial.println("debounce");
while (PB_State == On){

delay(100);
bool SW_Status = digitalRead(Switch);
Serial.println(SW_Status);
if (SW_Status != On){
    delay(100);
    PB_State = SW_Status;    
    }  
  }
  return false;  
}


