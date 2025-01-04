// Page change event:
void PgSelKeyPadAPopCallback(void *ptr)  // If page 0 is loaded on the display, the following is going to execute:
{
  
CurrentPage = 4;  // keypad page

while(CurrentPage == 4){
  
nexLoop(nex_listen_list_PG4);  // Check for any touch event

if (LDA.SetPoint.ChangeDetectFlag != 1){
LDA.SetPoint.ChangeDetectFlag = 1;
}

}


}  // End of press event
