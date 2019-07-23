#pragma once

#include "HorizontalLine.h"
#include "VerticalLine.h"

//�������� �������� ������ ���������� ������� �������� ����

class Walls
{
	HorizontalLine* UpLine;
	HorizontalLine* DawnLine;
	VerticalLine* LeftLine;
	VerticalLine* RightLine;
public:
	//����������� ������
	//��������� ����� � ������ �������� ����
	Walls(int map_length, int map_width);
	
	~Walls();
	
	void DrawField();	//����� ��������� ������ �������� ����

	/* ����� ����������� ������������ ������ ������ � ����� �� ������ ���� */
	bool IsWallsHit(Figure fig_snake);
};

