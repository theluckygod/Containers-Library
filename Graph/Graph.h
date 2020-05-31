#pragma once
#include "ArrayDictionary.h"
#include "SinglyLinkedList.h"
#include "Vertex.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "PrimNode.h"
#include <iostream>
using namespace std;

template <class labelT>
class Graph
{
private:
	int m_NumberOfVertices, m_NumberOfEdges;
	ArrayDictionary <labelT, Vertex <labelT> *> m_vertices;
private:
	void copyGraph(const Graph<labelT>& src);
	void unvisitAllVertices();
	void depthFirstTraversalHelper(Vertex<labelT>* v);
	void breadthFirstTraversalHelper(Vertex<labelT>* v);
	void dfsSpanningTreeHelper(Vertex<labelT> *v, Graph<labelT> &g);
	void bfsSpanningTreeHelper(Vertex<labelT> *v, Graph<labelT> &g);

public:
	Graph();
	Graph(const Graph<labelT>& src);
	~Graph();
	Graph<labelT>& operator=(const Graph<labelT>& src);

	bool isEmpty() const;
	int getNumberOfVertices() const;
	int getNumberOfEdges() const;
	double getSumOfWeight();
	
	void add(const labelT& start_vtL, const labelT& end_vtL, const double& w = 0);
	bool remove(const labelT& vtL);
	void clear();

	double getEdgeWeight(const labelT& start_vtL, const labelT& end_vtL) const;

	void depthFirstTraversal(const labelT& v);
	void breadthFirstTraversal(const labelT& v);

	SinglyLinkedList<labelT> topologicalSort();
	Graph<labelT> dfsSpanningTree(const labelT& start_vt);
	Graph<labelT> bfsSpanningTree(const labelT& start_vt);

	Graph<labelT> minimumSpanningTree(const labelT& start_vt);

	template <class labelT>
	friend ostream& operator<<(ostream& out, Graph<labelT> g);

	void traversaled(ostream& out) const;
};


template <class labelT>
void Graph<labelT>::copyGraph(const Graph<labelT>& src)
{
	m_NumberOfEdges = src.m_NumberOfEdges;
	m_NumberOfVertices = src.m_NumberOfVertices;
	ArrayDictionaryIterator<labelT, Vertex<labelT>*> it;
	for (it = src.m_vertices.begin(); it != src.m_vertices.end(); ++it)
	{
		m_vertices.add((*it)->getLabel(), new Vertex<labelT>(*(*it)));
	}
}
template <class labelT>
void Graph<labelT>::unvisitAllVertices()
{
	ArrayDictionaryIterator<labelT, Vertex<labelT>*> it;
	for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		(*it)->unvisit();
	}
}
template <class labelT>
void Graph<labelT>::depthFirstTraversalHelper(Vertex<labelT>* v)
{
	Vertex<labelT>* u;

	v->visit();
	//cout << v->getLabel() << endl;
	v->resetIterator();
	for (int i = 0, outDegree = v->getOutDegree(); i < outDegree; i++)
	{
		u = m_vertices.getItem(v->getNext());
		if (!u->isVisited())
			depthFirstTraversalHelper(u);
	}
}
template <class labelT>
void Graph<labelT>::breadthFirstTraversalHelper(Vertex<labelT>* v)
{
	Queue<Vertex <labelT>*> queue;
	queue.enQueue(v);
	v->visit();
	Vertex<labelT>* u;
	while (!queue.isEmpty())
	{
		v = queue.front();
		queue.deQueue();

		//cout << v->getLabel() << endl;
		v->resetIterator();
		for (int i = 0, outDegree = v->getOutDegree(); i < outDegree; i++)
		{
			u = m_vertices.getItem(v->getNext());
			if (!u->isVisited())
			{
				u->visit();
				queue.enQueue(u);
			}
		}
	}
}
template <class labelT>
void Graph<labelT>::dfsSpanningTreeHelper(Vertex<labelT> *v, Graph<labelT> &g)
{
	Vertex<labelT>* u;
	labelT lab, vlab = v->getLabel();
	v->visit();
	v->resetIterator();
	for (int i = 0, outDegree = v->getOutDegree(); i < outDegree; i++)
	{
		lab = v->getNext();
		u = m_vertices.getItem(lab);
		if (!u->isVisited())
		{
			g.add(vlab, lab, v->getEdgeWeight(lab));
			g.add(lab, vlab, u->getEdgeWeight(vlab));
			dfsSpanningTreeHelper(u, g);
		}
	}
}
template <class labelT>
void Graph<labelT>::bfsSpanningTreeHelper(Vertex<labelT> *v, Graph<labelT> &g)
{
	Queue<Vertex<labelT>*> queue;
	queue.enQueue(v);
	v->visit();

	while (!queue.isEmpty())
	{
		v = queue->front();
		queue.deQueue();
		v->resetIterator();

		Vertex<labelT> * u;
		labelT lab, vlab = v->getLabel();
		for (int i = 0, outDegree = v->getOutDegree(); i < outDegree; i++)
		{
			lab = v->getNext();
			u = m_vertices.getItem(lab);

			if (!u->isVisited())
			{
				g.add(vlab, lab, v->getEdgeWeight(lab));
				g.add(lab, vlab, u->getEdgeWeight(vlab));
				u->visit();
				queue.enQueue(u);
			}
		}
	}
}


template <class labelT>
Graph<labelT>::Graph()
{
	m_NumberOfEdges = m_NumberOfVertices = 0;
}
template <class labelT>
Graph<labelT>::Graph(const Graph<labelT>& src)
{
	copyGraph(src);
}
template <class labelT>
Graph<labelT>::~Graph()
{
	clear();
}
template <class labelT>
Graph<labelT>& Graph<labelT>::operator=(const Graph<labelT>& src)
{
	if (this != &src)
	{
		clear();
		copyGraph(src);
	}
	return *this;
}

template <class labelT>
bool Graph<labelT>::isEmpty() const
{
	return m_NumberOfVertices == 0;
}
template <class labelT>
int Graph<labelT>::getNumberOfVertices() const
{
	return m_NumberOfVertices;
}
template <class labelT>
int Graph<labelT>::getNumberOfEdges() const
{
	return m_NumberOfEdges;
}

template <class labelT>
void Graph<labelT>::add(const labelT& start_vtL, const labelT& end_vtL, const double& w)
{
	if (start_vtL == end_vtL) return;

	if (!m_vertices.isContain(start_vtL))
	{
		m_vertices.add(start_vtL, new Vertex<labelT>(start_vtL));
		m_NumberOfVertices++;
	}
	if (!m_vertices.isContain(end_vtL))
	{
		m_vertices.add(end_vtL, new Vertex<labelT>(end_vtL));
		m_NumberOfVertices++;
	}
	
	if (m_vertices.getItem(start_vtL)->connect(end_vtL, w))
		m_NumberOfEdges++;
}
template <class labelT>
bool Graph<labelT>::remove(const labelT& vtL)
{
	if (m_vertices.isContain(vtL))
	{
		Vertex<labelT> *removeV = m_vertices.getItem(vtL);
		int outDegree = removeV->getOutDegree(), i;
		for (i = 0; i < outDegree; i++)
		{
			removeV->resetIterator();
			removeV->disconnect(removeV->getNext());
			m_NumberOfEdges--;
		}
		delete removeV;

		m_vertices.remove(vtL);
		m_NumberOfVertices--;

		ArrayDictionaryIterator<labelT, Vertex<labelT>*> it;
		for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
		{
			Vertex<labelT>* nowV = (*it)->getItem();
			nowV->resetIterator();

			for (i = 0, outDegree = nowV->getOutDegree(); i < outDegree; i++)
				if (vtL == nowV->getNext())
				{
					nowV->disconnect(vtL);
					m_NumberOfEdges--;
					break;
				}
		}
		return true;
	}
	return false;
}
template <class labelT>
void Graph<labelT>::clear()
{
	ArrayDictionaryIterator<labelT, Vertex<labelT>*> it;
	for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		if(*it != NULL)	delete (*it);
	}
	m_vertices.clear();

	m_NumberOfEdges = m_NumberOfVertices = 0;
}


template <class labelT>
double Graph<labelT>::getEdgeWeight(const labelT& start_vtL, const labelT& end_vtL) const
{
	if (m_vertices.isContain(start_vtL))
	{
		return m_vertices->getItem(start_vtL)->getWeight(end_vtL);
	}
	return -1;
}

template <class labelT>
void Graph<labelT>::depthFirstTraversal(const labelT& vstart)
{
	unvisitAllVertices();
	depthFirstTraversalHelper(m_vertices.getItem(vstart));
}
template <class labelT>
void Graph<labelT>::breadthFirstTraversal(const labelT& vstart)
{
	unvisitAllVertices();
	breadthFirstTraversalHelper(m_vertices.getItem(vstart));
}

template <class labelT>
SinglyLinkedList<labelT> Graph<labelT>::topologicalSort()
{
	SinglyLinkedList<labelT> list;
	Queue<labelT> queue;
	ArrayDictionaryIterator<labelT, Vertex<labelT> *> it;
	unvisitAllVertices();

	for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
		if ((*it)->getOutDegree() == 0 && (*it)->isVisited == false)
		{
			queue.enQueue((*it)->getLabel());
			(*it)->visit();
		}

	labelT lab;
	while (!queue.isEmpty())
	{
		lab = queue.front();
		queue.deQueue(lab);
		list.insertFirst(lab);
		remove(lab);
		
		for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
			if ((*it)->getOutDegree() == 0 && (*it)->isVisited == false)
			{
				queue.enQueue((*it)->getLabel());
				(*it)->visit();
			}
	}

	if (m_vertices.isEmpty()) return list;
	return SinglyLinkedList <labelT>();
}
template <class labelT>
Graph<labelT> Graph<labelT>::dfsSpanningTree(const labelT& start_vt)
{
	unvisitAllVertices();
	Graph<labelT> g;
	dfsSpanningTreeHelper(m_vertices.getItem(start_vt), g);
	return g;
}
template <class labelT>
Graph<labelT> Graph<labelT>::bfsSpanningTree(const labelT& start_vt)
{
	unvisitAllVertices();
	Graph<labelT> g;
	bfsSpanningTreeHelper(m_vertices.getItem(start_vt), g);
	return g;
}
template <class labelT>
Graph<labelT> Graph<labelT>::minimumSpanningTree(const labelT& start_vt)
{
	PriorityQueue<PrimNode<labelT> > pQ;
	ArrayDictionaryIterator<labelT, Vertex<labelT> *>
		iter;
	for (iter = m_vertices.begin(); iter != m_vertices.end();
		iter++) {
		labelT lab = (*iter)->getLabel();
		PrimNode<labelT> pn(lab, lab);
		if (lab == start_vt)
			pn.setWeight(0);
		pQ.enQueue(pn);
	}
	Graph<labelT> g;
	while (!pQ.isEmpty()) {
		labelT inLab, outLab;
		PrimNode<labelT> pn = pQ.front();
		pQ.deQueue();
		inLab = pn.getLabel();
		g.add(pn.getParent(), inLab, pn.getWeight());
		g.add(inLab, pn.getParent(), pn.getWeight());
		Vertex<labelT> * v = m_vertices.getItem(inLab);
		PriorityQueue<PrimNode<labelT> > temp;
		while (!pQ.isEmpty()) {
			pn = pQ.front();
			pQ.deQueue();
			outLab = pn.getLabel();
			v->resetIterator();
			for (int i = 0; i < v->getOutDegree(); i++)
				if (outLab == v->getNext()) {
					if (v->getEdgeWeight(outLab) <	pn.getWeight()) 
					{
						pn.setParent(inLab);
						pn.setWeight(v -> getEdgeWeight(outLab));
					}
					break;
				}
			temp.enQueue(pn);
		}
		pQ = temp;
	}return g;
}

template <class labelT>
ostream& operator<<(ostream& out, Graph<labelT>g)
{
	g.unvisitAllVertices();
	ArrayDictionaryIterator<labelT, Vertex<labelT>*> it;
	for (it = g.m_vertices.begin(); it != g.m_vertices.end(); ++it)
	{
		Vertex<labelT>* v = (*it);
		v->visit();
		v->resetIterator();
		
		labelT lab;
		for (int i = 0, oD = v->getOutDegree(); i < oD; i++)
		{
			lab = v->getNext();
			if(!g.m_vertices.getItem(lab)->isVisited())
				out << v->getLabel() << " " << lab << " " << v->getEdgeWeight(lab) << endl;
		}
	}
	return out;
}

template <class labelT>
double Graph<labelT>::getSumOfWeight()
{
	double sum = 0;
	unvisitAllVertices();
	ArrayDictionaryIterator<labelT, Vertex<labelT>*> it;
	for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		Vertex<labelT>* v = (*it);
		v->visit();
		v->resetIterator();

		labelT lab;
		for (int i = 0, oD = v->getOutDegree(); i < oD; i++)
		{
			lab = v->getNext();
			if (!m_vertices.getItem(lab)->isVisited())
				sum += v->getEdgeWeight(lab);
		}
	}
	return sum;
}

template <class labelT>
void Graph<labelT>::traversaled(ostream& out) const
{
	int count = 0;
	ArrayDictionaryIterator <labelT, Vertex <labelT> *> it;
	for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		if ((*it)->isVisited()) count++;
	}
	out << count << endl;
	for (it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		if ((*it)->isVisited()) out << (*it)->getLabel() << " ";
	}
}