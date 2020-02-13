/*
* Developed by Vitor Assis Camargo, at 2019
* version 2.1.0
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

//INICIO STRUCT MENU
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
//FIM STRUCT MENU

//INICIO STRUCT CANVAS
struct canvas{
	int notification_area;
	int border;
	int title_area;
	int forecolor;
	int backcolor;
}canvasSetting;
//FIM STRUCT CANVAS

/*
*	@param border char default '#'
*	@param notification_area int default 0 (this showss or not the notification area)
*	@param title_area int default 0 (this showss or not the title area)
*	@param forecolor int default 7
*	@param backcolor int default 0
*	
*	@returnType void
*/
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
*	@returnType void
*/                                  
void clearCanvas(){    //IT CLEANS INSIDE THE FRAME AREA
	int yi = canvasSetting.title_area ? 4 : 2;      
	int yf = canvasSetting.notification_area ? 19 : 21;
	clearCoordinates(2, yi, 79, yf);   
}


/*
*	@param start int
*	@param finish int
*	@param horizontal int default 0
*	@param border int default '#'
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
void hideCursor(){
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}


/*	
*	@returnType void
*/
void drawCanvas(){ 	//IT DRAWS CANVAS FRAME BORDERING THE WINDOW
	hideCursor();
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
	textbackground(0);
	clearCoordinates(2, 22, 79, 22);
}


/*
*	@param texto[] char
*	
*	@returnType int => CENTER X
*/
int centralize(const char texto[]){ //CENTRALIZE TEXT
	return ((78-strlen(texto))/2) +1;
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

void showTitle(const char title[], int color=7){
	textcolor(color);
	printCenter(title, 2);
	textcolor(7);
}

/*
*	@param text[] char
*	
*	@returnType void
*/
void showToast(const char text[], int type=7){ //SHOW NOTIFICATION TEXT
	removeToast();
	textcolor(type);
	textbackground(0);
	gotoxy(centralize(text), 22);printf("* %s *", text);
	textcolor(7);
}


/*
*	@param x int
*	@param y int
*	@param maxLength int
*	@param showPrevious int default 0
*	
*	@returnType int => INT READ VARIABLE
*/
int readInt(int x, int y, int maxLength, int showPrevious=0){ //IT SHOWS INT INPUT
	int yi, yf=yi=y;
	int sizeInt = maxLength;
	char aux[sizeInt];
	int clear_untill;
	clearCoordinates(x, yi, x+maxLength, yf);
	if(showPrevious != 0){
		gotoxy(x, yi+1); printf("(%d)", showPrevious);
	}
	textbackground(8);
	textcolor(0);
	for(int i = x; i<x+maxLength; i++){
		gotoxy(i, y);printf(" ");
	}
	fflush(stdin);
	gotoxy(x, yi); 
	
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
		clearCoordinates(x, yi, x+maxLength, yf);
		gotoxy(x, yi); puts(aux);
	}
	
	aux[pos] = '\0';
	
	textbackground(0);
	textcolor(7);
	if(showPrevious != 0){
		if(stricmp(aux, "\0") == 0){
			gotoxy(x, yi); printf("%d", showPrevious);
		}
		clear_untill = x+maxLength+10 < 79 ? x+maxLength+10 : 79;
		clearCoordinates(x, yi+1, clear_untill, yf+1);
	}	
	clearCoordinates(x, y, x+maxLength, y);
	int retorno = showPrevious ? stricmp(aux, "\0") == 0 ? showPrevious : atoi(aux) : atoi(aux);
	gotoxy(x, yi); printf("%d",retorno);
	return retorno;
}


/*
*	@param x int
*	@param y int
*	@param maxLength int
*	@param showPrevious int default 0
*	
*	@returnType float => FLOAT READ VARIABLE
*/
float readFloat(int x, int y, int maxLength, float showPrevious=0){ //IT SHOWS FLOAT INPUT
	int yi, yf=yi=y;
	int sizeFloat = maxLength;
	char aux[sizeFloat];
	int clear_untill;
	clearCoordinates(x, yi, x+maxLength, yf);
	if(showPrevious != 0){
		gotoxy(x, yi+1); printf("(%.1f)", showPrevious);
	}
	textbackground(8);
	textcolor(0);
	for(int i = x; i<x+maxLength; i++){
		gotoxy(i, y);printf(" ");
	}
	
	fflush(stdin);
	gotoxy(x, y); 
	
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
		clearCoordinates(x, yi, x+maxLength, yf);
		gotoxy(x, yi); puts(aux);
	}
		
	textbackground(0);
	textcolor(7);
	aux[pos] = '\0';
	if(showPrevious != 0){
		if(stricmp(aux, "\0") == 0){
			gotoxy(x, yi); printf("%.1f", showPrevious);
		}
		clear_untill = x+maxLength+10 < 79 ? x+maxLength+10 : 79;
		clearCoordinates(x, yi+1, clear_untill, yf+1);
	}
	clearCoordinates(x, yi, clear_untill, yf);
	float retorno = showPrevious ? stricmp(aux, "\0") == 0 ? showPrevious : atof(aux) : atof(aux);
	gotoxy(x, yi); printf("%.1f", retorno);
	
	return retorno;
}


/*
*	@param variable[] char
*	@param x int
*	@param y int
*	@param maxLength int
*	@param showPrevious int default 0
*
*	@returnType void
*/
void readString(char variable[], int x, int y, int maxLength, int showPrevious = 0){ //IT SHOWS STRING INPUT
	char ancient[maxLength];
	char tecla='\0';
	
	strcpy(ancient, variable);
	strcpy(variable, "\0");
	
	
	if(showPrevious){
		gotoxy(x+1, y+1);printf("(%s)", ancient);
	}
	
	textcolor(0);
	textbackground(8);
	
	clearCoordinates(x, y, x+maxLength, y);
	
	
	int pos=0;
	int size=0;
	
	while(tecla != 13){
		tecla = getch();
		
		switch(tecla){
			case 8: //backspace
				if(size > 0 && pos > 0){
					for(int i=pos-1; i<size; i++)
						variable[i] = variable[i+1];
					size--;
					pos--;
					variable[size] = '\0';
				}
				break;
			case 9: //tab
				break;
			case -32:
			case 0:
				tecla = getch();
				switch(tecla){
					case 71: //home
						pos = 0;
						break;
					case 75: //seta pra esquerda
						if(pos > 0)
							pos--;
						break;
					case 77: //seta pra direita
						if(pos < size)
							pos++;
						break;
					case 79: //end
						pos = size;
						break;
				}
				break;
			
			default:
				
				if(size <= maxLength && tecla !=13){
					if(pos != size)
						for(int i=size; i>pos; i--)
							variable[i] = variable[i-1];
							
					variable[pos] = tecla;
					size++;
					pos++;
					variable[size] = '\0';
				}
			
		}
		
		gotoxy(x, y);
		
		if(tecla!= 13)
			for(int i=0; i<maxLength; i++){
				if(i==pos){
					textcolor(7);
					textbackground(0);
				}
				if(i<size)
					printf("%c", variable[i]);
				else
					printf(" ");
				if(i==pos){
					textcolor(0);
					textbackground(8);
				}
			}
		
	}
	textbackground(0);
	textcolor(7);
	
	if(showPrevious){
		if(strlen(variable) == 1){
			strcpy(variable, ancient);
			size = strlen(ancient);
		}
		int clear_untill = x+maxLength+10 < 79 ? x+maxLength+10 : 79;
		clearCoordinates(x, y+1, clear_untill, y+1);
	}
	clearCoordinates(x, y, x+maxLength, y);
	variable[size] = '\0';
	gotoxy(x, y); printf("%s", variable);
}


/*
*	@param x int 
*	@param y int
*	@param showPrevious default 0
*/
char readChar(int x, int y, char showPrevious = 0){ //IT SHOWS CHAR INPUT
	if(showPrevious){
		gotoxy(x+1, y+1);printf("(%c)", showPrevious);
	}
	
	textcolor(0);
	textbackground(8);
	
	clearCoordinates(x, y, x, y);
	
	char tecla = 0;
	int again=1;
	
	gotoxy(x, y);
	do{
		if(again)
			tecla = getch();
		
		switch(tecla) {
			case -32:
			case 0:
				tecla = getch();
				again = 1;
				break;
			default:
				again = 0;
		}
	}while(again);	
	
	textcolor(7);
	textbackground(0);
	
	int clear_untill;
	
	if(showPrevious != 0){
		if(tecla == 13){
			gotoxy(x, y); printf("%c", showPrevious);
		}
		clear_untill = x+1+10 < 79 ? x+1+10 : 79;
		clearCoordinates(x, y+1, clear_untill, y+1);
	}	
	clearCoordinates(x, y, x, y);
	int retorno = showPrevious ? tecla == 13 ? showPrevious : tecla : tecla;
	gotoxy(x, y); printf("%c",retorno);
	
	return retorno;
}



int maskChar(char caracter){
	return caracter == 'd' || caracter == 'a' || caracter == 'A' || caracter == 'x';
}

/*
*	@param variable[] char
*	@param mask[] char
*	@param x int
*	@param y int
*	@param maxLength int
*	@param showPrevious int default 0
*
*	@returnType void
*/
void readMaskedString(char variable[], const char mask[], int xi, int y, int showPrevious = 0){ //IT SHOWS STRING INPUT
	int yi, yf=yi=y;
	int clear_untill;
	char ancient[40];
	strcpy(ancient, variable);
	strcpy(variable, mask);
	int len = strlen(mask);
	int xf = xi+len;
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious){
		gotoxy(xi, yi+1); printf("(%s)", ancient);
	}
	
	textcolor(0);
	textbackground(8);
	for(int i = xi; i<xf; i++){
		gotoxy(i, y);printf(" ");
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
	textcolor(7);
	textbackground(0);
	variable[pos] = '\0';
		
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
		if(stricmp(variable, "\0") == 0){
			gotoxy(xi, yi); printf("%s", ancient);
			strcpy(variable, ancient);
		}
	}
	
	clearCoordinates(xi, yi, xf, yf);
	gotoxy(xi, yi); puts(variable);
}

/*
*	@param variable[] char
*	@param mask char
*	@param x int
*	@param y int
*	@param maxLength int
*	@param showPrevious int default 0
*
*	@returnType void
*/
void readPassword(char variable[], char mask, int x, int y, int maxLength){ //IT SHOWS STRING INPUT
	int yi, yf=yi=y;
	int clear_untill;
	strcpy(variable, "\0");
	
	clearCoordinates(x, yi, x+maxLength, yf);
	fflush(stdin);
	
	textbackground(8);
	textcolor(0);
	for(int i=x; i<x+maxLength; i++){
		gotoxy(i, y);printf(" ");
	}
	
	gotoxy(x, yi);
	char tecla='0';
	int pos=0;
	while(tecla != 13){
		tecla = getch();
		
		if(tecla == 8){ //BASCKSPACE
			
			if(pos>0)
				pos--;
			variable[pos] = '\0';
		}else if(tecla != 13 && pos < maxLength){
			variable[pos] = tecla;
			variable[pos+1] = '\0';
			pos++;
		}
		clearCoordinates(x, yi, x+maxLength, yf);
		gotoxy(x, yi); 
		for(int j=0; j<strlen(variable); j++)
			printf("%c", mask);
	}
	
	variable[pos] = '\0';
	
	textcolor(7);
	textbackground(0);
	clearCoordinates(x, yi, x+maxLength, yf);
	gotoxy(x, yi); 
	for(int j=0; j<strlen(variable); j++)
		printf("%c", mask);
}


/*
*	@param menuSettings menu
*	
*	@returnType int => SELECTED INT MENU INDEX (THE SAME ORDER YOU ADDED)
*/
int showMenu(menu menuSettings, int option=0){ //IT SHOWS CUSTOMIZED VERTICAL MENU AND RETURNS THE INDEX
	int coord;
	int y;
	for(y=option; y<menuSettings.menu_size && !menuSettings.options[y].enabled; y++);
	
	coord = menuSettings.min + y;
	menuSettings.max = menuSettings.min + menuSettings.menu_size-1;
	char tecla;
	
	clearCoordinates(menuSettings.x, menuSettings.min, menuSettings.x+25, menuSettings.max);
	
	for(int i=0; i<menuSettings.menu_size; i++){
		gotoxy(menuSettings.x, i+menuSettings.min);
		if(!menuSettings.options[i].enabled)
			textcolor(4);
		printf("%s", menuSettings.options[i].option);
		if(!menuSettings.options[i].enabled)
			textcolor(7);
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
				while(!menuSettings.options[coord-menuSettings.min].enabled && coord <= menuSettings.max)
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
