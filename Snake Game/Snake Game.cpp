// ConsoleApplication21.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>


using namespace std;

const int MAX_TAIL_LENGTH = 100;
bool gameOver=false;
int height=20;
int width =30;
int x,y,fruitX,fruitY;
int tailX[MAX_TAIL_LENGTH], tailY[MAX_TAIL_LENGTH];
enum direction {UP, DOWN, RIGHT, LEFT, STOP}dir;
direction moveDir=STOP;
int score =0;
int lenTail=0;
int trackT;


void setup(){
	srand(time(0));
	fruitX=rand() % width;
	fruitY=rand() % height;
	x=width/2;
	y=height/2;

}


void draw(){
	system("CLS");
	for(int i=0;i<width+2;i++)
		cout<<"#";
	cout<<endl;

	trackT=lenTail;

	for (int i=0;i<height;i++){
		cout<<"#";

		for(int j=0; j<width;j++){
			
			if (y==i && x==j){
				cout<<"O";
			}
			else if(fruitX==j &&fruitY==i)
				cout<<"F";
			else
			{
				bool didprint = false;
				for (int k = 0; k<lenTail; k++){
					if (tailX[k]==j && tailY[k]==i){
						cout<<"o";
						didprint=true;
					}
				}
				if (!didprint)
				cout<<" ";
			}
		}
		cout<<"#";
		cout<<endl;
	}
	for(int i=0;i<width+2;i++)
		cout<<"#";
	cout<<"\nScore: "<<score;
}


void logic(){
	int prevX= tailX[0];
	int prevY = tailY[0];
	int prev2X,prev2Y;
	tailX[0]=x;
	tailY[0]=y;

	for(int i =1; i<lenTail; i++)
		if (tailX[i]==x && tailY[i]==y)
			gameOver=true;

	for (int i=1; i<lenTail;i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;	
		prevY = prev2Y;
	}

	if (_kbhit()){
		switch (_getch())
		{
		case 'w':
			moveDir=UP;
			y--;
			break;
		case 's':
			moveDir=DOWN;
			y++;
			break;
		case 'd':
			moveDir=RIGHT;
			x++;
			break;
		case 'a':
			moveDir=LEFT;
			x--;
			break;
		}
	}
	else if (moveDir==UP)
		y--;
	else if(moveDir==DOWN)
		y++;
	else if(moveDir==RIGHT)
		x++;
	else if (moveDir==LEFT)
		x--;

	if ((x>=width) || (x<0) || (y>=height) || (y<0))
		gameOver=true;
	if (x==fruitX && y==fruitY){
		fruitX=rand() % width;
		fruitY=rand() % height;
		lenTail++;
		score+=10;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"\n\n\n\n\n\n\n\n\n\n                            WELCOME TO SNAKE THE GAME \n                            CHOOSE DIFFICULTY(1/2/3):\n                                        ";
	int diff;
	cin>>diff;
	
	setup();	draw();
	logic();
	while (gameOver==false){
		draw();
		logic();
		Sleep(100/diff);
	}
	Sleep(500);
	system("CLS");
	cout<<"\n\n\n\n\n\n\n\n\n\n                                    GAME OVER\n                               YOUR SCORE WAS: "<<score<<endl<<endl;
	cout<<"\n\n\n\n\n\n\n\n\n\n\nPRESS ANY KEY TO CLOSE GAME";
	
	_getch();
	return 0;
}

