#pragma once
#include "SinglyLinkedList.h"

template <class T>
class PriorityQueue
{
private:
	SinglyLinkedList<T> pQueue;
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue&);
	~PriorityQueue();

	PriorityQueue& operator=(const PriorityQueue&);

	bool isEmpty() const;
	void enQueue(const T&);
	void deQueue();
	T front() const;
};


template <class T>
PriorityQueue<T>::PriorityQueue()
{}
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& src) : pQueue(src.pQueue) {}
template <class T>
PriorityQueue<T>::~PriorityQueue() {}
template <class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& src)
{
	if (this != &src)
	{
		this->~PriorityQueue();
		pQueue = src.pQueue;
	}
	return *this;
}


template <class T>
bool PriorityQueue<T>::isEmpty() const
{
	return pQueue.isEmpty();
}
template <class T>
void PriorityQueue<T>::enQueue(const T& data)
{
	if (isEmpty())
	{
		pQueue.insertLast(data);
	}
	else
	{
		PriorityQueue<T> temp(*this);
		this->~PriorityQueue();
		T i;
		bool added = false;
		while (!temp.isEmpty())
		{
			i = temp.front();
			temp.pQueue.removeFirst();

			if (i <= data)
			{
				pQueue.insertLast(i);
			}
			else
			{
				pQueue.insertLast(data);
				pQueue.insertLast(i);
				added = true;
				break;
			}
		}

		if(added == false)
			pQueue.insertLast(data);
		else
		{
			while (!temp.isEmpty())
			{
				pQueue.insertLast(temp.front());
				temp.pQueue.removeFirst();
			}
		}
	}
}
template <class T>
void PriorityQueue<T>::deQueue()
{
	pQueue.removeFirst();
}
template <class T>
T PriorityQueue<T>::front() const
{
	return pQueue.getFirst();
}