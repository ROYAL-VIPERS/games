#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define wieght 80
#define height 20
#define player '¤'
#define borderY '|'
#define borderX '_'
bool gameOver = false;

using namespace std;

void Draw(char field[height][wieght])
{
	system("cls");
	for (int i = 0; i < height; i++)
	{
		cout << field[i] << endl;
	}
	cout << "Для рисования нажмите E...(x - выход)";
}

void CreateField(char field[height][wieght])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < wieght; j++)
			if (i == 0 || i ==  height - 1)
				field[i][j] = borderX;
			else if (j == wieght - 2 || j == 0)
				field[i][j] = borderY;
			else
				field[i][j] = ' ';
		field[i][wieght - 1] = '\0';
	}
}


void moveKEYS(char field[height][wieght], char playerAction, int playerCoords[2], int& paint) {
	int lastcoords[2];
	lastcoords[0] = playerCoords[0];
	lastcoords[1] = playerCoords[1];
	if (playerAction == 'ц' || playerAction == 'w')
	{
		playerCoords[0]--;
	}
	else if (playerAction == 'ы' || playerAction == 's')
	{
		playerCoords[0]++;
	}
	else if (playerAction == 'ф' || playerAction == 'a')
	{
		playerCoords[1]--;
	}
	else if (playerAction == 'в' || playerAction == 'd')
	{
		playerCoords[1]++;
	}
	else if (playerAction == 'у' || playerAction == 'e')
	{
		paint++;
	}
	else if (playerAction == 'ч' || playerAction == 'x')
	{
		gameOver = true;
	}

	if (field[playerCoords[0]][playerCoords[1]] == ' ' || field[playerCoords[0]][playerCoords[1]] == '*')
	{
		if (paint % 2 == 0)
			field[lastcoords[0]][lastcoords[1]] = ' ';
		else
			field[lastcoords[0]][lastcoords[1]] = '*';
	}

	else {
		playerCoords[0] = lastcoords[0];
		playerCoords[1] = lastcoords[1];
	}

}


int main()
{

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0));
	char field[height][wieght];
	int playerCoords[2] = { height / 2, wieght / 2 };
	char playerAction;
	int paint = 0;
	CreateField(field);
	while (true)
	{
		field[playerCoords[0]][playerCoords[1]] = player;
		Draw(field);
		Sleep(0);
		playerAction = _getch();
		moveKEYS(field, playerAction, playerCoords, paint);
		if (gameOver == true) {
			break;
		}
	}
}