#pragma once

#include "Figure.h"

class HorizontalLine: public Figure
{
public:
	HorizontalLine(int xleft, int xright, int y/*, char simb*/);
	~HorizontalLine();
};

