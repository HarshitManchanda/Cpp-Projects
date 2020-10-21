#include <iostream>
#include <string>
#include <vector>

using namespace std;

class NumCaller{
    private:
    unsigned long number;
    string caller;

    public:
    NumCaller();
    ~NumCaller();

    friend class HashTable;
};

class HashTable{
    private:
    int size = 0;
    int numberOfElements = 0;
    vector<NumCaller> list;

    public:
    //HashTable();
    HashTable(int inputSize);
    bool insertKey(unsigned long key, string callerID);
    int searchKey(unsigned long key);
    bool deleteKey(unsigned long key);
    void resize(int inputSize);
    string getCaller(int position);
    //void print();
    ~HashTable();

};
