#include "stdafx.h"
#include "VerticalLine.h"


VerticalLine::VerticalLine(int x, int yup, int ydawn/*, char simb*/)
{
	pList.reserve(ydawn - yup); //для вектора
	for (int y = yup; y < ydawn; y++)
	{
		Point p(x, y, '|');
		pList.push_back(p);
	}
}


VerticalLine::~VerticalLine()
{
}
