# Interface I/O C

* Developed by Vitor Assis Camargo, at 2019
* version 1.0.1
* Certify you have conio2.h installed in your PC before using this library
* THIS ONLY RUNS ON WINDOWS MACHINES!
* If you like, please, comment and share it.

## Steps: 

1. Download this or clone.
1. Put interio.h with your source
1. Then: `#include "interio.h"`
1. You are ready to code with it!

## Example:

```
#include <stdio.h>
#include "interio.h"

int main(){
  drawCanvas(); // IT DRAWS A FRAME FOR YOUR APPLICATION
  gotoxy(centralize("Title"), 9); printf("Title"); // FUNCTION centralize(const char[]) RETURNS THE IDEAL X POSITION TO TEXT
  
  char options[3][50]; // PLEASE, ALWAYS USE 50 IN SECOND DIMENSION, OTHERWISE IT WON'T WORK
  strcpy(options[0], "Option 1"); // SET OPTIONS WITH strcpy(char*, char*)
  strcpy(options[1], "Option 2");
  strcpy(options[2], "Option 3");

  int coord;
  
  do{
    coord = showMenu(options, 10, 12, 30); // showMenu(char options[], int min_y, int max_y, int x)
    
    showToast(options[coord-10]); // IT SHOWS ON NOTIFICATION AREA WHICH OPTION HAVE BEEN SELECTED
    getch();
    removeToast(); // IT CLEANS NOTIFICATION AREA 
  }while(coord != 12);
  return 0;
}
```
