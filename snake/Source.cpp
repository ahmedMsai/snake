#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int width = 40;
const int height = 20;
const string gameOverText("GAME OVER");
const float speed = 100;
const int fpsCap = 1000 / 20;


bool gameOver;
bool quit;

int x, y, fruitX, fruitY, score, frames;
int tailX[100], tailY[100];
int nTail;

long nowIs,lmt, lastDrownFrame;

enum eDirection{ STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void start() {
	
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		nowIs = ms.count();
		lmt = nowIs;
		lastDrownFrame = nowIs;
		frames = 0;

		gameOver = false;
		quit = false;

		score = 0;
		dir = STOP;
		nTail = 0;


		x = width / 2;
		y = height / 2;

		srand(time(NULL));
		fruitX = rand() % width;
		fruitY = rand() % height;
		
}

void drow() {
	long nextFrame = lastDrownFrame + fpsCap;
	if (nowIs > nextFrame) {
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
		cout << "score : " << score << " | frames : " << frames;
		lastDrownFrame = nowIs;
		frames++;
	}
}

void input() {
	if (_kbhit()) {
		switch (_getch())
		{
			case 75:
				if (dir != RIGHT)dir = LEFT;
				break;	
			case 77:
				if (dir != LEFT)dir = RIGHT;
				break;
			case 72:
				if (dir != DOWN)dir = UP;
				break;
			case 80:
				if (dir != UP)dir = DOWN;
				break;
			case 'o':
				gameOver = true;
				break;
			case 'x':
				gameOver = true;
				quit = true;
				break;
			case 27:
				gameOver = true;
				quit = true;
				break;
			default:
				break;
		}
	}
}

void logic() {
	long nextMove = lmt + speed;
	
	if (nowIs > nextMove) {
		if (x == fruitX && y == fruitY) {
			fruitX = rand() % width;
			fruitY = rand() % height;
			score += 10;
			nTail++;
		}
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
		if (x < 0 || x >= width || y < 0 || y >= height) {
			gameOver = true;
		}
		for (int i = 0; i < nTail; i++) {
			if (x == tailX[i] && y == tailY[i]) {
				gameOver = true;
			}
		}

		lmt = nowIs;
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
	cout << "score : " << score << " | speed : " << speed << " | frames : " << frames;
}
int main() {

	start();
	while (!gameOver){
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		nowIs = ms.count();
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