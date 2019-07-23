#include "stdafx.h"
#include "Game.h"

#include "conio.h"
#include "Windows.h"
#include "iostream"
#include "string"
#include "io.h"
#include "fstream"
#include "array"

#include "Point.h"
#include "SnakeClass.h"
#include "FoodCreatorClass.h"
#include "Menu.h"


//Game::Game():
//{
//	printf("  Game  ");
//}

/* деструктор освобождает занятую границыми поля пямять */
Game::~Game()
{}


/* метод содержит саму игру змейку */
void Game::SnakeGame()
{
	srand(time(NULL));
	Game::GetCurrentScore(); //отрисовка текущего результата игры
	
	//создадим змейку: создадим точку с некторыми координатами. Это  будет хвост змейки
	Point MyTail(4, 5);

	//создадим начальную змеку с хвостом в точке MyTail и длиной 4. Нарисуем её на экране
	SnakeClass Snake(MyTail);
	Snake.DrawLine();

	//создаем точку с едой
	FoodCreatorClass FoodCreator(80, 25);
	Point Food = FoodCreator.CreateFood();
	Food.DrawSimbol();

	//движение змейки
	while (true)
	{
		/* проверяем столкнется ли змейка с препятствием;
		 * если змейка ударяется о границу поли или свое тело, то генерируем исключение */
		if (Game::IsWallsHit(Snake) || Snake.IsTailHit())
			throw - 1;		// исключение -1

		/* змейка перемещается */
		Snake.Move();
		Sleep(170);
		
		/* проверяем будет ли съедена еда и создаем новую, если ее съедят
		 * счетчик съеденой еды увеличивается */
		if (Snake.Eat(Food))
		{
			mResult.Score++;
			Game::GetCurrentScore(); //отрисовка текущего результата игры
			Food = FoodCreator.CreateFood();
			Food.DrawSimbol();
		}

		/* меням направление движения змейки, если была нажата одна из стрелок;
		 * если была нажата клавиша ESC, то вызывается меню паузы;
		 * в остальных случаях (были нажаты клавиши-стрелки) обрабатывается изменение направления движения змейки */
		if ( _kbhit() )
		{
			KEYS CanICallPauseMenu = static_cast<KEYS>(_getch()); //отдельная переменная для фиксации нажатия клавиши ESC

			/* если была нажата клавиша ESC, то вызывается функция меню-паузы, определяет дальнейшие действия;
			 * Возможно сгенерированы исключения:
			 * 100 (те выбран пункт To Main Menu);
			 * 101 (те выбран пункт Exit Game);
			 *
			 * все выработанные исключения (в том числе и исключение полученное при столкновении в границей поля или хвостом) 
			 * завершают выполнение цикла игры и метода SnakeGame;
			 * исключения обрабатываются в вызывающем методе MainMenu;
			 *-------------------------*
			 * если была нажата клавиша-стрелка, то она обрабатывается по ветке else */
			if (CanICallPauseMenu == KEYS::KEY_ESC)
				Menu::PauseMenu();
			else
			{
				KEYS key = static_cast<KEYS>(_getch()); //переменная для обработки клавиш-стрклок
				Snake.ChangeDirection(key);
			}
		
			
			/*_getch();
			int choice = _getch();
			Snake.ChangeDirection(choice);*/
		}
	} //end of while
}


/* метод сохранения результатов игры */
void Game::SaveGame()
{
	Menu::CursorParam(true);	//курсор делаем видимым

	HANDLE hConsol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position; Position.X = 85; Position.Y = 7;
	SetConsoleCursorPosition(hConsol, Position);
	SetConsoleTextAttribute(hConsol, (WORD)(0 << 4 | 4));
	std::cout << " GAME OVER!";
	SetConsoleTextAttribute(hConsol, (WORD)(0 << 4 | 15));

	Position.Y += 2;
	SetConsoleCursorPosition(hConsol, Position);
	std::cout << "Seve your result?(y/n) >> ";
	fflush(stdin);
	if (getchar() == 'y') // с эхо отображением
	{
		Position.Y++;
		SetConsoleCursorPosition(hConsol, Position);
		std::cout << "Enter your name >> ";
		fflush(stdin);
		gets_s(mResult.Name);
		
		/* сохраням результат игры в файл */
		FILE* FResults;
		if (fopen_s(&FResults, "Records.txt", "rb") != 0)
			return;

		//буфер для хранения записей, уже находящихся в файле
		//в начале весь буфер инициализируется
		Result buffer[10];
		for (int i = 0; i < 10; i++)
		{
			strcpy_s(buffer[i].Name, ""); buffer[i].Score = 0;
		}

		int nInd = 0; //индекс буферного массива
		//считываем все записи из файла в буфер
		while (fread(&buffer[nInd], sizeof(Result), 1, FResults))
		{
			nInd++;
		}
		fclose(FResults);

		//сортиртировка массива
		//если текущий результат игры больше чем значение буфера на i-ой итерации
		//то элементы массива ниже текущего и он сам смещаются на одну позицию вниз(последний элемент массива стирается)
		//смещение происходит с конца буферного массива
		//вместо текущего элемента массива записывается результат сохраняемой игры
		//цикл сортировки на этом завершается
		for (int i = 0; i < 10; i++)
		{
			if (mResult.Score > buffer[i].Score)
			{
				for (int j = 9; j >= i; j--)
				{
					strcpy_s(buffer[j].Name, buffer[j - 1].Name);
					buffer[j].Score = buffer[j - 1].Score;
				}
				strcpy_s(buffer[i].Name, mResult.Name);
				buffer[i].Score = mResult.Score;
				break;
			}				
		}

		//отсортированнный массив записывается заново в файл
		if (fopen_s(&FResults, "Records.txt", "wb") != 0)
			return;
		for (int i = 0; i < 10; i++)
		{
			if (buffer[i].Score != 0)
				fwrite(&buffer[i], sizeof(Result), 1, FResults);
		}
		fclose(FResults);
	}

	Menu::CursorParam(false);	//курсор делаем невидимым
}


/* метод вывода дополнительной информации */
void Game::PrintOtherInf()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position; Position.X = 82; Position.Y = 1;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "Press ESC to stop the game...";

	Position.Y = 3;
	SetConsoleCursorPosition(hConsole, Position);
	Game::GetMaxResult();
	std::cout << "MAX score: " << MAXResult;

	Game::Clear_mResult();
}

/* метод вывода текущего результата */
void Game::GetCurrentScore()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position; Position.X = 82; Position.Y = 4;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "Your score: " << mResult.Score;
}


/* метод считывающий из файла рейтинг игроков 
 * в стиле С */
void Game::GetRating()
{
	// отрисовка шапки
	std::cout << "		TOP 10 players" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "| №  |        Name        |    Max result   |" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	/* открываем файл и проверяем открытие */
	FILE* FResults;
	if (fopen_s(&FResults, "Records.txt", "rb") != 0)
		return;

	/* считываем все содержимое файла */
	int nInd = 1;
	while ( fread(&mResult, sizeof(Result), 1, FResults) )
	{
		printf("|%-4d|%-20s|%-17d|\n", nInd, mResult.Name, mResult.Score);
		nInd++;
	}
	std::cout << "---------------------------------------------" << std::endl;
	fclose(FResults);
	Game::Clear_mResult();
	system("pause");
}

/* метод получения масимального результата игры */
void Game::GetMaxResult()
{
	/* открываем файл и проверяем открытие */
	FILE* FResults;
	if (fopen_s(&FResults, "Records.txt", "rb") != 0)
		return;

	/* считываем только первую запись, тк она соответствует максимальному результату игры */
	fread(&mResult, sizeof(mResult), 1, FResults);
	MAXResult = mResult.Score;
	fclose(FResults);
}

/* метод стирающий информацию из структуры mResults */
void Game::Clear_mResult()
{
	strcpy_s(mResult.Name, "");
	mResult.Score = 0;
}

/* метод проверки существования файла с рейтиногм игрогов;
 * проверяем существование файла функцией _access();
 * если файл не существует то он создается */
int Game::IsFileExist(char str[])
{
	FILE* fname;
	if (_access(str, 0) == -1)
	{
		fopen_s(&fname, str, "wb");
		fclose(fname);
		return 1;
	}
	return 0;
}
