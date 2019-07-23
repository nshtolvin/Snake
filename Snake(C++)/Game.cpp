#include "stdafx.h"
#include "Game.h"

#include "conio.h"
#include "Windows.h"
#include "iostream"
#include "string"
#include "io.h"
#include "fstream"
#include "array"

#include "Point.h"
#include "SnakeClass.h"
#include "FoodCreatorClass.h"
#include "Menu.h"


//Game::Game():
//{
//	printf("  Game  ");
//}

/* ���������� ����������� ������� ��������� ���� ������ */
Game::~Game()
{}


/* ����� �������� ���� ���� ������ */
void Game::SnakeGame()
{
	srand(time(NULL));
	Game::GetCurrentScore(); //��������� �������� ���������� ����
	
	//�������� ������: �������� ����� � ��������� ������������. ���  ����� ����� ������
	Point MyTail(4, 5);

	//�������� ��������� ����� � ������� � ����� MyTail � ������ 4. �������� � �� ������
	SnakeClass Snake(MyTail);
	Snake.DrawLine();

	//������� ����� � ����
	FoodCreatorClass FoodCreator(80, 25);
	Point Food = FoodCreator.CreateFood();
	Food.DrawSimbol();

	//�������� ������
	while (true)
	{
		/* ��������� ���������� �� ������ � ������������;
		 * ���� ������ ��������� � ������� ���� ��� ���� ����, �� ���������� ���������� */
		if (Game::IsWallsHit(Snake) || Snake.IsTailHit())
			throw - 1;		// ���������� -1

		/* ������ ������������ */
		Snake.Move();
		Sleep(170);
		
		/* ��������� ����� �� ������� ��� � ������� �����, ���� �� ������
		 * ������� �������� ��� ������������� */
		if (Snake.Eat(Food))
		{
			mResult.Score++;
			Game::GetCurrentScore(); //��������� �������� ���������� ����
			Food = FoodCreator.CreateFood();
			Food.DrawSimbol();
		}

		/* ����� ����������� �������� ������, ���� ���� ������ ���� �� �������;
		 * ���� ���� ������ ������� ESC, �� ���������� ���� �����;
		 * � ��������� ������� (���� ������ �������-�������) �������������� ��������� ����������� �������� ������ */
		if ( _kbhit() )
		{
			KEYS CanICallPauseMenu = static_cast<KEYS>(_getch()); //��������� ���������� ��� �������� ������� ������� ESC

			/* ���� ���� ������ ������� ESC, �� ���������� ������� ����-�����, ���������� ���������� ��������;
			 * �������� ������������� ����������:
			 * 100 (�� ������ ����� To Main Menu);
			 * 101 (�� ������ ����� Exit Game);
			 *
			 * ��� ������������ ���������� (� ��� ����� � ���������� ���������� ��� ������������ � �������� ���� ��� �������) 
			 * ��������� ���������� ����� ���� � ������ SnakeGame;
			 * ���������� �������������� � ���������� ������ MainMenu;
			 *-------------------------*
			 * ���� ���� ������ �������-�������, �� ��� �������������� �� ����� else */
			if (CanICallPauseMenu == KEYS::KEY_ESC)
				Menu::PauseMenu();
			else
			{
				KEYS key = static_cast<KEYS>(_getch()); //���������� ��� ��������� ������-�������
				Snake.ChangeDirection(key);
			}
		
			
			/*_getch();
			int choice = _getch();
			Snake.ChangeDirection(choice);*/
		}
	} //end of while
}


/* ����� ���������� ����������� ���� */
void Game::SaveGame()
{
	Menu::CursorParam(true);	//������ ������ �������

	HANDLE hConsol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position; Position.X = 85; Position.Y = 7;
	SetConsoleCursorPosition(hConsol, Position);
	SetConsoleTextAttribute(hConsol, (WORD)(0 << 4 | 4));
	std::cout << " GAME OVER!";
	SetConsoleTextAttribute(hConsol, (WORD)(0 << 4 | 15));

	Position.Y += 2;
	SetConsoleCursorPosition(hConsol, Position);
	std::cout << "Seve your result?(y/n) >> ";
	fflush(stdin);
	if (getchar() == 'y') // � ��� ������������
	{
		Position.Y++;
		SetConsoleCursorPosition(hConsol, Position);
		std::cout << "Enter your name >> ";
		fflush(stdin);
		gets_s(mResult.Name);
		
		/* �������� ��������� ���� � ���� */
		FILE* FResults;
		if (fopen_s(&FResults, "Records.txt", "rb") != 0)
			return;

		//����� ��� �������� �������, ��� ����������� � �����
		//� ������ ���� ����� ����������������
		Result buffer[10];
		for (int i = 0; i < 10; i++)
		{
			strcpy_s(buffer[i].Name, ""); buffer[i].Score = 0;
		}

		int nInd = 0; //������ ��������� �������
		//��������� ��� ������ �� ����� � �����
		while (fread(&buffer[nInd], sizeof(Result), 1, FResults))
		{
			nInd++;
		}
		fclose(FResults);

		//������������� �������
		//���� ������� ��������� ���� ������ ��� �������� ������ �� i-�� ��������
		//�� �������� ������� ���� �������� � �� ��� ��������� �� ���� ������� ����(��������� ������� ������� ���������)
		//�������� ���������� � ����� ��������� �������
		//������ �������� �������� ������� ������������ ��������� ����������� ����
		//���� ���������� �� ���� �����������
		for (int i = 0; i < 10; i++)
		{
			if (mResult.Score > buffer[i].Score)
			{
				for (int j = 9; j >= i; j--)
				{
					strcpy_s(buffer[j].Name, buffer[j - 1].Name);
					buffer[j].Score = buffer[j - 1].Score;
				}
				strcpy_s(buffer[i].Name, mResult.Name);
				buffer[i].Score = mResult.Score;
				break;
			}				
		}

		//���������������� ������ ������������ ������ � ����
		if (fopen_s(&FResults, "Records.txt", "wb") != 0)
			return;
		for (int i = 0; i < 10; i++)
		{
			if (buffer[i].Score != 0)
				fwrite(&buffer[i], sizeof(Result), 1, FResults);
		}
		fclose(FResults);
	}

	Menu::CursorParam(false);	//������ ������ ���������
}


/* ����� ������ �������������� ���������� */
void Game::PrintOtherInf()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position; Position.X = 82; Position.Y = 1;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "Press ESC to stop the game...";

	Position.Y = 3;
	SetConsoleCursorPosition(hConsole, Position);
	Game::GetMaxResult();
	std::cout << "MAX score: " << MAXResult;

	Game::Clear_mResult();
}

/* ����� ������ �������� ���������� */
void Game::GetCurrentScore()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position; Position.X = 82; Position.Y = 4;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "Your score: " << mResult.Score;
}


/* ����� ����������� �� ����� ������� ������� 
 * � ����� � */
void Game::GetRating()
{
	// ��������� �����
	std::cout << "		TOP 10 players" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "| �  |        Name        |    Max result   |" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	/* ��������� ���� � ��������� �������� */
	FILE* FResults;
	if (fopen_s(&FResults, "Records.txt", "rb") != 0)
		return;

	/* ��������� ��� ���������� ����� */
	int nInd = 1;
	while ( fread(&mResult, sizeof(Result), 1, FResults) )
	{
		printf("|%-4d|%-20s|%-17d|\n", nInd, mResult.Name, mResult.Score);
		nInd++;
	}
	std::cout << "---------------------------------------------" << std::endl;
	fclose(FResults);
	Game::Clear_mResult();
	system("pause");
}

/* ����� ��������� ������������ ���������� ���� */
void Game::GetMaxResult()
{
	/* ��������� ���� � ��������� �������� */
	FILE* FResults;
	if (fopen_s(&FResults, "Records.txt", "rb") != 0)
		return;

	/* ��������� ������ ������ ������, �� ��� ������������� ������������� ���������� ���� */
	fread(&mResult, sizeof(mResult), 1, FResults);
	MAXResult = mResult.Score;
	fclose(FResults);
}

/* ����� ��������� ���������� �� ��������� mResults */
void Game::Clear_mResult()
{
	strcpy_s(mResult.Name, "");
	mResult.Score = 0;
}

/* ����� �������� ������������� ����� � ��������� �������;
 * ��������� ������������� ����� �������� _access();
 * ���� ���� �� ���������� �� �� ��������� */
int Game::IsFileExist(char str[])
{
	FILE* fname;
	if (_access(str, 0) == -1)
	{
		fopen_s(&fname, str, "wb");
		fclose(fname);
		return 1;
	}
	return 0;
}
