#include <graphics.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fstream>

using namespace std;

#define Black  0
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

#define P_emptyF 0
#define P_soldF 1
#define P_lineF 2
#define P_ltslashF 3
#define P_slashF 4
#define P_bkslashF 5
#define P_ltbkslashF 6
#define P_hatchF 7
#define P_xhatchF 8
#define P_interleaveF 9
#define P_widedotF 10
#define P_closedotF 11
#define P_userF 12

#define MENU 0
#define PLAYGAMEMENU 1
#define _TBIG 2
#define WORDSHUFFLE 3
#define RANDOMKEY 4
#define FALLINGWORD 5
#define HELP 6
#define RECORDS 7
#define HIGHSCORE 8
#define STREETWORD 9
#define SETTIME 10
#define EXIT 11
#define ABOUTME 12
#define RESUME 13
#define HALFSEC 14
#define ONESEC 15
#define TWOSEC 16

void User_Input();
void SetColor(short n);
void Menu();
void Set_Time();
void PlayGamesMenu();
void PlayGames(short index);
void TBIG();
string RandomWord();
void Timer();
void SetGameTime();
void WordShuffle();
void PrintText(short _x,short _y, string _word , short _col);
void Reset();
void RandomKey();
char GetRandomKey();
void Frame();
void FallingWord();
void AboutMe();
void Help();
void SaveStatus(int game);
void High_Score();
void StreetWord();
void DrawRoad();
void SaveRecord();
void ShowRecord();
void GameMenu();
void Loading();
void BlockWords();

float roadLinesX[5];

char PlayerName[15];
int Score;

float width = GetSystemMetrics(SM_CXSCREEN);
float height = GetSystemMetrics(SM_CYSCREEN);
char gName[] = "Typing Game";

int x = width/2;
int y = height/2;

bool GameOver = false;
bool GamePaused = false;
bool ButtonPressed = false;
int Seconds = 60;
int ps = 0;
int gameSec = 0;
int uSec = 60;
int shuffleTimer = 0;

int Word_Delay = 0;
int activeWord = -1;
bool ActiveWord = false;

int friction_Delay = 2;
bool StreetGameIsRunning = false;
int GameTimer = 0;

string RecordName[100];
int RecordScore[100];

class Word{
	private:
		float X;
	
		float mass;
		string word;
	public:
		float Y;
		Word(){
			X = rand()%(int)width/2+200;
			Y = -15;
			word = RandomWord();
		}
		
		void Reset(){
			X = rand() % (int)width/2 + 200;
			Y = -15;
			word = RandomWord();
			cleardevice();
		}
		int wordLength(){
			return word.length();
		}
		void setWordPos(float _x,float _y){
			X = _x;
			Y = _y;
		}
		void TypeWord(int _index){
			word[_index] = '-';
		}
		void AddForce(float _xforce,float _yforce){
			Y += _yforce;
			X += _xforce;
		}
		bool chMatch(int _index,char _ch){
			if(word[_index] == _ch)
				return true;
			else
				return false;
		}
		void SpawnWord(int _color){
			PrintText(X,Y,word,_color);
		}
		void NewWord(){
			word = RandomWord();
		}
};

class Vehicle{
	private:
		float X;
		float Y;
		float mass;
	public:
		Vehicle(float _x,float _y){
			X = _x;
			Y = _y;
			mass = 2;
		}
		void Print(){
			setlinestyle(1,P_soldF,3);
			setcolor(D_Red);
			arc(X,Y,-80,80,50);
			line(X,Y-45,X-60,Y-45);
			line(X,Y-46,X+8,Y-49);
			line(X-28,Y-45,X-35,Y-65);
			line(X-40,Y-45,X-40,Y-65);
			line(X-35,Y-65,X-40,Y-65);
			line(X-60,Y-45,X-90,Y-50);
			line(X-90,Y-50,X-140,Y-45);
			line(X-140,Y-45,X-145,Y);
			line(X-30,Y-30,X-100,Y-35);
			line(X-30,Y-30,X-100,Y-30);
			line(X-100,Y-30,X-100,Y-35);
			
			line(X-35,Y-25,X-35,Y+25);
			line(X-35,Y-25,X-20,Y-20);
		
			line(X-110,Y-20,X-110,Y+20);
			line(X-110,Y-20,X-125,Y-15);
			
			line(X-125,Y-15,X-125,Y+15);
			line(X-110,Y+20,X-125,Y+15);
			
			line(X-20,Y-20,X-20,Y+20);
			line(X-35,Y+25,X-20,Y+20);
			
			line(X,Y+45,X-60,Y+45);
			line(X,Y+46,X+8,Y+49);
			line(X-28,Y+45,X-35,Y+65);
			line(X-40,Y+45,X-40,Y+65);
			line(X-35,Y+65,X-40,Y+65);
			line(X-60,Y+45,X-90,Y+50);
			line(X-90,Y+50,X-140,Y+45);
			line(X-140,Y+45,X-145,Y);
			line(X-30,Y+30,X-100,Y+35);
			line(X-30,Y+30,X-100,Y+30);
			line(X-100,Y+30,X-100,Y+35);
		}
		void AddForce(float _force){
			float acce = _force/mass;
			X += acce;
		}
		bool GreaterThenWidth(){
			bool c;
			if(X+100 > width){
				c = true;
			}
			else c = false;
			
			return c;
		}
		bool LessThenWidth(){
			bool c;
			if(X+100 < 0){
				c = true;
			}
			else c = false;
			return c;
		}
};

class Button{
	private:
		int x;
		int y;
		int color;
		string Text;
		int Func;
		int Text_Length;
		int size;
		int dec;
		int inc;
	public:
		Button(int _x,int _y,int _col,int _func,string _Text){
			x = _x;
			y = _y;
			color = _col;
			Func = _func;
			Text = _Text;
			Text_Length = Text.length();
			size = (Text_Length+20)*8;
			dec = 20,inc = 15;
		}
		~Button(){
			ButtonPressed = false;
		}
		void Box(int _x,int _y){
			setlinestyle(1,P_soldF,8);
			line(_x-size/2,_y-dec,x+size/2,_y-dec);
			line(_x-size/2,_y+inc,x+size/2,_y+inc);
			line(_x-size/2,_y-dec,x-size/2,_y+inc);
			line(_x+size/2,_y-dec,x+size/2,_y+inc);
		}
		void Display(){
			settextjustify(1,1);
			settextstyle(10,0,2);
			PrintText(x,y,Text,color);
			Box(x,y);
			MouseClick();
		}
		void MouseClick(){
			int mX,mY;
			POINT cursorPosition;
			GetCursorPos(&cursorPosition);
			mX = cursorPosition.x;
			mY = cursorPosition.y;
			if(mX > x-size/2 && mX < x+size/2 && mY > y && mY < y+inc+20)
				color = D_Red;
			else
				color = L_Yellow;
			
			if(GetAsyncKeyState(VK_LBUTTON)){
				if(mX > x-size/2 && mX < x+size/2 && mY > y && mY < y+inc+20){
					color = L_Red;
					Loading();
					CallFunction();
					ButtonPressed = true;
				}
			}
		}
		void CallFunction(){
			switch(Func){
				case MENU:
					cleardevice();
					Menu();
					break;
				case PLAYGAMEMENU:
					cleardevice();
					PlayGamesMenu();
					break;
				case _TBIG:
					cleardevice();
					TBIG();
					break;
				case WORDSHUFFLE:
					cleardevice();
					WordShuffle();
					break;
				case RANDOMKEY:
					cleardevice();
					RandomKey();
					break;
				case FALLINGWORD:
					cleardevice();
					FallingWord();
					break;
				case HELP:
					cleardevice();
					Help();
					break;
				case RECORDS:
					cleardevice();
					ShowRecord();
					break;
				case HIGHSCORE:
					cleardevice();
					High_Score();
					break;
				case STREETWORD:
					cleardevice();
					StreetWord();
					break;
				case SETTIME:
					cleardevice();
					Set_Time();
					break;
				case ABOUTME:
					cleardevice();
					AboutMe();
					break;
				case RESUME:
					GamePaused = false;
					cleardevice();
					break;
				case HALFSEC:
					Seconds = 30;
					uSec = Seconds;
					PrintText(x,y+200,"Time is Set to 30 Seconds",L_Yellow);
					delay(2*1000);
					cleardevice();
					Menu();
					break;
				case ONESEC:
					Seconds = 60;
					uSec = Seconds;
					PrintText(x,y+200,"Time is Set to 30 Seconds",L_Yellow);
					delay(2*1000);
					cleardevice();
					Menu();
					break;
				case TWOSEC:
					Seconds = 120;
					uSec = Seconds;
					PrintText(x,y+200,"Time is Set to 30 Seconds",L_Yellow);
					delay(2*1000);
					cleardevice();
					Menu();
					break;
				case EXIT:
					exit(0);
					break;
			}
		}
};

main(){
	srand(time(NULL));
	initwindow(width,height,gName,50,50,true,true);
	setbkcolor(D_Green);
	
	User_Input();
	Menu();
	cleardevice();
}

void User_Input(){
	int n = 0;
	settextjustify(0,1);
	settextstyle(8,0,2);
	cleardevice();
	INPUT:
		Frame();
		line(x-100,y,x+100,y);
		line(x-100,y+50,x+100,y+50);
		line(x-100,y,x-100,y+50);
		line(x+100,y,x+100,y+50);
		PrintText(x-98,y-25,"Enter Your Name: ",L_Yellow);
		char ch = getch();
		if(GetAsyncKeyState(VK_BACK)){
			if(n>0){
				n--;
				PlayerName[n] = '\0';
				cleardevice();
				outtextxy(x-96,y+25,PlayerName);
			}
				
		}else{
			PlayerName[n] = ch;
			outtextxy(x-96,y+25,PlayerName);
			n++;
		}
	if(GetAsyncKeyState(VK_RETURN)){
		cleardevice();
		settextjustify(1,1);
		settextstyle(10,0,2);
		setcolor(L_Yellow);
		char ch[30];
		sprintf(ch,"Welcome %s To The Typing Game Project",PlayerName);
		outtextxy(x,y-50,ch);
		delay(2*1000);
	}
	else {
		goto INPUT;
	}
}

void Menu(){
	int page = getactivepage();
	Frame();
	Button B1(x,y-50,L_Yellow,PLAYGAMEMENU,"Play Games");
	Button B2(x,y,L_Yellow,SETTIME,"Set Time");
	Button B3(x,y+50,L_Yellow,HIGHSCORE,"Records");
	Button B4(x,y+100,L_Yellow,HELP,"Help");
	Button B5(x,y+150,L_Yellow,ABOUTME,"About Me");
	Button B6(x,y+200,L_Yellow,EXIT,"Exit");
	while(!ButtonPressed){
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
		Frame();
		B1.Display();
		B2.Display();
		B3.Display();
		B4.Display();
		B5.Display();
		B6.Display();
		delay(100);
		page = 1-page;
	}
}

void Set_Time(){
	int page = 0;
	ButtonPressed = false;
	Button b1(x,y-50,L_Yellow,HALFSEC,"30 Seconds");
	Button b2(x,y,L_Yellow,ONESEC,"One Minute");
	Button b3(x,y+50,L_Yellow,TWOSEC,"Two Minutes");
	Button b4(x,y+100,L_Yellow,MENU,"Back");
	while(!ButtonPressed){
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
		Frame();
		b1.Display();
		b2.Display();
		b3.Display();
		b4.Display();
		delay(100);
		page = 1-page;
	}
}

void PlayGamesMenu(){
	int page = getactivepage();
	ButtonPressed = false;
	Button B1(x,y-50,L_Yellow,_TBIG,"Type Before it's gone!");
	Button B2(x,y,L_Yellow,WORDSHUFFLE,"Word Shuffle");
	Button B3(x,y+50,L_Yellow,RANDOMKEY,"Random Key");
	Button B4(x,y+100,L_Yellow,FALLINGWORD,"Falling Word Game");
	Button B5(x,y+150,L_Yellow,STREETWORD,"Street Speed Challenge");
	Button B6(x,y+200,L_Yellow,MENU,"Back");
	
	while(!ButtonPressed){
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
		Frame();
		B1.Display();
		B2.Display();
		B3.Display();
		B4.Display();
		B5.Display();
		B6.Display();
		delay(100);
		page = 1-page;
	}
}

void GameMenu(int Game){
	int page = getactivepage();
	Reset();
	settextjustify(1,1);
	Button B1(x,y-50,L_Yellow,Game,"Restart");
	Button B2(x,y,L_Yellow,PLAYGAMEMENU,"Play Other Games");
	Button B3(x,y+50,L_Yellow,MENU,"Menu");
	Button B4(x,y+100,L_Yellow,EXIT,"Exit");
	
	while(!ButtonPressed){
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
		Frame();
		B1.Display();
		B2.Display();
		B3.Display();
		B4.Display();
		delay(100);
		page = 1-page;
	}
}
void TBIG(){
	Reset();
	float wX = 0,wY = y;
	float page = getactivepage(),speed = 0.09;
	string w = RandomWord();
	int wLength = w.length()-1;
	char ScoreString[30];
	char word[wLength+1];
	strcpy(word,w.c_str());
	int Type_Index = 0;
	SetGameTime();
	setbkcolor(0);
	cleardevice();
	shuffleTimer = 3;
	while(!GameOver){
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
		sprintf(ScoreString,"Score: %d \t\tTime: %d:%d",Score,Seconds/60,Seconds%60);
		setcolor(L_Cyan);
		settextjustify(0,1);
		outtextxy(50,y-50,ScoreString);
		
		if(shuffleTimer <= 0){
			speed += 0.02;
			shuffleTimer = 3;
		}
		if(wLength == Type_Index){
			w = RandomWord();
			wLength == w.length()-1;
			strcpy(word,w.c_str());
			char word[wLength+1];
			wLength  = w.length();
			wX = 0;
			Score++;
			Type_Index = 0;
			cleardevice();
		}
		if(wX > width){
			w = RandomWord();
			wLength == w.length();
			strcpy(word,w.c_str());
			wX = 0;
			Type_Index = 0;
			cleardevice();
		}
		setfillstyle(P_xhatchF,D_Cyan);
		bar(0,y-40,width,y-20);
		setcolor(L_Green);
		outtextxy(wX,wY,word);
		bar(0,y+20,width,y+40);
		wX = wX + speed;
		
		if(kbhit()){
			if(GetAsyncKeyState(VK_ESCAPE)){
				setactivepage(page);
				setvisualpage(1-page);
				page = 1- page;
				cleardevice();
				setactivepage(page);
				GamePaused = true;
				while(GamePaused){
					Button B1(x,y-50,L_Yellow,RESUME,"Resume");
					Button B2(x,y,L_Yellow,_TBIG,"Restart");
					Button B3(x,y+50,L_Yellow,PLAYGAMEMENU,"Play Others Games");
					Button B4(x,y+100,L_Yellow,EXIT,"Exit");
					
					while(!ButtonPressed){
						PrintText(x,y-100,"Game Paused",L_Yellow);
						B1.Display();
						B2.Display();
						B3.Display();
						B4.Display();
						delay(100);
						cleardevice();
					}
				}
			}
			char ch = getch();
			if(ch == word[Type_Index]){
				word[Type_Index] = '-';
				Type_Index++;
			}
			
		}
		Timer();
		page = 1-page;
	}
	setactivepage(page);
	setvisualpage(1-page);
	page = 1- page;
	cleardevice();
	setactivepage(page);
	Frame();
	settextjustify(1,1);
	SaveStatus(1);
	PrintText(x,y-50,"Game Over",L_Yellow);
	sprintf(ScoreString,"%s Your Score: %d",PlayerName,Score);
	outtextxy(x,y-25,ScoreString);
	delay(2*1000);
	getch();
	GameMenu(_TBIG);
}

void SetGameTime(){
	gameSec = clock()/1000;
}

void Timer(){
	int sec = clock()/1000-gameSec;
	if(sec > ps){
		Seconds--;
		if(shuffleTimer>0)
		shuffleTimer--;
		if(Word_Delay > 0)
		Word_Delay--;
		if(friction_Delay > 0)
		friction_Delay--;
		if(StreetGameIsRunning == true){
			GameTimer++;
		}
		ps = sec;
	}
	if(Seconds <= 0)
		GameOver = true;
	else
		GameOver = false;
}
void Reset(){
	Seconds = uSec;
	ps = 0;
	GameOver = false;
	Score = 0;
	setbkcolor(D_Green);
	StreetGameIsRunning = false;
	GameTimer = 0;
}
void WordShuffle(){
	Reset();
	settextjustify(0,1);
	settextstyle(10,0,2);
	setbkcolor(0);
	string word[7];
	string Word_To_Type;
	char ScoreString[100];
	int Type_Index = 0;
	int User_Index = 0;
	int wordLen;
	for(int i = 0; i<7;i++){
		word[i] = RandomWord();
	}
	SetGameTime();
	Word_To_Type = word[Type_Index];
	wordLen = Word_To_Type.length();
	shuffleTimer = 3;
	game:
		setfillstyle(P_hatchF,D_Red);
		Timer();
		if(wordLen == User_Index){
			cleardevice();
			Score++;
			User_Index = 0;
			if(Type_Index >= 6){
				Type_Index = 0;
				for(int i = 0; i<7;i++){
					word[i] = RandomWord();
				}
			}
			else
			Type_Index++;
			
			Word_To_Type = word[Type_Index];
			wordLen = Word_To_Type.length();
			shuffleTimer = 3;
		}
		if(shuffleTimer == 0){
			cleardevice();
			User_Index = 0;
			if(Type_Index >= 6){
				Type_Index = 0;
				for(int i = 0; i<7;i++){
					word[i] = RandomWord();
				}
			}
			else
			Type_Index++;
			Word_To_Type = word[Type_Index];
			wordLen = Word_To_Type.length();
			shuffleTimer = 3;
		}
		sprintf(ScoreString,"Score: %d              Time: %d:%d                 ShuffleTimer: %d",Score,Seconds/60,Seconds%60,shuffleTimer);
		settextjustify(1,1);
		bar(0,0,width,50);
		setcolor(White);
		outtextxy(width/2,25,ScoreString);
		settextjustify(0,1);
		PrintText(2,75,word[0],L_Blue);
		if(Type_Index == 0)
		PrintText(900,75,Word_To_Type,L_Blue);
		bar(0,100,width,150);
		PrintText(2,175,word[1],L_Green);
		if(Type_Index == 1)
		PrintText(900,175,Word_To_Type,L_Green);
		bar(0,200,width,250);
		PrintText(2,275,word[2],L_Red);
		if(Type_Index == 2)
		PrintText(900,275,Word_To_Type,L_Red);
		bar(0,300,width,350);
		PrintText(2,375,word[3],L_Cyan);
		if(Type_Index == 3)
		PrintText(900,375,Word_To_Type,L_Cyan);
		bar(0,400,width,450);
		PrintText(2,475,word[4],L_Yellow);
		if(Type_Index == 4)
		PrintText(900,475,Word_To_Type,L_Yellow);
		bar(0,500,width,550);
		PrintText(2,575,word[5],L_Pink);
		if(Type_Index == 5)
		PrintText(900,575,Word_To_Type,L_Pink);
		bar(0,600,width,650);
		PrintText(2,675,word[6],L_Blue);
		if(Type_Index == 6)
		PrintText(900,675,Word_To_Type,L_Blue);
		bar(0,700,width,750);
		
		if(kbhit()){
			if(GetAsyncKeyState(VK_ESCAPE)){
				GamePaused = true;
				while(GamePaused){
					Button B1(x,y-50,L_Yellow,RESUME,"Resume");
					Button B2(x,y,L_Yellow,WORDSHUFFLE,"Restart");
					Button B3(x,y+50,L_Yellow,PLAYGAMEMENU,"Play Others Games");
					Button B4(x,y+100,L_Yellow,EXIT,"Exit");
					
					while(!ButtonPressed){
						PrintText(x,y-100,"Game Paused",L_Yellow);
						B1.Display();
						B2.Display();
						B3.Display();
						B4.Display();
						delay(100);
						cleardevice();
					}
				}
			}
			char ch = getch();
			if(ch == Word_To_Type[User_Index]){
				Word_To_Type[User_Index] = '-';
				User_Index++;
			}
		}
	if(!GameOver)
		goto game;
	cleardevice();
	cleardevice();
	Frame();
	SaveStatus(2);
	settextjustify(1,1);
	PrintText(x,y-50,"Game Over",L_Yellow);
	sprintf(ScoreString,"%s Your Score: %d",PlayerName,Score);
	outtextxy(x,y-25,ScoreString);
	delay(2*1000);
	getch();
	GameMenu(WORDSHUFFLE);
}

void RandomKey(){
	char Type_Key;
	Type_Key = GetRandomKey();
	string KeyP;
	SetGameTime();
	settextstyle(10,0,3);
	settextjustify(1,0);
	setbkcolor(D_Green);
	char ScoreString[80];
	KeyP = Type_Key;
	Reset();
	while(!GameOver){
		Timer();
		Frame();
		sprintf(ScoreString,"Score: %d              Time: %d:%d",Score,Seconds/60,Seconds%60);
		PrintText(width/2,200,ScoreString,L_Cyan);
		setfillstyle(P_userF,D_Grey);
		circle(x,y,50);
		PrintText(x,y,KeyP,D_Red);
		if(kbhit()){
			if(GetAsyncKeyState(VK_ESCAPE)){
				GamePaused = true;
				while(GamePaused){
					Button B1(x,y-50,L_Yellow,RESUME,"Resume");
					Button B2(x,y,L_Yellow,RANDOMKEY,"Restart");
					Button B3(x,y+50,L_Yellow,PLAYGAMEMENU,"Play Others Games");
					Button B4(x,y+100,L_Yellow,EXIT,"Exit");
					
					while(!ButtonPressed){
						PrintText(x,y-100,"Game Paused",L_Yellow);
						B1.Display();
						B2.Display();
						B3.Display();
						B4.Display();
						delay(100);
						cleardevice();
					}
				}
			}
			if(getch() == Type_Key){
				Score++;
				Type_Key = GetRandomKey();
				KeyP = Type_Key;
			}
		}
	}
	cleardevice();
	Frame();
	settextstyle(10,0,2);
	SaveStatus(3);
	PrintText(x,y-50,"Game Over",L_Yellow);
	sprintf(ScoreString,"%s Your Score: %d",PlayerName,Score);
	outtextxy(x,y-25,ScoreString);
	delay(2*1000);
	getch();
	GameMenu(RANDOMKEY);
}

void FallingWord(){
	Reset();
	Word w[10];
	int Words = 0;
	int user_Index = 0;
	int wordRange = 0;
	char ScoreString[50];
	SetGameTime();
	Word_Delay = 4;
	setbkcolor(0);
	cleardevice();
	while(!GameOver){
		if(Word_Delay == 0) {
			if(Words == sizeof(w))
				Words = 0;
			else
				Words++;
			Word_Delay = 4;
			if(Words > wordRange){
				if(wordRange == 10){
					wordRange = 10;
				}else
				wordRange++;
			}
		}
		
		sprintf(ScoreString,"Score: %d              Time: %d:%d",Score,Seconds/60,Seconds%60);
		setcolor(L_Yellow);
		outtextxy(x,200,ScoreString);
		for(int i = 0; i <wordRange; i++){
			if(w[i].Y > height){
				w[i].Reset();
				if(activeWord == i){
					ActiveWord = false;
				}
			}
			if(activeWord == i)
				w[i].SpawnWord(L_Red);
			else
				w[i].SpawnWord(L_Green);
			w[i].AddForce(0,0.05);
		}
		Frame();
		if(kbhit()){
			if(GetAsyncKeyState(VK_ESCAPE)){
				GamePaused = true;
				while(GamePaused){
					Button B1(x,y-50,L_Yellow,RESUME,"Resume");
					Button B2(x,y,L_Yellow,FALLINGWORD,"Restart");
					Button B3(x,y+50,L_Yellow,PLAYGAMEMENU,"Play Others Games");
					Button B4(x,y+100,L_Yellow,EXIT,"Exit");
					
					while(!ButtonPressed){
						PrintText(x,y-100,"Game Paused",L_Yellow);
						B1.Display();
						B2.Display();
						B3.Display();
						B4.Display();
						delay(100);
						cleardevice();
					}
				}
			}
			char ch = getch();
			if(ActiveWord == true){
				if(w[activeWord].chMatch(user_Index,ch) == true){
					if(w[activeWord].wordLength()-1 == user_Index){
						Score++;
						w[activeWord].Reset();
						ActiveWord = false;
						activeWord = -1;
					}else{
						w[activeWord].TypeWord(user_Index);
						user_Index++;	
					}
				}
			}else{
				for(int i =0;i<wordRange;i++){
					if(w[i].chMatch(0,ch) == true){
						activeWord = i;
						ActiveWord = true;
						w[i].TypeWord(0);
						user_Index = 1;
						break;
					}
				}
			}
		}
		
		Timer();
	}
	ActiveWord = false;
	setbkcolor(D_Green);
	cleardevice();
	SaveStatus(4);
	PrintText(x,y-50,"Game Over",L_Yellow);
	sprintf(ScoreString,"%s Your Score: %d",PlayerName,Score);
	outtextxy(x,y-25,ScoreString);
	delay(2*1000);
	getch();
	GameMenu(FALLINGWORD);
}

void AboutMe(){
	Frame();
	settextjustify(0,1);
	settextstyle(8,0,1);
	PrintText(200,y-200,"Hello My Name is Syed Sulaiman Shah and I'm The Student of BS-Software Enginnering ",L_Yellow);
	PrintText(200,y-175,"at the University of Sindh. I Belong to Syed Family and i live at Bypass Town Moro",L_Yellow);
	PrintText(200,y-150,"Thanks",L_Yellow);
	
	PrintText(200,y,"Press 1 for The Menu",D_Cyan);
	reTry:
	if(getch() == '1'){
		cleardevice();
		Menu();
	}else
	goto reTry;
}

void Help(){
	settextjustify(0,1);
	settextstyle(10,0,1);
	Frame();
	PrintText(50,y-200,"Welcome to the Typing Games In 1st option PlayGames you will find multiple",L_Yellow);
	PrintText(50,y-175,"games to Play next Option is Set Time you can set time for your games duration.",L_Yellow);
	PrintText(50,y-150,"Type Before it Gone",L_Red);
	PrintText(50,y-125,"In This game WORD move to the right side of screen you have to type before it gone.",L_Yellow);
	PrintText(50,y-100,"Word Shuffle",L_Red);
	PrintText(50,y-75,"In Word Shuffle The word will change its place every 4 seconds you have to Type the",L_Yellow);
	PrintText(50,y-50,"word in that time.",L_Yellow);
	PrintText(50,y-25,"Random Key",L_Red);
	PrintText(50,y,"This game is very simple a character is in your middle of screen and you have to type",L_Yellow);
	PrintText(50,y+25,"by playing this game your concentration skills develop in Typnig",L_Yellow);
	PrintText(50,y+50,"Falling Word",L_Red);
	PrintText(50,y+75,"This one is my favourite game words fall from above towards down and you have to type",L_Yellow);
	PrintText(50,y+100,"that word there are multiple words which gives a lot of challenge",L_Yellow);
	PrintText(50,y+125,"All the Game Over on Time you have set if you don't set time there will be 1 minute ",L_Yellow);
	PrintText(50,y+150,"for every game as default Time",L_Yellow);
	PrintText(50,y+175,"Street Typing Speed Challenge",L_Red);
	PrintText(50,y+200,"IF your searching for challenge then this is perfect game for you in this game",L_Yellow);
	PrintText(50,y+225,"you have to type word to accelerate your Vehicle yes there are vehicle on road",L_Yellow);
	PrintText(50,y+250,"Thanks For Reading I Hope This section clear the things about the game",L_Yellow);
	PrintText(50,y+275,"Press 1 for the Menu",L_Yellow);
	reTry:
	if(getch() == '1'){
		cleardevice();
		Menu();
	}else
	goto reTry;
}

void SaveStatus(int game){
	ofstream SaveData("High_Score.txt", ios::out | ios::app);
	SaveData<<endl<<PlayerName<<" "<<Score<<" "<<game;
	SaveData.close();
}

void High_Score(){
	string name;
	int _score;
	int gID;
	char str[30];
	settextjustify(0,1);
	settextstyle(8,0,1);
	Frame();
	string line;
	ifstream HS("High_Score.txt");
	int g1yPos = 150,g2yPos = 150,g3yPos = 150,g4yPos = 150;
	int g1Xpos = 200, g2Xpos = 500,g3Xpos = 800,g4Xpos = 1100;
	PrintText(g1Xpos,100,"Type Before it's gone!",L_Yellow);
	PrintText(g2Xpos,100,"Word Shuffle",L_Yellow);
	PrintText(g3Xpos,100,"Random Key",L_Yellow);
	PrintText(g4Xpos,100,"Falling Word",L_Yellow);
	while(HS>>name>>_score>>gID){
		sprintf(str," %d ",_score);
		int leng = name.length()*12+10;
		if(gID == 1){
			PrintText(g1Xpos,g1yPos,name,L_Yellow);
			outtextxy(g1Xpos+leng,g1yPos,str);
			g1yPos += 25;
		}
		if(gID == 2){
			PrintText(g2Xpos,g2yPos,name,L_Yellow);
			outtextxy(g2Xpos+leng,g2yPos,str);
			g2yPos += 25;
		}
		if(gID == 3){
			PrintText(g3Xpos,g3yPos,name,L_Yellow);
			outtextxy(g3Xpos+leng,g3yPos,str);
			g3yPos += 25;
		}
		if(gID == 4){
			PrintText(g4Xpos,g4yPos,name,L_Yellow);
			outtextxy(g4Xpos+leng,g4yPos,str);
			g4yPos += 25;
		}
	}
	
	Button B(x,height-200,L_Yellow,MENU,"Back");
	B.Display();
	while(!ButtonPressed){
		B.MouseClick();
		delay(100);
		//cleardevice();
	}
}

void Frame(){
	setfillstyle(P_slashF,L_Cyan);
	bar(0,0,30,height);
	bar(0,0,width,30);
	bar(width-30,0,width,height);
	bar(0,height-30,width,height);
}

char GetRandomKey(){
	srand(time(NULL));
	char syb[] = {'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M','1','2','3','4','5','6','7','8','9','0',
	              'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
	short index = rand() % 62;
	return syb[index];
}

string RandomWord(){
	string W[] = {"three","reason","building","plain","meal","furniture","deafening","soup","cart",
				  "poised","heady","mourn","achiever","hungry","adamant","attractive","telling","drag"
				  ,"oil","scintillating","enjoy","nappy","carry","premium","ugliest","number","cracker",
				  "morning","grateful","beginner","prepare","descriptive","clap","dam","chunky","understood",
				  "bomb","disillusioned","envious","bare","impartial","knotty","remain","discover","bite",
				  "bawdy","hurried","fascinated","furtive","vacuous","The","Quick","Brown","Fox","Jumps","Over","Lazy","Dog"};
	short index = rand()%58;
	return W[index];
}
void PrintText(short _x,short _y, string _word , short _col){
	setcolor(_col);
	int len = _word.length();
	char w[len+1];
	strcpy(w,_word.c_str());
	outtextxy(_x,_y,w);
}

void StreetWord(){
	Vehicle car(150,y-70);
	Word word;
	float friction = -0.4;
	float velocity = 14.9;
	
	int User_Index = 0;
	
	roadLinesX[0] = 0;
	roadLinesX[1] = 360;
	roadLinesX[2] = 360*2;
	roadLinesX[3] = 360*3;
	roadLinesX[4] = 360*4;
	
	char ScoreString[100];
	SetGameTime();
	word.setWordPos(110+15,y-125);
	int page = 0;
	Reset();
	game:
		setactivepage(page);
		if(car.GreaterThenWidth() == true){
			SaveRecord();
			PrintText(x,y-75,"YOU WON THE GAME",D_Red);
			setcolor(L_Yellow);
			sprintf(ScoreString,"%s You Reached checkpoint in %d Seconds",PlayerName,GameTimer%60);
			PrintText(x,y-50,ScoreString,L_Yellow);
			PrintText(x,y-25,"Press 1 for next menu",L_Yellow);
			re:
			if(getch() != '1')
				goto re;
			GameMenu(STREETWORD);
		}
		if(car.LessThenWidth() == true){
			PrintText(x,y-75,"GameOver",D_Red);
			setcolor(L_Yellow);
			sprintf(ScoreString,"%s You Take %d Seconds and Failed",PlayerName,GameTimer%60);
			PrintText(x,y-50,ScoreString,L_Yellow);
			PrintText(x,y-25,"Press 1 for next menu",L_Yellow);
			le:
			if(getch() != '1')
				goto le;
			GameMenu(STREETWORD);
		}
		setvisualpage(1-page);
		
		cleardevice();
		StreetGameIsRunning = true;
		settextjustify(1,1);
		settextstyle(8,1,1);
		PrintText(width-100,y,"checkpoint",White);
		settextstyle(10,0,2);
		settextjustify(1,1);
		sprintf(ScoreString,"Time  %d:%d",Seconds/60,Seconds%60);
		outtextxy(x,y-250,ScoreString);
		
		if(friction_Delay == 0){
			car.AddForce(friction);
			word.AddForce(friction/2,0);
		}
					
		if(word.wordLength() == User_Index){
			word.NewWord();
			User_Index = 0;
		}
		if(kbhit()){
			if(GetAsyncKeyState(VK_ESCAPE)){
				setactivepage(page);
				setvisualpage(1-page);
				page = 1- page;
				cleardevice();
				setactivepage(page);
				GamePaused = true;
				while(GamePaused){
					Button B1(x,y-50,L_Yellow,RESUME,"Resume");
					Button B2(x,y,L_Yellow,STREETWORD,"Restart");
					Button B3(x,y+50,L_Yellow,PLAYGAMEMENU,"Play Others Games");
					Button B4(x,y+100,L_Yellow,RECORDS,"Records");
					Button B5(x,y+150,L_Yellow,EXIT,"Exit");
					
					while(!ButtonPressed){
						PrintText(x,y-100,"Game Paused",L_Yellow);
						B1.Display();
						B2.Display();
						B3.Display();
						B4.Display();
						B5.Display();
						delay(100);
						cleardevice();
					}
				}
			}
			char ch = getch();
			if(word.chMatch(User_Index,ch) == true){
				car.AddForce(velocity);
				word.AddForce(velocity/2,0);
				word.TypeWord(User_Index);
				User_Index++;
				friction_Delay = 1;
			}
		}
		Timer();
		DrawRoad();
		car.Print();
		word.SpawnWord(D_Yellow);

		page = 1 - page;
	if(!GameOver){
		goto game;
	}
	setactivepage(page);
	setvisualpage(1-page);
	page = 1- page;
	cleardevice();
	setactivepage(page);
	settextstyle(10,0,2);
	setbkcolor(D_Green);
	cleardevice();
	PrintText(x,y-75,"GameOver",D_Red);
	setcolor(L_Yellow);
	sprintf(ScoreString,"%s You Run out of Time",PlayerName,GameTimer%60);
	outtextxy(x,y-50,ScoreString);
	PrintText(x,y-25,"Press Any Key",L_Yellow);
	getch();
	GameMenu(STREETWORD);
}

/*void BlockWords(){
	settextstyle(10,0,2);
	settextjustify(0,1);
	int yPos = 20;
	Word word;
	word.setWordPos(x-90,y);
	word.SpawnWord(L_Yellow);
	
	
	setfillstyle(P_xhatchF,D_Blue);
	bar(x-100,y-150,x-120,y+150);
	bar(x+100,y-150,x+120,y+150);
	bar(x-120,y+150,x+120,y+175);
	
}*/

void DrawRoad(){
	setfillstyle(P_soldF,White);
	bar(0,y-210,width,y-200);
	setfillstyle(P_soldF,0);
	bar(0,y-200,width,y+200);
	setfillstyle(P_soldF,White);
	bar(0,y+200,width,y+210);
	
	setfillstyle(P_soldF,L_Green);
	bar(width-100,y-200,width-110,y+200);
	
	setfillstyle(P_soldF,White);
	bar(roadLinesX[0],y-5,roadLinesX[0]+300,y+5);
	bar(roadLinesX[1],y-5,roadLinesX[1]+300,y+5);
	bar(roadLinesX[2],y-5,roadLinesX[2]+300,y+5);
	bar(roadLinesX[3],y-5,roadLinesX[3]+300,y+5);
	bar(roadLinesX[4],y-5,roadLinesX[4]+300,y+5);
	
	if(roadLinesX[0]+300<0) roadLinesX[0] = width;
	if(roadLinesX[1]+300<0) roadLinesX[1] = width;
	if(roadLinesX[2]+300<0) roadLinesX[2] = width;
	if(roadLinesX[3]+300<0) roadLinesX[3] = width;
	if(roadLinesX[4]+300<0) roadLinesX[4] = width;
	roadLinesX[0] -= 0.7;
	roadLinesX[1] -= 0.7;
	roadLinesX[2] -= 0.7;
	roadLinesX[3] -= 0.7;
	roadLinesX[4] -= 0.7;
}

void SaveRecord(){
	ofstream SaveData("Records.txt", ios::out | ios::app);
	SaveData<<endl<<PlayerName<<" "<<GameTimer;
	SaveData.close();
}
void ShowRecord(){
	int index = 0;
	string name;
	int seconds;
	ifstream Record("Records.txt");
	char str[50];
	while(Record>>name>>seconds){
		RecordName[index] = name;
		RecordScore[index] = seconds;
		index++;
	}
	for(int i = 0; i<index;i++)
	for(int j = 0; j<index;j++){
		if(RecordScore[j] > RecordScore[j+1]){
			int swap = 0;
			string n;
			if(j == index-1){
				break;
			}else{
				swap = RecordScore[j];
				RecordScore[j] = RecordScore[j+1];
				RecordScore[j+1] = swap;
				n = RecordName[j];
				RecordName[j] = RecordName[j+1];
				RecordName[j+1] = n;
			}
		}
	}
	int range = 200;
	PrintText(x,y-range-25,"Records",L_Yellow);
	for(int i = 0;i< index; i++){
		PrintText(x-80,y-range,RecordName[i],L_Yellow);
		sprintf(str," %d Seconds",RecordScore[i]);
		outtextxy(x+80,y-range,str);
		range -= 25;
	}
	char ch;
	PrintText(x,y-range,"Press 1 For previous Menu",L_Yellow);
	while(ch != '1'){
		ch = getch();
	}
	cleardevice();
}
void Loading(){
	int page = getactivepage();
	setactivepage(page);
	setvisualpage(1-page);
	page = 1- page;
	cleardevice();
	setactivepage(page);
	for(int i = 0; i<5;i++){
		PrintText(x+i*5,y-400,".",D_Cyan);
		delay(500);
	}
}
