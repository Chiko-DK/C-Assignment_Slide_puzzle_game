game: main.cpp TileManager.cpp PGMimage.cpp
	g++ main.cpp TileManager.cpp PGMimage.cpp -o game

run:
	./game 3 output 5 mona512.pgm
	
clean:
	rm game output*
