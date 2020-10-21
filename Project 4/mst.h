//  ECE 250
//  mst.h
//
//  Purpose: Three classes Node, Set and MST to represent a weighted
//  undirected graph. The graph is represented by an adjacency matrix.
//  Provides services like insert edge, delete edge, find number of edges,
//  find the minimum spanning tree and return its weight, etc.
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Class Node to be used to create sets and stored inside the vector list in the Set class
class Node{
    // Data members
    private:
    int vertex;     // stores the vertex
    Node *next;     // next node pointer
    Node *prev;     // precious node pointer

    public:
    Node(int u, Node *n_next, Node *n_prev);    // Constructor of the class
    ~Node();                                    // Destructor of the class

    friend class Set;       // freind class declaration to use its members
};

// Struct to be used in MST class to store the edge weights and its respective vertices
struct graphEdge{
    double weight;      // weight of the edge
    int u;              // vertex u
    int v;              // vertex v
};

// Struct to be used in Set class to store the sets (nodes) in the vector list
struct nodeStruct{
    Node *head;         // pointer to the head of the set 
    Node *tail;         // pointer to the tail of the set
};

// Class Set which helps in applying Kruskal's algorithm to find mst
class Set{
    // Data member
    private:
    vector<nodeStruct> list;    // Stores the sets (nodes) in this vector

    // Fuction Definitions
    public:
    void makeSet(int n);        // function to intialise the vector by creating a node of each vertex
    void unionSet(int u, int v);    // joins two sets together
    Node *findSet(int u);           // returns the head pointer of that vertex
};

// Class MST which has all the functions related to the graph and also finds the minimum spanning tree
class MST{
    // Data members
    private:
    int n = 0;      // the number of nodes (vertices) in the graph
    int numOfEdges = 0;     // holds the number of edges in the graph
    vector<vector<double>> matrix;      // Adjacency matrix to store the edges of the graph
    vector<graphEdge> edgeWeights;      // vector stores the edge weights and corresponding vertices

    // Function Definitions
    public:
    void createGraph(int size);     // reserves the size of the matrix and initalises it
    bool insertEdge(int u, int v, double w);    // inserts an edge if the vertices are valid
    bool deleteEdge(int u, int v);      // deletes an edge if the vertices are valid
    int degree(int u);          // returns the number of vertices that vertex is connected to
    int edgeCount();        // returns the number of edges in the graph
    void clearEdges();      // clears all the edges of the graph
    double minSpanningTree();       // finds and returns the weight of minimum spanning tree
    void printMatrix();
};

class illegal_argument{};       // class to throw an exception in case of invalid argument
