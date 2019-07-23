#include "stdafx.h"
#include "FoodCreatorClass.h"


FoodCreatorClass::FoodCreatorClass(int mapL, int mapW, int fsimb) 
	: MapLength(mapL), MapWidth(mapW), FoodSimb(fsimb)
{	}


FoodCreatorClass::~FoodCreatorClass()
{
}

Point FoodCreatorClass::CreateFood()
{
	int x = 1 + rand() % (MapLength-2);
	int y = 1 + rand() % (MapWidth-2);
	return Point(x, y, FoodSimb);
}