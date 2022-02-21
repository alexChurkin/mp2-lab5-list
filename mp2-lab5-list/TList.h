#pragma once
#include <iostream>

/* TListException - класс исключения для TList */

class TLException
{
private:
	std::string desc;

public:
	TLException(std::string _desc)
	{
		desc = _desc;
	}
	TLException(const TLException& e)
	{
		desc = e.desc;
	}

	friend std::ostream& operator<<(std::ostream& os, const TLException& e)
	{
		os << "Exception message: " << e.desc << '\n';
		return os;
	}
};

/* ...................... TNode ...................... */

template <class T>
struct TNode
{
	T value;
	TNode<T>* pNext;
};

/* ...................... TList ...................... */

template <class T>
class TList
{
protected:
	TNode<T>* pFirst;
	TNode<T>* pLast;
	//Для добавления эл-та в середину списка и удаления: [] -> [pPrev] -> [pCurr] -> []
	TNode<T>* pPrev;
	TNode<T>* pCurr;
	//pStop будет равен указателю на голову, чтобы не иметь
	//проблем при переходе от лин. списка к кольцевому
	TNode<T>* pStop;
	//Длина списка
	int length;

public:
	TList();
	~TList();

	bool IsEmpty();

	//Добавление элемента в начало списка
	void InsFirst(T element);
	//Добавление элемента в конец списка
	void InsLast(T element);
	//Добавление элемента в текущую позицию (перед текущим) (текущим становится добавленный)
	void InsCurr(T element);

	//Удаление первого элемента списка
	void DelFirst();
	//Удаление текущего элемента списка (текущим становится следующий за ним)
	void DelCurr();

	//Получение текущего элемента списка
	T GetCurr();

	//Возврат итератора в исходное состояние
	void Revert();
	//Перевод итератора далее
	void GoNext();
	//Проверка на достижение итератором конца списка
	bool IsEnd();

	friend std::ostream& operator<<(
		std::ostream& out,
		const TList<T>& l)
	{
		out << "[ ";
		//TODO Later
		out << "]";
		return out;
	}
};

template <class T>
TList<T>::TList()
{
	pStop = nullptr;
	pFirst = pLast = pPrev = pCurr = pStop;
	length = 0;
}

template <class T>
TList<T>::~TList()
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

template <class T>
bool TList<T>::IsEmpty()
{
	return pFirst == pStop;
}

template <class T>
void TList<T>::InsFirst(T element)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = element;
	newNode->pNext = pFirst;
	pFirst = newNode;
	length++;
	if (length == 1)
		pLast = pFirst;
}

template <class T>
void TList<T>::InsLast(T element)
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

template <class T>
void TList<T>::InsCurr(T element)
{
	if (pCurr == pFirst)
		InsFirst(element);
	else if (pPrev == pLast)
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

template <class T>
void TList<T>::DelFirst()
{
	if (pFirst == pStop)
		throw TLException("Can't delete first element: it's a barrier");

	TNode<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	delete tmp;
	length--;
}

template <class T>
void TList<T>::DelCurr()
{
	if (pCurr == pStop)
		throw TLException("Can't delete current element: it's a barrier");

	if (pFirst == pCurr)
	{
		DelFirst();
	}
	else
	{
		TNode<T>* tmp = pCurr;
		pCurr = pCurr->pNext;
		pPrev->pNext = pCurr;
		delete tmp;
		length--;
	}
}

template <class T>
T TList<T>::GetCurr()
{
	if (pCurr == pStop)
		throw TLException("Can't get current element: it's a barrier");
	return pCurr->value;
}

template <class T>
void TList<T>::Revert()
{
	pPrev = pStop;
	pCurr = pFirst;
}

template <class T>
void TList<T>::GoNext()
{
	pPrev = pCurr;
	pCurr = pCurr->pNext;
}

template <class T>
bool TList<T>::IsEnd()
{
	return pCurr == pStop;
}

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