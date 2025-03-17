#include "TileManager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -s <gridSize> -o <outputBase> -n <moves> <inputImage>\n";
        return 1;
    }

    int gridSize = std::stoi(argv[1]);
    std::string outputBase = argv[2];
    int moves = std::stoi(argv[3]);
    std::string inputImage = argv[4];

    srand(time(0));

    TileManager manager(inputImage, gridSize, moves, outputBase);

    return 0;
}
