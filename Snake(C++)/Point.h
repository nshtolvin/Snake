#pragma once

#include "Directions.h"


/* �������� ����� Point 
 * ����� ����� �� ������ ���������������:
 * ����������� �� ���� � � �; ��������, ������� ������������ ����� */

class Point
{
	int mX;
	int mY;
	char mSimb;

public:
	Point();	//����������� ������ �� ���������

	//����������� ����� �� ������� ������������ ����� ������� ������
	Point(int x, int y, char simb = '*') :mX(x), mY(y), mSimb(simb)
	{ };

	~Point();

	void DrawSimbol(); //����� ��������� �����
	void Clear();	//����� �������� �����
	
	//����� ��������� ����� �� ��������� offset � ������������ dir
	void Move(int offset, Direction dir);
	
	//�����, ����������� ���������� ��������� �������-�����, ������� ������ �����, � ������, ����������� � �������� ���������
	bool IsHit(Point p);
	
	//����� �������� ������ ��� ����������� �����
	//������, ������� ������ ����� ������������ ����� �� ������, ���������� � �������� ��������� 
	void ChangeSimb(char newsimb);
};
