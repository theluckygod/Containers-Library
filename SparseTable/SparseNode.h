#pragma once
#include <iostream>
using namespace std;

template <class T>
class SparseNode
{
private:
	int m_row;
	int m_col;
	T m_data;
	SparseNode<T>* m_HNext;
	SparseNode<T>* m_VNext;
public:
	SparseNode();
	SparseNode(int row, int col, T data);
	SparseNode(int row, int col, T data, SparseNode<T>* hNext, SparseNode<T>* vNext);

	void setRow(int row);
	void setCol(int col);
	void setData(T data);
	void setHNext(SparseNode<T>* next);
	void setVNext(SparseNode<T>* next);

	int getRow() const;
	int getCol() const;
	T getData() const;
	SparseNode<T>* getHNext() const;
	SparseNode<T>* getVNext() const;
};

template <class T>
SparseNode<T>::SparseNode()
{
	m_row = m_col = -1;
	m_HNext = m_VNext = NULL;
}
template <class T>
SparseNode<T>::SparseNode(int row, int col, T data)
{
	m_data = data;
	m_row = row;
	m_col = col;
	m_HNext = m_VNext = NULL;
}
template <class T>
SparseNode<T>::SparseNode(int row, int col, T data, SparseNode<T>* HNext, SparseNode<T>* VNext)
{
	m_data = data;
	m_row = row;
	m_col = col;
	m_HNext = HNext;
	m_VNext = VNext;
}

template <class T>
void SparseNode<T>::setRow(int row)
{
	m_row = row;
}
template <class T>
void SparseNode<T>::setCol(int col)
{
	m_col = col;
}
template <class T>
void SparseNode<T>::setData(T data)
{
	m_data = data;
}
template <class T>
void SparseNode<T>::setHNext(SparseNode<T>* next)
{
	m_HNext = next;
}
template <class T>
void SparseNode<T>::setVNext(SparseNode<T>* next)
{
	m_VNext = next;
}

template <class T>
int SparseNode<T>::getRow() const
{
	return m_row;
}
template <class T>
int SparseNode<T>::getCol() const
{
	return m_col;
}
template <class T>
T SparseNode<T>::getData() const
{
	return m_data;
}
template <class T>
SparseNode<T>* SparseNode<T>::getHNext() const
{
	return m_HNext;
}
template <class T>
SparseNode<T>* SparseNode<T>::getVNext() const
{
	return m_VNext;
}