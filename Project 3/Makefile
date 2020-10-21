all: qtdriver

qtdriver: qttest.cpp quadtree.h quadtree.cpp
	g++ -std=c++11 -o qtdriver qttest.cpp quadtree.cpp

run:
	./qtdriver < test.in > mytest.out

clean:
	rm qtdriver