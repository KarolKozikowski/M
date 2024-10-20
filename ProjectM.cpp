#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <limits>
#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80

using namespace std;

//using windows API to get screensize gotoxy function and color function
void screensize(int& width, int& height) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
		height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
}
void gotoxy(int x, int y){
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
void color(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
//

class Brush{	
	int x, y, size;
	char symbol;	
	public:	
		Brush(int x, int y, int size) : x(x), y(y), size(size){}		
		void setXY(int x, int y){
			this->x = x;
			this->y = y;
		}		
		void setSymbol(char symbol){  //allows to manualy set symbol
			this->symbol = symbol;
		}
		void setSize(int size){  //allows to manualy set size of M
			this->size = size;
		}
		void draw(){   //draws the M symbol based on x y and size
			int tempX = x;
			int tempY = y;
			for(int i=1; i<size; i++){
				gotoxy(x, y);
				cout << symbol;
				y--;
			}
			for(int j=0; j<size/2; j++){
				gotoxy(x, y);
				cout << symbol;
				x--;
				y++;
			}
			for(int k=0; k<size/2; k++){
				gotoxy(x, y);
				cout << symbol;
				x--;
				y--;
			}
			for(int l=0; l<size; l++){
				gotoxy(x, y);
				cout << symbol;
				y++;
			}
			x = tempX;
			y = tempY;
			gotoxy(x, y);
		}
};

class Screen{  //contains and collects data about screen size
	int width, height;
	void update(){
		screensize(width, height);
	}
	public:
		int getX(){
			update();
			return width;
		}
		int getY(){
			update();
			return height;
		}
};

int startMenu(int position){	
	system("cls");
	Screen okno;
	Brush brush((okno.getX()/2)-1, (okno.getY()/2)+8, 20); //create brush object
	brush.setSymbol('#');
	color(8);
	gotoxy(0,okno.getY()-1);
	cout << "Projekt nr: 126";
	int selector = position;
	string word[4] = {"Start", "Controls", "Credits", "Exit"}; //added these using array cuz it's easier to add later something
	while(1){ 
		if(selector == 4){ //paints M in menu in different color if selector=4
			color(11);
			brush.draw();
		}
		else{
			color(3); //on default M is darker
			brush.draw();
		}
		for(int i = 0; i<4; i++){ //based on selector value highlights one of the names
			gotoxy((okno.getX()/2)+12, (okno.getY()/2)-5+(i*3));
			selector == i ? color(15) : color(8);
			if(selector == 3 && i == 3) color(12);
			cout << word[i];
		}
		Sleep(100); //makes using menu easier so when you hold arrow key it doesn't go wooooooooo
		int c = getch();
		if(c && c == 224){  //makes sure that e.g. UP arrow key is not equal to H
			switch(getch()){
				case KEY_UP:
					if(selector !=4){
						selector == 0 ? selector = 3 : selector--;
						position = selector;
					}
					break;
				case KEY_DOWN:
					if(selector !=4){
						selector == 3 ? selector = 0 : selector++;
						position = selector;
					}
					break;
				case KEY_LEFT:
					selector == 4 ? selector = position : selector = 4;
					break;
				case KEY_RIGHT:
					selector == 4 ? selector = position : selector = 4;
					break;
			}
		}
		else if(c == 13 || c == 10) return selector;
	}
}

void controls(){  //UI for controls
	system("cls"); 
	string what[7] = {" Navigate in Menu: ", " Navigate in program: ", " Go back: ", " Change M size: ", " Change M color: ", " Change M color type (dark/bright): ", " Help: "};
	string how[7] = {"UP/DOWN", "UP/DOWN/LEFT/RIGHT", "ESC", "+/-", "[/]", "*", "H"};
	color(15);
	cout << "\n\n CONTROLS: \n\n";
	for(int i=0; i<7; i++){ //prints controls from array
		color(8);
		cout << what[i];
		color(3);
		cout << how[i] << "\n\n";
	}
	color(8);
	cout << "\n *note: the big M in the Main Menu is for decorative purposes only, and you definitely cannot click it!";
	Screen win;
	gotoxy(1, win.getY()-2);
	color(15);
	cout << "BACK [ESC]";
	while(getch()!=27);
}

void doTheM(){ //the "main" function of the progtram
	system("cls");
	Screen okno;
	char symbol;
	int size;
	int colorType[7] = {9, 10, 11, 12, 13, 14, 15};
	int colorTypeDark[7] = {1, 2, 3, 4, 5, 6, 8};
	int colnr=6;
	bool isDark = false;
	int lim;
	int x = okno.getX()-1;
	int y = okno.getY()-1;
	//setup menu
	gotoxy((okno.getX()/2)-7, (okno.getY()/2)-2);
	color (8);
	cout << "Enter symbol: ";
	color(15);
	cin >> symbol;
	gotoxy((okno.getX()/2)-12, (okno.getY()/2));
	color(8);
	cout << "Enter size (3-" << okno.getY() << "): ";
	color(15);
	start:
	while(!(cin >> size)){  //checks if size is int
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        gotoxy((okno.getX()/2)+7, (okno.getY()/2));
        cout << "          " << "\b\b\b\b\b\b\b\b\b\b";
    }
    if(size<3 || size>okno.getY()){ //checks id size is from 3 to 25
    	gotoxy((okno.getX()/2)+7, (okno.getY()/2));
        cout << "          " << "\b\b\b\b\b\b\b\b\b\b";
        goto start;
	}
	system("cls");
	//
	Brush brush(okno.getX()-1, okno.getY()-1, size); //creates brush object
	brush.setSymbol(symbol);
	while(1){
		size%2!=0 ? lim = 1 : lim = 0;
		brush.draw();
		int c = getch();
		if(c && c == 224){
			switch(getch()){
				case KEY_UP:
					y>=size ? y-- : 0;
					break;
				case KEY_DOWN:
					y<okno.getY()-1 ? y++ : 0;
					break;
				case KEY_LEFT:
					x>size-lim ? x-- : 0;
					break;
				case KEY_RIGHT:
					x<okno.getX()-2 ? x++ : 0;
					break;
			}
		}
		switch(c){  //controls
			case 27:
				return;
			case '+':
				if (size < okno.getY() && y >= size && x > size) size++;
				break;
			case '-':
				size > 3 ? size-- : 0;
				break;
			case '[':
				colnr == 0 ? colnr = 6 : colnr--;
				color(isDark?colorTypeDark[colnr]:colorType[colnr]);
				break;
			case ']':
				colnr == 6 ? colnr = 0 : colnr++;
				color(isDark?colorTypeDark[colnr]:colorType[colnr]);
				break;
			case '*':
				isDark ? isDark = false : isDark = true;
				color(isDark?colorTypeDark[colnr]:colorType[colnr]);
				break;
			case 'h':
				controls();
				system("cls");
				break;
		}
		brush.setSymbol(' '); //draws M with space and not "symbol" so that it doesn't stay and just moves
		brush.draw();
		brush.setSymbol(symbol);
		brush.setXY(x, y);
		brush.setSize(size);
	}
}

void credits(){
	system("cls");
	color(15);
	cout << "\n\n EVERYTHING:";
	color(8);
	cout << "\n Karol Kozikowski";
	color(15);
	cout << "\n\n OTHER:";
	color(8);
	cout << "\n Did some research on YouTube & StackOverflow on how to use windows.h and stuff";
	Screen win;
	gotoxy(1, win.getY()-2);
	color(15);
	cout << "BACK [ESC]";
	while(getch()!=27);
}

int main(){
// using Windows API to hide console cursor
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ci;
	ci.dwSize = 25;
	ci.bVisible = FALSE;
	SetConsoleCursorInfo(output, &ci);
//
	int position = 0;
	while(1){  //used to start other functions 
		switch(startMenu(position)){
			case 3:
				return 0;
			case 0:
				doTheM();
				position = 0;
				break;
			case 1:
				controls();
				position = 1;
				break;
			case 2:
				credits();
				position = 2;
				break;
			case 4:
				string search_URL = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
   				ShellExecuteA(NULL, "open", search_URL.c_str(), NULL, NULL, SW_SHOWNORMAL);
   				return 0;
		}
	}
}