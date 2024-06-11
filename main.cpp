#include"AvlTree.h"
#include"Node.h"
#include"Entry.h"
#include"ClosedAdd.h"

#include<iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

void driver() {

    int s = 40;
    ClosedAdd tree(s);
    int key = 0, value = 0;
    srand(time(NULL));

    for (int i = 0; i < s; i++) {
        key = rand() % 200;
        value = rand() % 150;
        tree.insert(key, value);
    }
    tree.display();

    // Losowanie klucza z tablicy
    int randomKey = tree.getRandomKey();
    if (randomKey != -1) {
        cout << "Random key selected: " << randomKey << endl;
    }
    else {
        cout << "No key found or too many attempts." << endl;
    }
    // Przyjmuj�c, �e chcesz wydrukowa� drzewo w pierwszym buckecie 

    int n;
    do {
        cout << "Call bucket at number (0 - " << s << ") :";
        cin >> n;
        
    } while (n<0 && n>s);

    cout << endl;

    Bucket* firstBucket = tree.getBucket(n); // Pobranie pierwszego bucketa
    if (firstBucket != nullptr) {
        firstBucket->printBucketTree(firstBucket); // Wywo�anie printBucketTree dla pierwszego bucketa
    }
    else {
        std::cout << "Bucket is empty" << std::endl;
    }
}

void driver_2() {
    ClosedAdd table(10);
    table.insert(5,1);
    table.insert(2,2);
    table.insert(8,3);
    table.insert(3,4);
    table.insert(15, 5);
    table.insert(25, 6); 
    table.insert(85, 12);
    table.insert(35, 7);
    table.insert(45, 8);
    
    table.insert(65, 10);
    table.insert(55, 9);
    table.insert(75, 11);
   
    table.insert(95,13);
    table.display();

    Bucket* firstBucket = table.getBucket(5); // Pobranie pierwszego bucketa
    if (firstBucket != nullptr) {
        firstBucket->printBucketTree(firstBucket); // Wywo�anie printBucketTree dla pierwszego bucketa
    }
    else {
        std::cout << "Bucket is empty" << std::endl;
    }
}

void test() {
    ClosedAdd table(10);

    for (int i = 0; i < 200; i += 5) {
        table.insert(i, i + 9);
    }

    table.display();

    Bucket* firstBucket = table.getBucket(5); // Pobranie pierwszego bucketa
    if (firstBucket != nullptr) {
        firstBucket->printBucketTree(firstBucket); // Wywo�anie printBucketTree dla pierwszego bucketa
    }
    else {
        std::cout << "Bucket is empty" << std::endl;
    }
}

using namespace std;

int main() {

    //driver_2();
    //driver();
    test();
   

	return 0;
}