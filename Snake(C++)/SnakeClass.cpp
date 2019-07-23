#include "stdafx.h"
#include "SnakeClass.h"


/* Конструктор класса. Он принимает следующие параметры:
* tail - объект класса Point, всегда имеет координату ХВОСТА змеки;
* length - длина змеки;
* direction - направление в котором змейка будет двигаться при началле игры(по умолчанию сделаем ВПРАВО)
* сама змейка представляется вектором, длинной length
* --------------------------------*
* запоминам текущее направление движения змейки
* выделяем память под элементы вектора, их число == length;
* в цикле отрисовываем тело змейки:
  - создаем копию точки tail (она будет иметь те же координаты что и tail);
  - смещаем копию на величину № итер.цикла(offset) в направлении, сохраненном в m_direction;
  - обавляем полученную точку в конец вектора;
* получается что последний элемент вектора это ГОЛОВА(head) змейки, а нулевой - ХВОСТ(tail)  */
SnakeClass::SnakeClass(Point tail, int length, Direction _direction)
{
	m_direction = _direction;
	//pList.reserve(length); //для вектора
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

/* движение змейки осуществляется следующим способом:
 * из вектора извлекается 0-й элемент-хвост;
 * хвост удаляется из вектора;
 * создается точка-голова путем вызова функции GetNextPoint;
 * новыя голова добавляется в конец вектора;
 * хвост стирается с экрана, а новая голова отрисовывается */
void SnakeClass::Move()
{
	Point tail = pList.front();
	pList.erase(pList.begin()); //для вектора удаление нулевого элемента-хвоста
	//pList.pop_front(); //для списка
	Point head = GetNextPoint();
	pList.push_back(head);
	tail.Clear();
	head.DrawSimbol();
}

/* метод создающий новую голову змейки, иметируя движение змейки:
 * из вектора извлекается последний элемент;
 * создается его копия, которая смещается на 1 в сохраненном направлении;
 * новая голова возвращается в вызывающую функцию*/
Point SnakeClass::GetNextPoint()
{
	Point oldHead = pList.back();
	Point newHead(oldHead);
	newHead.Move(1, m_direction);
	return newHead;
}

/* метод, изменяющий направление движения змейки */
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

/* метод сигнализирующий о том, что еда съедена;
 * узнаем где будет голова змейки в слудущий момент;
 * если координаты головы и еды(переданной как аргумент) совпали, то перерисовываем символ точки и добавляем в конец вектора */
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

/* метод, проверяющий столкновение головы змейки с одной из точек ее тела
 * для этого необходимо из вектора, которым описана змейка, извлечь последний элемент-голову;
 * в цикле, вызывая метод проверки совпадения координат IsHit класса Point, проверяем солкновение головы с одной из точек тела */
bool SnakeClass::IsTailHit()
{
	Point head = pList.back();
	for (int i = 0; i < pList.size() - 1; i++)
	{
		if (head.IsHit(pList[i])) return true;
	}
	return false;
}