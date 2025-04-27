# Image-based Slide Puzzle Program

## Overview
This program takes a PGM image as input, divides it into tiles to create a tile puzzle. The program saves the intermediate steps as separate images and optionally generates a summary image showing all steps. The program is executed via the command line with specified arguments.

## File Descriptions

### **1. `main.cpp`**
- This is the entry point of the program.
- It parses command-line arguments and ensures valid input parameters.
- It initializes a `TileManager` instance to handle tile operations.

### **2. `TileManager.h`**
- Header file for `TileManager` and `Tile` classes.
- Defines functions for tile manipulation, random moves, and saving images.

### **3. `TileManager.cpp`**
- Implements the `TileManager` class.
- Reads the input image and divides it into a grid of tiles.
- Shuffles the tiles by making random moves while keeping one empty tile.
- Saves the puzzle images at each step.

### **4. `PGMimage.h`**
- Header file for the `PGMimage` class.
- Defines functions for reading and writing PGM images.

### **5. `PGMimage.cpp`**
- Implements the `PGMimage` class.
- Provides functionality to read a PGM image file and store pixel data.
- Writes a PGM image to an output file.

### **6. `Makefile`**
- Defines the build process for compiling the program.
- Ensures all source files are compiled correctly.

### **7. `README.md`**
- Provides an overview of the program.
- Explains the purpose of each file.
- Guides users on running the program.

## Usage Instructions
### **Compilation**
If using a `Makefile`, compile the program with:
```bash
make
```
and preset `run` function, by writing:
```bash
make run
```
Use `clean` to delete files produced by the `run` function above:
```bash
make clean
```
Otherwise, manually compile using:
```bash
g++ -o game main.cpp TileManager.cpp PGMimage.cpp
```

### **Running the Program**
Execute the program with the required arguments:
```bash
./game <gridSize> <output_baseName> <moves> <input_file>
```

#### **Arguments:**
- `<gridSize>` : Grid size (e.g., `3` for a `3x3` puzzle).
- `<output_base>` : Base name for output files without pgm extension.
- `<input_file>` : Path to the input PGM image.
- `<moves>` : Number of random moves to shuffle the puzzle.

#### **Example:**
```bash
./game 3 output 5 mona512.pgm
```
This will:
1. Read `mona512.pgm`.
2. Create a `3x3` tile puzzle.
3. Make `5` random moves.
4. Save shuffled images as `output-0.pgm`, `output-1.pgm`, ... , `output-5.pgm`.

## Troubleshooting
- Ensure the input file exists and is in **PGM (P5) format**.
- The grid size must be a positive integer greater than `1`.
- The number of moves should be a non-negative integer.
- Ensure the output directory has write permissions.

## Notes
- The empty tile is always in the bottom-right corner at the start.
- The program prevents invalid tile swaps to maintain solvability.

---
**Author:** Chiko Kasongo  
**Date:** 18/03/2025

