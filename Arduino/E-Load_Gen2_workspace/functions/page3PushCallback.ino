// Page change event:
void page3PushCallback(void *ptr)  // If page 3 is loaded on the display, the following is going to execute:
{
  CurrentPage = 3;  // Set variable as 3 so from now on arduino knows page 0 is loaded on the display
}  // End of press event
