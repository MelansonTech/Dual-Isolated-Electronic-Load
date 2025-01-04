int currentNexPage(void);

int incomingByte;

Serial1.print("sendme");
Serial1.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
Serial1.write(0xff);
Serial1.write(0xff); 
delay(10);
while (Serial1.available() > 0){

incomingByte = Serial1.read();
if(incomingByte == 102){
    
CurrentPage = Serial1.read();
Serial.print("I received: ");
                Serial.println(CurrentPage, DEC);
}

Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
                
  delay(50);
}
  

Serial.println(CurrentPage);
