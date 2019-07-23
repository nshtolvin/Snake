#include "stdafx.h"
#include "SnakeClass.h"


/* ����������� ������. �� ��������� ��������� ���������:
* tail - ������ ������ Point, ������ ����� ���������� ������ �����;
* length - ����� �����;
* direction - ����������� � ������� ������ ����� ��������� ��� ������� ����(�� ��������� ������� ������)
* ���� ������ �������������� ��������, ������� length
* --------------------------------*
* ��������� ������� ����������� �������� ������
* �������� ������ ��� �������� �������, �� ����� == length;
* � ����� ������������ ���� ������:
  - ������� ����� ����� tail (��� ����� ����� �� �� ���������� ��� � tail);
  - ������� ����� �� �������� � ����.�����(offset) � �����������, ����������� � m_direction;
  - �������� ���������� ����� � ����� �������;
* ���������� ��� ��������� ������� ������� ��� ������(head) ������, � ������� - �����(tail)  */
SnakeClass::SnakeClass(Point tail, int length, Direction _direction)
{
	m_direction = _direction;
	//pList.reserve(length); //��� �������
	for (int i = 0; i < length; i++)
	{
		Point copy_point(tail);
		copy_point.Move(i, m_direction);
		pList.push_back(copy_point);
	}
}

SnakeClass::~SnakeClass()
{
}

/* �������� ������ �������������� ��������� ��������:
 * �� ������� ����������� 0-� �������-�����;
 * ����� ��������� �� �������;
 * ��������� �����-������ ����� ������ ������� GetNextPoint;
 * ����� ������ ����������� � ����� �������;
 * ����� ��������� � ������, � ����� ������ �������������� */
void SnakeClass::Move()
{
	Point tail = pList.front();
	pList.erase(pList.begin()); //��� ������� �������� �������� ��������-������
	//pList.pop_front(); //��� ������
	Point head = GetNextPoint();
	pList.push_back(head);
	tail.Clear();
	head.DrawSimbol();
}

/* ����� ��������� ����� ������ ������, �������� �������� ������:
 * �� ������� ����������� ��������� �������;
 * ��������� ��� �����, ������� ��������� �� 1 � ����������� �����������;
 * ����� ������ ������������ � ���������� �������*/
Point SnakeClass::GetNextPoint()
{
	Point oldHead = pList.back();
	Point newHead(oldHead);
	newHead.Move(1, m_direction);
	return newHead;
}

/* �����, ���������� ����������� �������� ������ */
void SnakeClass::ChangeDirection(/*int*/ KEYS _key)
{
	switch (_key)
	{
	case KEY_LEFT: m_direction = Direction::LEFT; break;
	case KEY_UP: m_direction = Direction::UP; break;
	case KEY_RIGHT: m_direction = Direction::RIGHT; break;
	case KEY_DAWN: m_direction = Direction::DOWN; break;
	}
}

/* ����� ��������������� � ���, ��� ��� �������;
 * ������ ��� ����� ������ ������ � �������� ������;
 * ���� ���������� ������ � ���(���������� ��� ��������) �������, �� �������������� ������ ����� � ��������� � ����� ������� */
bool SnakeClass::Eat(Point food)
{
	Point head = GetNextPoint();
	if (head.IsHit(food))
	{
		food.ChangeSimb('*');
		food.DrawSimbol();
		pList.push_back(food);
		return true;
	}
	else
		return false;
}

/* �����, ����������� ������������ ������ ������ � ����� �� ����� �� ����
 * ��� ����� ���������� �� �������, ������� ������� ������, ������� ��������� �������-������;
 * � �����, ������� ����� �������� ���������� ��������� IsHit ������ Point, ��������� ����������� ������ � ����� �� ����� ���� */
bool SnakeClass::IsTailHit()
{
	Point head = pList.back();
	for (int i = 0; i < pList.size() - 1; i++)
	{
		if (head.IsHit(pList[i])) return true;
	}
	return false;
}