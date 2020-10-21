//  ECE 250
//  quadtree.h
//
//  Purpose: Two classes Node and QuadTree to represent a Quad tree made using
//  linked list data structure. Provides services to insert or search a node, 
//  print or clear the tree and find max, min and total value of some attribute.
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <string>

using namespace std;

// Class Node to be used to create nodes and perform actions on them in the tree
class Node{

    // Data Members
    private:
    Node *NW = nullptr;           // North West pointer
    Node *NE = nullptr;           // North East pointer
    Node *SW = nullptr;           // South West pointer
    Node *SE = nullptr;           // South East pointer
    string cityName;              // Stores city name
    double x;                     // Longitude value of the city
    double y;                     // Latitude value of the city
    int p;                        // Population of the city
    int r;                        // Cost of Living of the city
    int s;                        // Average Net Salary of the city

    // Function Definitions
    public:
    // Constructor for creating a new node
    Node(string name = "", double longitude = 0.0, double latitude = 0.0, int population = 0, int cost = 0, int salary = 0);
    bool insert(Node *city, Node *newCity);                         // Inserts the new node if it already doesn't exist
    Node* search(Node *city, double longitude, double latitude);    // Returns the Node pointer of the node being searched for
    void max(Node *city, int &maxValue, string attribute);          // Calculates the maximum value of attribute in the given direction using Inorder traversal
    void min(Node *city, int &minValue, string attribute);          // Calculates the minimum value of attribute in the given direction using Inorder traversal
    void total(Node *city, int &totalValue, string attribute);      // Calculates the sum of attributes of all nodes using Inorder traversal
    void print(Node *city);                 // Recursively prints the tree using Inorder traversal
    void clear(Node* city);                 // Recursively deletes all the nodes usinf Post-Order traversal
    string returnCityName(Node *city);      // Returns the city_name of the node (used for search function)

    friend class QuadTree;      // Declaring QuadTree class as its friend so it can access all its data members
};

// Class Quad Tree utilizes class Node
class QuadTree{

    // Data Members
    private:
    int size = 0;                 // Size of the tree 
    Node *root = nullptr;         // Pointer pointing to the root of the tree

    // Function Definitions
    public:
    bool insertNode(string name, double x1, double y1, int population, int cost, int salary);   // Creates a new node and calls the Node's insert function to insert it in the tree
    Node* searchNode(double longitude, double latitude);                        // Searches for the node with the latitude and longitude
    int findMax(double longitude, double latitude, string d, string attr);      // Finds the maximum value of attribute in the given direction
    int findMin(double longitude, double latitude, string d, string attr);      // Finds the minimum value of attribute in the given direction
    int findTotal(double longitude, double latitude, string d, string attr);    // Finds the sum of attributes in the given direction
    void printTree();           // Prints the tree using Node's print function
    void clearTree();           // Deletes the tree
    int treeSize();             // Returns the size of the tree
    ~QuadTree();                // Destructor for releasing the memory
};
