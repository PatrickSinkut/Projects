﻿#include <iostream>
#include <math.h>
#include <conio.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup() {   // настройки игры(вызывается один раз)
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void Draw() {   //отрисовка карты и змейки
	system("cls");
	for (int i = 0; i < width +1; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruit_y && j == fruit_x)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tail_x[k] == j && tail_y[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
				    cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;


}   


void Input() {   //получение данных с клавиатуры

	if (_kbhit()) {
		switch (_getch()) {
		case 'a': 
			dir = LEFT;
			break;
		case 'd': 
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

void Logic() {   //логика игры
	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int prev_2x, prev_2y;

	tail_x[0] = x;
	tail_y[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev_2x = tail_x[i];
		prev_2y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;
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
	}

	//if (x > width || x < 0 || y>height || y < 0)
		//gameOver = true;

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 2;

	for (int i = 0; i < nTail; i++) {
		if (tail_x[i] == x && tail_y[i] == y)
			gameOver = true;
	}

	if (x == fruit_x && y == fruit_y) {
		score += 10;
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		nTail++;
	}

}


int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}

	return 0;
}
