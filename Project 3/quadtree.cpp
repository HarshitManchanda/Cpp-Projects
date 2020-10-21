//  ECE 250
//  quadtree.cpp
//
//  Purpose: Two classes Node and QuadTree to represent a Quad tree made using
//  linked list data structure. Provides services to insert or search a node, 
//  print or clear the tree and find max, min and total value of some attribute.
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <string>
#include "quadtree.h"

using namespace std;

// Function Declarations for class Node

// Constuctor for Node class used when inserting the new node
Node::Node(string name, double longitude, double latitude, int population, int cost, int salary){
    cityName = name;
    x = longitude;
    y = latitude;
    p = population;
    r = cost;
    s = salary;
}

// Insert function which uses the conditions mentioned to find the direction and uses recursion until it finds an empty place to insert it
bool Node::insert(Node *city, Node *newCity){
    // Checks if a node with the same longitude and latitude doesn't already exist
    if((city->x == newCity->x) && (city->y == newCity->y)){
        return 0;
    }

    if((newCity->x >= city->x) && (newCity->y > city->y)){
        // If the node doesn't exist, insert it
        if(city->NE == nullptr){
            city->NE = newCity;
            return 1;
        }
        // Otherwise move to the it's child node to check if it is empty
        else{
            return insert(city->NE, newCity);
        }
    }
    else if((newCity->x < city->x) && (newCity->y >= city->y)){
        if(city->NW == nullptr){
            city->NW = newCity;
            return 1;
        }
        else{
            return insert(city->NW, newCity);
        }
    }
    else if((newCity->x <= city->x) && (newCity->y < city->y)){
        if(city->SW == nullptr){
            city->SW = newCity;
            return 1;
        }
        else{
            return insert(city->SW, newCity);
        }
    }
    else if((newCity->x > city->x) && (newCity->y <= city->y)){
        if(city->SE == nullptr){
            city->SE = newCity;
            return 1;
        }
        else{
            return insert(city->SE, newCity);
        }
    }
}

// Searches for the node using the same conditions to find which direction to move in recursively and returns the node's address if found
Node* Node::search(Node *city, double longitude, double latitude){
    // Returns the node if the longitude and latitude match
    if((city->x == longitude) && (city->y == latitude)){
        return city;
    }

    if((longitude >= city->x) && (latitude > city->y)){
        // If the node is null, return null, otherwise move to its child and check
        if(city->NE == nullptr){
            return nullptr;
        }
        else{
            return search(city->NE, longitude, latitude);
        }
    }
    else if((longitude < city->x) && (latitude >= city->y)){
        if(city->NW == nullptr){
            return nullptr;
        }
        else{
            return search(city->NW, longitude, latitude);
        }
    }
    else if((longitude <= city->x) && (latitude < city->y)){
        if(city->SW == nullptr){
            return nullptr;
        }
        else{
            return search(city->SW, longitude, latitude);
        }
    }
    else if((longitude > city->x) && (latitude <= city->y)){
        if(city->SE == nullptr){
            return nullptr;
        }
        else{
            return search(city->SE, longitude, latitude);
        }
    }
}

// Finds the maximum value of the given attribute using Inorder traversal
void Node::max(Node *city, int &maxValue, string attribute){
    // If the node is not null, keep traversing
    if(city != nullptr){
        max(city->NE, maxValue, attribute);
        max(city->NW, maxValue, attribute);
        // Comparing the value to check if the current node's attribute is bigger than the value already present
        if((city->p > maxValue) && (attribute == "p")){
            maxValue = city->p;
        }
        else if((city->r > maxValue) && (attribute == "r")){
            maxValue = city->r;
        }
        else if((city->s > maxValue) && (attribute == "s")){
            maxValue = city->s;
        }
        max(city->SW, maxValue, attribute);
        max(city->SE, maxValue, attribute);
    }
}

// Finds the minimum value of the given attribute using Inorder traversal
void Node::min(Node *city, int &minValue, string attribute){
    // If the node is not null, keep traversing
    if(city != nullptr){
        min(city->NE, minValue, attribute);
        min(city->NW, minValue, attribute);
        // Comparing the value to check if the current node's attribute is smaller than the value already present
        if((city->p < minValue) && (attribute == "p")){
            minValue = city->p;
        }
        else if((city->r < minValue) && (attribute == "r")){
            minValue = city->r;
        }
        else if((city->s < minValue) && (attribute == "s")){
            minValue = city->s;
        }
        min(city->SW, minValue, attribute);
        min(city->SE, minValue, attribute);
    }
}

// Calculates and returns the sum of attribute of all the nodes in the given direction using Inorder traversal
void Node::total(Node *city, int &totalValue, string attribute){
    // If the node is not null, keep traversing
    if(city != nullptr){
        total(city->NE, totalValue, attribute);
        total(city->NW, totalValue, attribute);
        // Checking for which attribute to add and adding it to the previous total
        if(attribute == "p"){
            totalValue = totalValue + city->p;
        }
        else if(attribute == "r"){
            totalValue = totalValue + city->r;
        }
        else if(attribute == "s"){
            totalValue = totalValue + city->s;
        }
        total(city->SW, totalValue, attribute);
        total(city->SE, totalValue, attribute);
    }
}

// Prints the tree using Inorder traversal (Ne, NW, Root, SW, SE)
void Node::print(Node *city){
    // Keep traversing until the node is not null
    if(city != nullptr){
        print(city->NE);
        print(city->NW);
        // Print the city_name for the last node in that direction
        cout << city->cityName << " ";
        print(city->SW);
        print(city->SE);
    }
}

// Removes all the nodes from the tree using Post-Order traversal
void Node::clear(Node *city){
    // Stop and move in the other direction if the node is null
    if(city == nullptr){
        return;
    }
    clear(city->NE);
    clear(city->NW);
    clear(city->SW);
    clear(city->SE);
    // Deleting that node and releasing memory
    free(city);
}

// Returns the city_name for the node sent as the parameter
string Node::returnCityName(Node *city){
    return city->cityName;
}

// Function Declarations for class QuadTree

// Insert function to insert a new node with the given information in the tree
bool QuadTree::insertNode(string name, double x1, double y1, int population, int cost, int salary){
    // If the tree is empty, insert the new node as root
    if(size == 0){
        root = new Node(name, x1, y1, population, cost, salary);
        size++;
        return 1;
    }
    // Otherwise, call the Node's insert function with the root and new node as its parameters
    else{
        Node *newCity = new Node(name, x1, y1, population, cost, salary);
        Node a;
        bool result;
        result = a.insert(root, newCity);
        if(result == 1){
            size++;
        }
        return result;
    }
}

// Searches for the node with the given longitude and latitude
Node* QuadTree::searchNode(double longitude, double latitude){
    // Return null if the tree is empty
    if(root == nullptr){
        return nullptr;
    }
    // Otherwise, search for the node with the given coordinates using Node's search function
    else{
        Node a;
        return a.search(root, longitude, latitude);
    }
}

// Finds the Maximum value of the attribute in the given direction of the specific node
int QuadTree::findMax(double longitude, double latitude, string d, string attr){
    // If the tree is empty, return false
    if(root == nullptr){
        return -1;
    }
    else{
        // First search for the specific node in whose direction to search for max value
        Node a;
        Node *city = a.search(root, longitude, latitude);
        Node *directionalCity;

        // Based on the direction, get the child node in that direction
        if(d == "NW"){
            directionalCity = city->NW;
        }
        else if(d == "NE"){
            directionalCity = city->NE;
        }
        else if(d == "SW"){
            directionalCity = city->SW;
        }
        else if(d == "SE"){
            directionalCity = city->SE;
        }

        // If the city does not exist or if there is no node in that direction, return false
        if((city == nullptr) || (directionalCity == nullptr)){
            return -1;
        }
        else{
            Node a;
            int maxValue;
            // Based on the attribute, let the initial max value be attribute value in the directional node
            if(attr == "p"){
                maxValue = directionalCity->p;
            }
            else if(attr == "r"){
                maxValue = directionalCity->r;
            }
            else if(attr == "s"){
                maxValue = directionalCity->s;
            }

            // Using the Node's max function, find the maximum value
            a.max(directionalCity, maxValue, attr);
            return maxValue;
        }
    }
}

// Finds the Minimum value of the attribute in the given direction of the specific node
int QuadTree::findMin(double longitude, double latitude, string d, string attr){
    // If the tree is empty, return false
    if(root == nullptr){
        return -1;
    }
    else{
        // First search for the specific node in whose direction to search for min value
        Node a;
        Node *city = a.search(root, longitude, latitude);
        Node *directionalCity;

        // Based on the direction, get the child node in that direction
        if(d == "NW"){
            directionalCity = city->NW;
        }
        else if(d == "NE"){
            directionalCity = city->NE;
        }
        else if(d == "SW"){
            directionalCity = city->SW;
        }
        else if(d == "SE"){
            directionalCity = city->SE;
        }

        // If the city does not exist or if there is no node in that direction, return false
        if((city == nullptr) || (directionalCity == nullptr)){
            return -1;
        }
        else{
            Node a;
            int minValue;
            // Based on the attribute, let the initial min value be attribute value in the directional node
            if(attr == "p"){
                minValue = directionalCity->p;
            }
            else if(attr == "r"){
                minValue = directionalCity->r;
            }
            else if(attr == "s"){
                minValue = directionalCity->s;
            }

            // Using the Node's min function, find the maximum value
            a.min(directionalCity, minValue, attr);
            return minValue;
        }
    }
}

// Finds the total value of the attributes in the given direction of the specific node
int QuadTree::findTotal(double longitude, double latitude, string d, string attr){
    // If the tree is empty, return false
    if(root == nullptr){
        return -1;
    }
    else{
        // First search for the specific node in whose direction to search for the total value
        Node a;
        Node *city = a.search(root, longitude, latitude);
        Node *directionalCity;

        // Based on the direction, get the child node in that direction
        if(d == "NW"){
            directionalCity = city->NW;
        }
        else if(d == "NE"){
            directionalCity = city->NE;
        }
        else if(d == "SW"){
            directionalCity = city->SW;
        }
        else if(d == "SE"){
            directionalCity = city->SE;
        }

        // If the city does not exist or if there is no node in that direction, return false
        if((city == nullptr) || (directionalCity == nullptr)){
            return -1;
        }
        else{
            Node a;
            int totalValue = 0;

            // Using the Node's total function, find the total value
            a.total(directionalCity, totalValue, attr);
            return totalValue;
        }
    }
}

// Prints the tree using the Node's print function by sending the root
void QuadTree::printTree(){
    Node a;
    a.print(root);
}

// Deletes all the nodes in the tree and changes the size to be 0
void QuadTree::clearTree(){
    // End if the tree is empty
    if(root == nullptr){
        return;
    }
    Node a;
    a.clear(root);
    root = nullptr;
    size = 0;
}

// Returns the size of the tree
int QuadTree::treeSize(){
    return size;
}

// Deletes the tree and frees dynamically allocated memory by calling clear function
QuadTree::~QuadTree(){
    if(root != nullptr){
        Node a;
        a.clear(root);
        root = nullptr;
    }
}