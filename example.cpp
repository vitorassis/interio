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
	
	do{
		coord = showMenu(mainMenu); // THIS DRAWS MENU AND GETS COORD WHEN USER PRESSES ENTER
		
		showToast("You selected some option"); // IT SHOWS ON NOTIFICATION AREA WHICH OPTION HAVE BEEN SELECTED
		
		switch(coord){
			case 0:
				char user[10], psswd[15];
				clearCanvas(); // IT CLEANS THE AREA INSIDE THE CANVAS, NEVER OUTSIDE
				printCenter("Login", 9);
				gotoxy(30, 11);printf("User: ");
				gotoxy(30, 12);printf("Password: ");
				do{
					readString(user, 36, 11, 10); //(STRING_VAR, X_POS, Y_POS, MAX_LENGTH)
					if(strlen(user) == 0)
						showToast("User is null", TOAST_ERROR);
				}while(strlen(user) == 0);
				removeToast();
				do{
					readPassword(psswd, '*', 40, 12, 15); //(STRING_VAR, MASK, X_POS, Y_POS, MAX_LENGTH)
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
