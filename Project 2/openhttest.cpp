#include <iostream>
#include <string>
#include <vector>
#include "openht.h"

using namespace std;

int main(){
    string line, caller;
    char cmd;
    bool res;
    int m, p;
    unsigned long k;

    getline(cin, line);
    m = stoi(line.substr(line.find(" ") + 1));
    HashTable mytable(m);
    cout << "success";

    while(!cin.eof()){
        getline(cin, line);
        cmd = line[0];
        switch(cmd){
            case 'n':
                m = stoi(line.substr(line.find(" ") + 1));
                mytable.resize(m);
                cout << endl;
                cout << "success";
                break;

            case 'i':
                k = stol(line.substr(line.find(" ") + 1, 10));
                caller = line.substr(line.find(";") + 1);
                // cout << endl;
                // cout << "number : " << k << " ; caller : " << caller; 
                res = mytable.insertKey(k, caller);
                if(res == 1){
                    cout << endl;
                    cout << "success";
                }
                else{
                    cout << endl;
                    cout << "failure";
                }
                break;

            case 's':
                k = stol(line.substr(line.find(" ") + 1));
                p = mytable.searchKey(k);
                if(p != -1){
                    cout << endl;
                    cout << "found " << mytable.getCaller(p) << " in " << p;
                }
                else{
                    cout << endl;
                    cout << "not found";
                }
                break;

            case 'd':
                k = stol(line.substr(line.find(" ") + 1));
                res = mytable.deleteKey(k);
                if(res == 1){
                    cout << endl;
                    cout << "success";
                }
                else{
                    cout << endl;
                    cout << "failure";
                }
                break;
        }
    }
    cout << endl;

    return 0;
}