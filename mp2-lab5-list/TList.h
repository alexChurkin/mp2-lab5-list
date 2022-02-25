#pragma once
#include <iostream>

/* TListException - ����� ���������� ��� TList */

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
	//��� ���������� ��-�� � �������� ������ � ��������: [] -> [pPrev] -> [pCurr] -> []
	TNode<T>* pPrev;
	TNode<T>* pCurr;
	//pStop ����� ����� ��������� �� ������, ����� �� �����
	//������� ��� �������� �� ���. ������ � ����������
	TNode<T>* pStop;
	//����� ������
	int length;

public:
	TList();
	~TList();

	bool IsEmpty();

	//���������� �������� � ������ ������
	void InsFirst(T element);
	//���������� �������� � ����� ������
	void InsLast(T element);
	//���������� �������� � ������� ������� (����� �������) (������� ���������� �����������)
	void InsCurr(T element);

	//�������� ������� �������� ������
	void DelFirst();
	//�������� �������� �������� ������ (������� ���������� ��������� �� ���)
	void DelCurr();

	//��������� �������� �������� ������
	T GetCurr();

	//������� ��������� � �������� ���������
	void Reset();
	//������� ��������� �����
	void GoNext();
	//�������� �� ���������� ���������� ����� ������
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
void TList<T>::Reset()
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