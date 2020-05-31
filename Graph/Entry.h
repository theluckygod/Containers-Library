#pragma once

template <class keyT, class itemT>
class Entry
{
private:
	keyT m_key;
	itemT m_item;
protected:
	void setKey(const keyT& key);
public:
	Entry();
	Entry(const Entry& src);
	Entry(const keyT& key, const itemT& item);

	void setItem(const itemT& item);
	itemT getItem() const;
	keyT getKey() const;
};

template <class keyT, class itemT>
Entry<keyT, itemT>::Entry() : m_key()
{}
template <class keyT, class itemT>
Entry<keyT, itemT>::Entry(const Entry& src)
{
	m_key = src.m_key;
	m_item = src.m_item;
}
template <class keyT, class itemT>
Entry<keyT, itemT>::Entry(const keyT& key, const itemT& item)
	: m_key(key), m_item(item)
{}

template <class keyT, class itemT>
void Entry<keyT, itemT>::setKey(const keyT& key)
{
	m_key = key;
}


template <class keyT, class itemT>
void Entry<keyT, itemT>::setItem(const itemT& item)
{
	m_item = item;
}
template <class keyT, class itemT>
itemT Entry<keyT, itemT>::getItem() const
{
	return m_item;
}
template <class keyT, class itemT>
keyT Entry<keyT, itemT>::getKey() const
{
	return m_key;
}