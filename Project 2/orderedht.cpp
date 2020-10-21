#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "orderedht.h"

using namespace std;

Node::Node(){
    number = 0;
    caller = "";
    next = nullptr;
}

Node::Node(unsigned long key, string callerID, Node *nextptr){
    number = key;
    caller = callerID;
    next = nextptr;
}

Node::~Node(){
    number = 0;
    caller = "";
    next = nullptr;
}

LinkedList::LinkedList(){
    head = nullptr;
}

LinkedList::~LinkedList(){
    head = nullptr;
}

HashTable::HashTable(int inputSize){
    size = inputSize;
    list.reserve(size);
    for(int i = 0 ; i < size ; i++){
        list[i].head = nullptr;
    }
}

bool HashTable::insertKey(unsigned long key, string callerID){
    int h = key % size;
    if(list[h].head == nullptr){
        Node *ptr = new Node(key, callerID);
        list[h].head = ptr;
        //numberOfElements++;
        return 1;
    }
    else{
        Node *temp = list[h].head;
        Node *prevNode = list[h].head;
        while(temp != nullptr){
            if(key > temp->number){
                prevNode = temp;
                temp = temp->next;
            }
            else if(key == temp->number){
                return 0;
            }
            else{
                if(temp == prevNode){
                    Node *ptr  = new Node(key, callerID, temp);
                    list[h].head = ptr;
                    return 1;
                }
                else{
                    Node *ptr = new Node(key, callerID, temp);
                    prevNode->next = ptr;
                    //numberOfElements++;
                    return 1;
                }
            }
        }
        Node *ptr = new Node(key, callerID);
        prevNode->next = ptr;
        return 1;
    }
}

bool HashTable::searchKey(unsigned long key){
    int h = key % size;
    Node *temp = list[h].head;
    while(temp != nullptr){
        if(key == temp->number){
            cout << "found " << temp->caller << " in " << h;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

bool HashTable::deleteKey(unsigned long key){
    int h = key % size;
    Node *temp = list[h].head;
    Node *prevNode = list[h].head;
    while(temp != nullptr){
        if(key == temp->number){
            if(temp == prevNode){
                list[h].head = temp->next;
                return 1;
            }
            else{
                prevNode->next = temp->next;
                return 1;
            } 
        }
        prevNode = temp;
        temp = temp->next;
    }
    return 0;
}

void HashTable::printTable(int position){
    if(list[position].head != nullptr){
        Node *temp = list[position].head;
        cout << temp->number;
        temp = temp->next;
        while(temp != nullptr){
            cout << " " << temp->number;
            temp = temp->next;
        }
    } 
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

int HashTable::numOfElements(int position){
    Node *temp = list[position].head;
    int num = 0;
    while(temp != nullptr){
        num++;
        temp = temp->next;
    }
    return num;
}

HashTable::~HashTable(){
    size = 0;
    list.erase(list.begin(), list.end());
    list.shrink_to_fit();
}