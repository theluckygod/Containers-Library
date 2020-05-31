#pragma once
#include "SinglyLinkedList.h"

template <class T>
class Stack
{
private:
	SinglyLinkedList<T> m_stack;
public:
	Stack();
	Stack(const Stack&);
	~Stack();
	Stack& operator=(const Stack&);

	bool isEmpty() const;
	void push(const T&);
	void pop();
	T top() const;
};

template <class T>
Stack<T>::Stack()
{}
template <class T>
Stack<T>::Stack(const Stack& src) : m_stack(src.m_stack)
{}
template <class T>
Stack<T>::~Stack(){}
template <class T>
Stack<T>& Stack<T>::operator=(const Stack & src)
{
	if (this != &src)
	{
		this->~Stack();
		m_stack = src.m_stack;
	}
	return *this;
}

template <class T>
bool Stack<T>::isEmpty() const
{
	return m_stack.isEmpty();
}
template <class T>
void Stack<T>::push(const T& data)
{
	m_stack.insertFirst(data);
}
template <class T>
void Stack<T>::pop()
{
	m_stack.removeFirst();
}
template <class T>
T Stack<T>::top() const
{
	return m_stack.getFirst();
}