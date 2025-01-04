// Page change event:
void page2PushCallback(void *ptr)  // If page 2 is loaded on the display, the following is going to execute:
{
  
CurrentPage = 2;  // Set variable as 2 so from now on arduino knows page 0 is loaded on the display

  Serial.println("Page 2 call back");
delay(500);
}  // End of press event
