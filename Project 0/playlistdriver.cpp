//  ECE 250
//  playlistdriver.cpp
//
//  Purpose: Tester file for PlaylistManager class
//  Invoke methods on PlaylistManager class read from standard
//	input and write expected output to standard output
//
//  Created by Harshit Manchanda on 2020-01-14.
//  Copyright © 2020 Harshit Manchanda. All rights reserved.

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#include "Playlist.h"

int main() {
    string inputLine, title, artist; // variables storing the line from input, title of the song and artist resp.
    char command; // command extracted from the line
    getline(cin, inputLine);
    int size, positionPlay, positionErase;
    size = stoi(inputLine.substr(inputLine.find(" ")+1)); // extracting the size of the playlist
    PlaylistManager mylist(size); // playlist object
    cout << "success";

    // loop for reading the whole input file
    while(!cin.eof()){
        cout << endl;
        getline(cin, inputLine);
        command = inputLine[inputLine.find(" ")-1];
        // based on the command, that particular block would be executed
        switch(command){
            case 'i':
                bool resultAddSong;
                title = inputLine.substr(inputLine.find(" ")+1, (inputLine.find(";")-inputLine.find(" ")-1)); // extracting the song title from the input line
                artist = inputLine.substr(inputLine.find(";")+1); // extracting the song artist from the input line
                resultAddSong = mylist.addSong(title, artist); // stores the return value from the addSong function

                // based on it's value, send the output
                if(resultAddSong == 1){
                    cout << "success";
                }
                else{
                    cout << "can not insert " << title << ";" << artist;
                }
                break;

            case 'p':
                bool resultPlaySong;
                positionPlay = stoi(inputLine.substr(inputLine.find(" ")+1)); // extracting the position of the song to play from the input line
                resultPlaySong = mylist.playSong(positionPlay); // storing the return value of playSong function

                // based on it's value, send the output
                if(resultPlaySong == 1){
                    cout << "played " << positionPlay << " " << mylist.getSongTitle(positionPlay) << ";" << mylist.getSongArtist(positionPlay);
                }
                else{
                    cout << "can not play " << positionPlay;
                }
                break;

            case 'e':
                bool resultEraseSong;
                positionErase = stoi(inputLine.substr(inputLine.find(" ")+1)); // extracting the position of the song to erase from the playlist from the input line
                resultEraseSong = mylist.eraseSong(positionErase);
                if(resultEraseSong == 1){
                    cout << "success";
                }
                else{
                    cout << "can not erase " << positionErase;
                }
                break;
            
        }

    }
    return 0;
}
