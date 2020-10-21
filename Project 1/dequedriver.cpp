//  ECE 250
//  dequedriver.cpp
//
//  Purpose: Tester file for Deque class
//  Invoke methods on Deque class read from standard
//	input and write expected output to standard output
//
//  Author: Harshit Manchanda
//  Student ID: h2mancha

#include <iostream>
#include <string>
#include "deque.h"

using namespace std;

int main(){
    string inputLine, command;                  // strings which takes the input and extracts the command
    int positionSpace, i, size, counter = 2;    // integers storing the position of space in input, value 
                                                // from the input, size of deque and a counter for printing endline
    bool result;                                // for storing the return value of funciton
    Deque mydeque;                              // Deque object

    // while loop for getting lines from input file (goes till one line before the end of file)
    while(getline(cin, inputLine) && !cin.eof()){
        positionSpace = inputLine.find(" ");
        if(positionSpace == -1){
            command = inputLine;        // for storing the commands without value
        }
        // for storing commands with a value
        else{
            command = inputLine.substr(0, positionSpace);
            i = stoi(inputLine.substr(positionSpace+1));
        }

        // Conditional statements for printing endline after every line
        if((counter == 1) && (command == "print")){
            // Do nothing
        }
        else if((counter == 1) && (command != "print")){
            cout << endl;
        }
        else if (counter == 0){
            cout << endl;
        }

        // Conditional statements for executing the function 
        if(command == "enqueue_front"){
            mydeque.addElementFront(i);
            cout << "success";
        }
        else if(command == "enqueue_back"){
            mydeque.addElementBack(i);
            cout << "success";
        }
        else if(command == "dequeue_front"){
            try{
                mydeque.removeElementFront();
                cout << "success";
            }
            catch(deque_empty){
                cout << "failure";
            }
        }
        else if(command == "dequeue_back"){
            try{
                mydeque.removeElementBack();
                cout << "success";
            }
            catch(deque_empty){
                cout << "failure";
            }
        }
        else if(command == "clear"){
            mydeque.clearDeque();
            cout << "success";
        }
        else if(command == "front"){
            try{
                mydeque.compareElementFront(i);
                cout << "success";
            }
            catch(deque_empty){
                cout << "failure";
            }
        }
        else if(command == "back"){
            try{
                mydeque.compareElementBack(i);
                cout << "success";
            }
            catch(deque_empty){
                cout << "failure";
            }
        }
        else if(command == "empty"){
            result = mydeque.dequeEmpty();
            if(result == 1){
                cout << "success";
            }
            else{
                cout << "failure";
            }
        }
        else if(command == "size"){
            size = mydeque.dequeSize();
            cout << "size is " << size;
        }
        else if(command == "print"){
            mydeque.printDeque();
        }

        // changing the value of counter if deque is empty
        if(mydeque.dequeEmpty()){
            counter = 1;
        }
        else{
            counter = 0;
        }
    }

    // gets the last line from the input file
    getline(cin, inputLine);
    positionSpace = inputLine.find(" ");
    if(positionSpace == -1){
        command = inputLine;
    }
    else{
        command = inputLine.substr(0, positionSpace);
        i = stoi(inputLine.substr(positionSpace+1));
    }

    // Conditional for endline before the last line's output
    if((counter == 1) && (command != "print")){
        cout << endl;
    }
    else if(counter == 0){
        cout << endl;
    }

    // for checking which function to execute
    if(command == "enqueue_front"){
        mydeque.addElementFront(i);
        cout << "success";
    }
    else if(command == "enqueue_back"){
        mydeque.addElementBack(i);
        cout << "success";
    }
    else if(command == "dequeue_front"){
        try{
            mydeque.removeElementFront();
            cout << "success";
        }
        catch(deque_empty){
            cout << "failure";
        }
    }
    else if(command == "dequeue_back"){
        try{
            mydeque.removeElementBack();
            cout << "success";
        }
        catch(deque_empty){
            cout << "failure";
        }
    }
    else if(command == "clear"){
        mydeque.clearDeque();
        cout << "success";
    }
    else if(command == "front"){
        try{
            mydeque.compareElementFront(i);
            cout << "success";
        }
        catch(deque_empty){
            cout << "failure";
        }
    }
    else if(command == "back"){
        try{
            mydeque.compareElementBack(i);
            cout << "success";
        }
        catch(deque_empty){
            cout << "failure";
        }
    }
    else if(command == "empty"){
        result = mydeque.dequeEmpty();
            if(result == 1){
            cout << "success";
        }
        else{
            cout << "failure";
        }
    }
    else if(command == "size"){
        size = mydeque.dequeSize();
        cout << "size is " << size;
    }
    else if(command == "print"){
        mydeque.printDeque();
    }

    return 0;
}