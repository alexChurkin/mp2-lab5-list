#pragma once
#include <iostream>
#include <string>

/* TListException - класс исключения для TList */

class TListException
{
private:
	std::string desc;

public:
	TListException(std::string _desc)
	{
		desc = _desc;
	}
	TListException(const TListException& e)
	{
		desc = e.desc;
	}

	friend std::ostream& operator<<(std::ostream& os, const TListException& e)
	{
		os << "Exception message: " << e.desc << '\n';
		return os;
	}
};

/* TNode - звено списка */

template <class T>
struct TNode
{
	T value;
	TNode* pNext;
};

/* TList - односвязный список */

template <class T>
class TList
{
private:
	TNode<T>* pFirst;
	TNode<T>* pLast;

	int size = 0;

public:
	TList();
	TList(const TList<T>& other);
	~TList();

	TList<T>& operator=(const TList<T>& other);

	bool IsEmpty() const;
	bool IsNotEmpty() const;

	bool operator==(const TList<T>& other) const;
	bool operator!=(const TList<T>& other) const;

	void PushFront(T element);
	void PushBack(T element);

	T PopFront();
	T PopBack();
	T& Get(int index);
	T& operator[](int index);

	T GetFirst() const;
	T GetLast() const;

	void Clear();

	friend std::ostream& operator<<(
		std::ostream& out,
		const TList<T>& l)
	{
		TNode<T>* node = l.pFirst;

		out << "[ ";
		while (node != nullptr)
		{
			out << node->value << ' ';
			node = node->pNext;
		}
		out << "]";

		return out;
	}

private:
	void CopyNodesFrom(const TList<T>& other);
};

template <class T>
TList<T>::TList() : pFirst(nullptr), pLast(nullptr) {}

template <class T>
TList<T>::TList(const TList<T>& other)
{
	pFirst = nullptr;
	pLast = nullptr;
	CopyNodesFrom(other);
	size = other.size;
}

template <class T>
TList<T>::~TList()
{
	Clear();
}

template <class T>
TList<T>& TList<T>::operator=(const TList<T>& other)
{
	if (this == &other)
		return *this;

	Clear();
	CopyNodesFrom(other);
	size = other.size;
}

template <class T>
bool TList<T>::IsEmpty() const
{
	return pFirst == nullptr;
}

template <class T>
bool TList<T>::IsNotEmpty() const
{
	return pFirst != nullptr;
}

template <class T>
bool TList<T>::operator==(const TList<T>& other) const
{
	TNode<T>* node = pFirst;
	TNode<T>* nodeOther = other.pFirst;

	//Сравнение элементов звеньев
	while (node != nullptr && nodeOther != nullptr)
	{
		if (node->value != nodeOther->value) return false;
		node = node->pNext;
		nodeOther = nodeOther->pNext;
	}

	//Если в списках различно число элементов -
	//они не равны
	if (node != nullptr || nodeOther != nullptr)
		return false;

	return true;
}

template <class T>
bool TList<T>::operator!=(const TList<T>& other) const
{
	return !operator==(other);
}

template <class T>
void TList<T>::PushFront(T element)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = element;
	newNode->pNext = pFirst;
	pFirst = newNode;

	size++;
}

template <class T>
void TList<T>::PushBack(T element)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = element;
	newNode->pNext = nullptr;

	if (pLast != nullptr)
		pLast->pNext = newNode;
	else
		pFirst = newNode;
	pLast = newNode;

	size++;
}

template <class T>
T TList<T>::PopFront()
{
	if (IsEmpty())
		throw TListException(
			"Can't pop front from an empty list");

	T value = pFirst->value;
	TNode<T>* oldFirst = pFirst;
	pFirst = oldFirst->pNext;
	delete oldFirst;

	if (pFirst == nullptr)
		pLast = nullptr;

	size--;
	return value;
}

template <class T>
T TList<T>::PopBack()
{
	if (IsEmpty())
		throw TListException(
			"Can't pop back from an empty list");

	TNode<T>* prevNode = pFirst;
	TNode<T>* node = pFirst;

	while (node->pNext != nullptr)
	{
		prevNode = node;
		node = node->pNext;
	}

	T value = node->value;

	if (prevNode == node)
	{
		delete pFirst;
		pFirst = nullptr;
		pLast = nullptr;
	}
	else
	{
		delete pLast;
		pLast = prevNode;
		pLast->pNext = nullptr;
	}

	size--;
	return value;
}

template <class T>
T& TList<T>::Get(int index)
{
	if (index < 0 || index >= size)
		throw TListException("Index out of bounds (list size is "
			+ std::to_string(size) + ")");

	int i = 0;
	TNode<T>* node = pFirst;
	while (node != nullptr)
	{
		if (i == index)
			return node->value;

		node = node->pNext;
		i++;
	}
}

template <class T>
T& TList<T>::operator[](int index)
{
	return Get(index);
}

template <class T>
T TList<T>::GetFirst() const
{
	if(IsEmpty())
		throw TListException(
			"Can't get first element of an empty list");
	return pFirst->value;
}

template <class T>
T TList<T>::GetLast() const
{
	if (IsEmpty())
		throw TListException(
		"Can't get last element of an empty list");
	return pLast->value;
}

template <class T>
void TList<T>::Clear()
{
	TNode<T>* node;
	while (pFirst != nullptr)
	{
		node = pFirst;
		pFirst = pFirst->pNext;
		delete node;
	}
	pLast = nullptr;
}

/* Последовательное копирование звеньев,
   начиная с 1-го */
template <class T>
void TList<T>::CopyNodesFrom(
	const TList<T>& other
)
{
	if (other.IsNotEmpty())
	{
		TNode<T>* newNode;
		//Копирование первого звена
		newNode = new TNode<T>;
		newNode->value = other.pFirst->value;
		newNode->pNext = nullptr;
		pFirst = newNode;

		//Копирование остальных звеньев:

		//Предыдущее звено текущего списка
		TNode<T>* prevNewNode = newNode;

		//Звено "другого" списка
		TNode<T>* otherNode = other.pFirst->pNext;

		while (otherNode != nullptr)
		{
			newNode = new TNode<T>;
			newNode->value = otherNode->value;
			newNode->pNext = nullptr;

			prevNewNode->pNext = newNode;

			prevNewNode = newNode;
			otherNode = otherNode->pNext;
		}
		pLast = prevNewNode;
	}
}