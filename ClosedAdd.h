#pragma once
#include"Entry.h"
#include"Node.h"
#include"AvlTree.h"
#include"Dictionary.h"

class ClosedAdd : public Dictionary
{
private:
	int size;
	int elementCounter;
	Bucket** buckets;

public:
	ClosedAdd(int size);
	~ClosedAdd();

	// Konstruktor kopiuj�cy
	ClosedAdd(const ClosedAdd& other) : size(other.size), elementCounter(other.elementCounter) {
		buckets = new Bucket * [size];
		for (int i = 0; i < size; ++i) {
			buckets[i] = new Bucket(*other.buckets[i]);
		}
	}

	int hash(int key) const;
	void insert(int key, int value);
	void remove(int key);
	void display();
	Bucket* getBucket(int index);
	double loadFactor() const;
	void rehash();

	int getRandomKey();
};
