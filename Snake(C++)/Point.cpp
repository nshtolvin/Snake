#include "stdafx.h"
#include "Point.h"
#include "iostream"
#include "Windows.h"


//конструктор класса по умолчанию
Point::Point()
{
}


Point::~Point()
{
}


void Point::DrawSimbol()	//метод рисования точки
{
	COORD position;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = mX;	position.Y = mY;
	SetConsoleCursorPosition(hConsole, position);
	std::cout << mSimb;
}

void Point::Clear()	//метод стирания точки
{
	mSimb = ' ';	//ставим пробел
	DrawSimbol();	//заново отрисовываем
}

//метод смещающий точку на величеину offset в направлениии dir
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

//метод, проверяющий совпадение координат объекта-точки, который вызвыл метод, с точкой, переданноый в качестве параметра
bool Point::IsHit(Point p)
{
	return(p.mX == mX && p.mY == mY);
}

//метод меняющий символ для отображения точки
//символ, которым теперь будет отображаться точки на экране, передается в качестве параметра 
void Point::ChangeSimb(char newsimb)
{
	mSimb = newsimb;
}