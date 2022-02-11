#pragma once
#include <iostream>
#include <string>

/* TList2021Exception - класс исключения для TList2021 */

class TList2021Exception
{
private:
	std::string desc;

public:
	TList2021Exception(std::string _desc)
	{
		desc = _desc;
	}
	TList2021Exception(const TList2021Exception& e)
	{
		desc = e.desc;
	}

	friend std::ostream& operator<<(std::ostream& os, const TList2021Exception& e)
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

/* TList2021 - односвязный список */

template <class T>
class TList2021
{
private:
	TNode<T>* pFirst;
	TNode<T>* pLast;

	int size = 0;

public:
	TList2021();
	TList2021(const TList2021<T>& other);
	~TList2021();

	TList2021<T>& operator=(const TList2021<T>& other);

	bool IsEmpty() const;
	bool IsNotEmpty() const;

	bool operator==(const TList2021<T>& other) const;
	bool operator!=(const TList2021<T>& other) const;

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
		const TList2021<T>& l)
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
	void CopyNodesFrom(const TList2021<T>& other);
};

template <class T>
TList2021<T>::TList2021() : pFirst(nullptr), pLast(nullptr) {}

template <class T>
TList2021<T>::TList2021(const TList2021<T>& other)
{
	pFirst = nullptr;
	pLast = nullptr;
	CopyNodesFrom(other);
	size = other.size;
}

template <class T>
TList2021<T>::~TList2021()
{
	Clear();
}

template <class T>
TList2021<T>& TList2021<T>::operator=(const TList2021<T>& other)
{
	if (this == &other)
		return *this;

	Clear();
	CopyNodesFrom(other);
	size = other.size;
}

template <class T>
bool TList2021<T>::IsEmpty() const
{
	return pFirst == nullptr;
}

template <class T>
bool TList2021<T>::IsNotEmpty() const
{
	return pFirst != nullptr;
}

template <class T>
bool TList2021<T>::operator==(const TList2021<T>& other) const
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
bool TList2021<T>::operator!=(const TList2021<T>& other) const
{
	return !operator==(other);
}

template <class T>
void TList2021<T>::PushFront(T element)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = element;
	newNode->pNext = pFirst;
	pFirst = newNode;

	size++;
}

template <class T>
void TList2021<T>::PushBack(T element)
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
T TList2021<T>::PopFront()
{
	if (IsEmpty())
		throw TList2021Exception(
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
T TList2021<T>::PopBack()
{
	if (IsEmpty())
		throw TList2021Exception(
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
T& TList2021<T>::Get(int index)
{
	if (index < 0 || index >= size)
		throw TList2021Exception("Index out of bounds (list size is "
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
T& TList2021<T>::operator[](int index)
{
	return Get(index);
}

template <class T>
T TList2021<T>::GetFirst() const
{
	if(IsEmpty())
		throw TList2021Exception(
			"Can't get first element of an empty list");
	return pFirst->value;
}

template <class T>
T TList2021<T>::GetLast() const
{
	if (IsEmpty())
		throw TList2021Exception(
		"Can't get last element of an empty list");
	return pLast->value;
}

template <class T>
void TList2021<T>::Clear()
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
void TList2021<T>::CopyNodesFrom(
	const TList2021<T>& other
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