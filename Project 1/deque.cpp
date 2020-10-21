//  ECE 250
//  deque.h
//
//  Purpose: Two classes Node and Deque to represent a queue made using
//  linked list data structure. Provides services to add, delete, compare a node.
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha


#include <iostream>
#include "deque.h"
using namespace std;

// Member functions for Node class
// Node constructor
Node::Node(int value, Node *prev, Node *next){
    n_prev = prev;                  // storing the address of the parameter in the next node pointer.
    n_next = next;                  // storing the address of the parameter in the previous node pointer.
    nodeValue = value;              // storing the value passed in the node
}

// Node destructor
Node::~Node(){
    n_next = nullptr;               // removing the next pointer by making it null
    n_prev = nullptr;               // removing the previous pointer by making it null
}


// Member functions for Deque class
// Deque constructor
Deque::Deque(){
    head = nullptr;                 // intialising the head and tail by making them null
    tail = nullptr;
    size = 0;                       // making the size of the list 0
}

// Function for adding node at the front of the list
void Deque::addElementFront(int value){
    // if list is empty, make head and tail point to the same node with next and prev pointers as null
    if(dequeEmpty()){
        head = new Node(value, nullptr, nullptr);
        tail = head;
    }
    // otherwise, make head point to the new node with its next pointer pointing to old header node
    else{
        Node *oldHead = head;
        head = new Node(value, nullptr, oldHead);
        oldHead->n_prev = head;
    }
    size++;
}

// Function for adding node at the back of the list
void Deque::addElementBack(int value){
    // if list is empty, make head and tail point to the same node with next and prev pointers as null
    if(dequeEmpty()){
        head = new Node(value, nullptr, nullptr);
        tail = head;
    }
    // otherwise, make tail point to the new node with its previous pointer pointing to old tail node
    else{
        Node *oldTail = tail;
        tail = new Node(value, oldTail, nullptr);
        oldTail->n_next = tail;
    }
    size++;
}

// Function to remove the node from the front
void Deque::removeElementFront(){
    // if the list is empty, then throw an exception
    if(dequeEmpty()){
        throw deque_empty();
    }
    else{
        // if size is greater than one, delete the front node and make head point to the next node
        if(size != 1){
            Node *oldHead = head;
            head = head->n_next;
            delete oldHead;
            head->n_prev = nullptr;
            size--;
        }
        // if only one node exists, delete it and make head and tail null
        else{
            Node *temp = head;
            head = nullptr;
            tail = nullptr;
            delete temp;
            size--;
        }
    }
}

// Function to remove the node from the back
void Deque::removeElementBack(){
    // if the list is empty, then throw an exception
    if(dequeEmpty()){
        throw deque_empty();
    }
    else{
        // if size is greater than one, delete the back node and make tail point to the previous node
        if(size != 1){
            Node *oldTail = tail;
            tail = tail->n_prev;
            delete oldTail;
            tail->n_next = nullptr;
            size--;
        }
        // if only one node exists, delete it and make head and tail null
        else{
            Node *temp = head;
            head = nullptr;
            tail = nullptr;
            delete temp;
            size--;
        }
    }
}

// Functions for clearing/deleting all the nodes of the linked list
void Deque::clearDeque(){
    // if not empty, then keep moving the head and go on deleting the nodes
    if(!dequeEmpty()){
        Node *temp = head;
        while(temp != nullptr){
            head = head->n_next;
            delete temp;
            temp = head;
            size--;
        }
        tail = nullptr;         // finally make the tail null
    }
}

// Function for comparing the value passed as a parameter with the front node's value
void Deque::compareElementFront(int compareValue){
    // throw an exception if deque is empty or the values aren't equal
    if((dequeEmpty()) || (head->nodeValue != compareValue)){
        throw deque_empty();
    }
}

// Function for comparing the value passed as a parameter with the back node's value
void Deque::compareElementBack(int compareValue){
    if((dequeEmpty()) || (tail->nodeValue != compareValue)){
        throw deque_empty();
    }
}

// Function to check if the deque is empty or not
bool Deque::dequeEmpty(){
    return (size == 0);
}

// Function to return the size of the deque linked list
int Deque::dequeSize(){
    return size;
}

// Function to print the node values of the deque
void Deque::printDeque(){
    // if the deque is not empty, print the values from front to back and from back to front
    if(!dequeEmpty()){
        Node *ptr = head;
        cout << ptr->nodeValue;
        ptr = ptr->n_next;
        while(ptr != nullptr){
            cout << " " << ptr->nodeValue;
            ptr = ptr->n_next;
        }

        cout << endl;

        ptr = tail;
        cout << ptr->nodeValue;
        ptr = ptr->n_prev;
        while(ptr != nullptr){
            cout << " " << ptr->nodeValue;
            ptr = ptr->n_prev;
        }
    }
}

// Deque destructor
Deque::~Deque(){
    head = nullptr;             // deleting the head and tail pointers by making them null
    tail = nullptr;
}