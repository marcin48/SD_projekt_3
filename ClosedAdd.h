#pragma once
#include"Entry.h"
#include"Node.h"
#include"AvlTree.h"

class ClosedAdd {
private:
	int size;
	Bucket** buckets;

public:
	ClosedAdd(int size);
	~ClosedAdd();

	int hash(int key) const;
	void insert(int key, int value);
	void remove(int key);
	void display();
};