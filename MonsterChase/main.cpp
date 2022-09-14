#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "Engine.h"

const int GRID_ROWS = 10;
const int GRID_COLS = 10;

const Point2D TOP_LEFT(0, 0);
const Point2D TOP_RIGHT(0, GRID_COLS - 1);
const Point2D BTM_LEFT(GRID_ROWS - 1, 0);
const Point2D BTM_RIGHT(GRID_ROWS - 1, GRID_COLS - 1);

const int MAX_MONSTER_LIFESPAN = 10;
const int MONSTER_DEATH_TIME = 3;

char** monsterNames;
int* monsterLifespans;
int* monsterDeathTimers;

int maxMonsters;

Point2D* monsterPositions;
Point2D playerPosition(4, 4);

void MoveUp();
void MoveDown();
void MoveLeft();
void MoveRight();

int DisplayGrid(char* playerName);

void DisplayMonsterNames();
void MoveMonster(int monsterIndex);

int main()
{
	char tempPlayerName[100];

	std::cout << "Welcome to MonsterChase! Enter the number of monsters you wish to play with (at least 1, at most 4): \n";
	std::cin >> maxMonsters;

	monsterNames = new char* [maxMonsters];
	monsterLifespans = new int[maxMonsters];
	monsterDeathTimers = new int[maxMonsters];

	monsterPositions = new Point2D[maxMonsters];

	// monsters spawn in the corners
	for (int i = 0; i < maxMonsters; i++)
	{
		if (i == 0)
		{
			monsterPositions[i] = TOP_LEFT;
		}
		else if (i == 1)
		{
			monsterPositions[i] = TOP_RIGHT;
		}
		else if (i == 2)
		{
			monsterPositions[i] = BTM_LEFT;
		}
		else if (i == 3)
		{
			monsterPositions[i] = BTM_RIGHT;
		}
	}

	int count = 0;
	int monsterDisplayName = 49;

	// if input is invalid, set monsters spawned to four.
	if (maxMonsters < 1 || maxMonsters > 4)
	{
		maxMonsters = 4;
	}

	for (int i = 0; i < maxMonsters; i++)
	{
		monsterLifespans[i] = MAX_MONSTER_LIFESPAN;
	}

	for (int i = 0; i < maxMonsters; i++)
	{
		monsterDeathTimers[i] = 0;
	}

	for (int i = 0; i < maxMonsters; i++)
	{
		char* input = new char[100];
		printf("Name monster #%i: \n", i + 1);
		std::cin >> input;
		char* name = new char[strlen(input) + 1];

		for (int i = 0; i < strlen(input); i++)
		{
			name[i] = input[i];
		}
		name[strlen(input)] = '\0';
		monsterNames[i] = name;

		delete[] input;
	}

	std::cout << "What's your name?\n";
	std::cin >> tempPlayerName;

	int playerNameLength = 0;
	for (int i = 0; i < 100; i++)
	{
		if (tempPlayerName[i] == NULL)
		{
			break;
		}
		else
		{
			playerNameLength++;
		}
	}

	char* playerName = new char[playerNameLength + 1];

	for (int i = 0; i < playerNameLength; i++)
	{
		playerName[i] = tempPlayerName[i];
	}
	playerName[playerNameLength] = '\0';

	// game loop
	while (true)
	{
		for (int i = 0; i < maxMonsters; i++)
		{
			if (monsterLifespans[i] != 0)
			{
				MoveMonster(i);
				monsterLifespans[i] -= 1;
			}
			else
			{
				monsterDeathTimers[i] += 1;
				if (monsterDeathTimers[i] == MONSTER_DEATH_TIME)
				{
					monsterLifespans[i] = MAX_MONSTER_LIFESPAN;
				}
			}
		}

		if (DisplayGrid(playerName) == 0)
		{
			return 0;
		}

		std::cout << "MONSTERS:\n";
		DisplayMonsterNames();

		std::cout << "Which direction would you like to move? (\"u\" for up, \"d\" for down, \"l\" for left, \"r\" for right\n";
		char input = _getch();
		if (input == 'u')
		{
			MoveUp();
		}
		else if (input == 'd')
		{
			MoveDown();
		}
		else if (input == 'l')
		{
			MoveLeft();
		}
		else if (input == 'r')
		{
			MoveRight();
		}
		else if (input == 'q')
		{
			printf("\nSo long!\n");
			return 0;
		}
		else
		{
			printf("Invalid action. Please try again.\n");
			continue;
		}
	}

	/*
	// DEALLOCATION
	*/

	// deallocate monster names array
	for (int i = 0; i < maxMonsters; i++)
	{
		delete[] monsterNames[i];
	}
	delete[] monsterNames;

	delete[] monsterLifespans;
	delete[] monsterDeathTimers;
	delete[] monsterPositions;

	delete[] playerName;

	return 0;
}

void MoveUp()
{
	Point2D prevPosition = playerPosition;
	if (playerPosition.x != 0)
	{
		playerPosition.x -= 1;
	}
}

void MoveDown()
{
	Point2D prevPosition = playerPosition;
	if (playerPosition.x != GRID_ROWS - 1)
	{
		playerPosition.x += 1;
	}
}

void MoveLeft()
{
	Point2D prevPosition = playerPosition;
	if (playerPosition.y != 0)
	{
		playerPosition.y -= 1;
	}
}

void MoveRight()
{
	Point2D prevPosition = playerPosition;
	if (playerPosition.y != GRID_COLS - 1)
	{
		playerPosition.y += 1;
	}
}

int DisplayGrid(char* playerName)
{
	for (int i = 0; i < maxMonsters; i++)
	{
		// check all live monsters, add them to grid
		if (monsterLifespans[i] != 0)
		{
			if (monsterPositions[i].x == playerPosition.x && monsterPositions[i].y == playerPosition.y)
			{
				std::cout << playerName << " DIED TO " << monsterNames[i] << std::endl;
				return 0;
			}
		}
	}

	int counter = 0;
	printf("\n");
	bool monsterPlaced = false;
	for (int i = 0; i < GRID_ROWS; i++)
	{
		for (int j = 0; j < GRID_COLS; j++)
		{
			/*std::cout << grid[i][j];*/
			for (int m = 0; m < maxMonsters; m++)
			{
				if ((i == monsterPositions[m].x && j == monsterPositions[m].y) && monsterLifespans[m] != 0)
				{
					std::cout << 'M';
					monsterPlaced = true;
				}
			}
			if (monsterPlaced == false)
			{
				if (i == playerPosition.x && j == playerPosition.y)
				{
					std::cout << 'P';
				}
				else
				{
					std::cout << '.';
				}
			}
			monsterPlaced = false;

			std::cout << " ";
		}
		std::cout << "\n";
	}
	printf("\n");

	return 1;
}

// display all of the monsters that are currently alive
void DisplayMonsterNames()
{
	for (int i = 0; i < maxMonsters; i++)
	{
		if (monsterLifespans[i] != 0)
		{
			std::cout << monsterNames[i] << std::endl;
		}
	}
	std::cout << "\n";
}

// move the selected monster in a random direction
void MoveMonster(int monsterIndex)
{
	// 0 = up, 1 = down, 2 = left, 3 = right
	int direction = rand() % 4;

	if (direction == 0 && monsterPositions[monsterIndex].x != 0)
	{
		monsterPositions[monsterIndex].x -= 1;
	}
	else if (direction == 1 && monsterPositions[monsterIndex].x != GRID_ROWS - 1)
	{
		monsterPositions[monsterIndex].x += 1;
	}
	else if (direction == 2 && monsterPositions[monsterIndex].y != 0)
	{
		monsterPositions[monsterIndex].y -= 1;
	}
	else if (direction == 3 && monsterPositions[monsterIndex].y != GRID_COLS - 1)
	{
		monsterPositions[monsterIndex].y += 1;
	}
}