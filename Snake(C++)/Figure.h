#pragma once

#include "Point.h"
#include "list"
#include "vector"

/* содержит класс Figure - базовый класс для основных объектов игры
 * таких как границы поля и сама змейка*/

using namespace std;

class Figure
{
protected:
	//list<Point> pList;
	vector<Point> pList;

public:
	/*Figure();
	~Figure();*/

	void DrawLine(); //метод рисования фигуры

	//метод для проверки столкновение обекта, который вызвал метод(это граница поля), с объектом, переданным в качестве параметра(змейка)
	bool IsFigureHit(Figure fig);
};

