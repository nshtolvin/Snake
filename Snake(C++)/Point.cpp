#include "stdafx.h"
#include "Point.h"
#include "iostream"
#include "Windows.h"


//����������� ������ �� ���������
Point::Point()
{
}


Point::~Point()
{
}


void Point::DrawSimbol()	//����� ��������� �����
{
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = mX;	position.Y = mY;
	SetConsoleCursorPosition(hConsole, position);
	std::cout << mSimb;
}

void Point::Clear()	//����� �������� �����
{
	mSimb = ' ';	//������ ������
	DrawSimbol();	//������ ������������
}

//����� ��������� ����� �� ��������� offset � ������������ dir
void Point::Move(int offset, Direction dir)
{
	switch (dir)
	{
	case UP: mY -= offset; break;
	case DOWN: mY += offset; break;
	case LEFT: mX -= offset; break;
	case RIGHT: mX += offset; break;
	}

}

//�����, ����������� ���������� ��������� �������-�����, ������� ������ �����, � ������, ����������� � �������� ���������
bool Point::IsHit(Point p)
{
	return(p.mX == mX && p.mY == mY);
}

//����� �������� ������ ��� ����������� �����
//������, ������� ������ ����� ������������ ����� �� ������, ���������� � �������� ��������� 
void Point::ChangeSimb(char newsimb)
{
	mSimb = newsimb;
}