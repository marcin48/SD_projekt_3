#include"AvlTree.h"
#include"Node.h"
#include"Entry.h"

#include <iomanip>
#include<iostream>

using namespace std;

void Bucket::insert(int key, int value) {
	bst = insertNode(bst, key, value);
	size++;
}

void Bucket::remove(int key) {
	bst = removeNode(bst, key);
	size--;
}

int Bucket::height(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	return node->height;
}

void Bucket::updateHeight(Node* node) {
	node->height = max(height(node->left), height(node->right)) + 1;
}

void Bucket::display() {
	if (bst == nullptr) {
		cout << "empty";
	}
	else {
		bst->printInOrder();
	}
}

Node* Bucket::insertNode(Node* node, int key, int value) {
	if (node == nullptr) {
		return new Node(new Entry(key, value));
	}

	if (key < node->entry->key) {
		node->left = insertNode(node->left, key, value);
	}
	else if(key>node->entry->key){
		node->right = insertNode(node->right, key, value);
	}
	else {
		node->entry->value = value;
	}

	updateHeight(node);
	return balance(node);
}

Node* Bucket::balance(Node* node) {
	if (height(node->left) - height(node->right) > 1) { //oznacza ¿e lewa strona jest ciê¿sza, rotacja w prawo

		if (height(node->left->left) >= height(node->left->right)) {

			return rotateRight(node);
		}
		else {

			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		
	}

	if (height(node->right) - height(node->left) > 1) { //oznacza ¿e prawa strona jest ciê¿sza, rotacja w lewo

		if (height(node->right->right) >= height(node->right->left)) {

			return rotateLeft(node);

		}else {

			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
		
	}
	return node;
}

Node* Bucket::rotateRight(Node* node) {
	
	Node* pivot = node->left;
	node->left = pivot->right;
	pivot->right = node;

	updateHeight(pivot);
	updateHeight(node);

	return pivot;
}

Node* Bucket::rotateLeft(Node* node) {
	
	Node* pivot = node->right;
	node->right = pivot->left;
	pivot->left = node;

	updateHeight(pivot);
	updateHeight(node);

	return pivot;
}

Node* Bucket::removeNode(Node* node, int key) {
	if (node == nullptr) {
		return nullptr;
	}

	if (key < node->entry->key) {
		node->left = removeNode(node->left, key);
	}
	else if (key > node->entry->key) {
		node->right = removeNode(node->right, key);
	}
	else {
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			return nullptr;
		}
		else if (node->left == nullptr) {
			Node* tmp = node->right;
			delete node;
			return tmp;
		}
		
		else if (node->right == nullptr) {
			Node* tmp = node->left;
			delete node;
			return tmp;
		}
		else {
			Node* tmp = findMin(node->right);
			swap(node->entry, tmp->entry);
			node->right = removeNode(node->right, tmp->entry->key);

		}
		
	}
	updateHeight(node);
	return balance(node);
}

Node* Bucket::findMin(Node* node) {
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}







void Bucket::printTree(Node* node, int level) {
	if (node != nullptr) {
		printTree(node->right, level + 1);
		cout << setw(4 * level) << ""; // Wciêcie poziome
		cout << "(" << node->entry->key << ", " << node->entry->value << ")" << endl; // Wyœwietlenie pary klucz-wartoœæ
		printTree(node->left, level + 1);
	}
}


void Bucket::printBucketTree(Bucket* bucket) {
	cout << "AVL Tree in Bucket" << endl;
	cout << "------------------" << endl;
	if (bucket->bst != nullptr) {
		printTree(bucket->bst);
	}
	else {
		cout << "Empty" << endl;
	}
	cout << endl;
}