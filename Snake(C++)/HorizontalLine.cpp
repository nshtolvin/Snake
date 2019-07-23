#include "stdafx.h"
#include "HorizontalLine.h"



HorizontalLine::HorizontalLine(int xleft, int xright, int y/*, char simb*/)
{
	pList.reserve(xright - xleft); //для вектора
	for (int x = xleft; x < xright; x++)
	{
		Point p(x, y, '-');
		pList.push_back(p);
	}
}


HorizontalLine::~HorizontalLine()
{
}
