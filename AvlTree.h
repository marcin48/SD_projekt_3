#pragma once
#include<iostream>

#include"Entry.h"
#include"Node.h"

class Bucket {
private:
	Node* bst;
	int size;

public:
	Bucket() : bst(nullptr), size(0) {}
	~Bucket() {}
	
	void insert(int key, int value);
	void remove(int key);
	int height(Node* node);
	void updateHeight(Node* node);

	Node* insertNode(Node* node, int key, int value);
	Node* removeNode(Node* node, int key);

	Node* findMin(Node* node);

	Node* balance(Node* node);
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);

};