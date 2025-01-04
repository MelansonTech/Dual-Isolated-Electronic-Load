// Page change event:
void page1PushCallback(void *ptr)  // If page 1 is loaded on the display, the following is going to execute:
{
  
  CurrentPage = 1;  // Set variable as 1 so from now on arduino knows page 0 is loaded on the display

}  // End of press event
