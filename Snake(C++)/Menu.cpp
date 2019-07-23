#include "stdafx.h"
#include "conio.h"
#include "Windows.h"
#include "iostream"

#include "Menu.h"
#include "Comands.h"
#include "Game.h"


using namespace std;


Menu::Menu()
{
}

Menu::~Menu()
{
}

/* метод задающий параметры окна 
 * название окна (title) меняется на SNAKE;
 * число строк в окне сокращается до 29;
 *-------------------------*
 * название окна имеет тип(строковый) LPCTSTR 
 *-------------------------*
 * для изменения размеров окна нужна: --переменная типа CONSOLE_SCREEN_BUFFER_INFOEX, хранящая расширенную информацию об окне консоли;
 *									  --дискриптор вывода 
 *  */
void Menu::SetParameters()
{
	LPCTSTR WindowName = L"SNAKE.exe";
	SetConsoleTitle(WindowName);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//получаем дискиптор
	CONSOLE_SCREEN_BUFFER_INFOEX WinInfo;				//определяем структуру с параметрами консоли
	WinInfo.cbSize = sizeof(WinInfo);					//заполене поля с размером структуры в байтах (без не работает)
	GetConsoleScreenBufferInfoEx(hConsole, &WinInfo);	//узнаем текущие перраметры консоли
	WinInfo.dwSize.Y = 29;								//изменяем высоту окна 
	SetConsoleScreenBufferInfoEx(hConsole, &WinInfo);	//устанавливаем изменения
	
	Menu::CursorParam(false); //курсор делаем невидимым
}


/* метод создания и отрисовки главного меню программы;
 * заголовок игры печатается желтым цветом, отальное меню - белым */
void Menu::MainMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//получаем дискриптор вывода для изменения цвета выводимого на экран текста
	int main_choice = 0; //индекс выбранного пункта главного меню
	bool END_FLAG = FALSE; //флаг завершеения цикла с главным меню

	Game* snake = new Game(); //создаем объект класса Game

	do
	{
		/* отрисовка главного меню */
		system("cls");
		std::cout << "\n\n\n";
		SetConsoleTextAttribute(hConsole, (WORD)(0 << 4 | 14));
		std::cout << "\t\tSNAKE" << endl << endl;
		SetConsoleTextAttribute(hConsole, (WORD)(0 << 4 | 15));
		std::cout << "\t ->";
		std::cout << "   New game" << endl;
		std::cout << "\t      Rating TOP10 players" << endl;
		std::cout << "\t      Exit";
		main_choice = ChoicOfMenu(5, 7, 9); //вызов метода (дружественного) выбора пункта главного меню

		switch (main_choice) 
		{
		// пункт главного меню New Game
		case 5:
			system("cls");
			try
			{
				snake->DrawField();
				snake->PrintOtherInf();
				snake->SnakeGame();
			}
			// обработка исключений, полученных в ходе игры
			catch (int exception)
			{
				switch (exception)
				{
				//обработка исключения - змейка врезалась в стену или хвост
				case -1: snake->SaveGame();	break;

				//обработка исключения - в меню-паузы выбран пункт To Main Menu
				case 100: break;
					
				//обработка исключения - в меню-паузы выбран пункт Exit Game
				// программа должна завершить свое выполнение полностью:
				// устанавливаем флаг завершения цикла в TRUE, затем метод Main Menu завершится и управлени вернется функции main консольного приложения
				case 101: END_FLAG = TRUE; break;
				}
			}
			break;
		
		// пункт главного меню Rating TOP 10 players
		case 6:  system("cls"); snake->GetRating(); break;
		
		// пункт главного меню Exit:
		// программа должна завершить свое выполнение полностью:
		// устанавливаем флаг завершения цикла в TRUE, затем метод Main Menu завершится и управлени вернется функции main консольного приложения
		case 7: END_FLAG = TRUE; break;
		}
	} while (!END_FLAG);

	delete snake;	//объект класса Game удаляется
}


/* меню паузы */
void Menu::PauseMenu()
{
	int sub_choice = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = 85;	Position.Y = 7;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "    Pause";

	Position.Y++;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "->" << " Continue";

	Position.Y++;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "   To Main Menu";

	Position.Y++;
	SetConsoleCursorPosition(hConsole, Position);
	std::cout << "   Exit Game";

	sub_choice = ChoicOfMenu(8, 10, 85); //вызов функции управления курсором(->) на экране

	switch (sub_choice)
	{
	case 8: Menu::DeleteMenu();	break;	//пункт продолжить -- возвращаемся в игру с кодом 0; подменю стирается
	case 9:	throw 100 ;	// пункт "В главное меню" -- исключение 100
	case 10: throw 101;	//пункт "Выход из игры" -- исключение 101
	}
}


//стирание подменю
void Menu::DeleteMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;	Position.X = 85; Position.Y = 7;
	for (int i = 0; i < 4; i++)
	{
		SetConsoleCursorPosition(hConsole, Position);
		std::cout << "                   ";
		Position.Y++;
	}

}


/* метод выбота пункта меню;
 * параметрами передаются индексы минимальной и максимальной строки на экране; необходимо для зацикливания меню;
 * также координата стрелки по оси Х;
 * управление осуществляется стрелками вверх / вниз;
 * выбор по нажатию клавиши ENTER;
 * движение стрелки по меню выполняется с помощью перемещения курсора, стрирания и перерисовки стрелки-указателя;
 * возвращает индекс выбранного пункта меню */
int ChoicOfMenu(int min, int max, int x)
{
	KEYS m_key = KEYS::NO_KEY; //полученная от пользователя клавиша

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = x;
	Position.Y = min;
	SetConsoleCursorPosition(hConsole, Position); //курсор устанавливается на строку с минимальным индексом

	while (m_key != KEYS::KEY_ENTER) 
	{
		m_key = static_cast<KEYS>(_getch());	//получаем нажатую клавишу и приводи ее к типу KEYS
		
		switch (m_key)
		{
		case KEYS::KEY_UP:		//обработка клавиши вверх
		{
							 if (Position.Y > min)
							 {
								 cout << "  ";
								 Position.Y--;
								 SetConsoleCursorPosition(hConsole, Position);
								 cout << "->";
								 SetConsoleCursorPosition(hConsole, Position);
							 }
							 else
							 {
								 cout << "  ";
								 Position.Y = max;
								 SetConsoleCursorPosition(hConsole, Position);
								 cout << "->";
								 SetConsoleCursorPosition(hConsole, Position);
							 }
							 break;
		}
		case KEYS::KEY_DAWN:	//обработка клавиши вниз
		{
							   if (Position.Y < max)
							   {
								   cout << "  ";
								   Position.Y++;
								   SetConsoleCursorPosition(hConsole, Position);
								   cout << "->";
								   SetConsoleCursorPosition(hConsole, Position);
							   }
							   else
							   {
								   cout << "  ";
								   Position.Y = min;
								   SetConsoleCursorPosition(hConsole, Position);
								   cout << "->";
								   SetConsoleCursorPosition(hConsole, Position);
							   }
							   break;
		}
		} //end of swotch
	} //end of while
	return Position.Y; //запоминаем индекс выбранного пункта главного меню
}


/* метод стирающий/отображающий курсор */
void Menu::CursorParam(bool inf)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursInfo;
	GetConsoleCursorInfo(hConsole, &CursInfo);
	CursInfo.bVisible = inf;
	SetConsoleCursorInfo(hConsole, &CursInfo);
}