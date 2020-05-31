#pragma once
#include "Entry.h"
#include "ArrayDictionaryIterator.h"

#define DEFAULT_CAPACITY 10

template <class keyT, class itemT>
class ArrayDictionary
{
private:
	Entry <keyT, itemT> * m_items;
	int m_EntryCount;
	int m_EntryMax;

	int findEntryIndex(const keyT& key) const;
	void copyArrayDictionary(const ArrayDictionary<keyT, itemT>& src);
public:
	friend class ArrayDictionaryIterator<keyT, itemT>;
public:
	ArrayDictionary();
	ArrayDictionary(const ArrayDictionary<keyT, itemT>& src);
	~ArrayDictionary();

	bool isEmpty() const;
	int getNumberOfEntries() const;
	bool add(const keyT& key, const itemT& item);
	bool remove(const keyT& key);
	
	void clear();

	bool isContain(const keyT&  key) const;
	itemT getItem(const keyT& key) const;

	ArrayDictionary<keyT, itemT>& operator=(const ArrayDictionary<keyT, itemT>& src);

	ArrayDictionaryIterator<keyT, itemT> begin() const;
	ArrayDictionaryIterator<keyT, itemT> end() const;
};

template <class keyT, class itemT>
int ArrayDictionary<keyT, itemT>::findEntryIndex(const keyT& key) const
{
	for (int i = 0; i < m_EntryCount; i++)
		if (key == m_items[i].getKey()) return i;
	return -1;
}
template <class keyT, class itemT>
void ArrayDictionary<keyT, itemT>::copyArrayDictionary(const ArrayDictionary<keyT, itemT>& src)
{
	m_EntryCount = src.m_EntryCount;
	m_EntryMax = src.m_EntryMax;
	m_items = new Entry<keyT, itemT>[m_EntryCount];
	for (int i = 0; i < m_EntryCount; i++)
	{
		m_items[i] = src.m_items[i];
	}
}

template <class keyT, class itemT>
ArrayDictionary<keyT, itemT>::ArrayDictionary()
{
	m_EntryCount = 0;
	m_EntryMax = DEFAULT_CAPACITY;
	m_items = new Entry<keyT, itemT>[m_EntryMax];
}
template <class keyT, class itemT>
ArrayDictionary<keyT, itemT>::ArrayDictionary(const ArrayDictionary<keyT, itemT>& src)
{
	copyArrayDictionary(src);
}
template <class keyT, class itemT>
ArrayDictionary<keyT, itemT>::~ArrayDictionary()
{
	delete[] m_items;
}

template <class keyT, class itemT>
bool ArrayDictionary<keyT, itemT>::isEmpty() const
{
	return m_EntryCount == 0;
}
template <class keyT, class itemT>
int ArrayDictionary<keyT, itemT>::getNumberOfEntries() const
{
	return m_EntryCount;
}
template <class keyT, class itemT>
bool ArrayDictionary<keyT, itemT>::add(const keyT& key, const itemT& item)
{
	int index = findEntryIndex(key);
	if (index < 0)
	{
		if (m_EntryCount == m_EntryMax)
		{
			m_EntryMax += DEFAULT_CAPACITY;
			Entry<keyT, itemT> *temp = new Entry<keyT, itemT>[m_EntryMax];
			for (int i = 0; i < m_EntryCount; i++)
			{
				temp[i] = m_items[i];
			}
			temp[m_EntryCount] = m_items[m_EntryCount];
			
			delete[] m_items;
			m_items = temp;
			++m_EntryCount;
		}
		else
		{
			m_items[m_EntryCount++] = Entry<keyT, itemT>(key, item);
		}
	}
	else
	{
		m_items[index].setItem(item);
	}
	return true;
}
template <class keyT, class itemT>
bool ArrayDictionary<keyT, itemT>::remove(const keyT& key)
{
	int index = findEntryIndex(key);
	if (index >= 0)
	{
		m_items[index] = m_items[--m_EntryCount - 1];
		return true;
	}
	return false;
}

template <class keyT, class itemT>
void ArrayDictionary<keyT, itemT>::clear()
{
	m_EntryCount = 0;
}

template <class keyT, class itemT>
bool ArrayDictionary<keyT, itemT>::isContain(const keyT&  key) const
{
	return findEntryIndex(key) >= 0;
}
template <class keyT, class itemT>
itemT ArrayDictionary<keyT, itemT>::getItem(const keyT& key) const
{
	int index = findEntryIndex(key);
	if (index < 0) throw (char *) "Truy xuat ngoai vung nho!\n";
	return m_items[index].getItem();
}

template <class keyT, class itemT>
ArrayDictionary<keyT, itemT>& ArrayDictionary<keyT, itemT>::operator=(const ArrayDictionary<keyT, itemT>& src)
{
	if (this != src)
	{
		this->~ArrayDictionary();
		copyArrayDictionary(src);
	}
	return *this;
}

template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT> ArrayDictionary<keyT, itemT>::begin() const
{
	return ArrayDictionaryIterator<keyT, itemT>(this, 0);
}
template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT> ArrayDictionary<keyT, itemT>::end() const
{
	return ArrayDictionaryIterator<keyT, itemT>(this, m_EntryCount);
}