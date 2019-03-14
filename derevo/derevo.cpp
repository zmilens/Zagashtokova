#include "pch.h"
#include <iostream>

template<typename T>
class myTree {
	struct Node {
		T item;
		Node *son;
		Node *bro;

		Node(T i, Node *s = NULL, Node *b = NULL) {
			item = i;
			son = s;
			bro = b;
		}
	};
	Node *root;
public:
	myTree() {
		root = NULL;
	}
	~myTree() {
		Delete(root);
	}
	int GetHeight() {
		return GetHeight(root);
	}
	int GetNodesOnLevel(int level) {
		return GetNodesOnLevel(root, level);
	}
	void add(const T &elem) {
		add(root, elem);
	}
	void print() {
		print(root);
	}
	void printSon() {
		printSon(root);
	}
	void printBro() {
		printBro(root);
	}
private:
	void add(Node *&node, const T &elem);
	void print(Node *&node);
	void printSon(Node *&node);
	void printBro(Node *&node);
	void Delete(Node *node);
	int GetHeight(Node *node);
	int GetNodesOnLevel(Node *node, int level);
};
int main() {
	myTree<int> tree;
	int n, a;
	std::cout << "Count" << std::endl;
	std::cin >> n;
	std::cout << std::endl << "Elements" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cin >> a;
		tree.add(a);
	}
	std::cout << std::endl << "Tree" << std::endl;
	tree.print();

	system("pause");
	return 0;
}
/*template<typename R>
R maximum(R *a, int len) {
	R max = a[0];
	for (int i = 1; i < len; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;
}*/

template<typename T>
void myTree<T>::add(Node *& node, const T & item)
{
	if (node == NULL) {
		node = new Node(item);
	}
	else if (item < node->item) {
		add(node->son, item);
	}
	else {
		add(node->bro, item);
	}
}

template<typename T>
void myTree<T>::print(Node *& node)
{
	/*int k = n;
	if (node != NULL) {
		std::cout << node->item << '\n';
		if (node->bro != NULL) {
			std::cout <<'\t';
			print(node->bro);
			k = n - 1;
		}
		if (k = n - 1) {
			std::cout << '\t';
		}
		if (node->son != NULL) {
			std::cout << std::endl;
			print(node->son);
		}
	}*/
	//std::cout << "lvl1" << '\t';
	printBro();
	std::cout << std::endl;
	printSon();
}

template<typename T>
void myTree<T>::printSon(Node *& node)
{
	if (node != NULL) {
		if (node->son != NULL) {
			printBro(node->son);
		}
		if (node->bro != NULL) {
			printSon(node->bro);
		}
		else std::cout << std::endl;
		printSon(node->son);
	}
}

template<typename T>
void myTree<T>::printBro(Node *& node)
{
	if (node != NULL) {
		std::cout << node->item << '\t';
		if (node->bro != NULL) {
			printBro(node->bro);
		}
		else std::cout << '\t';
	}
}

template<typename T>
void myTree<T>::Delete(Node * node)
{
	if (node) {
		Delete(node->son);
		Delete(node->bro);
		delete node;
	}
}

template<typename T>
int myTree<T>::GetHeight(Node * node)
{
	if (node == NULL)
		return 0;
	int max = 0;
	for (Node *current = node->son; current; current = current->bro) {
		int curHeight = GetHeight(current);
		if (curHeight > max)
			max = curHeight;
	}
	return max + 1;
}

template<typename T>
int myTree<T>::GetNodesOnLevel(Node * node, int level)
{
	if (node == NULL)
		return 0;
	if (level <= 0)
		return 0;

	return GetNodesOnLevel(node->son, level - 1) +
		(level == 1) +
		GetNodesOnLevel(node->bro, level);
}
