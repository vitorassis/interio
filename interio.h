/*
* Developed by Vitor Assis Camargo, at 2019
* version 1.0.3
* Certify you have conio2.h installed in your PC before using this library
* THIS ONLY RUNS ON WINDOWS MACHINES!
* If you like 
*/

#include <conio2.h>
#include <locale.h>
#include <string.h>

#define border []

#define clearScreen clrscr

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
	clearCoordinates(2, 4, 79, 21);   
}


/*
*	@param xi int
*	@param yi int
*	@param xf int default 0
*	@param yf int default 0
*	
*	@returnType void
*/
void drawLine(int start, int finish, int coordinate, int horizontal=0){
	int i;
	for (i=start; i<=finish; i++){
		if(!horizontal)
			gotoxy(i, coordinate);
		else
			gotoxy(coordinate, i);
		printf("*");
	}
}


/*	
*	@returnType void
*/
void drawCanvas(){ 	//IT DRAWS CANVAS FRAME BORDERING THE WINDOW
	drawLine(1, 80, 1); //TOP
	drawLine(1, 24, 1, 1); //LEFT
	drawLine(1, 80, 24); //BOTTOM
	drawLine(1, 24, 80, 1); //RIGHT
	
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
*	
*	@returnType void
*/
void showToast(const char texto[]){ //SHOW NOTIFICATION TEXT
	removeToast();
	gotoxy(centralize(texto), 22);printf("* %s *", texto);
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
	int aux;
	int clear_untill;
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious != 0){
		gotoxy(xi, yi+1); printf("(Atual: %d)", showPrevious);
	}
	fflush(stdin);
	gotoxy(xi, yi); scanf("%d",&aux);
	
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
	}
	
	return aux;
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
	float aux;
	int clear_untill;
	clearCoordinates(xi, yi, xf, yf);
	if(showPrevious != 0){
		gotoxy(xi, yi+1); printf("(Atual: %.1f)", showPrevious);
	}
	fflush(stdin);
	gotoxy(xi, yi); scanf("%f", &aux);
	if(showPrevious != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
	}
	
	return aux;
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
void readMaskedString(char variable[], char mask[], int xi, int y, int xf, int showPrevious = 0){ //IT SHOWS STRING INPUT
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
	while(pos < len && tecla != 13){
		tecla = getch();
		
		if(tecla == 8){ //BASCKSPACE
			if(pos>0)
				pos--;
			while(pos>0 && mask[pos] != 'd' && mask[pos] != 'a' && mask[pos] != 'A' && mask[pos] != 'x')
				pos--;
			variable[pos] = ' ';
		}else{
			removeToast();
			switch(mask[pos]){
				case 'd':
					if(tecla >= '0' && tecla <= '9'){
						variable[pos] = tecla;
						pos++;
						while(mask[pos] != 'd' && mask[pos] != 'a' && mask[pos] != 'A' && mask[pos] != 'x')
							pos++;
						caracter = tecla;
					}
					break;
				case 'a':
					if(tecla >= 'a' && tecla <= 'z'){
						variable[pos] = tecla;
						pos++;
						while(mask[pos] != 'd' && mask[pos] != 'a' && mask[pos] != 'A' && mask[pos] != 'x')
							pos++;
						caracter = tecla;
					}
					break;
				case 'A':
					if(tecla >= 'A' && tecla <= 'Z'){
						variable[pos] = tecla;
						pos++;
						while(mask[pos] != 'd' && mask[pos] != 'a' && mask[pos] != 'A' && mask[pos] != 'x')
							pos++;
						caracter = tecla;
					}
					break;
				case 'x':
					while((tecla >= '0' && tecla <= '9') || (tecla >= 'a' && tecla <= 'z') || (tecla >= 'A' && tecla <= 'Z')){
						variable[pos] = tecla;
						pos++;
						if(mask[pos] != 'd' && mask[pos] != 'a' && mask[pos] != 'A' && mask[pos] != 'x')
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
*	@param xi int
*	@param yi int
*	@param xf int
*	@param yf int
*	@param showPrevious int default 0
*	
*	@returnType int => INT READ VARIABLE
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
