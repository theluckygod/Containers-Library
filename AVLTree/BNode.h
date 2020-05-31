#pragma once
#include <iostream>
using namespace std;

template <class T>
class BNode
{
private:
	T* m_data;
	BNode<T>* m_left, *m_right;
public:
	BNode();
	BNode(T*);
	BNode(T*, BNode<T>*, BNode<T>*);

	void setData(T*);
	T* getData() const;
	void setLeft(BNode<T>*);
	BNode<T>* getLeft() const;
	void setRight(BNode<T>*);
	BNode<T>* getRight() const;
};

template <class T>
BNode<T>::BNode()
{
	m_left = m_right = NULL;
}
template <class T>
BNode<T>::BNode(T* data): m_data(data)
{
	m_left = m_right = NULL;
}
template <class T>
BNode<T>::BNode(T* data, BNode<T>* left, BNode<T>* right) : m_data(data)
{
	m_left = left;
	m_right = right;
}

template <class T>
void BNode<T>::setData(T* data)
{
	if (m_data != NULL) delete m_data;
	m_data = data;
}
template <class T>
T* BNode<T>::getData() const
{
	return m_data;
}
template <class T>
void BNode<T>::setLeft(BNode<T>* left)
{
	m_left = left;
}
template <class T>
BNode<T>* BNode<T>::getLeft() const
{
	return m_left;
}
template <class T>
void BNode<T>::setRight(BNode<T>* right)
{
	m_right = right;
}
template <class T>
BNode<T>* BNode<T>::getRight() const
{
	return m_right;
}