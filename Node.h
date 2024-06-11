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

    // Konstruktor kopiuj¹cy
    Node(const Node& other) : entry(new Entry(*other.entry)), right(nullptr), left(nullptr), height(other.height) {
        if (other.left) {
            left = new Node(*other.left);
        }
        if (other.right) {
            right = new Node(*other.right);
        }
    }

  //Funkcja pomocnicza do wizualizacji
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
