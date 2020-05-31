#pragma once
#include "SinglyLinkedList.h"

template <class T>
class Queue
{
private:
	SinglyLinkedList<T> queue;
public:
	Queue();
	Queue(const Queue&);
	~Queue();

	Queue& operator=(const Queue&);

	bool isEmpty() const;
	void enQueue(const T&);
	void deQueue();
	T front() const;
};

template <class T>
Queue<T>::Queue()
{}
template <class T>
Queue<T>::Queue(const Queue& src) : queue(src.queue){}
template <class T>
Queue<T>::~Queue(){}
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& src)
{
	if (this != &src)
	{
		this->~Queue();
		queue = src.queue;
	}
	return *this;
}


template <class T>
bool Queue<T>::isEmpty() const
{
	return queue.isEmpty();
}
template <class T>
void Queue<T>::enQueue(const T& data)
{
	queue.insertLast(data);
}
template <class T>
void Queue<T>::deQueue()
{
	queue.removeFirst();
}
template <class T>
T Queue<T>::front() const
{
	return queue.getFirst();
}