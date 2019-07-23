#include "stdafx.h"
#include "Figure.h"
//#include "Point.h"

//Figure::Figure()
//{
//}
//
//
//Figure::~Figure()
//{
//}


void Figure::DrawLine() //метод рисования фигуры
{
	for each (Point p in pList)
	{
		p.DrawSimbol();
	}
}

//метод для проверки столкновение обекта, который вызвал метод(это граница поля), с объектом, переданным в качестве параметра(змейка)
// тк змейка врезается в границу головой, то из векора-змейки извлекается последний элемент;
// далее в цикле проверятся совпадение координаты головы змейки со всеми точками, из которых состоит границы игрового поля
// для этого вызывается метод IsHit класса Point
bool Figure::IsFigureHit(Figure fig)
{
	Point sn_head = fig.pList.back();
	for each (Point wall_point in pList)
	{
		if (wall_point.IsHit(sn_head)) return true;
	}
	return false;
}