// Snake(C++).cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Menu.h"
#include "Game.h"



int main()
{
	// задаем параметры конмольного окна
	Menu::SetParameters();

	// выыод главного меню на экран
	Menu::MainMenu();

	return 0;
}

