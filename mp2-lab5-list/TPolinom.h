#pragma once
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

	//Равенство с точностью до постоянного множителя
	bool operator==(const TMonom& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool operator!=(const TMonom& other)
	{
		return (x != other.x || y != other.y || z != other.z);
	}

	bool operator<(const TMonom& other)
	{
		if (x < other.x) return true;
		else if (x == other.x)
		{
			if (y < other.y) return true;
			else if (y == other.y)
			{
				return z < other.z;
			}
			else return false;
		}
		else return false;
	}

	bool operator>(const TMonom& other)
	{
		return !operator<(other) && !operator==(other);
	}

	bool IsConst()
	{
		return x == 0 && y == 0 && z == 0;
	}

	friend std::istream& operator>>(std::istream& is, TMonom& m)
	{
		is >> m.coeff >> m.x >> m.y >> m.z;
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, TMonom& monom)
	{
		if (monom.x != 0)
		{
			os << "x";
			if (monom.x != 1)
				os << monom.x;
		}
		if (monom.y != 0)
		{
			os << "y";
			if (monom.y != 1)
				os << monom.y;
		}
		if (monom.z != 0)
		{
			os << "z";
			if (monom.z != 1)
				os << monom.z;
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
	TPolinom operator-(TPolinom& other);
	TPolinom operator*(float a);

	void print(std::ostream& os);

	friend std::ostream& operator<<(
		std::ostream& os,
		TPolinom& p)
	{
		p.print(os);
		return os;
	}
};

TPolinom::TPolinom() :THeadList::THeadList()
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
		//Из существующего полинома текущий моном добавляется в конец нового
		InsLast(other.GetCurr());
	}
}

TPolinom& TPolinom::operator=(TPolinom& other)
{
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

	//Заполним наш полином мономами из other
	other.Reset();
	while (!other.IsEnd())
	{
		InsLast(other.GetCurr());
		other.GoNext();
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

TPolinom TPolinom::operator+(TPolinom& other)
{
	TPolinom result(other);
	Reset(); result.Reset();

	while (!IsEnd())
	{
		std::cout << "result = " << result << '\n';

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

TPolinom TPolinom::operator-(TPolinom& other)
{
	return operator+(other.operator*(-1));
}

TPolinom TPolinom::operator*(float a)
{
	TPolinom result;

	if (a == 0) return result;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		m.coeff *= a;

		result.InsLast(m);
	}
	return result;
}

void TPolinom::print(std::ostream& os)
{
	TNode<TMonom>* _pCurr = pFirst;

	//Нулевой полином
	if (_pCurr == pStop)
	{
		os << "0";
		return;
	}

	//Вывод для первого монома полинома
	TMonom m = _pCurr->value;
	float absCoeff = fabs(m.coeff);

	if (m.coeff < 0) os << "- ";

	//Моном был константный
	if (m.IsConst())
	{
		os << absCoeff;
	}
	//Не константный
	else
	{
		if (absCoeff != 1) os << absCoeff << "*";
		os << m;
	}

	_pCurr = _pCurr->pNext;

	for (; _pCurr != pStop; _pCurr = _pCurr->pNext)
	{
		TMonom m = _pCurr->value;
		float absCoeff = fabs(m.coeff);

		if (m.coeff < 0) os << " - ";
		else os << " + ";

		if (m.IsConst())
		{
			os << absCoeff;
		}
		else
		{
			if (absCoeff != 1)
				os << absCoeff << "*";
			os << m;
		}
	}
}


/*
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
*/