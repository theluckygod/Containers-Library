#pragma once
#include <iostream>
using namespace std;

template <class T>
class node
{
private:
	T m_data;
	node* m_next;
public:
	node();
	node(const T&);
	node(const T&, const node*);
	~node();
	
	void setData(const T&);
	void setNext(node*);
	T getData() const;
	node* getNext() const;	
};

template <class T>
node<T>::node()
{
	m_next = NULL;
}
template <class T>
node<T>::node(const T& key)
{
	m_data = key;
	m_next = NULL;
}
template <class T>
node<T>::node(const T& key, const node* nextNode)
{
	m_data = key;
	m_next = nextNode;
}
template <class T>
node<T>::~node()
{}

template <class T>
void node<T>::setData(const T& newKey)
{
	m_data = newKey;
}
template <class T>
void node<T>::setNext(node* nextNode)
{
	m_next = nextNode;
}
template <class T>
T node<T>::getData() const
{
	return m_data;
}
template <class T>
node<T>* node<T>::getNext() const
{
	return m_next;
}