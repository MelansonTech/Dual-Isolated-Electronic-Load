int currentNexPage(void)
{
int incomingByte;

HWserial.print("sendme");
HWserial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
HWserial.write(0xff);
HWserial.write(0xff); 
delay(10);

while (HWserial.available() > 0){

incomingByte = HWserial.read();
if(incomingByte == 102){
    CurrentPage = HWserial.read();
}

}
return CurrentPage;
}
