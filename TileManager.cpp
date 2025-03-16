#include "TileManager.h"
#include <fstream>
#include <sstream>
#include <cstdlib> // For rand()
#include <ctime>

Tile::Tile(int w, int h) : width(w), height(h) {
    data = new unsigned char[w * h];
}

Tile::~Tile() {
    delete[] data;
}

void Tile::copyData(const unsigned char* src) {
    for (int i = 0; i < width * height; i++) {
        data[i] = src[i];
    }
}

TileManager::TileManager(const std::string& inputFile, int size, int moves, const std::string& outputBase)
    : gridSize(size), numMoves(moves), baseName(outputBase) {

    std::ifstream ifs(inputFile, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error opening file: " << inputFile << std::endl;
        exit(1);
    }

    std::string magic;
    ifs >> magic;
    if (magic != "P5") {
        std::cerr << "Invalid PGM format.\n";
        exit(1);
    }

    int width, height, maxVal;
    ifs >> width >> height >> maxVal;
    ifs.ignore();

    unsigned char* imageData = new unsigned char[width * height];
    ifs.read(reinterpret_cast<char*>(imageData), width * height);
    ifs.close();

    tileWidth = width / gridSize;
    tileHeight = height / gridSize;

    for (int r = 0; r < gridSize; ++r) {
        std::vector<Tile*> row;
        for (int c = 0; c < gridSize; ++c) {
            Tile* tile = new Tile(tileWidth, tileHeight);
            for (int i = 0; i < tileHeight; i++) {
                int imgIndex = ((r * tileHeight + i) * width) + (c * tileWidth);
                tile->copyData(imageData + imgIndex);
            }
            row.push_back(tile);
        }
        board.push_back(row);
    }

    delete[] imageData;

    emptyRow = gridSize - 1;
    emptyCol = gridSize - 1;
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
    std::ostringstream fileName;
    fileName << baseName << "-" << moveNum << ".pgm";

    std::ofstream ofs(fileName.str(), std::ios::binary);
    if (!ofs) {
        std::cerr << "Error saving image: " << fileName.str() << std::endl;
        return;
    }

    ofs << "P5\n" << (tileWidth * gridSize) << " " << (tileHeight * gridSize) << "\n255\n";

    for (int r = 0; r < gridSize; r++) {
        for (int i = 0; i < tileHeight; i++) {
            for (int c = 0; c < gridSize; c++) {
                ofs.write(reinterpret_cast<char*>(board[r][c]->data + (i * tileWidth)), tileWidth);
            }
        }
    }
    ofs.close();
}

void TileManager::shuffle() {
    saveCurrentBoard(0);
    for (int i = 1; i <= numMoves; i++) {
        makeRandomMove();
        saveCurrentBoard(i);
    }
}
