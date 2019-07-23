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
	/* конструктор класса;
	 * в качестве параметров пинимает длину и высоту поля, а также символ для отобоажения еды (по умолчанию это знак $)*/
	FoodCreatorClass(int mapL, int mapW, int fsimb = '$');

	~FoodCreatorClass();

	/* метод генерирующий следующую точку с едой в пределах игрового поля */
	Point CreateFood();
};

