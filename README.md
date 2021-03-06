# Interface I/O C

* Developed by Vitor Assis Camargo, at 2019
* version 3.0.0
* THIS ONLY RUNS ON WINDOWS MACHINES!
* If you like, please, comment and share it.

## Steps: 

1. Download this or clone.
1. Put interio.h inside your source directory
1. Then: `#include "interio.h"`
1. You are ready to code it!

## Types:

### Summary:
	1. canvas
	1. menu
	1. breadcrumb
	1. scrollpane

## Functions:

### Summary:
1. Canvas
	* [setCanvas](#setcanvaschar-int-int-int-int-int-int--void)
	* [drawCanvas](#drawcanvas--void)
	* [clearCanvas](#clearcanvas--void)
1. Menu
	* [setMenu](#setmenuint-int-char--menu)
	* [addMenuOption](#addmenuoptionmenu-const-char--int--void)
	* [clearMenuOptions](#clearmenuoptionsmenu--void)
	* [showMenu](#showmenumenu--int)
1. Breadcrumb
	* [setBreadcrumb](#setbreadcrumbconst-char--breadcrumb--breadcrumb)
	* [showBreadcrumbs](#showbreadcrumbsbreadcrumb--void)
1. ScrollPane
	* [setScrollPane](#setscrollpane--scrollpane)
	* [addScrollPaneItem](#addscrollpaneitemscrollpane-int-int-const-char---int)
1. Toast
	* [showToast](#showtoastconst-char--int--void)
	* [removeToast](#removetoast--void)
1. Input
	* [readInt](#readintint-int-int-int--int)
	* [readFloat](#readfloatint-int-int-float--float)
	* [readString](#readstringchar--int-int-int-int--void)
	* [readChar](#readcharint-int-char--char)
	* [readMaskedString](#readmaskedstringchar--const-char-int-int-int--void)
	* [readPassword](#readpasswordchar--char-int-int-int--void)
1. UI utils
	* [clearCoordinates](#clearcoordinatesint-int-int-int--void)
	* [drawLine](#drawlineint-int-int-int-char--void)
	* [centralize](#centralizeconst-char---int)
	* [printCenter](#printcenterconst-char--int--void)
	* [printAt](#printatint-int-char---void)

### setCanvas(char, int, int, int, int, int, int) : void

Must be called before `drawCanvas()`, explaned below, in order to configure it.

Receives:
```
char border default '>'
int notification_area default 0
int title_area flag default 0
int forecolor default 7
int backcolor default 0
int width default 0 // IT WILL KEEP THE CONSOLE'S DEFAULT
int height default 0 // IT WILL KEEP THE CONSOLE'S DEFAULT
```
Returns:
```
void
```

### drawCanvas() : void

It draws the canvas following the parameters sent in `setCanvas()` method

Returns:
```
void
```

### clearCanvas() : void

It clears inside the Canvas area (setted up in `setCanvas()`).

Returns:
```
void
```

### setMenu(int, int, char) : menu

Creates a menu according the parameters and returns it.

Receives:
```
int yStart
int x default 30
char cursor default '>'
```
Returns:
```
menu
```

### addMenuOption(menu, const char [], int) : void

Add the option to the sent menu as parameter.

Receives:
```
menu _menu
const char option[]
int enabled default 1
```
Returns:
```
void
```

### clearMenuOptions(menu) : void

Use this to remove all options from the sent menu.

Receives:
```
menu _menu
```
Returns:
```
void
```

### showMenu(menu) : int

It show menu and returns the position the user entered, it will be the index of the option.

Receives:
```
menu menuSettings
```
Returns:
```
int
```

### clearCoordinates(int, int, int, int) : void

It clears the screen inside the sent rectangle.
If xf (x final) or yf (y final) is equal 0 it will worth the same as the respective initial, then `clearCoordinates(4, 5)` clears only the position (4,5).

Receives:
```
int xi
int yi
int xf default 0
int yf default 0
```
Returns:
```
void
```

### drawLine(int, int, int, int, char) : void

It draws a line, if vertical param is 1, it will be vertical.

Receives:
```
int start
int finish
int coordinate
int vertical default 0
char border default '*'
```
Returns:
```
void
```

### hideCursor() : void

This hides the cursor, it will be call inside the `drawCanvas()` method.

Returns:
```
void
```

### showToast(const char [], int) : void

It shows the toast notification.

Toasts' type can be:

1. TOAST_SUCCESS
1. TOAST_FAILED
1. TOAST_WARNING

Receives:
```
const char text[]
int type default 7
```
Returns:
```
void
```

### removeToast() : void

It removes the toast notification.

Returns:
```
void
```

### centralize(const char []) : int

It returns the fit x to center the sent text.

Receives:
```
const char text[]
```
Returns:
```
int
```

### printCenter(const char [], int) : void

It prints the sent text in the informed line.

Receives:
```
const char text[]
int line
```
Returns:
```
void
```

### printAt(int, int, char*, ...) : void

It prints the sent text at the wished position.

Receives:
```
int x
int y
char* format
... (varibles for format's mask)
```
Returns:
```
void
``` 

### showTitle(const char [], int) : void

It prints the title with the sent color.

Receives:
```
const char title[]
int color default 7
```
Returns:
```
void
```


### setBreadcrumb(const char [], breadcrumb*) : breadcrumb

It creates a breadcrumb

Receives:
```
const char text []
breadcrumb *prev default NULL
```
Returns:
```
breadcrumb
```

### showBreadcrumbs(breadcrumb) : void

It shows the complete breadcrumb

Receives:
```
breadcrumb bread
```
Returns:
```
void
```

### setScrollPane() : scrollPane

It creates a scrollPane variable

Returns:
```
scrollPane pane
```

### addScrollPaneItem(scrollPane, int, int, const char []) : int

As the name suggests, this function adds some text in a scrollPane previously setted sent as parameter

Receives:
```
scrollPane &pane
int x
int y
const char text[]
```

Returns:
```
1 if it executed successfully else 0
```

### showScrollPane(scrollPane) :

It shows the scrollPane and it runs into a loop until the user hit ESC key
The user can change the displayed lines with hitting UP, DOWN, PAGE UP or PAGE DOWN keys.

Receives:
```
scrollPane pane
```

### readInt(int, int, int, int) : int

It requests an int input.
Send the previous value in `showPrevious` and it will enable the edit ancient value feature

Receives:
```
int x
int y
int maxLength
int showPrevious default 0
```
Returns:
```
int
```

### readFloat(int, int, int, float) : float

It requests a float input.
Send the previous value in `showPrevious` and it will enable the edit ancient value feature

Receives:
```
int x
int y
int maxLength
float showPrevious default 0
```
Returns:
```
float
```

### readString(char [], int, int, int, int) : void

It requests a string input.
Send 1 in `showPrevious` and it will enable the edit ancient value feature

Receives:
```
char variable[]
int x
int y
int maxLength
int showPrevious default 0
```
Returns:
```
void
```

### readChar(int, int, char) : char

It requests a char input.
Send the previous in `showPrevious` and it will enable the edit ancient value feature

Receives:
```
int x
int y
char showPrevious default 0
```
Returns:
```
char
```

### readMaskedString(char [], const char[], int, int, int) : void

It requests a masked string input.
Send 1 in `showPrevious` and it will enable the edit ancient value feature.
```
Masks char:

'd' => digit
'a' => lower alpha
'A' => upper alpha
'x' => all the above
```
```
Masks examples:

"AAA-dddd" => Acceptable value : "DEA-1234"
"a.dt xA"  => Acceptable value : "f.5t gR"
```
Receives:
```
char variable[]
const char mask[]
int x
int y
int showPrevious default 0
```
Returns:
```
void
```

### readPassword(char [], char, int, int, int) : void

It requests a password input.

Receives:
```
char variable[]
char mask
int x
int y
int maxLength
```
Returns:
```
void
```



## Example:

```
#include <stdio.h>
#include "interio.h"

int main(){
	setCanvas('#', 1, 0, 2, 0); //border, notification_area, title_area, textcolor, backgroundcolor
	showTitle("Title");
	drawCanvas(); // IT DRAWS A FRAME FOR YOUR APPLICATION
	breadcrumb home = setBreadcrumb("Home");
	
	printCenter("Menu", 9);
	
	
	menu mainMenu = setMenu(10); // CREATES A NEW MENU VARIABLE setMenu(int yStart)
	addMenuOption(mainMenu, "Option 1 (Login)", 1); // FIRSTLY THE MENU, SECONDLY THE LABEL AND, FINALLY, THE ENABLED
	addMenuOption(mainMenu, "Option 2 (Disabled)", 0); //THIS OPTION IS DISABLED
	addMenuOption(mainMenu, "Exit");
	
	breadcrumb option1 = setBreadcrumb("Option 1", &home);
	
	int coord;
	
	do{
		clearCanvas();
	
		showBreadcrumbs(home);
	
		coord = showMenu(mainMenu); // THIS DRAWS MENU AND GETS COORD WHEN USER PRESSES ENTER
		
		showToast("You selected some option"); // IT SHOWS ON NOTIFICATION AREA WHICH OPTION HAVE BEEN SELECTED
		
		switch(coord){
			case 0:
				char user[10], psswd[15];
				clearCanvas(); // IT CLEANS THE AREA INSIDE THE CANVAS, NEVER OUTSIDE
				showBreadcrumbs(option1);
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
```
