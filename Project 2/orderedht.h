#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node{
    private:
    unsigned long number;
    string caller;
    Node *next;

    public:
    Node();
    Node(unsigned long key, string callerID, Node *nextptr = nullptr);
    ~Node();

    friend class HashTable;
};

class LinkedList{
    private:
    Node *head;

    public:
    LinkedList();
    ~LinkedList();

    friend class HashTable;
};

class HashTable{
    private:
    int size = 0;
    //int numberOfElements = 0;
    vector<LinkedList> list;

    public:
    HashTable(int inputSize);
    bool insertKey(unsigned long key, string callerID);
    bool searchKey(unsigned long key);
    bool deleteKey(unsigned long key);
    void printTable(int position);
    void resize(int inputSize);
    int numOfElements(int position);
    ~HashTable();
    //string getCaller(int position);
};