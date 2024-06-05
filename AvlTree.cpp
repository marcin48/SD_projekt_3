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

Node* Bucket::balance(Node* node) {
	if (height(node->left) - height(node->right) > 1) { //oznacza ¿e lewa strona jest ciê¿sza, rotacja w prawo
		return rotateRight(node);
	}

	if (height(node->right) - height(node->left) > 1) { //oznacza ¿e prawa strona jest ciê¿sza, rotacja w lewo
		return rotateLeft(node);
	}
}