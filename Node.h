#pragma once
#include<iostream>
#include"Entry.h"

using namespace std;

class Node {
public:
	Entry* entry;
	Node* right;
	Node* left;
	int height;

	Node(Entry* e) : entry(e), left(nullptr), right(nullptr), height(1) {}
	~Node() {}

  
    void printInOrder() {
        if (left != nullptr) {
            left->printInOrder();
        }
        cout << "(key:" << entry->key << ",value: " << entry->value << ") ";
        if (right != nullptr) {
            right->printInOrder();
        }
    }
};
