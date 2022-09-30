CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = string_LL.o testwrapper.o

string_LL: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o testwrapper string_LL.o testwrapper.o

string_LL.o: string_LL.cpp string_LL.h
	$(CXX) -g $(CXXFLAGS) -c string_LL.cpp
	
testwrapper.o: string_LL.cpp string_LL.h testwrapper.cpp
	$(CXX) -g $(CXXFLAGS) -c testwrapper.cpp

clean: 
	rm -f *.o
	rm testwrapper
