#include "TileManager.h"
#include "PGMimage.h"
#include <vector>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " -s <gridSize> -o <outputBase> -n <moves> <inputImage> <summaryImage>\n";
        return 1;
    }

    int gridSize = std::stoi(argv[1]);
    std::string outputBase = argv[2];
    int moves = std::stoi(argv[3]);
    std::string inputImage = argv[4];
    string summaryImage = argv[5];
    int margin = 10; // Default margin can be changed with if


    srand(time(0));

    TileManager manager(inputImage, gridSize, moves, outputBase);

    // Load images
    vector<PGMimage> images;
    for (int i = 0; i <= moves; i++) {
        string filename = outputBase + "-" + to_string(i) + ".pgm";
        PGMimage img;
        img.read(filename);
        if (!img.isValid()) {
            cerr << "Error loading image: " << filename << endl;
            return 1;
        }
        images.push_back(img);
    }

    // Calculate optimal layout (rows & cols)
    int rows = ceil(sqrt(moves));
    int cols = ceil((double)moves / rows);

    // Image dimensions
    int tileWidth = images[0].getWidth();
    int tileHeight = images[0].getHeight();

    // Final summary image dimensions
    int finalWidth = cols * tileWidth + (cols + 1) * margin;
    int finalHeight = rows * tileHeight + (rows + 1) * margin;

    // Create a white background summary image
    PGMimage summary(finalWidth, finalHeight, 255); // 255 = white background
    cout << "Hereeeeee!!!!!!!! " << endl;
    summary.write(summaryImage);

    // Place images in grid
    for (int i = 0; i < moves; i++) {
        int row = i / cols;
        int col = i % cols;

        int x = col * tileWidth + (col + 1) * margin;
        int y = row * tileHeight + (row + 1) * margin;

        summary.embedImage(images[i], x, y);
    }

    // Save summary image
    summary.write(summaryImage);
    cout << "Summary image saved as: " << summaryImage << endl;

    return 0;
}
