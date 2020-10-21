all: dequedriver

dequedriver: dequedriver.cpp deque.h deque.cpp
	g++ -std=c++11 -o dequedriver dequedriver.cpp deque.cpp

run: dequedriver
	./dequedriver<test.in>test.out

clean:
	rm dequedriver