all: openhtdriver orderedhtdriver
 
openhtdriver: openhttest.cpp openht.h openht.cpp 
	g++ -std=c++11 -o  openhtdriver openhttest.cpp openht.cpp

orderedhtdriver: orderedhttest.cpp orderedht.h orderedht.cpp
	g++ -std=c++11 -o  orderedhtdriver orderedhttest.cpp orderedht.cpp

clean:
	rm openhtdriver 
	rm orderedhtdriver