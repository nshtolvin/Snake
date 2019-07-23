#include "stdafx.h"
#include "Walls.h"


//конструктор класса
//принимает длину и ширину игрового поля
Walls::Walls(int map_length, int map_width)
{
	UpLine = new HorizontalLine(0, map_length, 0);
	DawnLine = new HorizontalLine(0, map_length, map_width);
	LeftLine = new VerticalLine(0, 1, map_width);
	RightLine = new VerticalLine(map_length - 1, 1, map_width);

}

Walls::~Walls()
{
	delete UpLine;
	delete DawnLine;
	delete LeftLine;
	delete RightLine;
}

void Walls::DrawField()	//метод отрисовки границ игрового поля
{
	UpLine->DrawLine();
	RightLine->DrawLine();
	DawnLine->DrawLine();
	LeftLine->DrawLine();
}

/* метод проверяющий столкновение головы змейки с одной из границ поля 
 * обекты классов VerticalLine и HorizontalLine вызывают метод IsFigureHit, описанный в базовом для них класса Figure */
bool Walls::IsWallsHit(Figure fig_snake)
{
	if (UpLine->IsFigureHit(fig_snake)) return true;
	if (DawnLine->IsFigureHit(fig_snake)) return true;
	if (LeftLine->IsFigureHit(fig_snake)) return true;
	if (RightLine->IsFigureHit(fig_snake)) return true;
	return false;
}