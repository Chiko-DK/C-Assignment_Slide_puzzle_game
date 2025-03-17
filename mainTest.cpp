// copyright, Patrick Marais
// Department of Computer Science
// University of Cape Town
// (c) 2025

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "PGMimage.h"

using namespace std;

void createTilePuzzle(int gridSize, PGMimage& image, const string& outputFile) {
    int imageWidth, imageHeight, tileWd, tileHt;

    image.getDims(imageWidth, imageHeight);

    tileWd = int(float(imageWidth) / gridSize);
    tileHt = int(float(imageHeight) / gridSize);
    int numTiles = gridSize * gridSize;

    // Create an array of pointers to store tile data
    unsigned char** tiles = new unsigned char*[numTiles];
    int* tileIndices = new int[numTiles];

    // Extract tiles into dynamic memory
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            int tileIndex = row * gridSize + col;
            tileIndices[tileIndex] = tileIndex;

            tiles[tileIndex] = new unsigned char[tileWd * tileHt];

            for (int y = 0; y < tileHt; ++y) {
                for (int x = 0; x < tileWd; ++x) {
                    int srcIndex = (row * tileHt + y) * imageWidth + (col * tileWd + x);
                    tiles[tileIndex][y * tileWd + x] = image.getBuffer()[srcIndex];
                }
            }
        }
    }

    // Shuffle tiles (except for the last one, which remains empty)
    // srand(time(0));
    // random_shuffle(tileIndices, tileIndices + numTiles - 1);

    // Create new image data
    unsigned char* newData = new unsigned char[imageWidth * imageHeight];


    // Ensure last tile is black
    int lastTileIndex = numTiles - 1;
    tileIndices[lastTileIndex] = lastTileIndex; // Ensure last tile stays in its position
    std::fill(tiles[lastTileIndex], tiles[lastTileIndex] + (tileWd * tileHt), 0); // Set to black

    // Reconstruct image from shuffled tiles
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            int shuffledIndex = tileIndices[row * gridSize + col];
            unsigned char* tile = tiles[shuffledIndex];

            for (int y = 0; y < tileHt; ++y) {
                for (int x = 0; x < tileWd; ++x) {
                    int destIndex = (row * tileHt + y) * imageWidth + (col * tileWd + x);
                    newData[destIndex] = tile[y * tileWd + x];
                }
            }
        }
    }

    // Set new image data
    image.setImageData(newData, imageWidth, imageHeight);

    // Save shuffled image
    image.write(outputFile);

    // Clean up dynamic memory
    delete[] newData;
    for (int i = 0; i < numTiles; ++i) {
        delete[] tiles[i];
    }
    delete[] tiles;
    delete[] tileIndices;
}

int main(int argc, char* argv[])
{
    // check command line args: note a basic check - should be more robust, assumes all args are correct

    // Uncomment this later************************************
    // if (argc != 4)
    // {
    //     cerr << "Found " << argc - 1 << " arguments; expected 3\n";
    //     return 1;
    // }

    // // grid size
    // int boardSize = atoi(argv[1]);

    // // input image and output image names
    // string inImage = argv[2];
    // string outImage  = argv[3];
    // Just for faster stuff*************************************

    int boardSize = 3;
    string inImage = "raytrace.pgm";
    string outImage = "output.pgm";

    cout << "Parameters:\n";
    cout << " - board size: " << boardSize << endl;
    cout << " - input image: " << inImage << endl;
    cout << " - output image: " << outImage << endl;

    // read in initial image.

    PGMimage image; 
    
    //Try stuff
    //cout << "You are here!!!" << endl;
    //cout << image.getBuffer() << endl;


    // note - the destructor will remove  the internal storage on heap when this variable leaves scope at end of main. DO NOT DELETE THE POINTER TO IMAGE STORAGE 
    // if needed, make a copy
    //cout << image.getBuffer() << endl; why it doesn't print anything?

    image.read(inImage);
    // cout << "Next is here!!!" << endl;

    // work out tiles size
    // int imageWidth, imageHeight, tileWd, tileHt;

    // image.getDims(imageWidth, imageHeight);

    // cout << "Image dimensions: " << imageWidth << " x " << imageHeight << endl;
    

    // tileWd = int(float(imageWidth) / boardSize);
    // tileHt = int(float(imageHeight) / boardSize);

    // cout << "Tile dimensions: " << tileWd << " x " << tileHt << endl;
    
    // // char ** array = new char* [boardSize];
    
    // // for (int i=0; i<boardSize; i++) {
    // // 	array[i] = new char[boardSize];
    	
    // // 	for (int j=0; j<boardSize; j++) {
    // // 		array[i][j] = char(i*j + 1);
    // // 	}
    // // }
    
	// //random_shuffle(array);

    
    // image.write(outImage);

    createTilePuzzle(boardSize, image, outImage);

    return 0;
}



// #include "TileManager.h"
// #include "PGMimage.h"
// #include <cstdlib>
// #include <ctime>
// #include <cstring>

// Tile::Tile(int w, int h) : width(w), height(h) {
//     data = new unsigned char[w * h];
// }

// Tile::~Tile() {
//     delete[] data;
// }

// void Tile::copyData(const unsigned char* src) {
//     for (int i = 0; i < width * height; i++) {
//         data[i] = src[i];
//     }
// }

// TileManager::TileManager(const std::string& inputFile, int size, int moves, const std::string& outputBase)
//     : gridSize(size), numMoves(moves), baseName(outputBase) {
    
//     PGMimage image;
//     image.read(inputFile);

//     std::cout << tileWidth << std::endl; // 0
    
//     int imageWidth, imageHeight;
//     image.getDims(imageWidth, imageHeight);

//     //std::cout << tileWidth << " and" << tileHeight << " eheheh "<< std::endl; // 512/3=170.666

//     tileWidth = imageWidth / gridSize;
//     tileHeight = imageHeight / gridSize;
//     int numTiles = gridSize * gridSize;

//     std::cout << tileWidth << " and" << tileHeight << std::endl; // 170

//     // const unsigned char* imgBuffer = image.getBuffer();
//     // for (int r = 0; r < gridSize; ++r) {
//     //     std::vector<Tile*> row;
//     //     for (int c = 0; c < gridSize; ++c) {
//     //         Tile* tile = new Tile(tileWidth, tileHeight);
//     //         for (int i = 0; i < tileHeight; i++) {
//     //             int imgIndex = ((r * tileHeight + i) * image.getWidth()) + (c * tileWidth);
//     //             tile->copyData(imgBuffer + imgIndex);
//     //         }
//     //         row.push_back(tile);
//     //     }
//     //     board.push_back(row);
//     // }

//     // emptyRow = gridSize - 1;
//     // emptyCol = gridSize - 1;

//     // Create an array of pointers to store tile data
//     unsigned char** tiles = new unsigned char*[numTiles];
//     int* tileIndices = new int[numTiles];

//     // Extract tiles into dynamic memory
//     for (int row = 0; row < gridSize; ++row) {
//         for (int col = 0; col < gridSize; ++col) {
//             int tileIndex = row * gridSize + col;
//             tileIndices[tileIndex] = tileIndex;

//             tiles[tileIndex] = new unsigned char[tileWidth * tileHeight];

//             for (int y = 0; y < tileHeight; ++y) {
//                 for (int x = 0; x < tileWidth; ++x) {
//                     int srcIndex = (row * tileHeight + y) * image.getWidth() + (col * tileWidth + x);
//                     tiles[tileIndex][y * tileWidth + x] = image.getBuffer()[srcIndex];
//                 }
//             }
//         }
//     }

//     // Create new image data
//     unsigned char* newData = new unsigned char[image.getWidth() * image.getHeight()];


//     // Ensure last tile is black
//     int lastTileIndex = numTiles - 1;
//     tileIndices[lastTileIndex] = lastTileIndex; // Ensure last tile stays in its position
//     std::fill(tiles[lastTileIndex], tiles[lastTileIndex] + (tileWidth * tileHeight), 0); // Set to black

//     for (int row = 0; row < gridSize; ++row) {
//         for (int col = 0; col < gridSize; ++col) {
//             int shuffledIndex = tileIndices[row * gridSize + col];
//             unsigned char* tile = tiles[shuffledIndex];

//             for (int y = 0; y < tileHeight; ++y) {
//                 for (int x = 0; x < tileWidth; ++x) {
//                     int destIndex = (row * tileHeight + y) * image.getWidth() + (col * tileWidth + x);
//                     newData[destIndex] = tile[y * tileWidth + x];
//                 }
//             }
//         }
//     }

//     // Set new image data
//     //image.setImageData(newData, image.getWidth(), image.getHeight());

//     //image.write(outputBase + "-0.pgm");

//     // Clean up dynamic memory
//     // delete[] newData;
//     // for (int i = 0; i < numTiles; ++i) {
//     //     delete[] tiles[i];
//     // }
//     // delete[] tiles;
//     // delete[] tileIndices;

//     shuffle();
// }

// TileManager::~TileManager() {
//     for (auto& row : board) {
//         for (auto& tile : row) {
//             delete tile;
//         }
//     }
// }

// void TileManager::swapTiles(int r1, int c1, int r2, int c2) {
//     std::swap(board[r1][c1], board[r2][c2]);
//     emptyRow = r2;
//     emptyCol = c2;
// }

// void TileManager::makeRandomMove() {
//     std::vector<std::pair<int, int>> possibleMoves;
//     if (emptyRow > 0) possibleMoves.push_back({emptyRow - 1, emptyCol});
//     if (emptyRow < gridSize - 1) possibleMoves.push_back({emptyRow + 1, emptyCol});
//     if (emptyCol > 0) possibleMoves.push_back({emptyRow, emptyCol - 1});
//     if (emptyCol < gridSize - 1) possibleMoves.push_back({emptyRow, emptyCol + 1});

//     int randomIndex = rand() % possibleMoves.size();
//     swapTiles(emptyRow, emptyCol, possibleMoves[randomIndex].first, possibleMoves[randomIndex].second);
// }

// void TileManager::saveCurrentBoard(int moveNum) const {
//     PGMimage outputImage;
//     int imgWidth = tileWidth * gridSize;
//     int imgHeight = tileHeight * gridSize;
//     unsigned char* outputBuffer = new unsigned char[imgWidth * imgHeight];

//     for (int r = 0; r < gridSize; r++) {
//         for (int i = 0; i < tileHeight; i++) {
//             for (int c = 0; c < gridSize; c++) {
//                 int destIndex = ((r * tileHeight + i) * imgWidth) + (c * tileWidth);
//                 std::memcpy(outputBuffer + destIndex, board[r][c]->data + (i * tileWidth), tileWidth);
//             }
//         }
//     }
//     outputImage.setImageData(outputBuffer, imgWidth, imgHeight);
//     delete[] outputBuffer;

//     outputImage.write(baseName + "-" + std::to_string(moveNum) + ".pgm");
// }

// void TileManager::shuffle() {
//     saveCurrentBoard(0);
//     for (int i = 1; i <= numMoves; i++) {
//         makeRandomMove();
//         saveCurrentBoard(i);
//     }
// }


