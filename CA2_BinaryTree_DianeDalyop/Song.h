#pragma once

#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>

struct Song {
    std::string song;
    std::string artist;
    std::string genre;
    int downloads;
    std::string awards;
    int streams;
};
std::vector<Song> parseCSV(const std::string& filename);

#endif