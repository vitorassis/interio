#include <stdio.h>
#include "interio.h"

int main(){
  drawCanvas(); // IT DRAWS A FRAME FOR YOUR APPLICATION
  gotoxy(centralize("Title"), 9); printf("Title"); // FUNCTION centralize(const char[]) RETURNS THE IDEAL X POSITION TO TEXT
  
  menu mainMenu = setMenu(10, 12); // CREATES A NEW MENU VARIABLE setMenu(int yStart, int yEnd)
  addMenuOption(mainMenu, "Option 1", 1); // FIRSTLY THE MENU, SECONDLY THE LABEL AND, FINALLY, THE ENABLED
  addMenuOption(mainMenu, "Option2", 0); //THIS OPTION IS DISABLED
  addMenuOption(mainMenu, "Option3", 1);

  int coord;
  
  do{
    coord = showMenu(mainMenu); // THIS DRAWS MENU AND GETS COORD WHEN USER PRESSES ENTER
    
    showToast(mainMenu.options[coord-10].option); // IT SHOWS ON NOTIFICATION AREA WHICH OPTION HAVE BEEN SELECTED
    getch();
    removeToast(); // IT CLEANS NOTIFICATION AREA 
  }while(coord != 12);
  return 0;
}
