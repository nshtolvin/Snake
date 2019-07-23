#pragma once
#include "Walls.h"


/* содержит непосредственно игру */

class Game: public Walls
{
	struct Result
	{
		char Name[17];
		int Score;
	} mResult;
	int MAXResult; //максимальный результат игры

private:
	/* метод проверки существования файла с рейтиногм игрогов */
	int IsFileExist(char str[] = "Records.txt");

	/* метод получения масимального результата игрыы */
	void GetMaxResult();
	
	/* метод стирающий информацию из структуры mResults */
	void Clear_mResult();

public:
	/* конструктор класса Game автоматически создает границы игрового поля 80х25
	 * тк класс Game наследуется от Walls, а Walls должен инициализировать граници поля,
	 * то указываем, какой конструктор нужно вызвать для инициализации полей класса Walls */
	Game() : Walls(80, 25)
	{
		strcpy_s(mResult.Name, "");
		mResult.Score = 0;
		Game::IsFileExist();
	};
	/* деструктор освобождает занятую границыми поля пямять */
	~Game();

	/* метод с игрой змейка */
	void SnakeGame();

	/* метод вывода дополнительной информации */
	void PrintOtherInf();

	/* метод сохранения результатов игры */
	void SaveGame();

	/* метод вывода текущего результата */
	void GetCurrentScore();

	/* метод считывающий из файла рейтинг игроков */
	void GetRating();
};

