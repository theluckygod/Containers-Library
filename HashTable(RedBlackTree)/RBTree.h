#pragma once
#include "RBNode.h"
#include <algorithm>
using namespace std;
template <class T>
class RBTree
{
private:
	RBNode<T>* m_root;
	RBNode<T>* m_nil;

private:
	RBNode<T>* copyTree(RBNode<T>*, RBNode<T>*);
	int getHeightHelper(RBNode<T> *) const;
	int getNumberOfNodesHelper(RBNode<T> *) const;
	void clearHelper(RBNode<T> *);
	void addFixUp(RBNode<T>*);
	void removeFixUp(RBNode<T> *);
	T* searchHelper(RBNode<T> *, T*) const;
	void inorder(ostream&, const RBNode<T>*) const;
	void preorder(ostream&, const RBNode<T>*) const;
	void postorder(ostream&, const RBNode<T>*) const;
	RBNode<T>* getMinValueNode(RBNode<T>*) const;
	void rightRotate(RBNode<T>*);
	void leftRotate(RBNode<T>*);
public:
	RBTree();
	RBTree(const RBTree&);
	~RBTree();
	RBTree& operator=(const RBTree&);

	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;

	void add(T*);
	void remove(T*);
	void clear();
	T* search(T*) const;

	void inorderTravesal(ostream&) const;
	void preorderTravesal(ostream&) const;
	void postorderTravesal(ostream&) const;
};



template <class T>
RBNode<T>* RBTree<T>::copyTree(RBNode<T>* src, RBNode<T>* parent)
{
	if (src->getParent() == NULL) return m_nil;
	RBNode<T>* p = new RBNode<T>(src->getData());

	RBNode<T>* pleft = copyTree(src->getLeft(), p);
	RBNode<T>* pright = copyTree(src->getRight(), p);
	
	p->setColor(src->getColor());
	p->setLeft(pleft);
	p->setRight(pright);
	p->setParent(parent);

	return p;
}
template <class T>
int RBTree<T>::getHeightHelper(RBNode<T> * r) const
{
	if (r == m_nil) return 0;
	return 1 + max(getHeightHelper(r->getLeft()), getHeightHelper(r->getRight()));
}
template <class T>
int RBTree<T>::getNumberOfNodesHelper(RBNode<T> * r) const
{
	if (r == m_nil) return 0;
	return 1 + getNumberOfNodesHelper(r->getLeft()) + getNumberOfNodesHelper(r->getRight());
}
template <class T>
void RBTree<T>::clearHelper(RBNode<T> * r)
{
	if (r != m_nil)
	{
		clearHelper(r->getLeft());
		clearHelper(r->getRight());
		delete r->getData();
		delete r;
	}
}
template <class T>
void RBTree<T>::addFixUp(RBNode<T> * x)
{
	RBNode<T>* p, *u, *g;
	while (x->getParent()->getColor() == RED)
	{
		p = x->getParent();
		g = p->getParent();

		if (p == g->getLeft())
		{
			u = g->getRight();
			if (u->getColor() == RED)
			{
				u->setColor(BLACK);
				p->setColor(BLACK);
				g->setColor(RED);
				x = g;
			}
			else
			{
				if (x == p->getRight())
				{
					//left rotate
					p->setRight(x->getLeft());
					if(x->getLeft() != m_nil) x->getLeft()->setParent(p);
					x->setParent(g);
					if (g == m_nil) m_root = x;
					else
						if (p == g->getLeft()) g->setLeft(x);
						else g->setRight(x);
					x->setLeft(p);
					p->setParent(x);

					// Doi cha thanh con, con thanh cha
					x = p;
					p = x->getParent();
				}

				p->setColor(BLACK);
				g->setColor(RED);
				
				//right rotate
				g->setLeft(p->getRight());
				if (p->getRight() != m_nil) p->getRight()->setParent(g);
				p->setParent(g->getParent());
				if (g->getParent() == m_nil) m_root = p;
				else
					if (g == g->getParent()->getRight()) g->getParent()->setRight(p);
					else g->getParent()->setLeft(p);
				p->setRight(g);
				g->setParent(p);
			}
		}
		else
		{
			u = g->getLeft();
			if (u->getColor() == RED)
			{
				u->setColor(BLACK);
				p->setColor(BLACK);
				g->setColor(RED);
				x = g;
			}
			else
			{
				if (x == p->getLeft())
				{
					//right rotate
					p->setLeft(x->getRight());
					if (x->getRight() != m_nil) x->getRight()->setParent(p);
					x->setParent(g);
					if (g == m_nil) m_root = x;
					else
						if (p == g->getRight()) g->setRight(x);
						else g->setLeft(x);
					x->setRight(p);
					p->setParent(x);

					// Doi cha thanh con, con thanh cha
					x = p;
					p = x->getParent();
				}

				p->setColor(BLACK);
				g->setColor(RED);

				//left rotate
				g->setRight(p->getLeft());
				if (p->getLeft() != m_nil) p->getLeft()->setParent(g);
				p->setParent(g->getParent());
				if (g->getParent() == m_nil) m_root = p;
				else
					if (g == g->getParent()->getLeft()) g->getParent()->setLeft(p);
					else g->getParent()->setRight(p);
				p->setLeft(g);
				g->setParent(p);
			}
		}
	}
	m_root->setColor(BLACK);
}

template <class T>
void RBTree<T>::removeFixUp(RBNode<T> *x)
{
	RBNode<T>* w, *p, *g;
	while ((x->getColor() == BLACK) && (x != m_root))
	{
		p = x->getParent();
		g = p->getParent();

		if (x == x->getParent()->getLeft())
		{
			// delete left adjust
			w = x->getParent()->getRight();
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);

				leftRotate(x->getParent());

				w = x->getParent()->getRight();
			}
			if ((w->getRight()->getColor() == BLACK) && (w->getLeft()->getColor() == BLACK))
			{
				w->setColor(RED);
				x = x->getParent();
			}
			else
			{
				if (w->getRight()->getColor() == BLACK)
				{
					w->getLeft()->setColor(BLACK);
					w->setColor(RED);

					rightRotate(w);

					w = x->getParent()->getRight();
				}
				w->setColor(x->getParent()->getColor());
				x->getParent()->setColor(BLACK);
				w->getRight()->setColor(BLACK);

				leftRotate(x->getParent());

				x = m_root;
			}
		}
		else
		{
			// delete right adjust
			w = x->getParent()->getLeft();
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);

				rightRotate(x->getParent());


				w = x->getParent()->getLeft();
			}
			if ((w->getLeft()->getColor() == BLACK) && (w->getRight()->getColor() == BLACK))
			{
				w->setColor(RED);
				x = x->getParent();
			}
			else
			{
				//	del_rightAdjust(m_root, x);
				if (w->getLeft()->getColor() == BLACK)
				{
					w->getRight()->setColor(BLACK);
					w->setColor(RED);

					leftRotate(w);

					w = x->getParent()->getLeft();
				}
				w->setColor(x->getParent()->getColor());
				x->getParent()->setColor(BLACK);
				w->getLeft()->setColor(BLACK);

				rightRotate(x->getParent());

				x = m_root;
			}
		}
	}
	x->setColor(BLACK);
}
template <class T>
T* RBTree<T>::searchHelper(RBNode<T> * r, T* key) const
{
	if (r != m_nil)
	{
		if (*r->getData() == *key) return r->getData();
		T* searched = searchHelper(r->getLeft(), key);
		if (searched == NULL) searched = searchHelper(r->getRight(), key);

		return searched;
	}
	return NULL;
}
template <class T>
void RBTree<T>::inorder(ostream& out, const RBNode<T>* r) const
{
	if (r != m_nil)
	{
		inorder(out, r->getLeft());
		out << *r->getData() << "\n";
		inorder(out, r->getRight());
	}
}
template <class T>
void RBTree<T>::preorder(ostream& out, const RBNode<T>* r) const
{
	if (r != m_nil)
	{
		out << *r->getData() << "\n";
		preorder(out, r->getLeft());
		preorder(out, r->getRight());
	}
}
template <class T>
void RBTree<T>::postorder(ostream& out, const RBNode<T>* r) const
{
	if (r != m_nil)
	{
		postorder(out, r->getLeft());
		postorder(out, r->getRight());
		out << *r->getData() << "\n";
	}
}
template <class T>
RBNode<T>* RBTree<T>::getMinValueNode(RBNode<T>* r) const
{
	if (r == NULL) throw (string) "Truy xuat ngoai vung nho!\n";

	if (r->getLeft() == m_nil) return r;
	else getMinValueNode(r->getLeft());
}
template <class T>
void RBTree<T>::leftRotate(RBNode<T>* x) {
	RBNode<T>* y = x->getRight();
	x->setRight(y->getLeft());
	if (y->getLeft() != m_nil)
		y->getLeft()->setParent(x);
	y->setParent(x->getParent());
	if (x->getParent() == m_nil)
		m_root = y;
	else
		if (x == x->getParent()->getLeft())
			x->getParent()->setLeft(y);
		else
			x->getParent()->setRight(y);
	y->setLeft(x);
	x->setParent(y);
}
template <class T>
void RBTree<T>::rightRotate(RBNode<T>* x) {
	RBNode<T>* y = x->getLeft();
	x->setLeft(y->getRight());
	if (y->getRight() != m_nil)
		y->getRight()->setParent(x);
	y->setParent(x->getParent());
	if (x->getParent() == m_nil)
		m_root = y;
	else
		if (x == x->getParent()->getRight())
			x->getParent()->setRight(y);
		else
			x->getParent()->setLeft(y);
	y->setRight(x);
	x->setParent(y);
}



template <class T>
RBTree<T>::RBTree()
{
	m_nil = new RBNode<T>(NULL);
	m_nil->setColor(BLACK);
	m_nil->setLeft(m_nil);
	m_nil->setRight(m_nil);
	m_nil->setParent(m_nil);
	m_root = m_nil;
}
template <class T>
RBTree<T>::RBTree(const RBTree& src)
{
	m_nil = new RBNode<T>(NULL);
	m_nil->setColor(BLACK);
	m_nil->setLeft(m_nil);
	m_nil->setRight(m_nil);
	m_nil->setParent(m_nil);
	m_root = m_nil;

	m_root = copyTree(src, m_nil);
}
template <class T>
RBTree<T>::~RBTree() 
{ 
	clear(); 
	delete m_nil; 
	m_nil = m_root = NULL; 
}
template <class T>
RBTree<T>& RBTree<T>::operator = (const RBTree& src)
{
	if (this != &src)
	{
		this->~RBTree();
		m_nil = new RBNode<T>(NULL);
		m_nil->setColor(BLACK);
		m_nil->setLeft(m_nil);
		m_nil->setRight(m_nil);
		m_nil->setParent(m_nil);
		m_root = m_nil;

		m_root = copyTree(src, m_nil);
	}
	return *this;
}

template <class T>
bool RBTree<T>::isEmpty() const
{
	return (m_root == m_nil);
}
template <class T>
int RBTree<T>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(m_root);
}
template <class T>
int RBTree<T>::getHeight() const
{
	return getHeightHelper(m_root);
}

template <class T>
void RBTree<T>::add(T* key)
{
	RBNode<T>* x = new RBNode<T>(key, RED, m_nil, m_nil, m_nil);

	if (m_root == m_nil)
	{
		x->setColor(BLACK);
		m_root = x;
		return;
	}
	RBNode<T>* y = m_nil, *z = m_root;
	while (z != m_nil)
	{
		y = z;
		if (*key == *z->getData())
		{
			delete key;
			return;
		}
		if (*key < *z->getData()) z = z->getLeft();
		else z = z->getRight();
	}
	x->setParent(y);
	if (*key < *y->getData()) y->setLeft(x);
	else y->setRight(x);

	addFixUp(x);
}
template <class T>
void RBTree<T>::remove(T* key)
{
	if (m_root == m_nil) return;
	
	RBNode<T>* y, *z = m_root;
	while (z != m_nil)
	{
		if (*key == *z->getData()) break;
		else
			if (*key < *z->getData()) z = z->getLeft();
			else z = z->getRight();
	}
	if (z == m_nil) return;

	// xoa cay
	y = (z->getLeft() == m_nil || z->getRight() == m_nil) ?
		z : getMinValueNode(z);
	RBNode<T>* x = (y->getLeft() == m_nil) ? y->getRight() : y->getLeft();
	x->setParent(y->getParent());
	if (y->getParent() == m_nil) m_root = x;
	else
		if (y == y->getParent()->getLeft())
			y->getParent()->setLeft(x);
		else
			y->getParent()->setRight(x);
	if (y != z)
	{
		z->setData(y->getData());
	}
	if (y->getColor() == BLACK)
		removeFixUp(x);
	delete y;
}

template <class T>
void RBTree<T>::clear()
{
	if (m_root != m_nil)
	{
		clearHelper(m_root);
		m_root = m_nil;
	}
}
template <class T>
T* RBTree<T>::search(T* key) const
{
	return searchHelper(m_root, key);
}

template <class T>
void RBTree<T>::inorderTravesal(ostream& out) const
{
	inorder(out, m_root);
	out << endl;
}
template <class T>
void RBTree<T>::preorderTravesal(ostream& out) const
{
	preorder(out, m_root);
	out << endl;
}
template <class T>
void RBTree<T>::postorderTravesal(ostream& out) const
{
	postorder(out, m_root);
	out << endl;
}