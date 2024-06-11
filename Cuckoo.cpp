#include "Cuckoo.h"

using namespace std;

Cuckoo::Cuckoo(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    cycle = 0;
    table1 = new Entry * [capacity];
    table2 = new Entry * [capacity];
    for (int i = 0; i < capacity; i++) {
        table1[i] = nullptr;
        table2[i] = nullptr;
    }
}

Cuckoo::Cuckoo(const Cuckoo& other) {
    capacity = other.capacity;
    size = other.size;
    cycle = other.cycle;

    table1 = new Entry * [capacity];
    table2 = new Entry * [capacity];

    for (int i = 0; i < capacity; i++) {
        if (other.table1[i] != nullptr) {
            table1[i] = new Entry(other.table1[i]->key, other.table1[i]->value);
        }
        else {
            table1[i] = nullptr;
        }

        if (other.table2[i] != nullptr) {
            table2[i] = new Entry(other.table2[i]->key, other.table2[i]->value);
        }
        else {
            table2[i] = nullptr;
        }
    }
}

Cuckoo::~Cuckoo() {
    delete[] table1;
    delete[] table2;
}

void Cuckoo::insert(int key, int value) {
   // cout << endl<< "Insertuje: " << key;
    if (key < 1) {
        cout << "\n Nieprawidlowy klucz";
        return;
    }
    if (getLoadFactor() > 0.5)
        rehash();

        int index1 = hash1(key);
        int index2 = hash2(key);

        if (index2 >= capacity) {
            cout << endl << index2;
            cout << endl << capacity;
        }

        // aktualizacja wartosci klucza
        if ((table1[index1] && table1[index1]->key == key)) {
            table1[index1]->value = value;
            return;
        }
        else if (table2[index2] && table2[index2]->key == key) {
                table2[index2]->value = value;
                return;
            
        }

        // wstawianie nowego elementu
        Entry* entry = new Entry(key, value);
        Entry* temp;
        int maxIterations = 10;
        int count = 0;

        while (count < maxIterations) {

            index1 = hash1(entry->key);

            if (table1[index1] == nullptr) { // jesli jest puste miejsce to wstawia 
                table1[index1] = entry;
                size++;
                return;
            }
            else {
                temp = table1[index1];
                table1[index1] = entry;
                entry = temp;

                // przenies entry do tablicy 2

                index2 = hash2(entry->key);
                if (table2[index2] == nullptr) { // jesli puste to wstaw
                    table2[index2] = entry;
                    size++;
                    return;
                }
                else { // jesli zajete, to wstawiamy i przenosimy entry do tab 1
                    temp = table2[index2];
                    table2[index2] = entry;
                    entry = temp;
                }
            }

            count++;
            if (count >= maxIterations) {
                rehash();
                count = 0;
            }
        }
}

void Cuckoo::rehash() {

   // cout <<endl<< "Rehashuje";

    if (cycle > 2)
        cycle = 0;
    else
        cycle++;

    int oldCapacity = capacity;
    capacity = 2 * capacity;
    size = 0;

    Entry** temp_table1 = table1;
    Entry** temp_table2 = table2;

    table1 = new Entry * [capacity];
    table2 = new Entry * [capacity];

    for (int i = 0; i < capacity; i++){

        table1[i] = nullptr;
        table2[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; i++) {

        if (temp_table1[i] != nullptr){

            insert(temp_table1[i]->key, temp_table1[i]->value);
        }

        if (temp_table2[i] != nullptr) {

            insert(temp_table2[i]->key, temp_table2[i]->value);
        }

    }

    delete[] temp_table1;
    delete[] temp_table2;

   // cout << endl << "Rehash zakonczony";
}

void Cuckoo::remove(int key) {
    int index1 = hash1(key);
    int index2 = hash2(key);

    if (table1[index1] != nullptr && table1[index1]->key == key) {
        delete table1[index1];
        table1[index1] = nullptr;
        size--;
        return;
    }
    else if (table2[index2] != nullptr && table2[index2]->key == key) {
        delete table2[index2];
        table2[index2] = nullptr;
        size--;
        return;
    }
}

void Cuckoo::display() {
    cout << "Table 1:" << endl;
    for (int i = 0; i < capacity; i++) {
        if (table1[i] != nullptr) {
            cout << capacity <<" "<<getLoadFactor()<< "  Index " << i << ": Key = " << table1[i]->key <<", Hash: "<<hash1(table1[i]->key) << ", Value = " << table1[i]->value << endl;
        }
    }

    cout << "Table 2:" << endl;
    for (int i = 0; i < capacity; i++) {
        if (table2[i] != nullptr) {
            cout << capacity << " " << getLoadFactor() << "  Index " << i << ": Key = " << table2[i]->key << ", Hash: " << hash2(table2[i]->key) << ", Value = " << table2[i]->value << endl;
        }
    }

    cout << endl << "Capacity: " << capacity <<endl<<"Size: "<<size<<endl<< "Load factor: " << getLoadFactor();
}

int Cuckoo::hash1(int key) {
    switch (cycle) {
    case 0:return f_hash1(key);
    case 1:return f_hash2(key);
    case 2:return f_hash3(key);
    case 3:return f_hash4(key);
    default:return f_hash1(key);
    }
}
int Cuckoo::hash2(int key) {
    switch (cycle) {
    case 0:return f_hash2(key);
    case 1:return f_hash4(key);
    case 2:return f_hash1(key);
    case 3:return f_hash1(key);
    default:return f_hash1(key);
    }

}

int Cuckoo::f_hash1(int key) {
   return key%capacity;
}
int Cuckoo::f_hash2(int key) {
    
    return (int)(key * 0.7145616) % capacity;
}
int Cuckoo::f_hash3(int key) {
    double value = key * 0.6201059;
    value = value - floor(value);
    return (int)(value * capacity);
}
int Cuckoo::f_hash4(int key) {

    return (int)(key * 0.43672) % capacity;
}

int Cuckoo::getRandomKey() {
    if (size == 0) {
        return -1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, capacity - 1);

    int randomIndex = dis(gen);
    while (table1[randomIndex] == nullptr && table2[randomIndex] == nullptr) {
        randomIndex = dis(gen);
    }

    if (table1[randomIndex] != nullptr) {
        return table1[randomIndex]->key;
    }
    else {
        return table2[randomIndex]->key;
    }
}
double Cuckoo::getLoadFactor() {
    return (double)size / (double)capacity;
}
int Cuckoo::getSize() const {
    return size;
}
int Cuckoo::getCapacity() const {
    return capacity;
}
