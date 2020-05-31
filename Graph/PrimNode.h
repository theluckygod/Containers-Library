#pragma once
#include <climits>

template <class labelT>
class PrimNode
{
private:
	labelT m_label, m_parent;
	double m_weight;
public:
	PrimNode();
	PrimNode(const PrimNode& src);
	PrimNode(const labelT& lb, const labelT& prt, const double& w = INT_MAX);

	void setLabel(const labelT& lb);
	labelT getLabel() const;
	void setParent(const labelT& prt);
	labelT getParent() const;
	void setWeight(const double& w);
	double getWeight() const;

	bool operator > (const PrimNode<labelT>& src);
	bool operator <= (const PrimNode<labelT>& src);
};


template <class labelT>
PrimNode<labelT>::PrimNode()
{}
template <class labelT>
PrimNode<labelT>::PrimNode(const PrimNode& src) : m_label(src.m_label), m_parent(src.m_parent)
{
	m_weight = src.m_weight;
}
template <class labelT>
PrimNode<labelT>::PrimNode(const labelT& lb, const labelT& prt, const double& w)
{
	m_label = lb; 
	m_parent = prt;
	m_weight = w;
}

template <class labelT>
void PrimNode<labelT>::setLabel(const labelT& lb)
{
	m_label = lb;
}
template <class labelT>
labelT PrimNode<labelT>::getLabel() const
{
	return m_label;
}
template <class labelT>
void PrimNode<labelT>::setParent(const labelT& prt)
{
	m_parent = prt;
}
template <class labelT>
labelT PrimNode<labelT>::getParent() const
{
	return m_parent;
}
template <class labelT>
void PrimNode<labelT>::setWeight(const double& w)
{
	m_weight = w;
}
template <class labelT>
double PrimNode<labelT>::getWeight() const
{
	return m_weight;
}

template <class labelT>
bool PrimNode<labelT>::operator > (const PrimNode<labelT>& src)
{
	return m_weight > src.m_weight;
}
template <class labelT>
bool PrimNode<labelT>::operator <= (const PrimNode<labelT>& src)
{
	return m_weight <= src.m_weight;
}