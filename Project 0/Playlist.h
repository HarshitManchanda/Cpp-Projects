//  ECE 250
//  Playlist.h
//
//  Purpose: Two classes PlaylistManager and Song to represent a playlist
//  storing songs. Provides services to add, play and erase a song
//
//  Created by Harshit Manchanda on 2020-01-14.
//  Copyright © 2020 Harshit Manchanda. All rights reserved.

#include <iostream>
#include <string>
using namespace std;

// Song class used for storing the song title and artist
class Song{

//class variables
private:
    string songTitle; //song title
    string songArtist; // song artist

// class functions
public:
    Song();
    void setTitleArtist(const string& title, const string& artist); // setting the values of member variables for the song
    string getTitle(); // extracting the title to display in the output file
    string getArtist(); // extracting the artist to display in the output file
};

//PlaylistManager class used for storing all the songs
class PlaylistManager{

// class variables
private:
    Song *playlist; // dynamic playlist array
    int playlistSize; // size of playlist
    int numberOfSongs = 0; // stores the number of songs in the playlist
    
// class functions
public:
    PlaylistManager(const int& size); // constructor
    ~PlaylistManager(); // destructor
    bool addSong(const string& title, const string& artist); // adding song to the playlist
    bool playSong(const int& position); // playing song from the playlist
    bool eraseSong(const int& position); // erasing a song from the playlist
    string getSongTitle(const int& position); // for outputting the title to the output file
    string getSongArtist(const int& position); // or outputting the artist to the output file
};


