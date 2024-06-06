#include"AvlTree.h"
#include"Node.h"
#include"Entry.h"

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
	node->height = max(node->left->height, node->right->height) + 1;
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

//poprawiæ funkcje balance
Node* Bucket::balance(Node* node) {
	if (height(node->left) - height(node->right) > 1) { //oznacza ¿e lewa strona jest ciê¿sza, rotacja w prawo
		return rotateRight(node);
	}

	if (height(node->right) - height(node->left) > 1) { //oznacza ¿e prawa strona jest ciê¿sza, rotacja w lewo
		return rotateLeft(node);
	}
}

Node* Bucket::rotateRight(Node* node) {
	//Napisaæ funkcjê
	Node* pivot = node->left;
	node->left = pivot->right;
	pivot->right = node;

	updateHeight(pivot);
	return pivot;
}

Node* Bucket::rotateLeft(Node* node) {
	//Napisaæ funkcjê
	Node* pivot = node->right;
	node->right = pivot->left;
	pivot->left = node;

	updateHeight(pivot);
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