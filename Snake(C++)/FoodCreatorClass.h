#pragma once

#include "Point.h"
#include "stdlib.h"
#include "time.h"

class FoodCreatorClass
{
	int MapLength;
	int MapWidth;
	char FoodSimb;

public:
	/* ����������� ������;
	 * � �������� ���������� �������� ����� � ������ ����, � ����� ������ ��� ����������� ��� (�� ��������� ��� ���� $)*/
	FoodCreatorClass(int mapL, int mapW, int fsimb = '$');

	~FoodCreatorClass();

	/* ����� ������������ ��������� ����� � ���� � �������� �������� ���� */
	Point CreateFood();
};

