#include "stdafx.h"
#include "Figure.h"
//#include "Point.h"

//Figure::Figure()
//{
//}
//
//
//Figure::~Figure()
//{
//}


void Figure::DrawLine() //����� ��������� ������
{
	for each (Point p in pList)
	{
		p.DrawSimbol();
	}
}

//����� ��� �������� ������������ ������, ������� ������ �����(��� ������� ����), � ��������, ���������� � �������� ���������(������)
// �� ������ ��������� � ������� �������, �� �� ������-������ ����������� ��������� �������;
// ����� � ����� ���������� ���������� ���������� ������ ������ �� ����� �������, �� ������� ������� ������� �������� ����
// ��� ����� ���������� ����� IsHit ������ Point
bool Figure::IsFigureHit(Figure fig)
{
	Point sn_head = fig.pList.back();
	for each (Point wall_point in pList)
	{
		if (wall_point.IsHit(sn_head)) return true;
	}
	return false;
}