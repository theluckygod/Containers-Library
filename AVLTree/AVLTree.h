#pragma once
#include "BNode.h"
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class AVLTree
{
private:
	BNode<T>* m_root;

private:
	BNode<T>* copyTree(BNode<T>*);
	int getHeightHelper(BNode<T> *) const;
	int getNumberOfNodesHelper(BNode<T> *) const;
	void clearHelper(BNode<T> *);
	BNode<T>* addHelper(BNode<T> *, T*, bool&);
	BNode<T>* removeHelper(BNode<T> *, T*, bool&);
	T* searchHelper(BNode<T> *, T*) const;
	BNode<T>* balanceHelper(BNode<T> * r, bool&);
	void inorder(ostream&, const BNode<T>*) const;
	void preorder(ostream&, const BNode<T>*) const;
	void postorder(ostream&, const BNode<T>*) const;
	T* getMinValueNode(const BNode<T>*) const;
public:
	AVLTree();
	AVLTree(T*);
	AVLTree(T*, const BNode<T>*, const BNode<T>*);
	AVLTree(const AVLTree&);
	~AVLTree();

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
BNode<T>* AVLTree<T>::copyTree(BNode<T>* src)
{
	if (src == NULL) return NULL;

	BNode<T>* pleft = copyTree(src->getLeft());
	BNode<T>* pright = copyTree(src->getRight());
	BNode<T>* p = new BNode<T>(src->getData(), pleft, pright);

	return p;
}
template <class T>
int AVLTree<T>::getHeightHelper(BNode<T> * r) const
{
	if (r == NULL) return 0;
	return 1 + max(getHeightHelper(r->getLeft()), getHeightHelper(r->getRight()));
}
template <class T>
int AVLTree<T>::getNumberOfNodesHelper(BNode<T> * r) const
{
	if (r == NULL) return 0;
	return 1 + getNumberOfNodesHelper(r->getLeft()) + getNumberOfNodesHelper(r->getRight());
}
template <class T>
void AVLTree<T>::clearHelper(BNode<T> * r)
{
	if (r != NULL)
	{
		clearHelper(r->getLeft());
		clearHelper(r->getRight());
		delete r->getData();
		delete r;
		r = NULL;
	}
}
template <class T>
BNode<T>* AVLTree<T>::addHelper(BNode<T> * r, T* key, bool& flag)
{
	if (r != NULL)
	{
		if (*r->getData() == *key)
		{
			return r;
		}
		if (*r->getData() > *key)
		{
			r->setLeft(addHelper(r->getLeft(), key, flag));
			if(flag == false) r = balanceHelper(r, flag);
		}
		else
		{
			r->setRight(addHelper(r->getRight(), key, flag));
			if (flag == false) r = balanceHelper(r, flag);
		}

		return r;
	}
	else
	{
		return new BNode<T>(key);
	}
}
template <class T>
BNode<T>* AVLTree<T>::removeHelper(BNode<T> *r, T* key, bool &flag)
{
	if (r == NULL) return NULL;

	if (*key < *r->getData())
	{
		r->setLeft(removeHelper(r->getLeft(), key, flag));
		r = balanceHelper(r, flag);
	}
	else
		if (*key > *r->getData())
		{
			r->setRight(removeHelper(r->getRight(), key, flag));
			r = balanceHelper(r, flag);
		}
		else
		{
			if (r->getLeft() == NULL || r->getRight() == NULL)
			{
				BNode<T>* temp = (r->getLeft()) ? r->getLeft() : r->getRight();
				if (temp == NULL)
				{
					delete r;
					return NULL;
				}
				else
				{
					r->setData(temp->getData());
					delete temp;
					r->setLeft(NULL);
					r->setRight(NULL);
					return r;
				}
			}
			else
			{
				r->setData(getMinValueNode(r->getRight()));
				r->setRight(removeHelper(r->getRight(), r->getData(), flag));
				r = balanceHelper(r, flag);
				return r;
			}
		}
}
template <class T>
T* AVLTree<T>::searchHelper(BNode<T> * r, T* key) const
{
	if (r != NULL)
	{
		if (*r->getData() == *key) return r->getData();
		T* searched = searchHelper(r->getLeft(), key);
		if (searched == NULL) searched = searchHelper(r->getRight(), key);
		
		return searched;
	}
	return NULL;
}
template <class T>
BNode<T>* AVLTree<T>::balanceHelper(BNode<T> * r, bool& flag)
{
	if (r == NULL) return NULL;
	
	int heightLeft = getHeightHelper(r->getLeft()),
		heightRight = getHeightHelper(r->getRight());
	if (heightLeft > heightRight + 1)
	{
		BNode<T>* p1 = r->getLeft();
		int heightP1Left = getHeightHelper(p1->getLeft());

		if (heightP1Left == heightLeft - 1)
		{
			r->setLeft(p1->getRight());
			p1->setRight(r);

			r = p1;
		}
		else
		{
			BNode<T>* p2 = p1->getRight();

			r->setLeft(p2->getRight());
			p2->setRight(r);
			p1->setRight(p2->getLeft());
			p2->setLeft(p1);

			r = p2;
		}

		flag = true;
	}
	else
		if (heightLeft + 1 < heightRight)
		{
			BNode<T>* p1 = r->getRight();
			int heightP1Left = getHeightHelper(p1->getLeft());

			if (heightP1Left != heightRight - 1)
			{
				r->setRight(p1->getLeft());
				p1->setLeft(r);

				r = p1;
			}
			else
			{
				BNode<T>* p2 = p1->getLeft();

				r->setRight(p2->getLeft());
				p2->setLeft(r);
				p1->setLeft(p2->getRight());
				p2->setRight(p1);

				r = p2;
			}

			flag = true;
		}

	return r;
}
template <class T>
void AVLTree<T>::inorder(ostream& out, const BNode<T>* r) const
{
	if (r)
	{
		inorder(out, r->getLeft());
		out << *r->getData() << "\n";
		inorder(out, r->getRight());
	}
}
template <class T>
void AVLTree<T>::preorder(ostream& out, const BNode<T>* r) const
{
	if (r)
	{
		out << *r->getData() << "\n";
		preorder(out, r->getLeft());
		preorder(out, r->getRight());
	}
}
template <class T>
void AVLTree<T>::postorder(ostream& out, const BNode<T>* r) const
{
	if (r)
	{
		postorder(out, r->getLeft());
		postorder(out, r->getRight());
		out << *r->getData() << "\n";
	}
}
template <class T>
T* AVLTree<T>::getMinValueNode(const BNode<T>* r) const
{
	if (r == NULL) throw (string) "Truy xuat ngoai vung nho!\n";

	if (r->getLeft() == NULL) return r->getData();
	else getMinValueNode(r->getLeft());
}



template <class T>
AVLTree<T>::AVLTree() : m_root(NULL) {}
template <class T>
AVLTree<T>::AVLTree(T* key) : m_root(new BNode<T>(key)){}
template <class T>
AVLTree<T>::AVLTree(T* data, const BNode<T>* pleft, const BNode<T>* pright) : m_root(new BNode<T>(data))
{
	m_root->m_left = copyTree(pleft);
	m_root->m_right = copyTree(pright);
}
template <class T>
AVLTree<T>::AVLTree(const AVLTree& src) : m_root(copyTree(src.m_root)){}
template <class T>
AVLTree<T>::~AVLTree() { clear(); };

template <class T>
bool AVLTree<T>::isEmpty() const
{
	if (m_root == NULL) return 1;
	return 0;
}
template <class T>
int AVLTree<T>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(m_root);
}
template <class T>
int AVLTree<T>::getHeight() const
{
	return getHeightHelper(m_root);
}

template <class T>
void AVLTree<T>::add(T* key)
{
	bool flag = false;
	m_root = addHelper(m_root, key, flag);
}
template <class T>
void AVLTree<T>::remove(T* key)
{
	bool flag = false;
	m_root = removeHelper(m_root, key, flag);
}
template <class T>
void AVLTree<T>::clear()
{
	if (m_root != NULL)
	{
		clearHelper(m_root);
		m_root = NULL;
	}
}
template <class T>
T* AVLTree<T>::search(T* key) const
{
	return searchHelper(m_root, key);
}

template <class T>
void AVLTree<T>::inorderTravesal(ostream& out) const
{
	inorder(out, m_root);
	out << endl;
}
template <class T>
void AVLTree<T>::preorderTravesal(ostream& out) const
{
	preorder(out, m_root);
	out << endl;
}
template <class T>
void AVLTree<T>::postorderTravesal(ostream& out) const
{
	postorder(out, m_root);
	out << endl;
}