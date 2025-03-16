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
    string inImage = "mona512.pgm";
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
