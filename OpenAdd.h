#pragma once
#include <iostream>
#include <random>
#include "Entry.h"
#include "Dictionary.h"

class OpenAdd : public Dictionary
{
private:
    Entry** table; // tablica wskaznikow obiektow Entry
    int capacity;
    int size;

    void resize();
    int hash(int key);

public:
    OpenAdd(int capacity);
    ~OpenAdd();
    OpenAdd(const OpenAdd& other);
    void insert(int key, int value);
    int search(int key);
    void remove(int key);
    int getSize() const;
    double getLoadFactor() const;
    void display();
    int getRandomKey();
};
