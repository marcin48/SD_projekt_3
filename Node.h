#pragma once
#include<iostream>
#include"Entry.h"

class Node {
public:
	Entry* entry;
	Node* right;
	Node* left;
	int height;

	Node(Entry* e) : entry(e), left(nullptr), right(nullptr), height(1) {}
	~Node() {}
};