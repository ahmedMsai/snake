#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int width = 40;
const int height = 20;
const string gameOverText("GAME OVER");

bool gameOver;
bool quit;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

int lmt;
float speed;

enum eDirection{ STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void start() {
	gameOver = false;
	quit = false;
	lmt = 0;
	score = 0;
	dir = STOP;
	nTail = 0;
	speed = 1000;

	x = width / 2;
	y = height / 2;

	srand(time(NULL));
	fruitX = rand() % width;
	fruitY = rand() % height;

}

void drow() {
	system("cls");

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++)
		{
			if (i == 0) {
				cout << "#";
			}

			
			if (x == i && y == j) {
				cout << "O";
			}
			else if (fruitX == i && fruitY == j) {
				cout << "x";
			}
			else {
				bool isTail = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == i && tailY[k] == j) {
						cout << "o";
						isTail = true;
						break;
					}
					
				}
				if(!isTail){
					cout << " ";
				}
			}
			

			if (i == width - 1) {
				cout << "#";
			}
			
		}
		cout << endl;
	}


	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "score : " << score << " | time : " << time(NULL);
}

void input() {
	if (_kbhit()) {
		switch (_getch())
		{
			case 'q':
				if (dir != RIGHT)dir = LEFT;
				break;	
			case 'd':
				if (dir != LEFT)dir = RIGHT;
				break;
			case 'z':
				if (dir != DOWN)dir = UP;
				break;
			case 's':
				if (dir != UP)dir = DOWN;
				break;
			case 'o':
				gameOver = true;
				break;
			case 'x':
				gameOver = true;
				quit = true;
				break;
			default:
				break;
		}
	}
}

void logic() {
	int prevX = x;
	int prevY = y;
	int prevX2, prevY2;
	for (int i = 0; i < nTail; i++) {
		prevX2 = tailX[i];
		prevY2 = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevX2;
		prevY = prevY2;
	}

	time_t time = std::time(NULL);
	if (time >= lmt + speed) {
		switch (dir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
		}

		//lmt = time -1;
	}
	
	if (x == fruitX && y==fruitY) {
		fruitX = rand() % width;
		fruitY = rand() % height;
		score += 10;
		nTail++;
	}
	if (x<0 || x >= width || y<0 || y>=height) {
		gameOver = true;
	}
	for (int i = 0; i < nTail; i++) {
		if (x == tailX[i] && y== tailY[i]) {
			gameOver = true;
		}
	}
	
}


void drowGameOver() {
	system("cls");

	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++)
		{
			if (i == 0) {
				cout << "#";
			}

			if (j == height / 2 && i == (width - gameOverText.length()) / 2) {
				cout << gameOverText;
				i += gameOverText.length()-1;
			}
			else {
				cout << " ";
			}
			

			if (i == width - 1) {
				cout << "#";
			}

		}
		cout << endl;
	}


	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "score : " << score;
}
int main() {

	start();
	while (!gameOver){
		drow();
		input();
		logic();
	}



	drowGameOver();
	while (!quit) {
		input();
	}
	
	return 1;
}