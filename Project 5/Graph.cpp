//  ECE 250
//  Graph.cpp
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
#include <limits>
#include "Graph.h"

using namespace std;


// Node constructor
Node::Node(int pos, Node *next_value){
    next = next_value;
    position = pos;
}

// Extracts the minimum valued struct from the queue
vertexValues PriorityQueue::extractMin(){
    double minValue = numeric_limits<double>::infinity();
    int index;

    // Finding the minimum value's index
    for(int i = 0 ; i < size ; i++){
        if(queue[i].distance < minValue){
            index = i;
            minValue = queue[i].distance;
        }
    }

    // swapping with the last element
    vertexValues temp = queue[index];
    queue[index] = queue[size-1];
    queue[size-1] = temp;

    // removing the last value and returning it
    vertexValues min = queue[size-1];
    queue.pop_back();
    size--;
    queue.resize(size);
    return min;
}

// Searched the index of a vertex in the queue
int PriorityQueue::searchPosition(int vertex){
    for(int i = 0 ; i < size ; i++){
        if(queue[i].node == vertex){
            return i;
        }
    }
}

// Inserts a new node in the graph
void undirectedGraph::insertNode(string city){
    nodes++;
    cities.push_back(city);
    matrix.resize(nodes);
    for (int i = 0 ; i < nodes ; i++){
        for (int j = 0 ; j < nodes ; j++){
            matrix[i].push_back(0.0);
        }
    }

    // adds the new vertex in the linked list
    Node *newNode = new Node(cities.size()-1, nullptr);
    list.resize(nodes);
    list[nodes-1].tail = newNode;
    list[nodes-1].head = newNode;
}

// Sets the edge weight between two vertices if it doesnt already exists
void undirectedGraph::setDistance(int pos1, int pos2, double distance){
    if(matrix[pos1][pos2] == 0.0){
        edges++;
        // Add the adjacent vertices in the linked list 
        Node *newNode1 = new Node(pos1, nullptr);
        Node *newNode2 = new Node(pos2, nullptr);
        list[pos1].tail->next = newNode2;
        list[pos1].tail = newNode2;
        list[pos2].tail->next = newNode1;
        list[pos2].tail = newNode1;
    }
    // set the distance
    matrix[pos1][pos2] = distance;
    matrix[pos2][pos1] = distance;
}

// returns the position of the city in the graph
int undirectedGraph::searchCity(string city){
    for(int i = 0 ; i < nodes ; i++){
        if(cities[i] == city){
            return i;
        }
    }
    return -1;
}

// returns the degree of a city
int undirectedGraph::degreeOfCity(int pos){
    int count = 0;
    for(int i = 0 ; i < nodes ; i++){
        if(matrix[pos][i] != 0.0){
            count++;
        }
    }
    return count;
}

// returns the total number of nodes in the graph
int undirectedGraph::numberOfNodes(){
    return nodes;
}

// returns the total number of edges in the graph
int undirectedGraph::numberOfEdges(){
    return edges;
}

// returns the edge distance
double undirectedGraph::printDistance(int pos1, int pos2){
    return matrix[pos1][pos2];
}

// Calculates the shortest distance between two cities
double undirectedGraph::shortestDistance(int pos1, int pos2){
    // create a priority queue and add all the nodes in it initialized with value infinity
    PriorityQueue Q;
    for(int i = 0 ; i < nodes ; i++){
        vertexValues vertex = {i, numeric_limits<double>::infinity(), -1};
        Q.queue.push_back(vertex);
    }

    // make the value of source as 0
    Q.queue[pos1].distance = 0.0;
    Q.size = nodes;

    // Applying Dijktsra's algorithm to calculate the shortest distance of every vertex from source
    while(Q.size != 0){
        vertexValues u = Q.extractMin();    // extract the minimum
        S.push_back(u);         // add it in the set
        for(Node *v = list[u.node].head->next ; v != nullptr ; v = v->next){    // iterate through adjacent vertices
            int index = Q.searchPosition(v->position);
            if(Q.queue[index].distance > (u.distance + matrix[u.node][v->position])){
                Q.queue[index].distance = u.distance + matrix[u.node][v->position];     // change the value if its less than the one already present
                Q.queue[index].parent = u.node;
            }
        }
    }

    // find the index of the second city in the set S
    int index = -1;
    double shortestDistance = 0.0;

    for(int i = 0 ; i < nodes ; i++){
        if(S[i].node == pos2){
            index = i;
        }
    }

    // return shortest distance
    shortestDistance = S[index].distance;
    S.clear();
    return shortestDistance;
}

// Prints the path between two cities
void undirectedGraph::printPath(int pos1, int pos2){
    // Applying Dijktsra's algorithm again
    PriorityQueue Q;
    for(int i = 0 ; i < nodes ; i++){
        vertexValues vertex = {i, numeric_limits<double>::infinity(), -1};
        Q.queue.push_back(vertex);
    }

    Q.queue[pos1].distance = 0.0;
    Q.size = nodes;

    while(Q.size != 0){
        vertexValues u = Q.extractMin();
        S.push_back(u);
        for(Node *v = list[u.node].head->next ; v != nullptr ; v = v->next){
            int index = Q.searchPosition(v->position);
            if(Q.queue[index].distance > (u.distance + matrix[u.node][v->position])){
                Q.queue[index].distance = u.distance + matrix[u.node][v->position];
                Q.queue[index].parent = u.node;
            }
        }
    }

    int index = -1;

    for(int i = 0 ; i < nodes ; i++){
        if(S[i].node == pos2){
            index = i;
        }
    }

    // Now using the parents, looping back to the source to print the path
    string path = cities[pos2];
    for(int i =  S[index].parent ; i != -1 ; i = S[index].parent){
        path = cities[i] + " " + path;
        for(int k = 0 ; k < nodes ; k++){
            if(S[k].node == i){
                index = k;
            }
        }
    }

    cout << path << endl;
    S.clear();

}

// Clears the graph and removes all the edges
void undirectedGraph::clearGraph(){
    matrix.clear();
    cities.clear();
    // Deallocating the memory of linked list
    for(int i = 0 ; i < nodes ; i++){
        Node *current = list[i].head;
        Node *next;
        while(current != nullptr){
            next = current->next;  
            free(current);  
            current = next;
        }
    }
    nodes = 0;
    edges = 0;
}

// Destructor for graph class
undirectedGraph:: ~undirectedGraph(){
    matrix.clear();
    cities.clear();
    // Deallocating the memory of linked list
    for(int i = 0 ; i < nodes ; i++){
        Node *current = list[i].head;
        Node *next;
        while(current != nullptr){
            next = current->next;  
            free(current);  
            current = next;
        }
    }
    nodes = 0;
    edges = 0;
}

