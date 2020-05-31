#pragma once
#include "SparseNode.h"
#include <iostream>
using namespace std;

template <class T>
class SparseTable
{
private:
	int m_row, m_col;
	SparseNode<T>** m_rowHost, **m_colHost;
public:
	SparseTable();
	SparseTable(int, int);
	SparseTable(const SparseTable<T>&);
	~SparseTable();

	void insert(int, int, T);
	void remove(int, int);

	T getData(int, int) const;
	T getDataVorder(int, int) const;
	int getRow() const;
	int getCol() const;

	void print(ostream&) const;
	void printVorder(ostream&) const;
	void clear();

	SparseTable& operator=(const SparseTable&);
};

template <class T>
SparseTable<T>::SparseTable()
{
	m_row = m_col = 0;
	m_colHost = m_rowHost = NULL;
}
template <class T>
SparseTable<T>::SparseTable(int m, int n)
{
	m_row = m;
	m_col = n;
	m_rowHost = new SparseNode<T>*[m];
	m_colHost = new SparseNode<T>*[n];

	int i;
	for (i = 0; i < m; i++)
		m_rowHost[i] = NULL;
	for (i = 0; i < n; i++)
		m_colHost[i] = NULL;
}
template <class T>
SparseTable<T>::SparseTable(const SparseTable<T>& src)
{
	m_row = src.m_row;
	m_col = src.m_col;
	m_rowHost = new SparseNode<T>*[m_row];
	m_colHost = new SparseNode<T>*[m_col];

	int i;
	for (i = 0; i < m_row; i++)
		m_rowHost[i] = NULL;
	for (i = 0; i < m_col; i++)
		m_colHost[i] = NULL;

	SparseNode<T>* pHsrc;
	for (i = 0; i < m_row; i++)
	{
		pHsrc = src.m_rowHost[i];
		for (; pHsrc; pHsrc = pHsrc->getHNext())
			insert(pHsrc->getRow(), pHsrc->getCol(), pHsrc->getData());
	}
}
template <class T>
SparseTable<T>::~SparseTable()
{
	clear();
	delete[] m_rowHost;
	delete[] m_colHost;
}

template <class T>
void SparseTable<T>::insert(int x, int y, T key)
{
	if (x < 0 || x >= m_row || y < 0 || y >= m_col) throw (char *) "Truy cap ngoai vung nho!\n";

	SparseNode<T> * newNode = new SparseNode<T>(x, y, key);
	SparseNode<T> * pH, *pV;
	pH = m_rowHost[x];
	pV = m_colHost[y];
	bool finishAdd = false;

	if (pH == NULL) m_rowHost[x] = newNode;
	else
	{
		if (pH->getHNext() == NULL)
		{
			if (pH->getCol() == y)
			{
				pH->setData(key);
				delete newNode;
				finishAdd = true;
			}
			else
				if (pH->getCol() > y)
				{
					newNode->setHNext(pH);
					m_rowHost[x] = newNode;
				}
				else
				{
					pH->setHNext(newNode);
				}
		}
		else
		{
			if(pH->getCol() == y)
			{
				pH->setData(key);
				delete newNode;
				finishAdd = true;
			}
			else
				if(pH->getCol() > y)
				{
					newNode->setHNext(pH);
					m_rowHost[x] = newNode;
				}
				else
				{
					bool added = false;
					do
					{
						if(pH->getHNext()->getCol() == y)
						{
							pH->getHNext()->setData(key);
							delete newNode;
							finishAdd = true;
							added = true;
						}
						else
							if (pH->getHNext()->getCol() > y)
							{
								newNode->setHNext(pH->getHNext());
								pH->setHNext(newNode);
								added = true;
							}

						pH = pH->getHNext();
					} while (!added && pH->getHNext());

					if (!added) pH->setHNext(newNode);
				}
		}
	}

	if (!finishAdd)
	{
		if (pV == NULL) m_colHost[y] = newNode;
		else
		{
			if (pV->getVNext() == NULL)
			{
				if (pV->getRow() > x)
				{
					newNode->setVNext(pV);
					m_colHost[y] = newNode;
				}
				else
				{
					pV->setVNext(newNode);
				}
			}
			else
			{
				if (pV->getRow() > x)
				{
					newNode->setVNext(pV);
					m_colHost[y] = newNode;
				}
				else
				{
					bool added = false;
					do
					{
						if (pV->getVNext()->getRow() > x)
						{
							newNode->setVNext(pV->getVNext());
							pV->setVNext(newNode);
							added = true;
						}

						pV = pV->getVNext();
					} while (!added && pV->getVNext());

					if (!added) pV->setVNext(newNode);
				}
			}
		}
	}
}
template <class T>
void SparseTable<T>::remove(int x, int y)
{
	if (x < 0 || x >= m_row || y < 0 || y >= m_col) throw (char *) "Truy cap ngoai vung nho!\n";

	SparseNode<T> * removeNode = NULL;
	SparseNode<T> * pH, *pV;
	pH = m_rowHost[x];
	pV = m_colHost[y];

	if (pH != NULL)
	{
		SparseNode<T> * prevpH = m_rowHost[x];
		for (; pH; pH = pH->getHNext())
		{
			if (pH->getCol() == y) break;
			prevpH = pH;
		}
		if (pH != NULL)
		{
			if (pH == prevpH)
			{
				m_rowHost[x] = prevpH->getHNext();
			}
			else prevpH->setHNext(pH->getHNext());
			removeNode = pH;
		}
	}

	if (removeNode)
	{
		SparseNode<T> * prevpV = m_colHost[y];
		for (; pV; pV = pV->getVNext())
		{
			if (pV == removeNode) break;
			prevpV = pV;
		}
		if (pV != NULL)
		{
			if (pV == prevpV) m_colHost[y] = prevpV->getVNext();
			else prevpV->setVNext(pV->getVNext());
		}

		delete removeNode;
	}
}

template <class T>
T SparseTable<T>::getData(int x, int y) const
{
	if (x < 0 || x >= m_row || y < 0 || y >= m_col) throw (char *) "Truy cap ngoai vung nho!\n";

	SparseNode<T>* pH;
	for (pH = m_rowHost[x]; pH && pH->getCol() != y; pH = pH->getHNext());
	if (pH) return pH->getData();
	return 0;
}
template <class T>
T SparseTable<T>::getDataVorder(int x, int y) const
{
	if (x < 0 || x >= m_row || y < 0 || y >= m_col) throw (char *) "Truy cap ngoai vung nho!\n";

	SparseNode<T>* pV;
	for (pV = m_colHost[y]; pV && pV->getRow() != x; pV = pV->getVNext());
	if (pV) return pV->getData();
	return 0;
}
template <class T>
int SparseTable<T>::getRow() const
{
	return m_row;
}
template <class T>
int SparseTable<T>::getCol() const
{
	return m_col;
}
template <class T>
void SparseTable<T>::print(ostream& out) const
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			out << getData(i, j) << "  ";
		}
		out << endl;
	}
}
template <class T>
void SparseTable<T>::printVorder(ostream& out) const
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			out << getDataVorder(i, j) << "  ";
		}
		out << endl;
	}
}

template <class T>
void SparseTable<T>::clear()
{
	SparseNode<T> * pH, *prevpH;
	for (int i = 0; i < m_row; i++)
	{
		for (pH = m_rowHost[i]; pH;)
		{
			prevpH = pH;
			pH = pH->getHNext();
			delete prevpH;
		}
		m_rowHost[i] = NULL;
	}
	for (int i = 0; i < m_col; i++)
	{
		m_colHost[i] = NULL;
	}
}


template <class T>
SparseTable<T>& SparseTable<T>::operator=(const SparseTable& src)
{
	if (this != &src)
	{
		this->~SparseTable();
		m_row = src.m_row;
		m_col = src.m_col;
		m_rowHost = new SparseNode<T>*[m_row];
		m_colHost = new SparseNode<T>*[m_col];

		int i;
		for (i = 0; i < m_row; i++)
			m_rowHost[i] = NULL;
		for (i = 0; i < m_col; i++)
			m_colHost[i] = NULL;

		SparseNode<T>* pHsrc;
		for (i = 0; i < m_row; i++)
		{
			pHsrc = src.m_rowHost[i];
			for (; pHsrc; pHsrc = pHsrc->getHNext())
				insert(pHsrc->getRow(), pHsrc->getCol(), pHsrc->getData());
		}
	}
	return *this;
}