#pragma once
#include "ArrayDictionary.h"
#include "Edge.h"

template <class labelT>
class Vertex
{
private:
	labelT m_vertexLabel;
	bool m_visited;
	ArrayDictionary<labelT, Edge<labelT>*> m_adjList;
	ArrayDictionaryIterator <labelT, Edge<labelT>*> m_it;
private:
	void copyVertex(const Vertex<labelT>& src);
public:
	Vertex();
	Vertex(const Vertex& src);
	Vertex(labelT vertexLabel);
	~Vertex();
	Vertex<labelT>& operator=(const Vertex& src);

	labelT getLabel() const;

	void visit();
	void unvisit();
	bool isVisited() const;

	bool connect(const labelT& eVt, const double& w = 0);	
	bool disconnect(const labelT& eVt);

	double getEdgeWeight(const labelT& edL) const;
	int getOutDegree() const;

	bool operator==(const Vertex& src) const;

	void resetIterator();
	labelT getNext();
};

template <class labelT>
void Vertex<labelT>::copyVertex(const Vertex<labelT>& src)
{
	m_vertexLabel = src.m_vertexLabel;
	m_visited = src.m_visited;
	for (m_it = src.m_adjList.begin(); m_it != src.m_adjList.end(); ++m_it)
		connect((*m_it)->getEndVertex(), (*m_it)->getWeight());
	m_it = src.m_it;
}


template <class labelT>
Vertex<labelT>::Vertex()
{
	m_visited = 0;
}
template <class labelT>
Vertex<labelT>::Vertex(const Vertex& src)
{
	copyVertex(src);
}
template <class labelT>
Vertex<labelT>::Vertex(labelT vertexLabel)
	: m_vertexLabel(vertexLabel)
{
	m_visited = 0;
}
template <class labelT>
Vertex<labelT>::~Vertex()
{
	for (m_it = m_adjList.begin(); m_it != m_adjList.end(); ++m_it)
	{
		if (*m_it != NULL)
		{
			delete *m_it;
		}
	}
	m_adjList.clear();
}
template <class labelT>
Vertex<labelT>& Vertex<labelT>::operator=(const Vertex& src)
{
	if (this != &src)
	{
		this->~Vertex();
		copyVertex(src);
	}
	return *this;
}

template <class labelT>
labelT Vertex<labelT>::getLabel() const
{
	return m_vertexLabel;
}
template <class labelT>
void Vertex<labelT>::visit()
{
	m_visited = true;
}
template <class labelT>
void Vertex<labelT>::unvisit()
{
	m_visited = false;
}
template <class labelT>
bool Vertex<labelT>::isVisited() const
{
	return m_visited;
}

template <class labelT>
bool Vertex<labelT>::connect(const labelT& eVt, const double& w)
{
	return m_adjList.add(eVt, new Edge<labelT>(eVt, w));
}
template <class labelT>
bool Vertex<labelT>::disconnect(const labelT& eVt)
{
	Edge<labelT>* ed = m_adjList.getItem(eVt);
	delete ed;
	return m_adjList.remove(eVt);
}

template <class labelT>
double Vertex<labelT>::getEdgeWeight(const labelT& edL) const
{
	return m_adjList.getItem(edL)->getWeight();
}
template <class labelT>
int Vertex<labelT>::getOutDegree() const
{
	return m_adjList.getNumberOfEntries();
}

template <class labelT>
bool Vertex<labelT>::operator==(const Vertex& src) const
{
	return m_vertexLabel == src.m_vertexLabel;
}

template <class labelT>
void Vertex<labelT>::resetIterator()
{
	m_it = m_adjList.begin();
}
template <class labelT>
labelT Vertex<labelT>::getNext()
{
	return (*(m_it++))->getEndVertex();
}

