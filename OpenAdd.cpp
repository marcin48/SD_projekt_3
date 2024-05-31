#include "OpenAdd.h"

using namespace std;

// konstruktor
OpenAdd::OpenAdd(int capacity) : capacity(capacity), size(0) {
    table = new Entry * [capacity];
    for (int i = 0; i < capacity; i++) { // pusta tablica
        table[i] = nullptr;
    }
}

// konstruktor kopiujacy
OpenAdd::OpenAdd(const OpenAdd& other) : capacity(other.capacity), size(other.size) { 

    table = new Entry * [capacity];
  
    for (int i = 0; i < capacity; i++) {
        if (other.table[i] != nullptr) {
            table[i] = new Entry(other.table[i]->key, other.table[i]->value);
        }
        else {
            table[i] = nullptr;
        }
    }
}

// destruktor
OpenAdd::~OpenAdd() {
    for (int i = 0; i < capacity; ++i) {
        delete table[i];
    }
    delete[] table;
}

// funkcja hashujaca
int OpenAdd::hash(int key) {
    return key % capacity;
}

void OpenAdd::resize() {
    int newCapacity = capacity * 2;
    Entry** newTable = new Entry * [newCapacity];
    for (int i = 0; i < newCapacity; i++) { // czyszczenie tablicy
        newTable[i] = nullptr;
    }

    for (int i = 0; i < capacity; i++) { // przenoszenie danych ze starej tablicy
        if (table[i] != nullptr) {
            int index = hash(table[i]->key);
            while (newTable[index] != nullptr) {
                index = (index + 1) % newCapacity;
            }
            newTable[index] = table[i];
        }
    }

    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

// wstawianie wpisu
void OpenAdd::insert(int key, int value) {
    if (getLoadFactor() > 0.6) { // zwiekszanie capacity, by nie wystepowalo tyle kolizji
        resize();
    }

    int index = hash(key);
    while (table[index] != nullptr && table[index]->key != key) { // szuka dopoki nie znajdzie pustego miejsca, albo takiego samego klucza
        index = (index + 1) % capacity;
    }
    if (table[index] != nullptr && table[index]->key == key) { // zamienia wartoœæ znalezionego klucza na nowa
        table[index]->value = value;
    }
    else { // wstawia nowy wpis 
        table[index] = new Entry(key, value);
        size++;
    }
}

// wyszukiwanie
int OpenAdd::search(int key) {
    int index = hash(key);
    while (table[index] != nullptr && table[index]->key != key) { // szuka odpowiedniego klucza
        index = (index + 1) % capacity; // (nie moze byc index += index)
    }
    if (table[index] != nullptr && table[index]->key == key) { // jesli znajdzie odpowiedni klucz zwraca wartosc
        return table[index]->value;
    }
    return -1; // jesli dojdzie do nullptr i nie znajdzie klucza zwraca -1
}

// usuwanie
void OpenAdd::remove(int key) {
    int index = hash(key);
    while (table[index] != nullptr && table[index]->key != key) { // szuka pasujacego klucza
        index = (index + 1) % capacity;
    }
    if (table[index] != nullptr && table[index]->key == key) { // jesli znajdzie pasujacy klucz usuwa dany index 
        delete table[index];
        table[index] = nullptr;
        size--;
    }
}

// gettersy
int OpenAdd::getSize() const {
    return size;
}
double OpenAdd::getLoadFactor() const{
    return (double)size / (double)capacity;
}

// wyswietlanie do debugowania
void OpenAdd::display() {
    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr) {
            //cout << capacity<<" "<< getLoadFactor()<<" "<< getRandomKey()<< "  ";
            cout << "Key: " << table[i]->key <<", Hash: "<<hash(table[i]->key)<< ", Value: " << table[i]->value << endl;
        }
    }
}

// random key do testowania remove
int OpenAdd::getRandomKey() {
    if (size == 0) {
        return -1;
    }

    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(0, capacity - 1); // zakres losowania 0 - capacity-1

    int randomIndex = dis(gen);

    while (table[randomIndex] == nullptr) {
        randomIndex = (randomIndex + 1) % capacity;
    }

    return table[randomIndex]->key;
}