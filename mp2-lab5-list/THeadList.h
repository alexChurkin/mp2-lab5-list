#pragma once
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
	cout << "THeadList constructor called!!!\n";
}

//Также есть другой способ реализовать деструктор - через DelFirst
template<class T>
THeadList<T>::~THeadList()
{
	/*while (pFirst != pStop)
	{
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}*/
	//Вызов деструктора базового класса
	TList::~TList();
	delete pHead;
}

template <class T>
void THeadList<T>::InsFirst(T element)
{
	//Вызов метода родительского класса
	TList::InsFirst(element);
	pHead->pNext = pFirst;
	cout << "THeadList InsFirst called!!!\n";
}

template <class T>
void THeadList<T>::DelFirst()
{
	//Вызов метода родительского класса
	TList<T>::DelFirst();
	cout << "DelFirst for THeadList called!!!";
	pHead->pNext = pFirst;
}