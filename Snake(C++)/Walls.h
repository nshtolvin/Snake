#pragma once

#include "HorizontalLine.h"
#include "VerticalLine.h"

//содержит описание класса создающего границы игрового поля

class Walls
{
	HorizontalLine* UpLine;
	HorizontalLine* DawnLine;
	VerticalLine* LeftLine;
	VerticalLine* RightLine;
public:
	//конструктор класса
	//принимает длину и ширину игрового поля
	Walls(int map_length, int map_width);
	
	~Walls();
	
	void DrawField();	//метод отрисовки границ игрового поля

	/* метод проверяющий столкновение головы змейки с одной из границ поля */
	bool IsWallsHit(Figure fig_snake);
};

