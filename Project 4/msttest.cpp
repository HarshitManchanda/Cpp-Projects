//  ECE 250
//  msttest.cpp
//
//  Purpose: Tester file for MST class
//  Invoke methods on MST class read from standard
//	input and write expected output to standard output
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <sstream>
#include <vector>
#include "mst.h"

using namespace std;

int main(){
    string cmd, line, substr;       // strings which stores the extracted command, input and stores vertices and weights
    int u, m, degree, edge_count;   // integer values which hold the vertex, number of nodes, degree of a node and number of edges
    double mstWeight;       // stores the weight of mst
    bool result;        // stores the return values of the functions

    vector<string> values;      // vector to store the vertices and weights

    MST mygraph;        // Object of MST class
    getline(cin, line);     // extracts the first command which will be n
    m = stoi(line.substr(line.find(" ") + 1));      // get the number of nodes
    // Try and catch block to catch the exception if thrown
    try{
        mygraph.createGraph(m);     // create a graph for that size
        cout << "success" << endl;
    }
    catch(illegal_argument){
        cout << "failure" << endl;
        exit(0);
    }

    // Loop to get all the commands from the input file
    while(!cin.eof()){
        // get nect line
        getline(cin, line);
        // extract the command
        cmd = line.substr(0, line.find(" "));

        // Conditional statements to determine which command to run
        if(cmd == "i"){
            // extracts the valuable information from the input like vertices and weight separated by commas
            stringstream ss(line.substr(line.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            // Try catch block
            try{
                // Calls the insert edge function and stores the return value in result
                result = mygraph.insertEdge(stoi(values[0]), stoi(values[1]), stod(values[2]));
                if(result == 1){
                    cout << "success" << endl;
                }
                else{
                    cout << "failure" << endl;
                }
            }
            catch(illegal_argument){
                cout << "failure" << endl;
            }

            // clearing the vector
            values.clear();
        }
        else if(cmd == "d"){
            // exctracting vertices to find the edge to be deleted
            stringstream ss(line.substr(line.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            try{
                // Calls the delete edge function and stores the return value in result
                result = mygraph.deleteEdge(stoi(values[0]), stoi(values[1]));
                if(result == 1){
                    cout << "success" << endl;
                }
                else{
                    cout << "failure" << endl;
                }
            }
            catch(illegal_argument){
                cout << "failure" << endl;
            }

            // clearing the vector
            values.clear();
        }
        else if(cmd == "degree"){
            // the vertex of whose degree needs to be printed
            u = stoi(line.substr(line.find(" ")+1));
            try{
                // if the degree exists, store it in the int degree
                degree = mygraph.degree(u);
                cout << "degree of " << u << " is " << degree << endl;
            }
            catch(illegal_argument){
                cout << "failure" << endl;
            }
        }   
        else if(cmd == "edge_count"){
            // prints the result returned by the edge count function
            edge_count = mygraph.edgeCount();
            cout << "edge count is " << edge_count << endl;
        }
        else if(cmd == "clear"){
            // to clear all the edges
            mygraph.clearEdges();
            cout << "success" << endl;
        }
        else if(cmd == "mst"){
            // gets the mst value by calling the min spanning tree function
            mstWeight = mygraph.minSpanningTree();
            // if the value is not -1, then graph is connected and print the value
            if(mstWeight != -1){
                cout << "mst " << mstWeight << endl;
            }
            else{
                cout << "not connected" << endl;
            }
        }
        else if(cmd == "print"){
            mygraph.printMatrix();
        }
    }
    return 0;
}