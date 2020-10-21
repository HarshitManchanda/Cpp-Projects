#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "openht.h"

using namespace std;

NumCaller::NumCaller(){
    number = 0;
    caller = "";
}

NumCaller::~NumCaller(){
    number = 0;
    caller = "";
}

HashTable::HashTable(int inputSize){
    size = inputSize;
    list.reserve(size);
}

bool HashTable::insertKey(unsigned long key, string callerID){
    int h = key % size;
    int offset = int(floor(key / size)) % size;
    if(list[h].number == 0){
        list[h].number = key;
        list[h].caller = callerID;
        numberOfElements++;
        return 1;
    }
    else if(numberOfElements == size){
        return 0;
    }
    else{
        if(offset % 2 == 0){
            offset++;
        }
        while(list[h].number != 0){
            if(list[h].number == key){
                return 0;
            }
            h = (h + offset) % size;
        }

        list[h].number = key;
        list[h].caller = callerID;
        numberOfElements++;
        return 1;
    }
}

int HashTable::searchKey(unsigned long key){
    for(int i = 0 ; i < size ; i++){
        if(list[i].number == key){
            return i;
        }
    }
    return -1;
}

bool HashTable::deleteKey(unsigned long key){
    for(int i = 0 ; i < size ; i++){
        if(list[i].number == key){
            list[i].number = 0;
            list[i].caller = "";
            numberOfElements--;
            return 1;
        }
    }
    return 0;
}

void HashTable::resize(int inputSize){
    if(inputSize > size){
        size = inputSize;
        list.resize(size);
        list.reserve(size);
        list.clear();
    }
    else if(inputSize < size){
        size = inputSize;
        list.resize(size);
        list.reserve(size);
        list.shrink_to_fit();
        list.clear();
    }
    else{
        list.clear();
    }
    
}

string HashTable::getCaller(int position){
    return list[position].caller;
}

// void HashTable::print(){
//     for(int i = 0 ; i < list.capacity() ; i++){
//         cout << "number: " << list[i].number << " ; caller: " << list[i].caller << endl;
//     }

//     cout << list.size() << endl;
//     cout << list.capacity() << endl;
//     cout << endl;
// }

HashTable::~HashTable(){
    numberOfElements = 0;
    size = 0;
    list.erase(list.begin(), list.end());
    list.shrink_to_fit();
}

