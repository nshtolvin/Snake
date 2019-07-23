#pragma once


/* содержит класс описывающий работу главного меню и подменю игры */

class Menu
{
private:
	/* метод выбота пункта меню;
	 * параметрами передаются индексы минимальной и максимальной строки на экране; необходимо для зацикливания меню;
	 * также координата стрелки по оси Х */
	friend int ChoicOfMenu(int min, int max, int x);

public:
	Menu();
	~Menu();

	//метод задающий параметры окна
	static void SetParameters();

	//метод создания и отрисовки главного меню программы
	static void MainMenu();

	// меню паузы
	static void PauseMenu();

	//стирание подменю
	static void DeleteMenu();

	/* метод стирающий/отображающий курсор */
	static void CursorParam(bool inf);
};