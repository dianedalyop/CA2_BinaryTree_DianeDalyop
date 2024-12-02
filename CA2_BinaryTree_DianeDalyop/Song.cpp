#include "Song.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Song> parseCSV(const std::string& filename) {
    std::vector<Song> songtracks;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return songtracks;
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Song songtrack;

        std::getline(ss, songtrack.song, ',');
        std::getline(ss, songtrack.artist, ',');
        std::getline(ss, songtrack.genre, ',');
        std::getline(ss, field, ',');
        songtrack.downloads = std::stoi(field);
        std::getline(ss, songtrack.awards, ',');
        std::getline(ss, field, ',');
        songtrack.streams = std::stoi(field);

        songtracks.push_back(songtrack);
    }

    file.close();
    return songtracks;
}
