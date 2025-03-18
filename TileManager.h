#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <iostream>
#include <vector>
#include <string>

class Tile {
public:
    unsigned char* data;  // Store grayscale pixel data
    int width, height;

    Tile(int w, int h);
    ~Tile();
    void copyData(const unsigned char* src);
};

class TileManager {
private:
    int gridSize;
    int numMoves;
    std::string baseName;
    std::vector<std::vector<Tile*>> board; // 2D board of tile pointers
    int emptyRow, emptyCol; // Position of empty tile
    int tileWidth, tileHeight;

    void swapTiles(int r1, int c1, int r2, int c2);
    void makeRandomMove();
    void saveCurrentBoard(int moveNum) const;

public:
    TileManager(const std::string& inputFile, int size, int moves, const std::string& outputBase);
    ~TileManager();
    void shuffle();
};

#endif
