#include <iostream>
#include <conio.h> 
#include <random> 
#include <fstream> 
#include <chrono>
#include <ctime>

#include "OpenAdd.h"
#include "Cuckoo.h"

using namespace std;

void load(const string& filename, Dictionary* dictionary, int x) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file " << filename << endl;
        return;
    }

    int key, value;
    int count = 0;
    while (file >> key >> value && count < x) {
        dictionary->insert(key, value);
        count++;
    }

    file.close();
}

void run() {
    int choice = 0;
    OpenAdd openadd(10);
    Cuckoo cuckoo(10);
    Dictionary* dictionary = nullptr;
    cout << "Choose hash table:" << endl;
    cout << "1. Open Addresing" << endl;
    cout << "2. XXXXXXXXXXXXXXXXXXX" << endl;
    cout << "3. Cuckoo hashing" << endl;

    cin >> choice;
    system("cls");
    switch (choice) {
    case 1:
        dictionary = &openadd;
        break;
    case 2:
        break;
    case 3:
        dictionary = &cuckoo;
        break;
    default:
        cout << "Invalid choice!" << endl;
        return;
    }

    int n = 0;
    int x = 0;
    cout << "How many records do you want to load? ";
    cin >> n;

    load("1mln_2.txt", dictionary, n);
   // dictionary->display();
    cout << dictionary->getSize();

    cout << endl << endl << "How many do you want to remove? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        dictionary->remove(dictionary->getRandomKey());
    }
   // system("cls");
    cout << "After removing: \n";
    dictionary->display();
}

void generate_values(int count, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file " << filename << endl;
        return;
    }

    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(0, INT_MAX);

    for (int i = 0; i < count; i++) {
        int key = dis(gen);
        int value = dis(gen);
        file << key << " " << value << endl;
    }

    file.close();
}

int main(){
    //generate_values(1000000, "1mln_3.txt");
    run();
    //long int czas = 0;
    //OpenAdd openadd(10);
    //Cuckoo cuckoo(10);
    //Dictionary* dictionary{};
    //dictionary = &openadd;
    //int n = 100;
    //chrono::time_point<chrono::steady_clock> t1, t2;
    //load("1mln_2.txt",dictionary,n);
    //

    //srand(time(nullptr));
    //t1 = chrono::steady_clock::now();
    //dictionary->remove(dictionary->getRandomKey());
    //t2 = chrono::steady_clock::now();
    //czas = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    //cout << czas<<endl;
  /*  srand(time(nullptr));
    t1 = chrono::steady_clock::now();
    dictionary->insert(rand() % INT_MAX + 1,1000);
    t2 = chrono::steady_clock::now();
    czas = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

    cout << czas;*/


    /*Cuckoo cuckoo(10);
    Dictionary* dictionary{};
    dictionary = &cuckoo;
    int n = 100;
    load("1mln_2.txt", dictionary, n);
    dictionary->display();*/

    /*OpenAdd openadd(10);
    Dictionary* dictionary{};
    dictionary = &openadd;
    int n = 200;
    load("1mln_2.txt", dictionary, n);
    dictionary->display();*/
    
    return 0;
}



