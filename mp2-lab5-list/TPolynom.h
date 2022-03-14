#pragma once
#include<cmath>
#include<sstream>
#include "THeadList.h"
using namespace std;

/* ..................... TMonom ..................... */

struct TMonom
{
	//Коэффициент
	double coeff;

	//Степени при x, y и z
	int x, y, z;

	TMonom();
	TMonom(double _coeff, int _x, int _y, int _z);
	TMonom(int _x, int _y, int _z);

	//Сравнения с точностью до постоянного множителя
	bool operator==(const TMonom& other) const;
	bool operator!=(const TMonom& other) const;
	bool operator<(const TMonom& other) const;
	bool operator>(const TMonom& other) const;

	//IsConst() <-> степени при x, y и z равны 0
	bool IsConst() const;

	TMonom operator*(const TMonom& other);

	//Выводит текущий моном без коэффициента и знака
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

TMonom::TMonom()
{
	coeff = 0;
	x = y = z = 0;
}

TMonom::TMonom(
	double _coeff, int _x, int _y, int _z)
{
	coeff = _coeff;
	x = _x;
	y = _y;
	z = _z;
}

TMonom::TMonom(int _x, int _y, int _z)
{
	coeff = 0;
	x = _x;
	y = _y;
	z = _z;
}

bool TMonom::operator==(const TMonom& other) const
{
	return (x == other.x && y == other.y && z == other.z);
}

bool TMonom::operator!=(const TMonom& other) const
{
	return (x != other.x || y != other.y || z != other.z);
}

bool TMonom::operator<(const TMonom& other) const
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

bool TMonom::operator>(const TMonom& other) const
{
	return !operator<(other) && !operator==(other);
}

bool TMonom::IsConst() const
{
	return x == 0 && y == 0 && z == 0;
}

TMonom TMonom::operator*(const TMonom& other)
{
	TMonom result;
	result.coeff = coeff * other.coeff;
	result.x = x + other.x;
	result.y = y + other.y;
	result.z = z + other.z;
	return result;
}

/* .................... TPolynom .................... */

class TPolynom : public THeadList<TMonom>
{
protected:
	void Print(std::ostream& os) const;

public:
	TPolynom();

	//const TPolynom& не пишем, иначе Reset и GetNext
	//не будут работать
	TPolynom(TPolynom& other);
	TPolynom(const std::string& polyStr);
	TPolynom& operator=(TPolynom& other);

	void AddMonom(TMonom m);
	void AddMonom(double coeff, int x, int y, int z);

	bool operator==(const TPolynom& other) const;
	bool operator!=(const TPolynom& other) const;

	TPolynom operator+(TPolynom& other);
	TPolynom operator-(TPolynom& other);
	TPolynom operator*(TPolynom& other);
	TPolynom operator*(TMonom& monom);
	TPolynom operator*(double a);

	friend std::ostream& operator<<(
		std::ostream& os,
		TPolynom& p)
	{
		p.Print(os);
		return os;
	}

	friend TPolynom operator*(
		TMonom& m,
		TPolynom& p)
	{
		return p * m;
	}

	friend TPolynom operator*(
		double a,
		TPolynom& p)
	{
		return p * a;
	}
};

void TPolynom::Print(std::ostream& os) const
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
	double absCoeff = fabs(m.coeff);

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
		double absCoeff = fabs(m.coeff);

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

TPolynom::TPolynom() :THeadList::THeadList()
{
	TMonom m;
	m.coeff = 0;
	m.x = m.y = 0, m.z = -1;

	pHead->value = m;
}

TPolynom::TPolynom(TPolynom& other)
{
	TMonom m(0, 0, -1);
	pHead->value = m;
	for (other.Reset(); !other.IsEnd(); other.GoNext())
		InsLast(other.GetCurr());
}

//Считаем, что строка уже trim слева и справа
TPolynom::TPolynom(
	const std::string& polyStr): TPolynom()
{
	//Последний встреченный знак коэффициента
	char lastsgn = '+';

	//Временный моном для записи данных
	TMonom tm(1, 0, 0, 0);

	int i = 0;
	for (; i < polyStr.size(); i++)
	{
		if (isdigit(polyStr[i]))
		{
			size_t idx;
			double digit = stod(&polyStr[i], &idx);
			ostringstream ss;
			ss << digit;

			tm.coeff = digit;
			if (lastsgn == '-') tm.coeff *= (-1);

			i += idx - 1;
		}
		else if (polyStr[i] == 'x')
		{
			//Это конец строки (степень 1)
			if (i + 1 == polyStr.size())
			{
				tm.x = 1;
			}
			//Моном имеет явную степень (не 1)
			else if (isdigit(polyStr[i + 1]))
			{
				size_t idx;
				double digit = stod(&polyStr[i + 1], &idx);
				ostringstream ss;
				ss << digit;

				tm.x = digit;
				i += idx - 1;
			}
			//Моном имеет степень 1
			else
			{
				tm.x = 1;
			}
		}
		else if (polyStr[i] == 'y')
		{
			//Это конец строки (степень 1)
			if (i + 1 == polyStr.size())
			{
				tm.y = 1;
			}
			//Моном имеет явную степень (не 1)
			else if (isdigit(polyStr[i + 1]))
			{
				size_t idx;
				double digit = stod(&polyStr[i + 1], &idx);
				ostringstream ss;
				ss << digit;

				tm.y = digit;
				i += idx - 1;
			}
			//Моном имеет степень 1
			else
			{
				tm.y = 1;
			}
		}
		else if (polyStr[i] == 'z')
		{
			//Это конец строки (степень 1)
			if (i + 1 == polyStr.size())
			{
				tm.z = 1;
			}
			//Моном имеет явную степень (не 1)
			else if (isdigit(polyStr[i + 1]))
			{
				size_t idx;
				double digit = stod(&polyStr[i + 1], &idx);
				ostringstream ss;
				ss << digit;

				tm.z = digit;
				i += idx - 1;
			}
			//Моном имеет степень 1
			else
			{
				tm.z = 1;
			}
		}
		//Переход к считыванию следующего монома
		if (polyStr[i] == '+' || polyStr[i] == '-')
		{
			InsLast(tm);
			tm.coeff = 1;
			tm.x = tm.y = tm.z = 0;
			lastsgn = polyStr[i];
		}
	}
	//Дозапись последнего монома
	InsLast(tm);
}

TPolynom& TPolynom::operator=(TPolynom& other)
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

	//Заполним полином мономами из other
	other.Reset();
	while (!other.IsEnd())
	{
		InsLast(other.GetCurr());
		other.GoNext();
	}
	return *this;
}

void TPolynom::AddMonom(TMonom m)
{
	if (m.coeff == 0) return;

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

void TPolynom::AddMonom(double coeff, int x, int y, int z)
{
	AddMonom(TMonom(coeff, x, y, z));
}

bool TPolynom::operator==(const TPolynom& other) const
{
	return ToStr() == other.ToStr();
}

bool TPolynom::operator!=(const TPolynom& other) const
{
	return ToStr() != other.ToStr();
}

TPolynom TPolynom::operator+(TPolynom& other)
{
	TPolynom result(other);
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

TPolynom TPolynom::operator-(TPolynom& other)
{
	return operator+(other.operator*(-1));
}

TPolynom TPolynom::operator*(TPolynom& other)
{
	TPolynom result;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		TPolynom temp = m * other;
		result = result + temp;
	}

	return result;
}

TPolynom TPolynom::operator*(TMonom& monom)
{
	TPolynom result;

	if (monom.coeff == 0) return result;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		result.InsLast(m * monom);
	}

	return result;
}

TPolynom TPolynom::operator*(double a)
{
	TPolynom result;

	if (a == 0) return result;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		m.coeff *= a;

		result.InsLast(m);
	}
	return result;
}

/*
//Менее эффективная версия operator+
TPolynom TPolynom::operator+(TPolynom& other)
{
	TPolynom result(other);

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		result.AddMonom(m);
	}
	return result;
}
*/