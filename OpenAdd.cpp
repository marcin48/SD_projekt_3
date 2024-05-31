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
    int oldCapacity = capacity;
    capacity = newCapacity;
    Entry** newTable = new Entry * [newCapacity];
    for (int i = 0; i < newCapacity; i++) { // czyszczenie tablicy
        newTable[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; i++) { // przenoszenie danych ze starej tablicy
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
void OpenAdd::resize2() {
    int newCapacity = capacity/2;
    int oldCapacity = capacity;
    capacity = newCapacity;
    Entry** newTable = new Entry * [newCapacity];
    for (int i = 0; i < newCapacity; i++) { // czyszczenie tablicy
        newTable[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; i++) { // przenoszenie danych ze starej tablicy
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
    while (table[index] != nullptr /*0 gdy nullptr*/ && table[index]->key != key) { // szuka dopoki nie znajdzie pustego miejsca, albo takiego samego klucza
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

// usuwanie
void OpenAdd::remove(int key) {
    if (key == -1)
        return;
    int index = hash(key),attempts=0;

    if (table[index] != nullptr) {
        if (table[index]->key == key) {
            delete table[index];
            table[index] = nullptr;
            size--;

           // cout << endl << "1Delete " << key << " index " << index << endl;
        }
        else {
            while (table[index]->key != key)
            {
                index = (index + 1) % capacity;
                while (table[index] == nullptr) {
                    index = (index + 1) % capacity;
                   // cout << index << endl;
                  //  cout << "szukam bo index table jest puste" << endl;
                }
                //cout << index << endl;
                //cout << "szukam bo klucz sie nie zgadza" << endl;
            }
           // cout << endl << "5Usuwam " << key << " o indeksie " << index << endl;
            delete table[index];
            table[index] = nullptr;
            size--;
        }
    }
    else {
        while (table[index] == nullptr) {
            index = (index + 1) % capacity;
            //cout << index<<endl;
           // cout << "szukam bo index table jest puste" << endl;
        }

        while (table[index]->key != key)
            {
                index = (index + 1) % capacity;
                while (table[index] == nullptr) {
                    index = (index + 1) % capacity;
                   // cout << index << endl;
                  //  cout << "szukam bo index table jest puste" << endl;
                }
                //cout << index << endl;
                //cout << "szukam bo klucz sie nie zgadza" << endl;
            }
       // cout << endl << "2Usuwam " << key << " o indeksie " << index << endl;
        delete table[index];
        table[index] = nullptr;
        size--;
    }
    if (getLoadFactor() < 0.25)
        resize2();
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
            cout << capacity << " " << getLoadFactor()<<" "<<getSize();
            cout << " Key: " << table[i]->key <<", Hash: "<<hash(table[i]->key)<< ", Index: "<<i<< ", Value: " << table[i]->value << endl;
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
    uniform_int_distribution<> dis(0, capacity - 1);

    int attempts = 0;
    int randomIndex;

    do {
        randomIndex = dis(gen);
        attempts++;
        if (attempts > 10*capacity) {
            return -1;
        }
    } while (table[randomIndex] == nullptr);

    //cout << "Random key selected: " << table[randomIndex]->key << " at index " << randomIndex << endl;
    return table[randomIndex]->key;
}