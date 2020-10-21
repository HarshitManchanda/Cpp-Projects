//  ECE 250
//  Graph.h
//
//  Purpose: Three classes Node, PriorityQueue and undirectedGraph to represent a weighted
//  undirected graph. The graph is represented by an adjacency matrix.
//  Provides services like insert edge, set distance, print edge, find number of edges,
//  find the shortest distance between two nodes and return its weight, etc.
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <vector>

using namespace std;

// Class Node used to create a linked list to store the adjacent vertices of a vertex
class Node{
    private:
    Node *next;     // next node pointer
    int position;       // Node index

    public:
    Node(int pos, Node *next_value);        // Constructor

    friend class undirectedGraph;       // friend class declaration
};

// Struct used for creating a vector of type linked list
struct List{
    Node *head;     // head pointer
    Node *tail;     // tail pointer
};

// Struct to store all the values in the priority queue
struct vertexValues{
    int node;
    double distance;
    int parent;
};

// Priority queue class to help find the shortest distance and path
class PriorityQueue{
    private:
    vector<vertexValues> queue;     // vector of type struct vertexValues
    int size;

    public:
    vertexValues extractMin();      // extracts the minimum from the queue
    int searchPosition(int vertex);     // searches for the position at which the vertex exists in the queue

    friend class undirectedGraph;
};

class undirectedGraph{
    private:
    int nodes = 0;      // number of nodes
    int edges = 0;      // number of edges
    vector<string> cities;      // stores the name of the cities and helps in identifying the index of that vertex
    vector<vector<double>> matrix;      // stores the edgeweights
    vector<List> list;          // stores the adjacent vertices of a vertex
    vector<vertexValues> S;     // Stores the shortest distance of every vertex from a source

    public:
    void insertNode(string city);       // inderts a node in the graph
    void setDistance(int pos1, int pos2, double distance);      // sets the edge distance
    int searchCity(string city);        // searches if a city exists or not
    int degreeOfCity(int pos);          // returns the degree of a city
    int numberOfNodes();        // returns th number of nodes
    int numberOfEdges();        // returns the number of edges
    double printDistance(int pos1, int pos2);       // prints the edge weight between two cities
    double shortestDistance(int pos1, int pos2);        // find the SD between two cities
    void printPath(int pos1, int pos2);         // prints the shortest path between two cities
    void clearGraph();      // clears the graph
    ~undirectedGraph();
};