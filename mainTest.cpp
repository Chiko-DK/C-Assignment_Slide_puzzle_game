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
    int imageWidth, imageHeight, tileWd, tileHt;

    image.getDims(imageWidth, imageHeight);

    //cout << "Image dimensions: " << imageWidth << " x " << imageHeight << endl;
    

    tileWd = int(float(imageWidth) / boardSize);
    tileHt = int(float(imageHeight) / boardSize);

    //cout << "Tile dimensions: " << tileWd << " x " << tileHt << endl;
    
    char ** array = new char* [boardSize];
    
    for (int i=0; i<boardSize; i++) {
    	array[i] = new char[boardSize];
    	
    	for (int j=0; j<boardSize; j++) {
    		array[i][j] = char(i*j + 1);
    	}
    }
    
	//random_shuffle(array);

    
    image.write(outImage);

    return 0;
}
