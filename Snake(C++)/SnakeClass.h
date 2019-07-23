#pragma once
#include "Figure.h"
#include "Point.h"
#include "Comands.h"

/* �������� ����� SnakeClass - �����, �� ������� ������ */

class SnakeClass : public Figure
{
public: Direction m_direction;	//����������� � ������� ��������� ������

public:
	/* ����������� ������. �� ��������� ��������� ���������:
	 * tail - ������ ������ Point, ������ ����� ���������� ������ �����;
	 * length - ����� �����(�� ��������� ������� 4);
	 * direction - ����������� � ������� ������ ����� ��������� ��� ������� ����(�� ��������� ������� ������)
	 * ���� ������ �������������� ��������, ������� length*/
	SnakeClass(Point tail, int length = 4, Direction _direction = Direction::RIGHT);
	~SnakeClass();

	/* �����, ����������� ����������� ������ ��������� ��������:
	 * �� ������� ����������� 0-� �������-�����;
	 * ����� ��������� �� �������;
	 * ��������� �����-������ ����� ������ ������� GetNextPoint;
	 * ����� ������ ����������� � ����� �������;
	 * ����� ��������� � ������, � ����� ������ �������������� */
	void Move();
	
	/* ����� ��������� ����� ������ ������, �������� �������� ������:
	 * �� ������� ����������� ��������� �������;
	 * ��������� ��� �����, ������� ��������� �� 1 � ����������� �����������;
	 * ����� ������ ������������ � ���������� �������*/
	Point GetNextPoint();

	/* �����, ���������� ����������� �������� ������ */
	void ChangeDirection(/*int*/ KEYS _key);

	/* ����� ��������������� � ���, ��� ��� �������;
	* ������ ��� ����� ������ ������ � �������� ������;
	* ���� ���������� ������ � ���(���������� ��� ��������) �������, �� �������������� ������ ����� � ��������� � ����� ������� */
	bool Eat(Point food);

	/* �����, ����������� ������������ ������ ������ � ����� �� ����� �� ����
	 * ��� ����� ���������� �� �������, ������� ������� ������, ������� ��������� �������-������;
	 * � �����, ������� ����� �������� ���������� ��������� IsHit ������ Point, ��������� ����������� ������ � ����� �� ����� ���� */
	bool IsTailHit();
};
