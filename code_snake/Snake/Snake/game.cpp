#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void SetUp()
{
	gameOver = false;
	dir = STOP;

	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;

	score = 0;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < width + 1; i++)
	{
		cout << "_";
	}
	cout << endl;


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "|";
			}
			if (j == x && i == y)
			{
				cout << "@";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "$";
			}
			else {
				bool paint = false;
				for (int k = 0; k < nTail; k++)
				{
					if (i == tailY[k] && j == tailX[k])
					{
						cout << "o";
						paint = true;
					}
				}
				if (!paint) 
				{
					cout << " ";
				}
				
			}
		}
		
		cout << endl;
	}


	for (int i = 0; i < width + 1; i++)
	{
		cout << "_";
	}

	cout << endl;

	cout << "Score: " << score << endl;
	
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'w':
			{
				dir = UP;
				break;
			}
				
			case 'a':
			{
				dir = LEFT;
				break; }
				
			case 's':
			{
				dir = DOWN;
				break;
			}
				
			case 'd':
			{
				dir = RIGHT;
				break;
			}
				
			case 'x':
			{
				gameOver = true;
				break;
			}
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}



	switch (dir)
	{
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

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

	if (x < 0) 
	{
		x = width - 2;
	}
	else if (x >= width-1)
	{
		x = 0;
	}

	if (y < 0)
	{
		y = height - 1;
	} 
	else if (y >= height)
	{
		y = 0;
	}
	
	
	for (int i = 0; i < nTail; i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			gameOver = true;
			nTail = 0;
		}
	}
	
	if (gameOver)
	{
		cout << "Для продолжения нажмите любую клавишу... (х - выход)" << endl;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool restart = true;
	while (restart)
	{
		SetUp();
		while (!gameOver)
		{
			Draw();
			Input();
			Logic();
			//Sleep(20);     Ваня делает!
		}
		if (_getch() == 'x')
		{
			break;
		}
	}
	
	//system("pause");
}