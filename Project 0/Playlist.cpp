//  ECE 250
//  Playlist.cpp
//
//  Purpose: Two classes PlaylistManager and Song to represent a playlist
//  storing songs. Provides services to add, play and erase a song
//
//  Created by Harshit Manchanda on 2020-01-14.
//  Copyright © 2020 Harshit Manchanda. All rights reserved.

#include <iostream>
#include <string>
using namespace std;

#include "Playlist.h"

// Constructor for Song object
Song::Song(){
    songTitle = "";
    songArtist = "";
}

// Sets the value of song variables for the object
void Song::setTitleArtist(const string& title, const string& artist){
    songTitle = title;
    songArtist = artist;
}

// Extracts the title for that object
string Song::getTitle(){
    return songTitle;
}

// Extracts the artist for that object
string Song::getArtist(){
    return songArtist;
}

// Initializes the playlist with the size taken from the input file
PlaylistManager::PlaylistManager(const int& size){
    playlistSize = size;
    playlist = new Song[playlistSize];
}

// Checks if song is already present and adds new songs
bool PlaylistManager::addSong(const string& title, const string& artist){
    // checking if the song already exists or not by comparing the title and artist
    int stringsEqual = 0;
    for(int i = 0 ; i < numberOfSongs ; i++){
        if((playlist[i].getTitle().compare(title) == 0) && (playlist[i].getArtist().compare(artist) == 0)){
            stringsEqual = 1;
            break;
        }
    }
    if((numberOfSongs >= playlistSize) || (stringsEqual == 1)){
        return 0;
    }
    else{
        playlist[numberOfSongs].setTitleArtist(title, artist); // sets the title and artist for that song in the playlist
        numberOfSongs++;
        return 1;
    }
}

// Plays songs from the playlist
bool PlaylistManager::playSong(const int& position){
    if((position <= numberOfSongs) && (position >= 0)){
        return 1; // returns true if song exists
    }
    else{
        return 0;
    }
}

// Erases the song fromt he playlist and shifts the songs after it to the left
bool PlaylistManager::eraseSong(const int& position){
    // Shifting the songs to the left
    if((position <= numberOfSongs) && (position >= 0)){
        for(int i = position-1 ; i < numberOfSongs-1 ; i++){
            playlist[i] = playlist[i+1];
        }

        // deleting the last song
        playlist[numberOfSongs-1].setTitleArtist("", "");
        numberOfSongs--;
        return 1;
    }
    else{
        return 0;
    }
}

// Extracts song title from the song object
string PlaylistManager::getSongTitle(const int& position){
    return playlist[position-1].getTitle();
}

// Extracts song artist from the song object
string PlaylistManager::getSongArtist(const int& position){
    return playlist[position-1].getArtist();
}

// Deletes all elements of the playlist
PlaylistManager::~PlaylistManager(){
    delete[] playlist;
    playlistSize = 0;
    numberOfSongs = 0;
}
