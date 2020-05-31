#pragma once
#include "Node.h"

template <class T>
class SinglyLinkedList
{
private:
	node<T>* m_head;
	node<T>* m_tail;
	int m_itemCount;
public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList &);
	~SinglyLinkedList();

	bool isEmpty() const;
	int getLength() const;
	bool search(const T&) const;
	ostream& print(ostream&) const;
	
	T getFirst() const;
	T getLast() const;
	T get(int) const;
	void addList(SinglyLinkedList<T> &list);

	void insertFirst(const T&);
	void insertLast(const T&);
	void insert(const T&, int);

	void removeFirst();
	void removeLast();
	void remove(int);
	
	void clear();

	SinglyLinkedList<T>& operator= (const SinglyLinkedList<T>&);
};

template <class T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	m_head = m_tail = NULL;
	m_itemCount = 0;
}
template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList & src)
{
	m_head = m_tail = NULL;
	m_itemCount = 0;
	for (node<T>* p = src.m_head; p; p = p->getNext())
	{
		insertLast(p->getData());
	}
}
template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	clear();
}

template <class T>
bool SinglyLinkedList<T>::isEmpty() const
{
	return (m_itemCount == 0);
}
template <class T>
int SinglyLinkedList<T>::getLength() const
{
	return m_itemCount;
}
template <class T>
bool SinglyLinkedList<T>::search(const T& key) const
{
	for (node<T>* p = m_head; p; p = p->getNext())
	{
		if (p->getData() == key)
			return 1;
	}
	return 0;
}
template <class T>
ostream& SinglyLinkedList<T>::print(ostream& out) const
{
	for (node<T>* p = m_head; p; p = p->getNext())
	{
		out << p->getData() << "  ";
	}
	out << endl;
	return out;
}

template <class T>
T SinglyLinkedList<T>::getFirst() const
{
	if (isEmpty()) throw (char *) "Truy xuat danh sach rong!\n";
	return m_head->getData();
}
template <class T>
T SinglyLinkedList<T>::getLast() const
{
	if (isEmpty()) throw (char *) "Truy xuat danh sach rong!\n";
	return m_tail->getData();
}
template <class T>
T SinglyLinkedList<T>::get(int pos) const
{
	if (pos < 0 || pos >= m_itemCount) throw (char *) "Truy xuat ngoai vung cho phep cua danh sach!\n";
	node<T>* p = m_head;
	int i = 0;
	for (; i < pos; i++, p = p->getNext());
	return  p->getData();
}
template <class T>
void SinglyLinkedList<T>::addList(SinglyLinkedList<T> &list)
{
	if (list.m_itemCount == 0) return;

	if (m_itemCount == 0)
	{
		m_itemCount = list.m_itemCount;
		m_head = list.m_head;
		m_tail = list.m_tail;
	}
	else
	{
		m_itemCount += list.m_itemCount;
		m_tail->setNext(list.m_head);
		m_tail = list.m_tail;
	}

	list.m_itemCount = 0;
	list.m_head = list.m_tail = NULL;
}

template <class T>
void SinglyLinkedList<T>::insertFirst(const T& src)
{
	m_itemCount++;
	node<T>* newp = new node<T>(src);

	if (m_itemCount - 1 == 0)
	{
		m_head = m_tail = newp;
		return;
	}

	newp->setNext(m_head);
	m_head = newp;
}
template <class T>
void SinglyLinkedList<T>::insertLast(const T& src)
{
	if (m_itemCount == 0) insertFirst(src);
	else
	{
		m_itemCount++;
		node<T>* newp = new node<T>(src);
		m_tail->setNext(newp);
		m_tail = newp;
	}
}
template <class T>
void SinglyLinkedList<T>::insert(const T& src, int pos)
{
	if (pos <= 0) insertFirst(src);
	else
		if (pos >= m_itemCount) insertLast(src);
		else
		{
			m_itemCount++;
			node<T>* newp = new node<T>(src);
			node<T>* p = m_head, *p2;
			for (int i = 0; i < pos - 1; p = p->getNext(), i++);
			p2 = p->getNext();
			p->setNext(newp);
			newp->setNext(p2);
		}
}

template <class T>
void SinglyLinkedList<T>::removeFirst()
{
	if (m_itemCount == 0) throw (char *) "Xoa danh sach rong!\n";
	else
	{
		m_itemCount--;
		node<T>* p = m_head;
		if (p == m_tail)
		{
			m_head = m_tail = NULL;
		}
		else m_head = m_head->getNext();
		delete p;
	}
}
template <class T>
void SinglyLinkedList<T>::removeLast()
{
	if (m_itemCount == 0) throw (char *) "Xoa danh sach rong!\n";
	else
	{
		if (m_itemCount == 1) removeFirst();
		else
		{
			m_itemCount--;
			node<T>* p = m_head;
			for (; p->getNext() != m_tail; p = p->getNext())
				delete m_tail;
			m_tail = p;
			m_tail->setNext(NULL);
		}	
	}
}
template <class T>
void SinglyLinkedList<T>::remove(int pos)
{
	if (pos < 0 || pos >= m_itemCount) throw (char *) "Xoa vung nho ngoai danh sach!\n";

	if (pos == 0) removeFirst();
	else if (pos == m_itemCount) removeLast();
	else
	{
		m_itemCount--;
		node<T>* p = m_head, *prev;
		for (int i = 0; i < pos; i++, p = p->getNext())
		{
			prev = p;
		}
		prev->setNext(p->getNext());
		delete p;
	}
}

template <class T>
void SinglyLinkedList<T>::clear()
{
	while (m_head != NULL)
	{
		removeFirst();
	}
}

template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator= (const SinglyLinkedList<T>& src)
{
	if (this != &src)
	{
		clear();

		for (node<T>* p = src.m_head; p; p = p->getNext())
		{
			insertLast(p->getData());
		}
	}
	return *this;
}