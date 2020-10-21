//  ECE 250
//  deque.h
//
//  Purpose: Two classes Node and Deque to represent a queue made using
//  linked list data structure. Provides services to add, delete, compare a node.
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>

// Node class (for creating the double linked list)
class Node{
    private:
    // data members
    int nodeValue;
    Node *n_next; // pointer storing the address of the next node
    Node *n_prev; // pointer storing the address of the previous node

    public:
    // function members
    Node(int value, Node *prev, Node *next); // constructor with parameters
    ~Node(); // destructor

    friend class Deque; // declaring the Deque class as a friend class to use Node's data members
};

// Deque class
class Deque{
    private:
    // data members
    int size = 0; // size of the linked list
    Node *head; // pointer pointing to the head of the linked list
    Node *tail; // pointer pointing to the tail of the linked list

    public:
    // function members
    Deque(); // default constructor
    void addElementFront(int value); // for adding the node with value at the front of the linked list
    void addElementBack(int value); // for adding the node with value at the back of the linked list
    void removeElementFront(); // removes the node from the front of the list 
    void removeElementBack(); // removes the node from the back of the list
    void clearDeque();  // clearing the linked list by deleting all the nodes
    void compareElementFront(int compareValue); // compares the front node's value to the input value
    void compareElementBack(int compareValue); // compares the back node's value to the input value
    bool dequeEmpty(); // checks if the list is empty or not
    int dequeSize(); // returns the current size of the deque
    void printDeque(); // prints the deque in the output file
    ~Deque(); // default destructor
};

class deque_empty{}; // class for handling exceptions