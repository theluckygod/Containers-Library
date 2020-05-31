#pragma once
#include <iostream>
using namespace std;
#define BLACK 0
#define RED 1

template <class T>
class RBNode
{
private:
	T* m_data;
	bool m_color;
	RBNode<T>* m_left, *m_right, *m_parent;
public:
	RBNode();
	RBNode(T*);
	RBNode(T*, bool, RBNode<T>*, RBNode<T>*, RBNode<T>*);

	void setData(T*);
	T* getData() const;
	void setColor(bool color);
	bool getColor() const;
	void setLeft(RBNode<T>*);
	RBNode<T>* getLeft() const;
	void setRight(RBNode<T>*);
	RBNode<T>* getRight() const;
	void setParent(RBNode<T>*);
	RBNode<T>* getParent() const;
};

template <class T>
RBNode<T>::RBNode()
{
	m_color = BLACK;
	m_data = m_left = m_right = m_parent = NULL;
}
template <class T>
RBNode<T>::RBNode(T* data): m_data(data)
{
	m_color = BLACK;
	m_left = m_right = m_parent = NULL;
}
template <class T>
RBNode<T>::RBNode(T* data, bool color, RBNode<T>* left, RBNode<T>* right, RBNode<T>* parent) : m_data(data)
{
	m_color = color;
	m_left = left;
	m_right = right;
	m_parent = parent;
}

template <class T>
void RBNode<T>::setData(T* data)
{
	if (m_data != NULL) delete m_data;
	m_data = data;
}
template <class T>
T* RBNode<T>::getData() const
{
	return m_data;
}
template <class T>
void RBNode<T>::setColor(bool color)
{
	m_color = color;
}
template <class T>
bool RBNode<T>::getColor() const
{
	return m_color;
}
template <class T>
void RBNode<T>::setLeft(RBNode<T>* left)
{
	m_left = left;
}
template <class T>
RBNode<T>* RBNode<T>::getLeft() const
{
	return m_left;
}
template <class T>
void RBNode<T>::setRight(RBNode<T>* right)
{
	m_right = right;
}
template <class T>
RBNode<T>* RBNode<T>::getRight() const
{
	return m_right;
}
template <class T>
void RBNode<T>::setParent(RBNode<T>* parent)
{
	m_parent = parent;
}
template <class T>
RBNode<T>* RBNode<T>::getParent() const
{
	return m_parent;
}