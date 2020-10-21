//  ECE 250
//  mst.cpp
//
//  Purpose: Three classes Node, Set and MST to represent a weighted
//  undirected graph. The graph is represented by an adjacency matrix.
//  Provides services like insert edge, delete edge, find number of edges,
//  find the minimum spanninf tree and return its weight, etc.
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <vector>
#include <algorithm>
#include "mst.h"

using namespace std;

// Constructor and Destructor for class Node

// Node class constructor
Node::Node(int u, Node *n_next, Node *n_prev){
    prev = n_prev;
    next = n_next;
    vertex = u;
}

// Node class destructor makes the next and prev pointers null
Node::~Node(){
    next = nullptr;
    prev = nullptr;
}

// Function definitions for class Set

// Make set function which creates a set for each vertex
void Set::makeSet(int n){
    list.resize(n);     // resizes the vector so that it can store sets for each vertex
    
    // Loop to create nodes (sets) for each vertex and assign to head and tail
    for(int i = 0 ; i < n ; i++){
        list[i].head = new Node(i, nullptr, nullptr);
        list[i].tail = list[i].head;
    }
}

// Function which joins two different sets of the vertices sent as parameter
void Set::unionSet(int u, int v){
    // Making u the smaller of the two vertices
    if(u > v){
        int temp = u;
        u = v;
        v = temp;
    }

    Node *x = findSet(u);   // finds the address of vertex u
    Node *y = findSet(v);   // finds the address of vertex v

    Node *temp = x;
    Node *prevNode;
    while(temp != nullptr){
        prevNode = temp;
        temp = temp->next;
    }

    prevNode->next = y;
    y->prev = prevNode;
    Node *temp2 = y;
    Node *prevNode2;
    while(temp2 != nullptr){
        prevNode2 = temp2;
        list[prevNode2->vertex].tail = nullptr;
        list[prevNode2->vertex].head = x;
        temp2 = temp2->next;
    }
    list[x->vertex].tail = prevNode2;

}

Node* Set::findSet(int u){
    // returns the head pointer of that vertex's set
    return list[u].head;
}

// Function definitions of the class MST

// Resizes and initialises the adjacency matrix
void MST::createGraph(int size){
    // Throw an exception if number of nodes is less than 0
    if(size <= 0){
        throw illegal_argument();
    }
    else{
        n = size;
        matrix.resize(n, vector<double>(n, 0.0));   // Initialize the matrix with value 0.0 indicating no edge
    }
}

// Inserts a new edge between the vertices if they are valid
bool MST::insertEdge(int u, int v, double w){
    // If the vertices are out of range or the weight is negative, throw an exception
    if((u >= n) || (v >= n) || (u < 0) || (v < 0) || (w <= 0.0)){
        throw illegal_argument();
    }
    // If the vertices are equal, return false
    else if(u == v){
        return false;
    }
    // Otherwise increase the number of edges if a new edge, if not, then update its weight
    else{
        if(matrix[u][v] == 0.0){
            numOfEdges++;
        }
        matrix[u][v] = w;
        matrix[v][u] = w;
        return true;
    }
}

// Deletes an edge if the vertices are valid
bool MST::deleteEdge(int u, int v){
    // throw an exception if the arguments are invalid
    if((u >= n) || (v >= n) || (u < 0) || (v < 0)){
        throw illegal_argument();
    }
    // return false if there is no edge
    else if(matrix[u][v] == 0.0){
        return false;
    }
    // Otherwise, make the values in the matrix 0.0 and decrease the number of edges
    else{
        matrix[u][v] = 0.0;
        matrix[v][u] = 0.0;
        numOfEdges--;
        return true;
    }
}

// returns the number of vertices a vertex is connected to
int MST::degree(int u){
    // Throw an exception if the argument is invalid
    if((u >= n) || (u < 0)){
        throw illegal_argument();
    }
    // Otherwise, iterate through the row of that vertex in the matrix and count how many edges it is connected to
    else{
        int deg = 0;
        for(int i = 0 ; i < n ; i++){
            if(matrix[u][i] != 0.0){
                deg++;
            }
        }
        return deg;
    }
}

// Returns the variable which stores the number of edges in the graph
int MST::edgeCount(){
    return numOfEdges;
}

// Clears the whole graph by deleting all the edges in the matrix
void MST::clearEdges(){
    // Iterate through every element of the matrix and make it 0.0
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            matrix[i][j] = 0.0;
        }
    }
    // Make the number of edges 0
    numOfEdges = 0;
}

// Calculates the minimum spanning tree of the graph and returns its weight
double MST::minSpanningTree(){
    double minWeight = 0.0;
    int flag;       // returns false if the graph is disconnected
    // Iterate through every row to check if all elements are not 0.0
    for(int i = 0 ; i < n ; i++){
        flag = 0;
        for(int j = 0 ; j < n ; j++){
            if(matrix[i][j] != 0.0){
                flag = 1;
                break;
            }
        }
    }
    // If the graph is disconnected, then return false.
    if(flag == 0){
        return -1;
    }

    // Implementation of Kruskal's algorithm

    Set S;      // create an object of class Set
    S.makeSet(n);       // Make sets of each vertex
    // Loop to get all the edge weights and their respective vertices
    for(int i = 0 ; i < n-1 ; i++){
        for(int j = i+1 ; j < n ; j++){
            if(matrix[i][j] != 0.0){
                edgeWeights.push_back({matrix[i][j], i, j});
            }
        }
    }
    // Sorting the values in the vector based on the edge weights in ascending order
    sort(edgeWeights.begin(), edgeWeights.end(), [](graphEdge a, graphEdge b) {
        return a.weight < b.weight;   
    });

    // Loop iterating through the sorted vector which checks if the edge has been added in the tree or not and takes union
    for(int i = 0 ; i < edgeWeights.size() ; i++){
        if(S.findSet(edgeWeights[i].u) != S.findSet(edgeWeights[i].v)){
            minWeight = minWeight + edgeWeights[i].weight;
            S.unionSet(edgeWeights[i].u, edgeWeights[i].v);
        }
    }

    edgeWeights.clear();    // clearing the vector
    return minWeight;   // returns the weight of the mst
}

void MST::printMatrix(){
    for(int i = 0 ; i < matrix.size() ; i++){
        for(int j = 0 ; j < matrix.size() ; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
