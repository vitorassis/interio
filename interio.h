/*
* Developed by Vitor Assis Camargo, at 2019
* version 2.0.0
* Certify you have conio2.h installed in your PC before using this library
* THIS ONLY RUNS ON WINDOWS MACHINES!
* If you like, share, pull and enjoy it!
*/

#include <conio2.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

#define clearScreen clrscr

#define TOAST_SUCCESS 10
#define TOAST_WARNING 6
#define TOAST_ERROR 4

struct menuOption{
	char option[50];
	int enabled;
};

struct menu{
	int min;
	int max;
	int x;
	char cursor;
	menuOption options[20];
	int menu_size;
};

struct canvas{
	int notification_area;
	int border;
	int title_area;
	int forecolor;
	int backcolor;
}canvasSetting;



void setCanvas(char border='#', int notification_area=0, int title_area=0, int forecolor=7, int backcolor=0){
	canvasSetting.border = border;
	canvasSetting.backcolor = backcolor;
	canvasSetting.forecolor = forecolor;
	canvasSetting.notification_area = notification_area;
	canvasSetting.title_area = title_area;
}


/*
*	@param yStart int
*	@param x int default 30
*	@param cursor char default '>'
*	
*	@returnType menu
*/
menu setMenu(int yStart, int x=30, char cursor='>'){ //IT INITIALIZES THE MENU OBJECT
	menu _menu;
	_menu.min = yStart;
	_menu.x = x;
	_menu.cursor = cursor;
	_menu.menu_size = 0;
	return _menu;
}


/*
*	@param _menu menu
*	@param option[] char
*	@param enabled int default 1
*	
*	@returnType menu => CREATED MENU
*/
void addMenuOption(menu &_menu, const char option[], int enabled=1){ //IT ADDS A NEW MENU OPTION
	void showToast(const char[]), removeToast();
	strcpy(_menu.options[_menu.menu_size].option, option);
	_menu.options[_menu.menu_size].enabled = enabled;
	_menu.menu_size++;
}


/*
*	@param _menu menu
*	
*	@returnType void
*/
void clearMenuOptions(menu &_menu){
	_menu.menu_size = 0;
}


/*
*	@param xi int
*	@param yi int
*	@param xf int default 0
*	@param yf int default 0
*	
*	@returnType void
*/
void clearCoordinates(int xi, int yi, int xf=0, int yf=0){ 	//IT CLEANS INSIDE THE DETERMINED AREA
	xi = xi<1? 1 : xi;
	yi = yi<1? 1 : yi;
	
	xf = xf==0? xi : xf;
	yf = yf==0? yi : yf;
	
	int x, y;
	for (x = xi; x<=xf; x++){
		for (y = yi; y<=yf; y++){
			gotoxy(x, y);printf(" ");
		}                                                     
	}                             
}


/*
*	@param xi int
*	@param yi int
*	@param xf int default 0
*	@param yf int default 0
*	
*	@returnType void
*/                                  
void clearCanvas(){    //IT CLEANS INSIDE THE FRAME AREA
	int yi = canvasSetting.title_area ? 4 : 2;      
	int yf = canvasSetting.notification_area ? 19 : 21;
	clearCoordinates(2, yi, 79, yf);   
}


/*
*	@param xi int
*	@param yi int
*	@param xf int default 0
*	@param yf int default 0
*	
*	@returnType void
*/
void drawLine(int start, int finish, int coordinate, int horizontal=0, char border='*'){
	int i;
	for (i=start; i<=finish; i++){
		if(!horizontal)
			gotoxy(i, coordinate);
		else
			gotoxy(coordinate, i);
		printf("%c", border);
	}
}


/*	
*	@returnType void
*/
void drawCanvas(){ 	//IT DRAWS CANVAS FRAME BORDERING THE WINDOW
	textcolor(canvasSetting.forecolor);
	textbackground(canvasSetting.backcolor);
	
	drawLine(1, 80, 1, 0, canvasSetting.border); //TOP
	drawLine(1, 24, 1, 1, canvasSetting.border); //LEFT
	drawLine(1, 80, 24, 0, canvasSetting.border); //BOTTOM
	drawLine(1, 24, 80, 1, canvasSetting.border); //RIGHT
	if(canvasSetting.notification_area)
		drawLine(1, 80, 20, 0, canvasSetting.border); //BOTTOM
	if(canvasSetting.title_area)
		drawLine(1, 80, 3, 0, canvasSetting.border); //TOP
	textcolor(7);
	textbackground(0);
	
}

/*
*	@returnType void
*/
void removeToast(){ //REMOVE NOTIFICATION TEXT
	clearCoordinates(2, 22, 79, 22);
}


/*
*	@param texto[] char
*	
*	@returnType int => CENTER X
*/
int centralize(const char texto[]){ //CENTRALIZE TEXT
	return (78-strlen(texto))/2;
}

/*
*	@param texto[] char
*	@param y int
*	
*	@returnType void
*/
void printCenter(const char text[], int y){
	gotoxy(centralize(text), y);puts(text);
}

/*
*	@param texto[] char
*	
*	@returnType void
*/
void showToast(const char texto[], int type=7){ //SHOW NOTIFICATION TEXT
	removeToast();
	textcolor(type);
	gotoxy(centralize(texto), 22);printf("* %s *", texto);
	textcolor(7);
}


/*
*	@param xi int
*	@param y int
*	@param xf int
*	@param showPrevious int default 0
*	
*	@returnType int => INT READ VARIABLE
*/
int readInt(int xi, int y, int xf, int showPrevious=0){ //IT SHOWS INT INPUT
	int yi, yf=yi=y;
	int sizeInt = 32;
	char aux[sizeInt];
	int clear_untill;
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious != 0){
		gotoxy(xi, yi+1); printf("(Atual: %d)", showPrevious);
	}
	fflush(stdin);
	gotoxy(xi, yi); 
	
	aux[0] = '\0';
	char tecla='0';
	int pos=0;
	while(tecla != 13){
		tecla = getch();
		
		if(tecla == 8){ //BASCKSPACE
			
			if(pos>0)
				pos--;
			aux[pos] = '\0';
		}else if(tecla != 13 && isdigit(tecla) && pos < sizeInt){
			
			aux[pos] = tecla;
			aux[pos+1] = '\0';
			pos++;
		}
		clearCoordinates(xi, yi, xf, yf);
		gotoxy(xi, yi); puts(aux);
	}
	
	aux[pos] = '\0';
	
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
	}
	
	return atoi(aux);
}


/*
*	@param xi int
*	@param y int
*	@param xf int
*	@param showPrevious int default 0
*	
*	@returnType float => FLOAT READ VARIABLE
*/
float readFloat(int xi, int y, int xf, float showPrevious=0){ //IT SHOWS FLOAT INPUT
	int yi, yf=yi=y;
	int sizeFloat = 64;
	char aux[sizeFloat];
	int clear_untill;
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious != 0){
		gotoxy(xi, yi+1); printf("(Atual: %.1f)", showPrevious);
	}
	fflush(stdin);
	gotoxy(xi, yi); 
	
	aux[0] = '\0';
	char tecla='0';
	int pos=0;
	while(tecla != 13){
		tecla = getch();
		
		if(tecla == 8){ //BASCKSPACE
			
			if(pos>0)
				pos--;
			aux[pos] = '\0';
		}else if(tecla != 13 && (isdigit(tecla) || tecla == '.') && pos < sizeFloat){
			
			aux[pos] = tecla;
			aux[pos+1] = '\0';
			pos++;
		}
		clearCoordinates(xi, yi, xf, yf);
		gotoxy(xi, yi); puts(aux);
	}
	
	aux[pos] = '\0';
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
	}
	
	return atof(aux);
}


/*
*	@param variable[] char
*	@param xi int
*	@param y int
*	@param xf int
*	@param showPrevious int default 0
*
*	@returnType void
*/
void readString(char variable[], int xi, int y, int xf, int showPrevious = 0){ //IT SHOWS STRING INPUT
	int yi, yf=yi=y;
	int clear_untill;
	char ancient[40];
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious){
		strcpy(ancient, variable);
		gotoxy(xi, yi+1); printf("(Atual: %s)", variable);
	}
	fflush(stdin);
	gotoxy(xi, yi); gets(variable);
	
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
		if(stricmp(variable, "\0") == 0){
			gotoxy(xi, yi); printf("%s", ancient);
			strcpy(variable, ancient);
		}
	}
}


int maskChar(char caracter){
	return caracter == 'd' || caracter == 'a' || caracter == 'A' || caracter == 'x';
}

/*
*	@param variable[] char
*	@param mask[] char
*	@param xi int
*	@param y int
*	@param xf int
*	@param showPrevious int default 0
*
*	@returnType void
*/
void readMaskedString(char variable[], const char mask[], int xi, int y, int xf, int showPrevious = 0){ //IT SHOWS STRING INPUT
	int yi, yf=yi=y;
	int clear_untill;
	char ancient[40];
	strcpy(variable, mask);
	int len = strlen(mask);
	
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious){
		strcpy(ancient, variable);
		gotoxy(xi, yi+1); printf("(Atual: %s)", variable);
	}
	fflush(stdin);
	gotoxy(xi, yi);
	char caracter;
	for(int i=0; i<len; i++){
		caracter = mask[i];
		switch(caracter){
			case 'd':
			case 'a':
			case 'A':
			case 'x':
				caracter = ' ';
		}
		printf("%c", caracter);
		variable[i] = caracter;
	}
	variable[len-1] = '\0';
	
	gotoxy(xi, yi);
	char tecla='0';
	int pos=0;
	int start=0;
	for(start; !maskChar(mask[start]); start++);
	pos=start;
	while(tecla != 13){
		tecla = getch();
		
		if(tecla == 8){ //BACKSPACE
			if(pos > start)
				pos--;
			while(pos>start && !maskChar(mask[pos]))
				pos--;
			variable[pos] = ' ';
		}else if(pos < len){
			removeToast();
			switch(mask[pos]){
				case 'd':
					if(isdigit(tecla)){
						variable[pos] = tecla;
						pos++;
						while(!maskChar(mask[pos]))
							pos++;
						caracter = tecla;
					}
					break;
				case 'a':
					if(isalpha(tecla) && islower(tecla)){
						variable[pos] = tecla;
						pos++;
						while(!maskChar(mask[pos]))
							pos++;
						caracter = tecla;
					}
					break;
				case 'A':
					if(isalpha(tecla) && isupper(tecla)){
						variable[pos] = tecla;
						pos++;
						while(!maskChar(mask[pos]))
							pos++;
						caracter = tecla;
					}
					break;
				case 'x':
					if((isdigit(tecla)) || (isalpha(tecla))){
						variable[pos] = tecla;
						pos++;
						while(!maskChar(mask[pos]))
							pos++;
						caracter = tecla;
					}
					break;
				default:
					pos++;
			}
		}
		gotoxy(xi, yi); puts(variable);
	}
	
	variable[pos] = '\0';
		
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
		if(stricmp(variable, "\0") == 0){
			gotoxy(xi, yi); printf("%s", ancient);
			strcpy(variable, ancient);
		}
	}
}

/*
*	@param variable[] char
*	@param mask char
*	@param xi int
*	@param y int
*	@param xf int
*	@param showPrevious int default 0
*
*	@returnType void
*/
void readPassword(char variable[], char mask, int xi, int y, int xf, int showPrevious = 0){ //IT SHOWS STRING INPUT
	int yi, yf=yi=y;
	int clear_untill;
	char ancient[40];
	strcpy(variable, "\0");
	
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious){
		strcpy(ancient, variable);
		gotoxy(xi, yi+1); printf("(Atual: %s)", variable);
	}
	fflush(stdin);
	
	gotoxy(xi, yi);
	char tecla='0';
	int pos=0;
	while(tecla != 13){
		tecla = getch();
		
		if(tecla == 8){ //BASCKSPACE
			
			if(pos>0)
				pos--;
			variable[pos] = '\0';
		}else if(tecla != 13){
			removeToast();
			
			variable[pos] = tecla;
			variable[pos+1] = '\0';
			pos++;
		}
		clearCoordinates(xi, yi, xf, yf);
		gotoxy(xi, yi); 
		for(int j=0; j<strlen(variable); j++)
			printf("%c", mask);
	}
	
	variable[pos] = '\0';
		
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
		if(stricmp(variable, "\0") == 0){
			gotoxy(xi, yi); printf("%s", ancient);
			strcpy(variable, ancient);
		}
	}
}


/*
*	@param menuSettings menu
*	
*	@returnType int => SELECTED INT MENU INDEX (THE SAME ORDER YOU ADDED)
*/
int showMenu(menu menuSettings){ //IT SHOWS CUSTOMIZED VERTICAL MENU AND RETURNS THE INDEX
	int coord;
	int y;
	for(y=0; y<menuSettings.menu_size && !menuSettings.options[y].enabled; y++);
	
	coord = menuSettings.min + y;
	
	menuSettings.max = menuSettings.min + menuSettings.menu_size-1;
	char tecla;
	
	clearCoordinates(menuSettings.x, menuSettings.min, menuSettings.x+25, menuSettings.max);
	
	for(int i=0; i<menuSettings.menu_size; i++){
		gotoxy(menuSettings.x, i+menuSettings.min);printf("%s", menuSettings.options[i].option);
	}
	do{
		gotoxy(menuSettings.x-2, coord);printf("%c", menuSettings.cursor);
		tecla = getch();
		clearCoordinates(menuSettings.x-2, coord, menuSettings.x-1, coord);
		
		switch(tecla){
			case 72:
				coord = coord-1<menuSettings.min ? menuSettings.max : coord-1;
				while(!menuSettings.options[coord-menuSettings.min].enabled && coord-menuSettings.min >= 0)
					coord--;
				coord = coord < menuSettings.min ? menuSettings.max : coord;
				break;
			case 80:
				coord = coord+1>menuSettings.max ? menuSettings.min : coord+1;
				while(!menuSettings.options[coord-menuSettings.min].enabled && coord < menuSettings.max)
					coord++;
				coord = coord > menuSettings.max ? menuSettings.min : coord;
		}
	}while(tecla != 13);
	
	return coord-menuSettings.min;
}


/*
*	@param vetor[] int
*	@param size int
*	
*	@returnType void
*/
void dumpIntVector(int vetor[], int size){

	clearScreen();
	
	printf("Array => (\n");
	for(int i=0; i<size; i++){
		printf("\t[%d] => %d\n", i, vetor[i]);
	}
	printf(")");
	getch();
	clearScreen();
	drawCanvas();
}
