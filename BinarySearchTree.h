#ifndef BST
#define BST

#include <iostream>
const int PRE_ORDER = 0;
const int IN_ORDER = 1;
const int POST_ORDER = 2;
using namespace std;

template <typename T>
class Node {
	template <typename T>
	friend class BinarySearchTree;
public:
	Node(const T & data);
private:
	T data;
	Node<T> *leftChild;
	Node<T> *rightChild;
};

template <typename T>
class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();
	bool insert(const T & data);
	int remove(const T & data);
	T & get(const T & data);
	void traversal(const int order, ostream & stream) const;
private:
	Node<T> *root;
	bool isRemoved;
	void init();
	bool insert(Node<T> *current, const T & data);
	Node<T> *remove(Node<T> *current, const T &data);
	Node<T> *findNode(Node<T> *current, const T & data) const;
	Node<T> *findMaxNode(Node<T> *current) const;
	void preorderTraversal(Node<T> *current, ostream & stream) const;
	void inorderTraversal(Node<T> *current, ostream & stream) const;
	void postorderTraversal(Node<T> *current, ostream & stream) const;
	void destroyNode(Node<T> *current);
};

template <typename T>
Node<T>::Node(const T & data) {
	this->data = data;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
	init();
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	destroyNode(root);
}

template <typename T>
bool BinarySearchTree<T>::insert(const T & data) {
	if (root == NULL) {
		root = new Node<T>(data);
		return true;
	}
	else {
		return insert(root, data);
	}
}

template <typename T>
int BinarySearchTree<T>::remove(const T & data) {
	isRemoved = true;

	if (root == NULL) {
		return false;
	}

	if (data < root->data) {
		remove(root->leftChild, data);
	}
	else if (data > root->data) {
		remove(root->rightChild, data);
	}
	else if(data == root->data) {
		remove(root, data);
	}

	return isRemoved;
}

template <typename T>
T & BinarySearchTree<T>::get(const T & data) {
	Node<T> *target = findNode(root, data);
	return target->data;
}

template <typename T>
Node<T> *BinarySearchTree<T>::findNode(Node<T> *current, const T & data) const {
	if (data == current->data) {
		return current;
	}
	else if (data < current->data) {
		return findNode(current->leftChild, data);
	}
	else if (data > current->data) {
		return findNode(current->rightChild, data);
	}

	return NULL;
}

template <typename T>
Node<T> *BinarySearchTree<T>::findMaxNode(Node<T> *current) const {
	if (current->rightChild == NULL) {
		return current;
	}
	else {
		return findMaxNode(current->rightChild);
	}
}

template <typename T>
void BinarySearchTree<T>::traversal(const int order, ostream & stream) const {
	if (order == PRE_ORDER) {
		preorderTraversal(root, stream);
	}
	else if (order == IN_ORDER) {
		inorderTraversal(root, stream);
	}
	else if (order == POST_ORDER) {
		postorderTraversal(root, stream);
	}
}

template <typename T>
void BinarySearchTree<T>::init() {
	root = NULL;
	isRemoved = false;
}

template <typename T>
bool BinarySearchTree<T>::insert(Node<T> *current, const T & data) {
	if (data < current->data) {
		if (current->leftChild == NULL) {
			current->leftChild = new Node<T>(data);
		}
		else {
			return insert(current->leftChild, data);
		}
	}
	else if (data > current->data) {
		if (current->rightChild == NULL) {
			current->rightChild = new Node<T>(data);
		}
		else {
			return insert(current->rightChild, data);
		}
	}
	else if(data == current->data) {
		return false;
	}
}

template <typename T>
Node<T> *BinarySearchTree<T>::remove(Node<T> *current, const T & data) {
	if (current == NULL) {
		isRemoved = false;
		return NULL;
	}

	if (data < current->data) {
		current->leftChild = remove(current->leftChild, data);
	}
	else if (data > current->data) {
		current->rightChild = remove(current->rightChild, data);
	}
	else if (data == current->data) {
		if (current->leftChild != NULL && current->rightChild != NULL) {
			Node<T> *maxNode = findMaxNode(current->leftChild);

			current->data = maxNode->data;
			current->leftChild = remove(current->leftChild, maxNode->data);
		}
		else if (current->leftChild != NULL && current->rightChild == NULL) {
			Node<T> *temp = current;

			current = current->leftChild;
			delete temp;
		}
		else if (current->leftChild == NULL && current->rightChild != NULL) {
			Node<T> *temp = current;
			
			current = current->rightChild;
			delete temp;
		}
		else {
			delete current;
			current = NULL;
		}
	}

	return current;
}

template <typename T>
void BinarySearchTree<T>::preorderTraversal(Node<T> *current, ostream & stream) const {
	if (current != NULL) {
		stream << current->data << " ";
		preorderTraversal(current->leftChild, stream);
		preorderTraversal(current->rightChild, stream);
	}
}

template <typename T>
void BinarySearchTree<T>::inorderTraversal(Node<T> *current, ostream & stream) const {
	if (current != NULL) {
		inorderTraversal(current->leftChild, stream);
		stream << current->data << " ";
		inorderTraversal(current->rightChild, stream);
	}
}

template <typename T>
void BinarySearchTree<T>::postorderTraversal(Node<T> *current, ostream & stream) const {
	if (current != NULL) {
		postorderTraversal(current->leftChild, stream);
		postorderTraversal(current->rightChild, stream);
		stream << current->data << " ";
	}
}

template <typename T>
void BinarySearchTree<T>::destroyNode(Node<T> *current) {
	if (current != NULL) {
		destroyNode(current->leftChild);
		destroyNode(current->rightChild);
		delete current;
	}
}

void main() {
Node 
}
#endif