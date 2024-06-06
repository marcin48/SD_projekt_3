#include"AvlTree.h"
#include"Node.h"
#include"Entry.h"
#include"ClosedAdd.h"

#include<iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

void driver() {

    ClosedAdd tree(40);
    int key = 0, value = 0;
    srand(time(NULL));

    for (int i = 0; i < 40; i++) {
        key = rand() % 200;
        value = rand() % 150;
        tree.insert(key, value);
    }
    tree.display();
    // Przyjmuj¹c, ¿e chcesz wydrukowaæ drzewo w pierwszym buckecie
    Bucket* firstBucket = tree.getBucket(0); // Pobranie pierwszego bucketa
    if (firstBucket != nullptr) {
        firstBucket->printBucketTree(firstBucket); // Wywo³anie printBucketTree dla pierwszego bucketa
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
        firstBucket->printBucketTree(firstBucket); // Wywo³anie printBucketTree dla pierwszego bucketa
    }
    else {
        std::cout << "Bucket is empty" << std::endl;
    }
}

using namespace std;

int main() {

   // driver_2();
    //driver;
   
   

	return 0;
}