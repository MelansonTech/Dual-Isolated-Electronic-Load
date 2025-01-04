// Page change event:
void PgSelKeyPadBPopCallback(void *ptr)  // If page 0 is loaded on the display, the following is going to execute:
{
  
  
CurrentPage = 4;  // keypad page

while(CurrentPage == 4){
  
nexLoop(nex_listen_list_PG4);  // Check for any touch event

if (LDB.SetPoint.ChangeDetectFlag != 1){
LDB.SetPoint.ChangeDetectFlag = 1;
}

}

}  // End of press event
