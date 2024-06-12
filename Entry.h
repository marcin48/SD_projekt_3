#pragma once
class Entry {
public:
    int key;
    int value;

    Entry(int k, int v) : key(k), value(v) {}

    // Konstruktor kopiuj¹cy
    Entry(const Entry& other) : key(other.key), value(other.value) {}
};
