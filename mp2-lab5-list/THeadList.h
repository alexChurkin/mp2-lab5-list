#pragma once
#include <iostream>
#include "TList.h"

/* .................... THeadList .................... */

template <class T>
class THeadList: public TList<T>
{
protected:
	TNode<T>* pHead;
public:
	THeadList();
	~THeadList();
	void InsFirst(T element);
	void DelFirst();
};

template<class T>
THeadList<T>::THeadList()
{
	pHead = new TNode<T>;
	pHead->pNext = pHead;
	pFirst = pLast = pPrev = pCurr = pStop = pHead;
	length = 0;
}

//����� ���� ������ ������ ����������� ���������� - ����� DelFirst
template<class T>
THeadList<T>::~THeadList()
{
	/*while (pFirst != pStop)
	{
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}*/
	//����� ����������� �������� ������
	TList::~TList();
	delete pHead;
}

template <class T>
void THeadList<T>::InsFirst(T element)
{
	//����� ������ ������������� ������
	TList::InsFirst(element);
	pHead->pNext = pFirst;
}

template <class T>
void THeadList<T>::DelFirst()
{
	//����� ������ ������������� ������
	TList::DelFirst();
	pHead->pNext = pFirst;
}