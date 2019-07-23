#pragma once


/* �������� ����� ����������� ������ �������� ���� � ������� ���� */

class Menu
{
private:
	/* ����� ������ ������ ����;
	 * ����������� ���������� ������� ����������� � ������������ ������ �� ������; ���������� ��� ������������ ����;
	 * ����� ���������� ������� �� ��� � */
	friend int ChoicOfMenu(int min, int max, int x);

public:
	Menu();
	~Menu();

	//����� �������� ��������� ����
	static void SetParameters();

	//����� �������� � ��������� �������� ���� ���������
	static void MainMenu();

	// ���� �����
	static void PauseMenu();

	//�������� �������
	static void DeleteMenu();

	/* ����� ���������/������������ ������ */
	static void CursorParam(bool inf);
};