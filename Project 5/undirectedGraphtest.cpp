//  ECE 250
//  undirectedGraphtest.cpp
//
//  Purpose: Tester file for  class undirectedGraph
//  Invoke methods on  class read from standard input
//	and write expected output to standard output
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include "Graph.h"

using namespace std;

int main(){
    string cmd, line, substr, city;       // strings which stores the extracted command, input and stores vertices and weights
    int degree, index;                                   // integer value degree of a city
    double sdWeight, distance;                    // double values weight of shortest distance and distance between two cities

    vector<string> values;      // vector to store the city names and distances 

    undirectedGraph mygraph;        // Object of undirectedGraph class

    // Loop to get all the commands from the input file
    while(!cin.eof()){
        // get next line
        getline(cin, line);
        // extract the command
        cmd = line.substr(0, line.find(" "));

        // Conditional statements to determine which command to run
        if(cmd == "i"){
            // extract city name
            city = line.substr(line.find(" ")+1);
            index = mygraph.searchCity(city);   // get the index
            if(index == -1){    // if the city doesnt exist then insert it
                mygraph.insertNode(city);
                cout << "success" << endl;
            }
            else{
                cout << "failure" << endl;
            }
        }
        else if(cmd == "setd"){
            // get all the inputs
            stringstream ss(line.substr(line.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }
            
            // find the indices of the cities
            int index1, index2;
            index1 = mygraph.searchCity(values[0]);
            index2 = mygraph.searchCity(values[1]);
            if(index1 == -1 || index2 == -1 || stod(values[2]) <= 0.0 || values[0] == values[1]){
                cout << "failure" << endl;
            }
            else{
                mygraph.setDistance(index1, index2, stod(values[2]));
                cout << "success" << endl;
            }

            // clearing the vector
            values.clear();
        }
        else if(cmd == "s"){
            city = line.substr(line.find(" ")+1);
            index = mygraph.searchCity(city);   // search for the city
            if(index != -1){        // found if an index is returned
                cout << "found " << city << endl;
            }
            else{
                cout << "not found" << endl;
            }
        }
        else if(cmd == "degree"){
            // the city of whose degree needs to be printed
            city = line.substr(line.find(" ")+1);
            int index = mygraph.searchCity(city);
            if(index != -1){        // find degree is city is found
                degree = mygraph.degreeOfCity(index);
                cout << "degree of " << city << " " << degree << endl;
            }
            else{
                cout << "failure" << endl;
            }
        }
        else if(cmd == "graph_nodes"){
            cout << "number of nodes " << mygraph.numberOfNodes() << endl;
        }   
        else if(cmd == "graph_edges"){
            cout << "number of edges " << mygraph.numberOfEdges() << endl;
        }
        else if(cmd == "d"){
            // get the inputs
            stringstream ss(line.substr(line.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            int index1, index2;
            index1 = mygraph.searchCity(values[0]);
            index2 = mygraph.searchCity(values[1]);
            if(index1 == -1 || index2 == -1 || values[0] == values[1]){
                cout << "failure" << endl;
            }
            else{
                // prints the distance if not 0
                distance = mygraph.printDistance(index1, index2);
                if(distance != 0.0){
                    cout << "direct distance " << values[0] << " to " << values[1] << " " << distance << endl;
                }
                else{
                    cout << "failure" << endl;
                }
                
            }

            values.clear();
        }
        else if(cmd == "shortest_d"){
            // get the inputs
            stringstream ss(line.substr(line.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            // search for the indices of the cities
            int index1, index2;
            index1 = mygraph.searchCity(values[0]);
            index2 = mygraph.searchCity(values[1]);
            if(index1 == -1 || index2 == -1 || values[0] == values[1]){
                cout << "failure" << endl;
            }
            else{
                // find the distance if the inputs are valid
                sdWeight = mygraph.shortestDistance(index1, index2);
                if(sdWeight == numeric_limits<double>::infinity()){
                    cout << "failure" << endl;
                }
                else{
                    cout << "shortest distance " << values[0] << " to " << values[1] << " " << sdWeight << endl;
                }
            }
            
            values.clear();
        }
        else if(cmd == "print_path"){
            // get the inputs
            stringstream ss(line.substr(line.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            // search for the indices of the cities
            int index1, index2;
            index1 = mygraph.searchCity(values[0]);
            index2 = mygraph.searchCity(values[1]);
            if(index1 == -1 || index2 == -1 || values[0] == values[1]){
                cout << "failure" << endl;
            }
            else{
                // print the path if inputs are valid
                mygraph.printPath(index1, index2);
            }
            
            values.clear();
        }
        else if(cmd == "clear"){
            // to clear all the edges
            mygraph.clearGraph();
            cout << "success" << endl;
        }
    }
    return 0;
}