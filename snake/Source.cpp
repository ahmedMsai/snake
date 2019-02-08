#include <iostream>
#include <conio.h>
#include<string>

using namespace std;

const int width = 40;
const int height = 20;
const string gameOverText("GAME OVER");

bool gameOver;
bool quit;
int x, y, fruitX, fruitY, score;

enum eDirection{ STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void start() {
	gameOver = false;
	quit = false;
	score = 0;
	dir = STOP;

	x = width / 2;
	y = height / 2;

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
				cout << " ";
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
}

void input() {
	if (_kbhit) {
		switch (_getch())
		{
			case 'q':
				dir = LEFT;
				break;	
			case 'd':
				dir = RIGHT;
				break;
			case 'z':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
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

	if (x == 0 || x == width + 2 || y == 0 || y == height - 1) {
		gameOver = true;
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
}
int main() {

	start();
	do{
		drow();
		input();
		logic();
	} while (!gameOver);



	drowGameOver();
	while (!quit) {
		input();
	}
	
	return 1;
}