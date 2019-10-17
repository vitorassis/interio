 # Interface I/O C

* Developed by Vitor Assis Camargo, at 2019
* version 1.0.3
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

   menu mainMenu = setMenu(10); // CREATES A NEW MENU VARIABLE setMenu(int yStart)
   addMenuOption(mainMenu, "Option 1", 1); // FIRSTLY THE MENU, SECONDLY THE LABEL AND, FINALLY, THE ENABLED
   addMenuOption(mainMenu, "Option 2"); // THIS IS ENABLED
   addMenuOption(mainMenu, "Option 3", 0); //THIS OPTION IS DISABLED
   addMenuOption(mainMenu, "Exit");

   int coord;

   do{
      coord = showMenu(mainMenu); // THIS DRAWS MENU AND GETS COORD WHEN USER PRESSES ENTER
      
      showToast(mainMenu.options[coord].option); // IT SHOWS ON NOTIFICATION AREA WHICH OPTION HAVE BEEN SELECTED
      getch();
      removeToast(); // IT CLEANS NOTIFICATION AREA 
   }while(coord != 3);
   return 0;
}
```
