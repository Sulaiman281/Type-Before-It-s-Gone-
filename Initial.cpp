#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>

#define Random  0
#define D_Blue 1
#define D_Green  2
#define D_Cyan 3
#define D_Red 4
#define D_Pink 5
#define D_Yellow 6
#define L_Grey 7
#define D_Grey 8
#define L_Blue 9
#define L_Green 10
#define L_Cyan 11
#define L_Red 12
#define L_Pink 13
#define L_Yellow 14
#define White 15
#define BG_DBLUE 16
#define BG_DGREEN 32
#define BG_DCYAN 48
#define BG_DRED 64
#define BG_DPINK 80
#define BG_DYELLOW 96
#define BG_LGREY 112
#define BG_DGREY 128
#define BG_LBLUE 144
#define BG_LGREEN 160
#define BG_LCYAN 176
#define BG_LRED 192
#define BG_LPINK 208
#define BG_LYELLOW 224
#define BG_WHITE 240

using namespace std;

void setup();
void draw();
void logic();
void menu();
void showMessage(short color,string line);
void SetColor(short n);
void printLine(short size, short color1,short color2);
void PrintHands();
void cls();

int main(){
	showMessage(White,"Hello How are You.");
}

void showMessage(short lineColor,short starColor,string line){
	SetColor(starColor);
	cout<<"*	";
	SetColor(lineColor);
	cout<<line<<endl;
}

void printLine(short size, short color1,short color2){
	for(short i = 0; i < size; i++){
		if(i== 0 || i == size-1){
			SetColor(color1);
			cout<<"*";
		}else{
			SetColor(color2);
			cout<<"-";
		}
	}
}

void SetColor(short n){
	if(n ==0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%15+1);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),n);
}

void cls()
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    cout.flush();

    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
    
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
    SetConsoleCursorPosition(hOut, topLeft);
}
void PrintHands(){
	
	for(short col=1;col<=22;col++){
		for(short row=1;row<=80;row++){
			// little finger
			if(col-row==5 && col > 6 && col <12 &&row>2&&row<7) cout<<"*";
			else if(col == 7 && row == 3) cout<<"*";
			else if(col-row==2 && col > 6 && col <13 &&row>2&&row<7) cout<<"*";
			//left side of middle finger
			else if(row >=10 && row < 12 && col == 3) cout<<"*";
			else if(col >3 && col < 10 && row > 8 && row <= 12 && row % 3 == 0) cout<<"*";
			// Middle finger
			else if(col > 2 && col < 10 && row > 14 && row < 19 &&row % 3 ==0 ) cout<<"*";
			else if(col == 2 && row > 15 && row < 18) cout<<"*";
			// right side of middle finger
			else if(col > 3 && col < 10 && row > 20 && row < 25 && row % 3 == 0) cout <<"*";
			else if(col == 3 && row >21 && row < 24) cout<<"*";
			// Thumb
			else if(row >= 24 && row <=27 && col >9 && col < 12 && col - row == -15 ) cout<<"*";
			else if(row > 26 && row <31 && col > 7 && col < 11 && col+row == 38) cout<<"*";
			else if(row >32 && col > 7 && col < 10 && row < 35 && col - row == -25) cout<<"*";
			else if(row > 24 && row <35 && col > 8  && col+row == 43) cout<<"*";
			//hand 
			else if(col>=12 && col < 16&&row == 7) cout<<"*";
			else if(col>= 16 && row >7 && row < 11 && col-row== 8) cout<<"*";
			else if( col >=19 && row == 11) cout<<"*";
			else if( row == 23 && col>= 19) cout<<"*";
			//Right Hand Thumb
			else if(col >= 8 && row >=40 && row < 42 && col + row == 49) cout<<"*";
			else if(col > 9 && col <= 18 && row >=40 && row <=49 && col-row == -30) cout<<"*";
			else if(col >= 8 && row >42 && row < 47 && col-row == -35) cout<<"*";
			//Right Hand Finger Left side of middle finger
			else if(col>=9 && col <=11 && row >= 46 && row <=49 && col+row == 57) cout<<"*";
			else if(col>= 4 && col <= 8 && row >= 48 && row < 52 && row % 3 == 0) cout<<"*";
			else if(col == 3 && row > 48 && row < 51) cout<<"*";
			// right hand middle finger
			else if(col >= 3 && col <= 8 && row > 53 && row < 58&& row % 3 == 0) cout<<"*";
			else if(col == 2 && row > 54&& row < 57) cout<<"*";
			// right hand finger right side of middle finger
			else if(col >= 4 && col <= 8 && row > 59 && row < 64&& row % 3 == 0) cout<<"*";
			else if(col ==3 && col <=8 && row > 60 && row < 63 ) cout<<"*";
			// right hand little finger
			else if(col >= 7 && col <= 8 && row >64&& row <=69 && col+row==74) cout<<"*";
			else if(col == 6 && row == 69) cout<<"*";
			else if(col == 7 && row == 70) cout<<"*";
			else if(col >=8 && row >65 && row <=70 && col+row == 78) cout<<"*";
			// right hand
			else if(col>12 && col < 16&& row == 65) cout<<"*";
			else if(col>=16 && col<19 && row >61 && row <=65&& col+row==81) cout<<"*";
			else if(col >= 19 && row == 62) cout<<"*";
			else if(col>=19 && row == 49) cout<<"*";
			else cout<<" ";
		}
		cout<<endl;
		SetColor(Random);
	}
}
