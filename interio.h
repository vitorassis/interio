/*
* Developed by Vitor Assis Camargo, at 2019
* version 1.0.1
* Certify you have conio2.h installed in your PC before using this library
* THIS ONLY RUNS ON WINDOWS MACHINES!
* If you like 
*/

#include <conio2.h>
#include <locale.h>
#include <string.h>

#define border []

#define clearScreen clrscr

void clearCoordinates(int xi, int yi, int xf=0, int yf=0){ 	
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
	                                  
void clearCanvas(){               
	clearCoordinates(2, 4, 79, 21);   
}

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

void drawCanvas(){ 	
	drawLine(1, 80, 1); //TOP
	drawLine(1, 24, 1, 1); //LEFT
	drawLine(1, 80, 24); //BOTTOM
	drawLine(1, 24, 80, 1); //RIGHT
	
}

void removeToast(){ //REMOVE NOTIFICATION TEXT
	clearCoordinates(2, 22, 79, 22);
}

int centralize(const char texto[]){ //CENTRALIZE TEXT
	return (78-strlen(texto))/2;
}

void showToast(const char texto[]){ //SHOW NOTIFICATION TEXT
	removeToast();
	gotoxy(centralize(texto), 22);printf("* %s *", texto);
}
int readIntVariable(int xi, int yi, int xf, int yf, int previous=0){ //IT SHOWS INT INPUT
	int aux;
	int clear_untill;
	clearCoordinates(xi, yi, xf, yf);
	if(previous != 0){
		gotoxy(xi, yi+1); printf("(Atual: %d)", previous);
	}
	fflush(stdin);
	gotoxy(xi, yi); scanf("%d",&aux);
	
	if(previous != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
	}
	
	return aux;
}

float readFloatVariable(int xi, int yi, int xf, int yf, float previous=0){ //IT SHOWS FLOAT INPUT
	float aux;
	int clear_untill;
	clearCoordinates(xi, yi, xf, yf);
	if(previous != 0){
		gotoxy(xi, yi+1); printf("(Atual: %.1f)", previous);
	}
	fflush(stdin);
	gotoxy(xi, yi); scanf("%f", &aux);
	if(previous != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
	}
	
	return aux;
}

void readStringVariable(char variable[], int xi, int yi, int xf, int yf, int previous = 0){ //IT SHOWS STRING INPUT
	int clear_untill;
	char ancient[40];
	clearCoordinates(xi, yi, xf, yf);
	if(previous){
		strcpy(ancient, variable);
		gotoxy(xi, yi+1); printf("(Atual: %s)", variable);
	}
	fflush(stdin);
	gotoxy(xi, yi); gets(variable);
	
	if(previous != 0){
		clear_untill = xf+10 < 79 ? xf+10 : 79;
		clearCoordinates(xi, yi+1, clear_untill, yf+1);
		if(stricmp(variable, "\0") == 0){
			gotoxy(xi, yi); printf("%s", ancient);
			strcpy(variable, ancient);
		}
	}
}

int showMenu(char options[][50], int min, int max, int x=9, char cursor=187){ //IT SHOWS CUSTOMIZED VERTICAL MENU AND RETURNS THE COORDINATE
	int coord = min;
	char tecla;
	int size = max-min;
	
	clearCoordinates(x, min, x+25, max);
	
	for(int i=0; i<=size; i++){
		gotoxy(x, i+min);printf("%s", options[i]);
	}
	do{
		gotoxy(x-2, coord);printf("%c", cursor);
		tecla = getch();
		clearCoordinates(x-2, coord, x-1, coord);
		
		switch(tecla){
			case 72:
				coord = coord-1<min ? max : coord-1;
				break;
			case 80:
				coord = coord+1>max ? min : coord+1;
		}
	}while(tecla != 13);
	
	return coord;
}
