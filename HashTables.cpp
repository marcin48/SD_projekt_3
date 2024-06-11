#include <iostream>
#include <conio.h> 
#include <random> 
#include <fstream> 
#include <chrono>
#include <ctime>

#include "OpenAdd.h"
#include "Cuckoo.h"
#include "ClosedAdd.h"


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
    ClosedAdd closeadd(10);
    Dictionary* dictionary = nullptr;
    cout << "Choose hash table:" << endl;
    cout << "1. Open Addresing" << endl;
    cout << "2. Balanced BST" << endl;
    cout << "3. Cuckoo hashing" << endl;

    cin >> choice;
    system("cls");
    switch (choice) {
    case 1:
        dictionary = &openadd;
        break;
    case 2:
        dictionary = &closeadd;
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

    load("1mln_3.txt", dictionary, n);
    dictionary->display();

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
    //run();
    Dictionary* dictionary{};
    /*long int czas = 0;
    OpenAdd openadd(10);
    Cuckoo cuckoo(10);
    
    dictionary = &openadd;
    int n = 200000;
    load("1mln_1.txt",dictionary,n);*/




    //BADANIA

    int final_time1[15], final_time2[15], final_time3[15];

    for (int x = 20000; x <= 200000; x = x + 20000) {
        ClosedAdd openadd1(10), openadd2(10), openadd3(10);
        dictionary = &openadd1;
        load("1mln_1.txt", dictionary, x);
        dictionary = &openadd2;
        load("1mln_2.txt", dictionary, x);
        dictionary = &openadd3;
        load("1mln_3.txt", dictionary, x);
        chrono::time_point<chrono::steady_clock> t1, t2;
        double czasy1[10], czasy2[10], czasy3[10];
        double czas1 = 0, czas2 = 0, czas3 = 0;

        for (int i = 0; i < 10; i++)
        {
            ClosedAdd* copy = new ClosedAdd(openadd1);
            dictionary = copy;

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, INT_MAX);
           // int key = dictionary->getRandomKey();
            srand(time(nullptr));
            t1 = chrono::steady_clock::now();
            dictionary->insert(dis(gen), dis(gen));
            t2 = chrono::steady_clock::now();
            czasy1[i] = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count()/10;
            czas1 = czas1 + czasy1[i];
            delete copy;
            
        }

        for (int i = 0; i < 10; i++)
        {
            ClosedAdd* copy = new ClosedAdd(openadd2);
            dictionary = copy;

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, INT_MAX);
            //int key = dictionary->getRandomKey();
            srand(time(nullptr));
            t1 = chrono::steady_clock::now();
            dictionary->insert(dis(gen), dis(gen));
            t2 = chrono::steady_clock::now();
            czasy2[i] = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() / 10;
            czas2 = czas2 + czasy2[i];
            delete copy;

        }
        for (int i = 0; i < 10; i++)
        {
            ClosedAdd* copy = new ClosedAdd(openadd3);
            dictionary = copy;

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, INT_MAX);
           // int key = dictionary->getRandomKey();
            srand(time(nullptr));
            t1 = chrono::steady_clock::now();
            dictionary->insert(dis(gen), dis(gen));
            t2 = chrono::steady_clock::now();
            czasy3[i] = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() / 10;
            czas3 = czas3 + czasy3[i];
            delete copy;

        }

        final_time1[(x / 20000) - 1] = czas1;
        final_time2[(x / 20000) - 1] = czas2;
        final_time3[(x / 20000) - 1] = czas3;

        cout << "Iteracja: " << x / 20000 << endl;

    }
    
    cout << endl << "Plik 1\n";
    for (int i = 0; i < 10; i++)
    {
        cout << final_time1[i] << endl;
    }
    cout << endl << "Plik 2\n";

    for (int i = 0; i < 10; i++)
    {
        cout << final_time2[i] << endl;
    }
    cout << endl << "Plik 3\n";
    for (int i = 0; i < 10; i++)
    {
        cout << final_time3[i] << endl;
    }

    

    
    return 0;
}



