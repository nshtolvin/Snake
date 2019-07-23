#pragma once
#include "Walls.h"


/* �������� ��������������� ���� */

class Game: public Walls
{
	struct Result
	{
		char Name[17];
		int Score;
	} mResult;
	int MAXResult; //������������ ��������� ����

private:
	/* ����� �������� ������������� ����� � ��������� ������� */
	int IsFileExist(char str[] = "Records.txt");

	/* ����� ��������� ������������ ���������� ����� */
	void GetMaxResult();
	
	/* ����� ��������� ���������� �� ��������� mResults */
	void Clear_mResult();

public:
	/* ����������� ������ Game ������������� ������� ������� �������� ���� 80�25
	 * �� ����� Game ����������� �� Walls, � Walls ������ ���������������� ������� ����,
	 * �� ���������, ����� ����������� ����� ������� ��� ������������� ����� ������ Walls */
	Game() : Walls(80, 25)
	{
		strcpy_s(mResult.Name, "");
		mResult.Score = 0;
		Game::IsFileExist();
	};
	/* ���������� ����������� ������� ��������� ���� ������ */
	~Game();

	/* ����� � ����� ������ */
	void SnakeGame();

	/* ����� ������ �������������� ���������� */
	void PrintOtherInf();

	/* ����� ���������� ����������� ���� */
	void SaveGame();

	/* ����� ������ �������� ���������� */
	void GetCurrentScore();

	/* ����� ����������� �� ����� ������� ������� */
	void GetRating();
};

