#pragma once
#include<iostream>
#include <iomanip>
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
	void display();

	Node* insertNode(Node* node, int key, int value);
	Node* removeNode(Node* node, int key);

	Node* findMin(Node* node);

	Node* balance(Node* node);
	Node* rotateLeft(Node* node);
	Node* rotateRight(Node* node);

	void printTree(Node* node, int level = 0);
	void printBucketTree(Bucket* bucket);

};
