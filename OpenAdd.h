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
    void resize2();
    int hash(int key);

public:
    OpenAdd(int capacity);
    ~OpenAdd();
    OpenAdd(const OpenAdd& other);
    void insert(int key, int value);
    void remove(int key);
    int getSize() const;
    double getLoadFactor() const;
    void display();
    int getRandomKey();
};
