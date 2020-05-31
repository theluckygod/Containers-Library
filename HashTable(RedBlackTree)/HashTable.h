#pragma once
#include "RBNode.h"
#include "Word.h"
#include <algorithm>
using namespace std;

#define MAX 30000

template <class TypeList, class TypeData>
class HashTable
{
private:
	TypeList* m_table;
public:
	static int HashFunction(Word*);
public:
	HashTable();
	HashTable(const HashTable&);
	~HashTable();
	HashTable& operator=(const HashTable&);

	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;

	void add(TypeData*);
	void remove(TypeData*);
	TypeData* search(TypeData*) const;

	void inorderTravesal(ostream&) const;
	void preorderTravesal(ostream&) const;
	void postorderTravesal(ostream&) const;
};

template <class TypeList, class TypeData>
int HashTable<TypeList, TypeData>::HashFunction(Word* key)
{
	return key->convertToInt() % MAX;
}


template <class TypeList, class TypeData>
HashTable<TypeList, TypeData>::HashTable()
{
	m_table = new TypeList[MAX];
}
template <class TypeList, class TypeData>
HashTable<TypeList, TypeData>::HashTable(const HashTable<TypeList, TypeData>& src)
{
	m_table = new TypeList[MAX];
	for (int i = 0; i < MAX; i++)
	{
		m_table[i] = src.m_table[i];
	}
}
template <class TypeList, class TypeData>
HashTable<TypeList, TypeData>::~HashTable()
{
	if (m_table != NULL)
	{
		delete[]  m_table;
		m_table = NULL;
	}
}
template <class TypeList, class TypeData>
HashTable<TypeList, TypeData>& HashTable<TypeList, TypeData>::operator=(const HashTable& src)
{
	if (this != &src)
	{
		this->~HashTable();
		m_table = new TypeList[MAX];
		for (int i = 0; i < MAX; i++)
		{
			m_table[i] = src.m_table[i];
		}
	}
	return *this;
}

template <class TypeList, class TypeData>
bool HashTable<TypeList, TypeData>::isEmpty() const
{
	if (m_table == NULL) return true;
	else
	{
		for (int i = 0; i < MAX; i++)
			if (!m_table[i].isEmpty()) return false;
		return true;
	}
}
template <class TypeList, class TypeData>
int HashTable<TypeList, TypeData>::getHeight() const
{
	int maxHeight = 0;
	if (m_table != NULL)
	{
		int temp;
		for (int i = 0; i < MAX; i++)
		{
			temp = m_table[i].getHeight();
			if (temp > maxHeight) maxHeight = temp;
		}
	}
	return maxHeight;
}
template <class TypeList, class TypeData>
int HashTable<TypeList, TypeData>::getNumberOfNodes() const
{
	int Total = 0;
	if (m_table != NULL)
	{
		for (int i = 0; i < MAX; i++)
		{
			Total += m_table[i].getNumberOfNodes();
		}
	}
	return Total;
}

template <class TypeList, class TypeData>
void HashTable<TypeList, TypeData>::add(TypeData* key)
{
	m_table[HashTable::HashFunction(key)].add(key);
}
template <class TypeList, class TypeData>
void HashTable<TypeList, TypeData>::remove(TypeData* key)
{
	m_table[HashTable::HashFunction(key)].remove(key);
}
template <class TypeList, class TypeData>
TypeData* HashTable<TypeList, TypeData>::search(TypeData* key) const
{
	return m_table[HashTable::HashFunction(key)].search(key);
}

template <class TypeList, class TypeData>
void HashTable<TypeList, TypeData>::inorderTravesal(ostream& out) const
{
	if (m_table != NULL)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (!m_table[i].isEmpty())
				m_table[i].inorderTravesal(out);
		}
	}
}
template <class TypeList, class TypeData>
void HashTable<TypeList, TypeData>::preorderTravesal(ostream& out) const
{
	if (m_table != NULL)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (!m_table[i].isEmpty())
				m_table[i].preorderTravesal(out);
		}
	}
}
template <class TypeList, class TypeData>
void HashTable<TypeList, TypeData>::postorderTravesal(ostream& out) const
{
	if (m_table != NULL)
	{
		for (int i = MAX - 1; i >= 0; i--)
		{
			if (!m_table[i].isEmpty())
				m_table[i].postorderTravesal(out);
		}
	}
}