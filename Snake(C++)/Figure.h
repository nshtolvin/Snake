#pragma once

#include "Point.h"
#include "list"
#include "vector"

/* �������� ����� Figure - ������� ����� ��� �������� �������� ����
 * ����� ��� ������� ���� � ���� ������*/

using namespace std;

class Figure
{
protected:
	//list<Point> pList;
	vector<Point> pList;

public:
	/*Figure();
	~Figure();*/

	void DrawLine(); //����� ��������� ������

	//����� ��� �������� ������������ ������, ������� ������ �����(��� ������� ����), � ��������, ���������� � �������� ���������(������)
	bool IsFigureHit(Figure fig);
};

