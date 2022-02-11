#pragma once
#include <iostream>

template <class T>
struct TNode
{
	T value;
	T* pNext;
};

template <class T>
class TList
{
protected:
	TNode<T>* pFirst;
	TNode<T>* pLast;
	//Для добавления эл-та в середину списка и удаления: [pPrev] -> [pCurr] -> []
	TNode<T>* pPrev;
	TNode<T>* pCurr;
	//pStop будет равен указателю на голову, чтобы не иметь
	//проблем при переходе от лин. списка к кольцевому
	TNode<T>* pStop;
	//Длина списка
	int length;

public:
	TList()
	{
		pStop = nullptr;
		pFirst = pLast = pPrev = pCurr = pStop;
		length = 0;
	}

	~TList()
	{
		while (pFirst != pStop)
		{
			TNode<T>* tmp = pFirst;
			pFirst = pFirst->pNext;
			delete tmp;
		}
		pLast = pPrev = pCurr = pStop;
		length = 0;
	}

	bool IsEmpty()
	{
		return pFirst == pStop;
	}

	//Добавление элемента в начало списка
	template <class T>
	void InsFirst(T element)
	{
		TNode<T>* newNode = new TNode<T>();
		newNode->value = element;
		newNode->pNext = pFirst;
		pFirst = newNode;
		length++;
		if (length == 1)
			pLast = pFirst;
	}

	//Добавление элемента в конец списка
	template <class T>
	void InsLast(T element)
	{
		if (length > 0)
		{
			TNode<T>* newNode = new TNode<T>();
			newNode->value = element;
			newNode->pNext = pStop;

			pLast->pNext = newNode;
			pLast = newNode;
			length++;
		}
		else
		{
			InsFirst(element);
		}
	}

	//Добавление элемента в текущую позицию (перед текущим) (текущим становится добавленный)
	template <class T>
	void InsCurr(T element)
	{
		if (pCurr == pFirst)
			InsFirst(element);
		else if (pPrev = pLast)
			InsLast(element);
		else
		{
			TNode<T>* newNode = new TNode<T>();
			newNode->value = element;

			newNode->pNext = pCurr;
			pPrev->pNext = newNode;
			pCurr = newNode;
			length++;
		}
	}

	//Удаление первого элемента списка
	template <class T>
	void DelFirst()
	{
		if (length == 0) throw "Can't delete from an empty list";

		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;

		length--;

		if (length == 0)
			pLast = pPrev = pCurr = pStop;
	}

	//Удаление текущего элемента списка (текущим становится следующий за ним)
	template <class T>
	void DelCurr()
	{
		if (length == 0) throw "Can't delete from an empty list";

		/* !!! Не факт, что это работает */
		if (pCurr == pFirst)
		{
			DelFirst();
			pCurr = pFirst;
		}
		else
		{
			pPrev->pNext = pCurr->pNext;
			delete pCurr;
			pCurr = pPrev->pNext;
			length--;
		}
	}
};

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

	bool operator==(const TMonom& other)
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool operator!=(const TMonom& other) {
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