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

/* ����� �������� ��������� ���� 
 * �������� ���� (title) �������� �� SNAKE;
 * ����� ����� � ���� ����������� �� 29;
 *-------------------------*
 * �������� ���� ����� ���(���������) LPCTSTR 
 *-------------------------*
 * ��� ��������� �������� ���� �����: --���������� ���� CONSOLE_SCREEN_BUFFER_INFOEX, �������� ����������� ���������� �� ���� �������;
 *									  --���������� ������ 
 *  */
void Menu::SetParameters()
{
	LPCTSTR WindowName = L"SNAKE.exe";
	SetConsoleTitle(WindowName);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//�������� ���������
	CONSOLE_SCREEN_BUFFER_INFOEX WinInfo;				//���������� ��������� � ����������� �������
	WinInfo.cbSize = sizeof(WinInfo);					//�������� ���� � �������� ��������� � ������ (��� �� ��������)
	GetConsoleScreenBufferInfoEx(hConsole, &WinInfo);	//������ ������� ���������� �������
	WinInfo.dwSize.Y = 29;								//�������� ������ ���� 
	SetConsoleScreenBufferInfoEx(hConsole, &WinInfo);	//������������� ���������
	
	Menu::CursorParam(false); //������ ������ ���������
}


/* ����� �������� � ��������� �������� ���� ���������;
 * ��������� ���� ���������� ������ ������, �������� ���� - ����� */
void Menu::MainMenu()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//�������� ���������� ������ ��� ��������� ����� ���������� �� ����� ������
	int main_choice = 0; //������ ���������� ������ �������� ����
	bool END_FLAG = FALSE; //���� ����������� ����� � ������� ����

	Game* snake = new Game(); //������� ������ ������ Game

	do
	{
		/* ��������� �������� ���� */
		system("cls");
		std::cout << "\n\n\n";
		SetConsoleTextAttribute(hConsole, (WORD)(0 << 4 | 14));
		std::cout << "\t\tSNAKE" << endl << endl;
		SetConsoleTextAttribute(hConsole, (WORD)(0 << 4 | 15));
		std::cout << "\t ->";
		std::cout << "   New game" << endl;
		std::cout << "\t      Rating TOP10 players" << endl;
		std::cout << "\t      Exit";
		main_choice = ChoicOfMenu(5, 7, 9); //����� ������ (��������������) ������ ������ �������� ����

		switch (main_choice) 
		{
		// ����� �������� ���� New Game
		case 5:
			system("cls");
			try
			{
				snake->DrawField();
				snake->PrintOtherInf();
				snake->SnakeGame();
			}
			// ��������� ����������, ���������� � ���� ����
			catch (int exception)
			{
				switch (exception)
				{
				//��������� ���������� - ������ ��������� � ����� ��� �����
				case -1: snake->SaveGame();	break;

				//��������� ���������� - � ����-����� ������ ����� To Main Menu
				case 100: break;
					
				//��������� ���������� - � ����-����� ������ ����� Exit Game
				// ��������� ������ ��������� ���� ���������� ���������:
				// ������������� ���� ���������� ����� � TRUE, ����� ����� Main Menu ���������� � ��������� �������� ������� main ����������� ����������
				case 101: END_FLAG = TRUE; break;
				}
			}
			break;
		
		// ����� �������� ���� Rating TOP 10 players
		case 6:  system("cls"); snake->GetRating(); break;
		
		// ����� �������� ���� Exit:
		// ��������� ������ ��������� ���� ���������� ���������:
		// ������������� ���� ���������� ����� � TRUE, ����� ����� Main Menu ���������� � ��������� �������� ������� main ����������� ����������
		case 7: END_FLAG = TRUE; break;
		}
	} while (!END_FLAG);

	delete snake;	//������ ������ Game ���������
}


/* ���� ����� */
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

	sub_choice = ChoicOfMenu(8, 10, 85); //����� ������� ���������� ��������(->) �� ������

	switch (sub_choice)
	{
	case 8: Menu::DeleteMenu();	break;	//����� ���������� -- ������������ � ���� � ����� 0; ������� ���������
	case 9:	throw 100 ;	// ����� "� ������� ����" -- ���������� 100
	case 10: throw 101;	//����� "����� �� ����" -- ���������� 101
	}
}


//�������� �������
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


/* ����� ������ ������ ����;
 * ����������� ���������� ������� ����������� � ������������ ������ �� ������; ���������� ��� ������������ ����;
 * ����� ���������� ������� �� ��� �;
 * ���������� �������������� ��������� ����� / ����;
 * ����� �� ������� ������� ENTER;
 * �������� ������� �� ���� ����������� � ������� ����������� �������, ��������� � ����������� �������-���������;
 * ���������� ������ ���������� ������ ���� */
int ChoicOfMenu(int min, int max, int x)
{
	KEYS m_key = KEYS::NO_KEY; //���������� �� ������������ �������

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;
	Position.X = x;
	Position.Y = min;
	SetConsoleCursorPosition(hConsole, Position); //������ ��������������� �� ������ � ����������� ��������

	while (m_key != KEYS::KEY_ENTER) 
	{
		m_key = static_cast<KEYS>(_getch());	//�������� ������� ������� � ������� �� � ���� KEYS
		
		switch (m_key)
		{
		case KEYS::KEY_UP:		//��������� ������� �����
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
		case KEYS::KEY_DAWN:	//��������� ������� ����
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
	return Position.Y; //���������� ������ ���������� ������ �������� ����
}


/* ����� ���������/������������ ������ */
void Menu::CursorParam(bool inf)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursInfo;
	GetConsoleCursorInfo(hConsole, &CursInfo);
	CursInfo.bVisible = inf;
	SetConsoleCursorInfo(hConsole, &CursInfo);
}