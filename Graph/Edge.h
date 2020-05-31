#pragma once

template <class labelT>
class Edge
{
private:
	labelT m_endVertex;
	double m_weight;
public:
	Edge();
	Edge(labelT eVt, double w = 0);
	Edge(const Edge& src);

	labelT getEndVertex() const;
	void setEndVertex(const labelT& eVt);
	double getWeight() const;
	void setWeight(double w);
};

template <class labelT>
Edge<labelT>::Edge()
{
	m_weight = 0;
}
template <class labelT>
Edge<labelT>::Edge(labelT eVt, double w) : m_endVertex(eVt)
{
	m_weight = w;
}
template <class labelT>
Edge<labelT>::Edge(const Edge& src) 
	: m_endVertex(src.m_endVertex), m_weight(src.m_weight)
{}

template <class labelT>
labelT Edge<labelT>::getEndVertex() const
{
	return m_endVertex;
}
template <class labelT>
void Edge<labelT>::setEndVertex(const labelT& eVt)
{
	m_endVertex = eVt;
}
template <class labelT>
double Edge<labelT>::getWeight() const
{
	return m_weight;
}
template <class labelT>
void Edge<labelT>::setWeight(double w)
{
	m_weight = w;
}