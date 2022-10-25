CXX = g++
CXXFLAGS = -Wall -std=c++11 

OBJECTS = board.o nqueens.o

nqueens: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o nqueens board.o nqueens.o

board.o: board.cpp board.h
	$(CXX) -g $(CXXFLAGS) -c board.cpp

nqueens.o: board.cpp board.h nqueens.cpp
	$(CXX) -g $(CXXFLAGS) -c nqueens.cpp

clean: 
	rm -f *.o
	rm nqueens