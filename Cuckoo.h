#pragma once
#include <iostream>
#include <random>
#include "Entry.h"
#include "Dictionary.h"
class Cuckoo : public Dictionary
{
private:
    Entry** table1;
    Entry** table2;
    int capacity;
    int size;
    int cycle;

    int f_hash1(int key);
    int f_hash2(int key);
    int f_hash3(int key);
    int f_hash4(int key);

    int hash1(int key);
    int hash2(int key);

    void rehash();
public:
    Cuckoo(int initialCapacity);
    Cuckoo(const Cuckoo& other);
    ~Cuckoo();

    void insert(int key, int value);
    void remove(int key);
    int getRandomKey();
    void display();
    int getSize() const;
    double getLoadFactor();
    int getCapacity() const;
};

