//  ECE 250
//  qttest.cpp
//
//  Purpose: Tester file for QuadTree class
//  Invoke methods on QuadTree class read from standard
//	input and write expected output to standard output
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "quadtree.h"

using namespace std;

int main(){
    string inputLine, command, substr;      // strings which stores the input, extracted command and stores each piece of city_info
    int max, min, total;                    // integers storing max, min and total values
    bool result;                            // stores the return value of fucntions

    vector<string> values;                  // vector storing key information from the input
    QuadTree tree;                          // Quad Tree object

    // Loop for getting the input line by line
    while(!cin.eof()){
        getline(cin, inputLine);
        command = inputLine.substr(0, inputLine.find(" "));     // Extracts the command

        // Conditional statements for executing the functions
        if(command == "i"){
            stringstream ss(inputLine.substr(inputLine.find(" ")+1));

            // Extracts and stors all the parameters in the vector
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            // Calls the function and stores the result in the result bool
            result = tree.insertNode(values[0], stod(values[1]), stod(values[2]), stoi(values[3]), stoi(values[4]), stoi(values[5]));
            
            if(result == 1){
                cout << "success" << endl;
            }
            else{
                cout << "failure" << endl;
            }

            // Clears all the values in the vector
            values.clear();

        }
        else if(command == "s"){
            stringstream ss(inputLine.substr(inputLine.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            // temp pointer stores the address of the pointer being searched for
            Node *temp;
            temp = tree.searchNode(stod(values[0]), stod(values[1]));

            if(temp != nullptr){
                cout << "found" << " " << temp->returnCityName(temp) << endl;
            }
            else{
                cout << "not found" << endl;
            }

            values.clear();

        }
        else if(command == "q_max"){
            stringstream ss(inputLine.substr(inputLine.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            max = tree.findMax(stod(values[0]), stod(values[1]), values[2], values[3]);

            if(max != -1){
                cout << "max " << max << endl;
            }
            else{
                cout << "failure" << endl;
            }

            values.clear();

        }
        else if(command == "q_min"){
            stringstream ss(inputLine.substr(inputLine.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            min = tree.findMin(stod(values[0]), stod(values[1]), values[2], values[3]);

            if(min != -1){
                cout << "min " << min << endl;
            }
            else{
                cout << "failure" << endl;
            }

            values.clear();

        }
        else if(command == "q_total"){
            stringstream ss(inputLine.substr(inputLine.find(" ")+1));
            while(ss.good()){
                getline(ss, substr, ';');
                values.push_back(substr);
            }

            total = tree.findTotal(stod(values[0]), stod(values[1]), values[2], values[3]);

            if(total != -1){
                cout << "total " << total << endl;
            }
            else{
                cout << "failure" << endl;
            }

            values.clear();

        }
        else if(command == "print"){
            if(tree.treeSize() != 0){
                tree.printTree();
                cout << endl;
            }
        }
        else if(command == "clear"){
            tree.clearTree();
            cout << "success" << endl;
        }
        else if(command == "size"){
            cout << "tree size " << tree.treeSize() << endl;
        }
    }
    return 0;
}