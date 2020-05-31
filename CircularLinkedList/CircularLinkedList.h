#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <class T>
class CircularLinkedList
{
private:
	node<T> * m_head, *m_tail;
	int m_itemCount;
public:
	CircularLinkedList();
	CircularLinkedList(const CircularLinkedList&);
	~CircularLinkedList();

	bool isEmpty() const;
	int getLength() const;

	bool Search(const T&) const;
	ostream& print(ostream&) const;

	T getFirst() const;
	T getLast() const;
	T get(int) const;

	void insertFirst(const T&);
	void insertLast(const T&);
	void insert(const T&, int);

	void removeFirst();
	void removeLast();
	void remove(int);
	void removeData(const T&);

	void clear();

	CircularLinkedList& operator=(const CircularLinkedList&);

public:
	T Josephus(long long n, long long k);
};

template <class T>
CircularLinkedList<T>::CircularLinkedList()
{
	m_head = m_tail = NULL;
	m_itemCount = 0;
}

template <class T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList& src)
{
	m_head = m_tail = NULL;
	m_itemCount = 0;

	if (src.m_head == NULL) return;
	node<T>* p = src.m_head;
	do
	{
		this->insertLast(p->getData());
		p = p->getNext();
	} while (p != src.m_head);
}

template <class T>
CircularLinkedList<T>::~CircularLinkedList()
{
	clear();
}

template <class T>
bool CircularLinkedList<T>::isEmpty() const
{
	return m_itemCount == 0;
}

template <class T>
int CircularLinkedList<T>::getLength() const
{
	return m_itemCount;
}

template <class T>
bool CircularLinkedList<T>::Search(const T& key) const
{
	if (m_head == NULL) return 0;

	node<T>* p = m_head;
	do
	{
		if (p->getData() == key) return 1;
		p = p->getNext();
	} while (p != m_head);
		
	return 0;
}

template <class T>
ostream& CircularLinkedList<T>::print(ostream& out) const
{
	if (m_head == NULL) return out;

	node<T>* p = m_head;
	do
	{
		out << p->getData() << " ";
		p = p->getNext();
	} while (p != m_head);
	return out;
}

template <class T>
T CircularLinkedList<T>::getFirst() const
{
	if (m_head == NULL) throw (char *) "Truy xuat danh sach rong!\n";
	return m_head->getData();
}
template <class T>
T CircularLinkedList<T>::getLast() const
{
	if (m_head == NULL) throw (char *) "Truy xuat danh sach rong!\n";
	return m_tail->getData();
}
template <class T>
T CircularLinkedList<T>::get(int pos) const
{
	if (m_head == NULL) throw (char *) "Truy xuat danh sach rong!\n";
	if (pos < 0) throw (char *) "Truy xuat ngoai vung du lieu!\n";
	pos %= m_itemCount;
	node<T>*p = m_head;

	for (int i = 0; i < pos; i++)
	{
		p = p->getNext();
	}

	return p->getData();
}

template <class T>
void CircularLinkedList<T>::insertFirst(const T& key)
{
	node<T>* p = new node<T>(key, m_head);
	m_itemCount++;
	if (m_head == NULL)
	{
		m_tail = m_head = p;
		m_head->setNext(m_head);
	}
	else
	{
		m_head = p;
		m_tail->setNext(m_head);
	}
}
template <class T>
void CircularLinkedList<T>::insertLast(const T& key)
{
	node<T>* p = new node<T>(key, m_head);
	m_itemCount++;

	if (m_head == NULL)
	{
		m_tail = m_head = p;
		m_head->setNext(m_head);
	}
	else
	{
		m_tail->setNext(p);
		m_tail = p;
	}
}
template <class T>
void CircularLinkedList<T>::insert(const T& key, int pos)
{
	pos %= m_itemCount + 1;
	if (pos == 0) insertFirst(key);
	else
		if (pos == m_itemCount) insertLast(key);
		else
		{
			node<T>* p = new node<T>(key), *pnext = m_head, *pprev = m_head;

			for (int i = 0; i < pos; i++)
			{
				pprev = pnext;
				pnext = pnext->getNext();
			}

			pprev->setNext(p);
			p->setNext(pnext);

			m_itemCount++;
		}
}

template <class T>
void CircularLinkedList<T>::removeFirst()
{
	if (m_head == NULL) throw (char *) "Remove danh sach rong!\n";

	node<T>* p = m_head;
	if (m_itemCount == 1)
	{
		m_head = m_tail = NULL;
	}
	else
	{
		m_head = m_head->getNext();
		m_tail->setNext(m_head);
	}
	delete p;
	m_itemCount--;
}
template <class T>
void CircularLinkedList<T>::removeLast()
{
	if (m_itemCount <= 1) removeFirst();
	else
	{
		node<T>* p = m_head;
		for (int i = 0; i < m_itemCount - 2; i++)
		{
			p = p->getNext();
		}

		p->setNext(m_head);
		delete m_tail;
		m_tail = p;
		m_itemCount--;
	}
}
template <class T>
void CircularLinkedList<T>::remove(int pos)
{
	if (pos < 0) throw (char *) "Remove ngoai vung nho!\n";
	
	pos %= m_itemCount;
	if (pos == 0) removeFirst();
	else
		if (pos == m_itemCount - 1) removeLast();
		else
		{
			node<T>* p, *pnext, *pprev;
			p = pnext = pprev = m_head;
			for (int i = 0; i < pos; i++)
			{
				pprev = pnext;
				pnext = pnext->getNext();
			}
			p = pnext;
			pnext = pnext->getNext();

			pprev->getNext(pnext);
			delete p;
			m_itemCount--;
		}
}
template <class T>
void CircularLinkedList<T>::removeData(const T& key)
{
	if (m_itemCount == 0) throw (char *) "Remove danh sach rong!\n";
	
	if (key == m_head->getData()) removeFirst();
	else if (key == m_tail->getData()) removeLast();
	else
	{
		node<T>* p = m_head, *pprev;
		do
		{
			pprev = p;
			p = p->getNext();
			if (key == p->getData()) break;
		} while (p != m_head);
		
		if (p != m_head)
		{
			pprev->setNext(p->getNext());
			delete p;
			m_itemCount--;
		}
	}
}

template <class T>
void CircularLinkedList<T>::clear()
{
	while (!isEmpty())
	{
		removeFirst();
	}
}

template <class T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList& src)
{
	if (this != *src)
	{
		this->~CircularLinkedList();

		if (src.m_head == NULL) return;
		node<T>* p = src.m_head;
		do
		{
			this->insertLast(p->getData());
			p = p->getNext();
		} while (p != src.m_head);
	}
	return *this;
}

template <class T>
T CircularLinkedList<T>::Josephus(long long n, long long k)
{
	this->~CircularLinkedList();

	if (n <= 0) return -1;

	long long i;
	for (i = 1; i <= n; i++)
		insertLast(i);
	
	node<T>* p = m_head, *pprev;

	while (m_itemCount > 1)
	{
		for (i = 0; i < k - 1; i++)
			p = p->getNext();
		pprev = p;
		p = p->getNext();
		removeData(pprev->getData());
	}

	return m_head->getData();
}