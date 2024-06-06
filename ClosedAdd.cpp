#include"AvlTree.h"
#include"Node.h"
#include"Entry.h"
#include"ClosedAdd.h"

#include<iostream>
using namespace std;

ClosedAdd::ClosedAdd(int size) {
	buckets = new Bucket * [size];
	for (int i = 0; i < size; i++) {
		buckets[i] = new Bucket();
	}
}

ClosedAdd::~ClosedAdd() {
	for (int i = 0; i < size; i++) {
		delete buckets[i];
	}
	delete[] buckets;
}

int ClosedAdd::hash(int key) const {
	return key % size;
}

void ClosedAdd::insert(int key, int value) {
	int id = hash(key);
	buckets[id]->insert(key, value);
}

void ClosedAdd::remove(int key) {
	int id = hash(key);
	buckets[id]->remove(key);
}

void ClosedAdd::display() {
	for (int i = 0; i < size; i++) {
		cout << "Bucket " << i << endl;
		Bucket* current = buckets[i];

		while()
			//skoñczyæ
	}
}