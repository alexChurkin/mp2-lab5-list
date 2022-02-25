#pragma once
#include<iostream>
#include "THeadList.h"

/* ..................... TMonom ..................... */

struct TMonom
{
	//Коэффициент
	double coeff;
	//Степени при x, y и z
	int x, y, z;

	TMonom()
	{
		coeff = 0;
		x = y = z = 0;
	}

	TMonom(int _x, int _y, int _z)
	{
		coeff = 0;
		x = _x;
		y = _y;
		z = _z;
	}

	bool operator==(const TMonom& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool operator!=(const TMonom& other)
	{
		return !operator==(other);
	}

	bool operator<(const TMonom& other)
	{
		if (x < other.x) return true;
		else if (x == other.x)
		{
			if (y < other.y) return true;
			else if (y == other.y)
			{
				if (z < other.z) return true;
				else if (z == other.z)
				{
					return coeff < other.coeff;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}

	bool operator>(const TMonom& other)
	{
		return !operator==(other) && !operator<(other);
	}

	friend std::istream& operator>>(std::istream& is, TMonom& m)
	{
		is >> m.coeff >> m.x >> m.y >> m.z;
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, TMonom& monom)
	{
		os << monom.coeff;
		if (monom.x != 0)
		{
			os << "x";
			if (monom.x != 1) os << "^" << monom.x;
		}
		if (monom.y != 0)
		{
			os << "y";
			if (monom.y != 1) os << "^" << monom.y;
		}
		if (monom.z != 0)
		{
			os << "z";
			if (monom.z != 1) os << "^" << monom.y;
		}
		return os;
	}
};

/* .................... TPolinom .................... */

class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();

	//Const тут не пишем, иначе Reset и GetNext
	//не будут работать
	TPolinom(TPolinom& other);

	//TODO оператор присваивания (на след. занятии напишем)
	void AddMonom(TMonom m);

	//уточнить, & или нет в первом случае
	TPolinom& operator+(TPolinom& p);
};

TPolinom::TPolinom():THeadList<TMonom>::THeadList()
{
	TMonom m;

	m.coeff = 0;

	m.x = m.y = 0, m.z = -1;
	pHead->value = m;
}

TPolinom::TPolinom(TPolinom& other)
{
	TMonom m(0, 0, -1);
	pHead->value = m;
	for (other.Reset(); !other.IsEnd(); other.GoNext())
	{
		//Из существующего полинома текущий моном добавляется в конец в новый
		InsLast(other.GetCurr());
	}
}

void TPolinom::AddMonom(TMonom m)
{
	Reset();
	//Переход к следующему моному, пока степень m меньше текущего
	while (m < pCurr->value)
	{
		GoNext();
	}
	//Обработка результатов
	//1. Мономы равны с точностью до коэф-та
	if (pCurr->value == m)
	{
		pCurr->value.coeff += m.coeff;
		//1.1. После сложения двух мономов коэф-т 0 - удаляем текущее звено
		if (pCurr->value.coeff == 0)
		{
			DelCurr();
		}
	}
	//2. Мономы не равны - добавим текущий в наш список
	else
	{
		InsCurr(m);
	}
}

TPolinom& TPolinom::operator+(TPolinom& other)
{
	//TODO
	TPolinom res(other);


	//проход по this
	//добавление к res
	//возврат результата
}