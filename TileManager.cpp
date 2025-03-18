// Author: Chiko Kasongo
// Date: 17/03/2025
// Purpose: To shuffle a given image into a tile puzzle and save the shuffled images

#include "TileManager.h"
#include "PGMimage.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

// Tile Class Implementation
Tile::Tile(int w, int h) : width(w), height(h) {
    data = new unsigned char[w * h];
}

Tile::~Tile() {
    delete[] data;
}

void Tile::copyData(const unsigned char* src) { // delete
    std::memcpy(data, src, width * height);
}

// TileManager Class Implementation
TileManager::TileManager(const std::string& inputFile, int size, int moves, const std::string& outputBase)
    : gridSize(size), numMoves(moves), baseName(outputBase) {
    
    PGMimage image;
    image.read(inputFile);

    int imageWidth, imageHeight;
    image.getDims(imageWidth, imageHeight);

    tileWidth = imageWidth / gridSize;
    tileHeight = imageHeight / gridSize;

    const unsigned char* imgBuffer = image.getBuffer();

    // Initialize Board
    for (int r = 0; r < gridSize; ++r) {
        std::vector<Tile*> row;
        for (int c = 0; c < gridSize; ++c) {
            Tile* tile = new Tile(tileWidth, tileHeight);
            for (int y = 0; y < tileHeight; ++y) {
                int imgIndex = ((r * tileHeight + y) * imageWidth) + (c * tileWidth);
                std::memcpy(tile->data + (y * tileWidth), imgBuffer + imgIndex, tileWidth);
            }
            row.push_back(tile);
        }
        board.push_back(row);
    }

    // Set bottom-right tile as empty (black)
    emptyRow = gridSize - 1;
    emptyCol = gridSize - 1;
    std::fill(board[emptyRow][emptyCol]->data, board[emptyRow][emptyCol]->data + (tileWidth * tileHeight), 0);

    shuffle();
}

TileManager::~TileManager() {
    for (auto& row : board) {
        for (auto& tile : row) {
            delete tile;
        }
    }
}

void TileManager::swapTiles(int r1, int c1, int r2, int c2) {
    std::swap(board[r1][c1], board[r2][c2]);
    emptyRow = r2;
    emptyCol = c2;
}

void TileManager::makeRandomMove() {
    std::vector<std::pair<int, int>> possibleMoves;
    if (emptyRow > 0) possibleMoves.push_back({emptyRow - 1, emptyCol});
    if (emptyRow < gridSize - 1) possibleMoves.push_back({emptyRow + 1, emptyCol});
    if (emptyCol > 0) possibleMoves.push_back({emptyRow, emptyCol - 1});
    if (emptyCol < gridSize - 1) possibleMoves.push_back({emptyRow, emptyCol + 1});

    int randomIndex = rand() % possibleMoves.size();
    swapTiles(emptyRow, emptyCol, possibleMoves[randomIndex].first, possibleMoves[randomIndex].second);
}

void TileManager::saveCurrentBoard(int moveNum) const {
    PGMimage outputImage;
    int imgWidth = tileWidth * gridSize;
    int imgHeight = tileHeight * gridSize;
    unsigned char* outputBuffer = new unsigned char[imgWidth * imgHeight];

    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < gridSize; c++) {
            for (int y = 0; y < tileHeight; y++) {
                int destIndex = ((r * tileHeight + y) * imgWidth) + (c * tileWidth);
                std::memcpy(outputBuffer + destIndex, board[r][c]->data + (y * tileWidth), tileWidth);
            }
        }
    }

    outputImage.setImageData(outputBuffer, imgWidth, imgHeight);
    delete[] outputBuffer;

    std::string outputFileName = baseName + "-" + std::to_string(moveNum) + ".pgm";
    outputImage.write(outputFileName);
}

void TileManager::shuffle() {
    saveCurrentBoard(0);
    for (int i = 1; i <= numMoves; i++) {
        makeRandomMove();
        saveCurrentBoard(i);
    }
}
