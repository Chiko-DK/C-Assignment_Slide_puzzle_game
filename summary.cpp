#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Structure to store image data
struct PGMImage {
    int width, height, maxVal;
    vector<vector<int>> pixels;
};

// Function to read a PGM file (supports P2 and P5 formats)
PGMImage readPGM(const string &filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string magic;
    file >> magic;  // Read magic number (P2 or P5)
    
    if (magic != "P2" && magic != "P5") {
        cerr << "Unsupported PGM format: " << magic << endl;
        exit(1);
    }

    int width, height, maxVal;
    file >> width >> height >> maxVal;
    file.ignore();  // Consume the newline character

    PGMImage img = {width, height, maxVal, vector<vector<int>>(height, vector<int>(width))};

    if (magic == "P2") {  // ASCII PGM
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                file >> img.pixels[i][j];
    } else {  // Binary PGM (P5)
        for (int i = 0; i < height; ++i)
            file.read(reinterpret_cast<char*>(img.pixels[i].data()), width);
    }

    file.close();
    return img;
}

// Function to calculate the optimal layout (rows × cols)
pair<int, int> getOptimalGrid(int N) {
    int rows = floor(sqrt(N));
    int cols = ceil((float)N / rows);
    return {rows, cols};
}

// Function to create the summary PGM image
void createSummaryImage(const vector<PGMImage>& images, const string &outputFile, int spacing) {
    if (images.empty()) {
        cerr << "No images provided!" << endl;
        return;
    }

    int N = images.size();
    pair<int, int> grid = getOptimalGrid(N);
    int rows = grid.first, cols = grid.second;

    int imgWidth = images[0].width;
    int imgHeight = images[0].height;

    int summaryWidth = cols * imgWidth + (cols + 1) * spacing;
    int summaryHeight = rows * imgHeight + (rows + 1) * spacing;

    // Create white background (maxVal for white)
    vector<vector<int>> summary(summaryHeight, vector<int>(summaryWidth, images[0].maxVal));

    int index = 0;
    for (int r = 0; r < rows && index < N; r++) {
        for (int c = 0; c < cols && index < N; c++) {
            int x = spacing + c * (imgWidth + spacing);
            int y = spacing + r * (imgHeight + spacing);

            for (int i = 0; i < imgHeight; i++)
                for (int j = 0; j < imgWidth; j++)
                    summary[y + i][x + j] = images[index].pixels[i][j];

            index++;
        }
    }

    // Write output PGM file
    ofstream outFile(outputFile, ios::binary);
    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    outFile << "P2\n" << summaryWidth << " " << summaryHeight << "\n" << images[0].maxVal << "\n";
    for (const auto &row : summary) {
        for (int pixel : row)
            outFile << pixel << " ";
        outFile << "\n";
    }

    outFile.close();
    cout << "Summary image saved as " << outputFile << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " -x <output.pgm> <image1.pgm> <image2.pgm> ..." << endl;
        return -1;
    }

    string outputFile;
    vector<PGMImage> images;
    int spacing = 10;  // Default spacing

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-x" && i + 1 < argc) {
            outputFile = argv[++i];
        } else {
            images.push_back(readPGM(argv[i]));
        }
    }

    createSummaryImage(images, outputFile, spacing);
    return 0;
}
