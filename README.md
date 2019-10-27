 # Interface I/O C

* Developed by Vitor Assis Camargo, at 2019
* version 2.1.0
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
	setCanvas('#', 1, 0, 2, 0); //border, notification_area, title_area, textcolor, backgroundcolor
	showTitle("Title");
	drawCanvas(); // IT DRAWS A FRAME FOR YOUR APPLICATION
	
	printCenter("Menu", 9);
	
	menu mainMenu = setMenu(10); // CREATES A NEW MENU VARIABLE setMenu(int yStart)
	addMenuOption(mainMenu, "Option 1 (Login)", 1); // FIRSTLY THE MENU, SECONDLY THE LABEL AND, FINALLY, THE ENABLED
	addMenuOption(mainMenu, "Option 2 (Disabled)", 0); //THIS OPTION IS DISABLED
	addMenuOption(mainMenu, "Exit");
	
	int coord;
	char string_coord[2];
	
	do{
		coord = showMenu(mainMenu); // THIS DRAWS MENU AND GETS COORD WHEN USER PRESSES ENTER
		
		itoa(coord, string_coord, 10);
		
		showToast(string_coord); // IT SHOWS ON NOTIFICATION AREA WHICH OPTION HAVE BEEN SELECTED
		
		switch(coord){
			case 0:
				char user[10];
				char psswd[15];
				clearCanvas();
				printCenter("Login", 9);
				gotoxy(30, 11);printf("User: ");
				gotoxy(30, 12);printf("Password: ");
				do{
					readString(user, 36, 11, 10);
					if(strlen(user) == 0)
						showToast("User is null", TOAST_ERROR);
				}while(strlen(user) == 0);
				removeToast();
				do{
					readPassword(psswd, '*', 40, 12, 15);
					if(strlen(psswd) == 0)
						showToast("Password is null", TOAST_ERROR);
					else if(strlen(psswd) < 8)
						showToast("Weak password", TOAST_WARNING);
				}while(strlen(psswd) < 8);
				showToast("Logged in successfully", TOAST_SUCCESS);
				getch();
				showToast(psswd);
				break;
		}
		
		if(coord != 2)
			getch();
			
		removeToast(); // IT CLEANS NOTIFICATION AREA 
	}while(coord != 2);
	return 0;
}
```
