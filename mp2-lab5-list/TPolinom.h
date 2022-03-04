#pragma once
#include<iostream>
#include<cmath>
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

	TMonom(int _coeff, int _x, int _y, int _z)
	{
		coeff = _coeff;
		x = _x;
		y = _y;
		z = _z;
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
		if (monom.x > 0)
		{
			os << "x";
			if (monom.x != 1) os << monom.x;
		}
		if (monom.y > 0)
		{
			os << "y";
			if (monom.y != 1) os << monom.y;
		}
		if (monom.z > 0)
		{
			os << "z";
			if (monom.z != 1) os << monom.z;
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
	TPolinom& operator=(TPolinom& other);

	void AddMonom(TMonom m);

	TPolinom operator+(TPolinom& other);
	TPolinom badOperatorPlus(TPolinom& other);

	TPolinom operator*(float a);

	friend std::ostream& operator<<(std::ostream& os, TPolinom& p)
	{
		p.Reset();
		if (p.IsEnd()) return os;

		//Вывод первого элемента
		TMonom m = p.GetCurr();
		if (m.coeff < 0) os << "- ";
		if(fabs(m.coeff) != 1)
			os << m.coeff;

		if ((m.x != 0 || m.y != 0 || m.z != 0) && fabs(m.coeff) != 1)
			os << "*";
		os << m;
		p.GoNext();

		if (p.IsEnd() && fabs(m.coeff) == 1) os << m.coeff;

		for (; !p.IsEnd(); p.GoNext())
		{
			TMonom m = p.GetCurr();
			if (m.coeff < 0) os << " - ";
			else os << " + ";
			if(fabs(m.coeff) != 1)
				os << fabs(m.coeff);

			if ((m.x != 0 || m.y != 0 || m.z != 0) && fabs(m.coeff) != 1)
				os << "*";
			os << m;
		}
		return os;
	}
};

TPolinom::TPolinom() :THeadList<TMonom>::THeadList()
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

TPolinom& TPolinom::operator=(TPolinom& other)
{
	//TODO оператор присваивания (на след. занятии напишем)

	//Моя версия:
	//Удаляем все звенья (кроме pHead)
	while (pFirst != pStop)
	{
		TNode<TMonom>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
	//Ставим все значения указателей обратно на pHead
	pFirst = pLast = pPrev = pCurr = pStop = pHead;
	length = 0;

	for (other.Reset(); !other.IsEnd(); other.GoNext())
	{
		AddMonom(other.GetCurr());
	}
	return *this;
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

TPolinom TPolinom::badOperatorPlus(TPolinom& other)
{
	TPolinom result(other);

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		result.AddMonom(m);
	}
	return result;
}

TPolinom TPolinom::operator+(TPolinom& other)
{
	TPolinom result(other);

	Reset(); result.Reset();

	while (!IsEnd())
	{
		if (result.pCurr->value > pCurr->value)
		{
			result.GoNext();
		}
		else if (result.pCurr->value < pCurr->value)
		{
			result.InsCurr(pCurr->value);
			GoNext();
		}
		else
		{
			result.pCurr->value.coeff += pCurr->value.coeff;
			if (result.pCurr->value.coeff == 0)
			{
				result.DelCurr();
				GoNext();
			}
			else
			{
				result.GoNext();
				GoNext();
			}
		}
	}
	return result;
}

TPolinom TPolinom::operator*(float a)
{
	TPolinom result;

	result.Reset();
	
	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		m.coeff *= a;

		result.AddMonom(m);

		//result.InsCurr(m);
		//result.GoNext();
	}
	return result;
}