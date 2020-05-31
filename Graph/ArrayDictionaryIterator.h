#pragma once

template <class keyT, class itemT>
class ArrayDictionary;

template <class keyT, class itemT>
class ArrayDictionaryIterator
{
private:
	const ArrayDictionary<keyT, itemT> * m_containerPtr;
	int m_currentItemIndex;
public:
	ArrayDictionaryIterator();
	ArrayDictionaryIterator(const ArrayDictionary<keyT, itemT>* srcContainerPtr, int srcIndex);
	ArrayDictionaryIterator(const ArrayDictionaryIterator& src);
	ArrayDictionaryIterator<keyT, itemT>& operator=(const ArrayDictionaryIterator<keyT, itemT>& src);

	const itemT operator*();

	ArrayDictionaryIterator<keyT, itemT> operator++();
	ArrayDictionaryIterator<keyT, itemT> operator++(int);

	bool operator==(const ArrayDictionaryIterator<keyT, itemT>& src) const;
	bool operator!=(const ArrayDictionaryIterator<keyT, itemT>& src) const;
};

template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT>::ArrayDictionaryIterator()
{
	m_containerPtr = nullptr;
	m_currentItemIndex = -1;
}
template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT>::ArrayDictionaryIterator(const ArrayDictionary<keyT, itemT>* srcContainerPtr, int srcIndex)
{
	m_containerPtr = srcContainerPtr;
	m_currentItemIndex = srcIndex;
}
template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT>::ArrayDictionaryIterator(const ArrayDictionaryIterator& src)
{
	m_containerPtr = src.m_containerPtr;
	m_currentItemIndex = src.m_currentItemIndex;
}
template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT>& ArrayDictionaryIterator<keyT, itemT>::operator=(const ArrayDictionaryIterator<keyT, itemT>& src)
{
	if (this != &src)
	{
		m_containerPtr = src.m_containerPtr;
		m_currentItemIndex = src.m_currentItemIndex;
	}
	return *this;
}

template <class keyT, class itemT>
const itemT ArrayDictionaryIterator<keyT, itemT>::operator*()
{
	return m_containerPtr->m_items[m_currentItemIndex].getItem();
}

template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT> ArrayDictionaryIterator<keyT, itemT>::operator++()
{
	m_currentItemIndex++;
	return *this;
}
template <class keyT, class itemT>
ArrayDictionaryIterator<keyT, itemT> ArrayDictionaryIterator<keyT, itemT>::operator++(int)
{
	ArrayDictionaryIterator temp(*this);
	++(*this);
	return temp;
}

template <class keyT, class itemT>
bool ArrayDictionaryIterator<keyT, itemT>::operator==(const ArrayDictionaryIterator<keyT, itemT>& src) const
{
	return (m_containerPtr == src.m_containerPtr && m_currentItemIndex == src.m_currentItemIndex);
}
template <class keyT, class itemT>
bool ArrayDictionaryIterator<keyT, itemT>::operator!=(const ArrayDictionaryIterator<keyT, itemT>& src) const
{
	return !(m_containerPtr == src.m_containerPtr && m_currentItemIndex == src.m_currentItemIndex);
}