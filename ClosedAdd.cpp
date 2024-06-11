#include"AvlTree.h"
#include"Node.h"
#include"Entry.h"
#include"ClosedAdd.h"

#include<iostream>
#include<functional>
using namespace std;

ClosedAdd::ClosedAdd(int size) : size(size), elementCounter(0) {
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

double ClosedAdd::loadFactor() const {
	return static_cast<double>(elementCounter) / size;
}

void ClosedAdd::insert(int key, int value) {
	int id = hash(key);
	buckets[id]->insert(key, value);
	elementCounter++;

	if (loadFactor() > 3.0) {
		rehash();
	}
}

void ClosedAdd::remove(int key) {
	int id = hash(key);
	buckets[id]->remove(key);
	elementCounter--;
}

void ClosedAdd::display() {
	for (int i = 0; i < size; i++) {
		cout << "Bucket " << i << ": ";
		buckets[i]->display();
		cout << endl << endl;
	}
}

Bucket* ClosedAdd::getBucket(int index) {
	if (index >= 0 && index < size && buckets[index]!=nullptr) {
		return buckets[index];
	}
	else {
		return nullptr;
	}
}

void ClosedAdd::rehash() {
	int newSize = size * 2;
	Bucket** newBuckets = new Bucket * [newSize];
	for (int i = 0; i < newSize; i++) {
		newBuckets[i] = new Bucket();
	}

	for (int i = 0; i < size; i++) {
		Node* current = buckets[i]->getRoot();
		std::function<void(Node*)> rehashNode = [&](Node* node) {
			if (node != nullptr) {
				rehashNode(node->left);
				int newId = node->entry->key % newSize;
				newBuckets[newId]->insert(node->entry->key, node->entry->value);
				rehashNode(node->right);
			}
			};
		rehashNode(current);
		delete buckets[i]; // Usuniêcie starych kube³ków
	}

	delete[] buckets; // Usuniêcie starej tablicy kube³ków

	buckets = newBuckets;
	size = newSize;
}







int ClosedAdd::getRandomKey() {
	if (elementCounter == 0) {
		return -1;  // Brak elementów w tablicy
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> bucketDis(0, size - 1);

	int randomIndex;

	do {
		randomIndex = bucketDis(gen);
	} while (buckets[randomIndex]->getRandomKeyFromBucket() == -1);

	return buckets[randomIndex]->getRandomKeyFromBucket();
}